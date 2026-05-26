#include "particle_soa.h"
#include "common.h"
#include <raylib.h>
#include <math.h>
#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)
    #include <immintrin.h>
    #define AVX_SUPPORTED 1
#else
    #define AVX_SUPPORTED 0
#endif

#define ALIGN64(size) (((size) + 63) & ~63)

void InitParticlesSoA(ParticleSystemSoA* soa, uint32_t count)
{
    char* currentPtr = (char*)soa->memoryBlock;

    soa->posX = (float*)currentPtr;
    currentPtr += ALIGN64(count * sizeof(float));

    soa->posY = (float*)currentPtr;
    currentPtr += ALIGN64(count * sizeof(float));

    soa->velX = (float*)currentPtr;
    currentPtr += ALIGN64(count * sizeof(float));

    soa->velY = (float*)currentPtr;
    currentPtr += ALIGN64(count * sizeof(float));

    soa->color = (Color*)currentPtr;
    currentPtr += ALIGN64(count * sizeof(Color));

    soa->mass = (float*)currentPtr;

    for (uint32_t i = 0; i < count; i++)
    {
        soa->posX[i] = (float)GetRandomValue(0, SCREEN_WIDTH);
        soa->posY[i] = (float)GetRandomValue(0, SCREEN_HEIGHT);
        
        soa->velX[i] = (float)GetRandomValue(-200, 200);
        soa->velY[i] = (float)GetRandomValue(-200, 200);
        
        soa->color[i] = (Color){ 
            (unsigned char)GetRandomValue(50, 100),  
            (unsigned char)GetRandomValue(150, 255), 
            (unsigned char)GetRandomValue(50, 100),  
            255                                      
        };
        
        soa->mass[i] = (float)GetRandomValue(1, 10);
    }
}
void UpdateParticlesSoA_Simple(ParticleSystemSoA* soa, uint32_t count, float delta)
{
    float* restrict posX = soa->posX;
    float* restrict posY = soa->posY;
    float* restrict velX = soa->velX;
    float* restrict velY = soa->velY;

    for (uint32_t i = 0; i < count; i++)
    {
        posX[i] += velX[i] * delta;
        posY[i] += velY[i] * delta;
    }
}

void UpdateParticlesSoA_Physics(ParticleSystemSoA* soa, uint32_t count, float delta)
{
    float* restrict posX = soa->posX;
    float* restrict posY = soa->posY;
    float* restrict velX = soa->velX;
    float* restrict velY = soa->velY;

    for (uint32_t i = 0; i < count; i++)
    {
        // apply gravity and drag
        velY[i] += GRAVITY_Y * delta;
        velX[i] *= DRAG;
        velY[i] *= DRAG;

        // integrate position
        posX[i] += velX[i] * delta;
        posY[i] += velY[i] * delta;

        // bounce off walls
        if (posX[i] <= 0.0f)
        {
            posX[i] = 0.0f;
            velX[i] = -velX[i] * 0.8f; 
        }
        else if (posX[i] >= SCREEN_WIDTH) 
        {
            posX[i] = SCREEN_WIDTH;
            velX[i] = -velX[i] * 0.8f;
        }

        if (posY[i] <= 0.0f)
        {
            posY[i] = 0.0f;
            velY[i] = -velY[i] * 0.8f;
        }
        else if (posY[i] >= SCREEN_HEIGHT)
        {
            posY[i] = SCREEN_HEIGHT;
            velY[i] = -velY[i] * 0.8f;
        }
    }
}

