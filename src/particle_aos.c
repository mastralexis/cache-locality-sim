#include "particle_aos.h"
#include "common.h"
#include <raylib.h>
#include <stdlib.h>
#include <math.h>

void InitParticlesAoS(ParticleAoS *particles, uint32_t count)
{
    for (uint32_t i = 0; i < count; i++)
    {
        // initialize random values
        particles[i].pos.x = (float) GetRandomValue(0, SCREEN_WIDTH);
        particles[i].pos.y = (float) GetRandomValue(0, SCREEN_HEIGHT);
        particles[i].vel.x = (float) GetRandomValue(-200, 200);
        particles[i].vel.y = (float) GetRandomValue(-200, 200);
        particles[i].mass  = (float) GetRandomValue(1, 10);
        particles[i].color = (Color) {
            (unsigned char)GetRandomValue(150, 255),
            (unsigned char)GetRandomValue(50, 100),
            (unsigned char)GetRandomValue(50, 100),
            255
        };
    }
}

void UpdateParticlesAoS_Simple(ParticleAoS* particles, uint32_t count, float delta)
{
    for (uint32_t i = 0; i < count; i++)
    {
        particles[i].pos.x += particles[i].vel.x * delta;
        particles[i].pos.y += particles[i].vel.y * delta;
    }
}

void UpdateParticlesAoS_Physics(ParticleAoS* particles, uint32_t count, float delta)
{
    for (uint32_t i = 0; i < count; i++)
    {
        particles[i].vel.y += GRAVITY_Y * delta;
        particles[i].vel.x *= DRAG;
        particles[i].vel.y *= DRAG;

        particles[i].pos.x += particles[i].vel.x * delta;
        particles[i].pos.y += particles[i].vel.y * delta;

        if (particles[i].pos.x <= 0.0f)
        {
            particles[i].pos.x = 0.0f;
            particles[i].vel.x = -particles[i].vel.x * 0.8f;
        }
        else if (particles[i].pos.x >= SCREEN_WIDTH)
        {
            particles[i].pos.x = SCREEN_WIDTH;
            particles[i].vel.x = -particles[i].vel.x * 0.8f;
        }

        if (particles[i].pos.y <= 0.0f) 
        {
            particles[i].pos.y = 0.0f;
            particles[i].vel.y = -particles[i].vel.y * 0.8f;
        }
        else if (particles[i].pos.y >= SCREEN_HEIGHT)
        {
            particles[i].pos.y = SCREEN_HEIGHT;
            particles[i].vel.y = -particles[i].vel.y * 0.8f;
        }
    }
}

void DrawParticlesAoS(const ParticleAoS* particles, uint32_t count)
{
    for (uint32_t i = 0; i < count; i++)
    {
        DrawPixelV(particles[i].pos, particles[i].color);
    }
}
