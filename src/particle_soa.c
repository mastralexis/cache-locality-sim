#include "particle_soa.h"
#include "common.h"
#include <raylib.h>

void InitParticlesSoA(ParticleSystemSoA* soa, uint32_t count)
{
    char* currentPtr = (char*)soa->memoryBlock;

    soa->pos = (Vector2*)currentPtr;
    currentPtr += count * sizeof(Vector2);

    soa->vel = (Vector2*)currentPtr;
    currentPtr += count * sizeof(Vector2);

    soa->color = (Color*)currentPtr;
    currentPtr += count * sizeof(Color);

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

void UpdateParticlesSoA(ParticleSystemSoA* soa, uint32_t count, float delta)
{
    for (uint32_t i = 0; i < count; i++)
    {
        soa->pos[i].x += soa->vel[i].x * delta;
        soa->pos[i].y += soa->vel[i].y * delta;

        // if (soa->pos[i].x <= 0) 
        // {
        //     soa->pos[i].x = 0; 
        //     soa->vel[i].x *= -1.0f;
        // }
        // else if (soa->pos[i].x >= SCREEN_WIDTH) 
        // {
        //     soa->pos[i].x = SCREEN_WIDTH;
        //     soa->vel[i].x *= -1.0f;
        // }
        //
        // if (soa->pos[i].y <= 0) 
        // {
        //     soa->pos[i].y = 0;
        //     soa->vel[i].y *= -1.0f;
        // }
        // else if (soa->pos[i].y >= SCREEN_HEIGHT) 
        // {
        //     soa->pos[i].y = SCREEN_HEIGHT;
        //     soa->vel[i].y *= -1.0f;
        // }
    }
}

void DrawParticlesSoA(const ParticleSystemSoA* soa, uint32_t count)
{
    for (uint32_t i = 0; i < count; i++)
        DrawPixelV(soa->pos[i], soa->color[i]);
}

