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
        for (uint32_t j = i + 1; j < count; j++)
        {
            float dx = particles[j].pos.x - particles[i].pos.x;
            float dy = particles[j].pos.y - particles[i].pos.y;
            float distSq = (dx * dx) + (dy * dy);
            
            if (distSq < 16.0f && distSq > 0.0001f)
            {
                float dist = sqrtf(distSq);
                float overlap = 4.0f - dist;
                float nx = dx / dist;
                float ny = dy / dist;
                
                particles[i].pos.x -= nx * overlap * 0.5f;
                particles[i].pos.y -= ny * overlap * 0.5f;
                particles[j].pos.x += nx * overlap * 0.5f;
                particles[j].pos.y += ny * overlap * 0.5f;
            }
        }
    }

    for (uint32_t i = 0; i < count; i++)
    {
        particles[i].pos.x += particles[i].vel.x * delta;
        particles[i].pos.y += particles[i].vel.y * delta;

        particles[i].pos.x = fmaxf(0.0f, fminf(SCREEN_WIDTH, particles[i].pos.x));
        particles[i].pos.y = fmaxf(0.0f, fminf(SCREEN_HEIGHT, particles[i].pos.y));

        particles[i].vel.x = (particles[i].pos.x <= 0.0f || particles[i].pos.x >= SCREEN_WIDTH) ? -particles[i].vel.x : particles[i].vel.x;
        particles[i].vel.y = (particles[i].pos.y <= 0.0f || particles[i].pos.y >= SCREEN_HEIGHT) ? -particles[i].vel.y : particles[i].vel.y;
    }
}

void DrawParticlesAoS(const ParticleAoS* particles, uint32_t count)
{
    for (uint32_t i = 0; i < count; i++)
    {
        DrawPixelV(particles[i].pos, particles[i].color);
    }
}