void UpdateParticlesSoA_Physics_SIMD(ParticleSystemSoA* soa, uint32_t count, float delta)
{
#if AVX_SUPPORTED
    // calculate the safe boundary for 8-lane SIMD
    uint32_t simdCount = count - (count % 8);
    // broadcast scalar values into 8-lane SIMD registers
    __m256 dt          = _mm256_set1_ps(delta);
    __m256 gravity     = _mm256_set1_ps(GRAVITY_Y * delta);
    __m256 drag        = _mm256_set1_ps(DRAG);
    __m256 zero        = _mm256_setzero_ps();
    __m256 screenW     = _mm256_set1_ps((float)SCREEN_WIDTH);
    __m256 screenH     = _mm256_set1_ps((float)SCREEN_HEIGHT);
    __m256 bounce      = _mm256_set1_ps(-0.8f);

    // process 8 particles at a time
    for (uint32_t i = 0; i < simdCount; i += 8) 
    {
        // load 8 X's and 8 Y's into registers (Requires 32-byte memory alignment)
        __m256 px = _mm256_load_ps(&soa->posX[i]);
        __m256 py = _mm256_load_ps(&soa->posY[i]);
        __m256 vx = _mm256_load_ps(&soa->velX[i]);
        __m256 vy = _mm256_load_ps(&soa->velY[i]);

        // apply Physics (Gravity and Drag)
        vy = _mm256_add_ps(vy, gravity);     // vy += gravity
        vx = _mm256_mul_ps(vx, drag);        // vx *= drag
        vy = _mm256_mul_ps(vy, drag);        // vy *= drag

        // integrate Position
        px = _mm256_add_ps(px, _mm256_mul_ps(vx, dt)); // px += vx * dt
        py = _mm256_add_ps(py, _mm256_mul_ps(vy, dt)); // py += vy * dt

        // handle X Collisions (Branchless)
        __m256 maskLeftX = _mm256_cmp_ps(px, zero, _CMP_LE_OQ);
        __m256 maskRightX = _mm256_cmp_ps(px, screenW, _CMP_GE_OQ);
        __m256 maskOutOfBoundsX = _mm256_or_ps(maskLeftX, maskRightX);

        // calculate bounce velocity
        __m256 bouncedVx = _mm256_mul_ps(vx, bounce);
        
        // blend: If mask is true, take bouncedVx. If false, keep original vx.
        vx = _mm256_blendv_ps(vx, bouncedVx, maskOutOfBoundsX);

        // clamp position to screen bounds
        px = _mm256_max_ps(px, zero); 
        px = _mm256_min_ps(px, screenW);

        // handle Y Collisions (Branchless)
        __m256 maskTopY = _mm256_cmp_ps(py, zero, _CMP_LE_OQ);
        __m256 maskBottomY = _mm256_cmp_ps(py, screenH, _CMP_GE_OQ);
        __m256 maskOutOfBoundsY = _mm256_or_ps(maskTopY, maskBottomY);

        __m256 bouncedVy = _mm256_mul_ps(vy, bounce);
        vy = _mm256_blendv_ps(vy, bouncedVy, maskOutOfBoundsY);

        py = _mm256_max_ps(py, zero);
        py = _mm256_min_ps(py, screenH);

        // store the updated data back into memory
        _mm256_store_ps(&soa->posX[i], px);
        _mm256_store_ps(&soa->posY[i], py);
        _mm256_store_ps(&soa->velX[i], vx);
        _mm256_store_ps(&soa->velY[i], vy);
    }

    // Tail Loop: Handle any leftover particles (will run 0 to 7 times)
    for (uint32_t i = simdCount; i < count; i++)
    {
        // apply gravity and drag
        soa->velY[i] += GRAVITY_Y * delta;
        soa->velX[i] *= DRAG;
        soa->velY[i] *= DRAG;

        // integrate position
        soa->posX[i] += soa->velX[i] * delta;
        soa->posY[i] += soa->velY[i] * delta;

        // bounce off walls
        if (soa->posX[i] <= 0.0f)
        {
            soa->posX[i] = 0.0f;
            soa->velX[i] = -soa->velX[i] * 0.8f; 
        }
        else if (soa->posX[i] >= SCREEN_WIDTH) 
        {
            soa->posX[i] = SCREEN_WIDTH;
            soa->velX[i] = -soa->velX[i] * 0.8f;
        }

        if (soa->posY[i] <= 0.0f)
        {
            soa->posY[i] = 0.0f;
            soa->velY[i] = -soa->velY[i] * 0.8f;
        }
        else if (soa->posY[i] >= SCREEN_HEIGHT)
        {
            soa->posY[i] = SCREEN_HEIGHT;
            soa->velY[i] = -soa->velY[i] * 0.8f;
        }
    }
#else
    // if ARM cpu is used
    UpdateParticlesSoA_Physics(soa, count, delta);
#endif
}

void UpdateParticlesSoA_Simple_SIMD(ParticleSystemSoA* soa, uint32_t count, float delta)
{
#if AVX_SUPPORTED
    uint32_t simdCount = count - (count % 8);
    __m256 dt = _mm256_set1_ps(delta);

    // process 8 particles at a time
    for (uint32_t i = 0; i < simdCount; i += 8) 
    {
        // load positions and velocities
        __m256 px = _mm256_load_ps(&soa->posX[i]);
        __m256 py = _mm256_load_ps(&soa->posY[i]);
        __m256 vx = _mm256_load_ps(&soa->velX[i]);
        __m256 vy = _mm256_load_ps(&soa->velY[i]);

        // integrate Position: p = p + (v * dt)
        px = _mm256_add_ps(px, _mm256_mul_ps(vx, dt));
        py = _mm256_add_ps(py, _mm256_mul_ps(vy, dt));

        // store updated positions back to memory
        _mm256_store_ps(&soa->posX[i], px);
        _mm256_store_ps(&soa->posY[i], py);
    }

    // tail Loop: Handle any leftover particles (will run 0 to 7 times)
    for (uint32_t i = simdCount; i < count; i++)
    {
        soa->posX[i] += soa->velX[i] * delta;
        soa->posY[i] += soa->velY[i] * delta;
    }
#else
    UpdateParticlesSoA_Simple(soa, count, delta);
#endif
}

void DrawParticlesSoA(const ParticleSystemSoA* soa, uint32_t count)
{
    for (uint32_t i = 0; i < count; i++)
        DrawPixel((int)soa->posX[i], (int)soa->posY[i], soa->color[i]);
}

