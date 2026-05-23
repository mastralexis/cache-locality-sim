#include "particle_soa.h"
#include "common.h"
#include <raylib.h>
#include <math.h>

#define ALIGN64(size) (((size) + 63) & ~63)

void InitParticlesSoA(ParticleSystemSoA* soa, uint32_t count)
{
    char* currentPtr = (char*)soa->memoryBlock;

    soa->pos = (Vector2*)currentPtr;
    currentPtr += ALIGN64(count * sizeof(Vector2));

    soa->vel = (Vector2*)currentPtr;
    currentPtr += ALIGN64(count * sizeof(Vector2));

    soa->color = (Color*)currentPtr;
    currentPtr += ALIGN64(count * sizeof(Color));

    soa->mass = (float*)currentPtr;

    for (uint32_t i = 0; i < count; i++)
    {
        soa->pos[i].x = (float)GetRandomValue(0, SCREEN_WIDTH);
        soa->pos[i].y = (float)GetRandomValue(0, SCREEN_HEIGHT);
        
        soa->vel[i].x = (float)GetRandomValue(-200, 200);
        soa->vel[i].y = (float)GetRandomValue(-200, 200);
        
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
    Vector2* restrict pos = soa->pos;
    Vector2* restrict vel = soa->vel;
    for (uint32_t i = 0; i < count; i++)
    {
        pos[i].x += vel[i].x * delta;
        pos[i].y += vel[i].y * delta;
    }
}

void UpdateParticlesSoA_Physics(ParticleSystemSoA* soa, uint32_t count, float delta)
{
    Vector2* restrict pos = soa->pos;
    Vector2* restrict vel = soa->vel;

    for (uint32_t i = 0; i < count; i++)
    {
        for (uint32_t j = i + 1; j < count; j++)
        {
            float dx = pos[j].x - pos[i].x;
            float dy = pos[j].y - pos[i].y;
            float distSq = (dx * dx) + (dy * dy);
            
            if (distSq < 16.0f && distSq > 0.0001f)
            {
                float dist = sqrtf(distSq);
                float overlap = 4.0f - dist;
                float nx = dx / dist;
                float ny = dy / dist;
                
                pos[i].x -= nx * overlap * 0.5f;
                pos[i].y -= ny * overlap * 0.5f;
                pos[j].x += nx * overlap * 0.5f;
                pos[j].y += ny * overlap * 0.5f;
            }
        }
    }

    for (uint32_t i = 0; i < count; i++)
    {
        pos[i].x += vel[i].x * delta;
        pos[i].y += vel[i].y * delta;

        pos[i].x = fmaxf(0.0f, fminf(SCREEN_WIDTH, pos[i].x));
        pos[i].y = fmaxf(0.0f, fminf(SCREEN_HEIGHT, pos[i].y));

        vel[i].x = (pos[i].x <= 0.0f || pos[i].x >= SCREEN_WIDTH) ? -vel[i].x : vel[i].x;
        vel[i].y = (pos[i].y <= 0.0f || pos[i].y >= SCREEN_HEIGHT) ? -vel[i].y : vel[i].y;
    }
}

void DrawParticlesSoA(const ParticleSystemSoA* soa, uint32_t count)
{
    for (uint32_t i = 0; i < count; i++)
        DrawPixelV(soa->pos[i], soa->color[i]);
}

