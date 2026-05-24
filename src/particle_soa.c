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
        // apply gravity and drag
        vel[i].y += GRAVITY_Y * delta;
        vel[i].x *= DRAG;
        vel[i].y *= DRAG;

        // integrate position
        pos[i].x += vel[i].x * delta;
        pos[i].y += vel[i].y * delta;

        // bounce off walls
        if (pos[i].x <= 0.0f)
        {
            pos[i].x = 0.0f;
            vel[i].x = -vel[i].x * 0.8f; 
        }
        else if (pos[i].x >= SCREEN_WIDTH) 
        {
            pos[i].x = SCREEN_WIDTH;
            vel[i].x = -vel[i].x * 0.8f;
        }

        if (pos[i].y <= 0.0f)
        {
            pos[i].y = 0.0f;
            vel[i].y = -vel[i].y * 0.8f;
        }
        else if (pos[i].y >= SCREEN_HEIGHT)
        {
            pos[i].y = SCREEN_HEIGHT;
            vel[i].y = -vel[i].y * 0.8f;
        }
    }
}

void DrawParticlesSoA(const ParticleSystemSoA* soa, uint32_t count)
{
    for (uint32_t i = 0; i < count; i++)
        DrawPixelV(soa->pos[i], soa->color[i]);
}

