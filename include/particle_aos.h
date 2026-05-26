#ifndef PARTICLE_AOS_H
#define PARTICLE_AOS_H

#include "common.h"
#include <raylib.h>

// Represents a single particle "object"
typedef struct {
    Vector2 pos;
    Vector2 vel;
    float mass; // useless data
    Color color;
} ParticleAoS;

/**
 * @brief Allocates and initializes an AoS array
 * @param particlesOut Pointer to the AoS array pointer
 * @param count Number of particles
 * @return true if successful, false if out of memory
 */
bool CreateParticlesAoS(ParticleAoS** particlesOut, uint32_t count);

/**
 * @brief Initializes an array of particles with random positions, velocities and colors
 * @param particles Pointer to the first element of the AoS array
 * @param count The total number of particle objects to Initialize
 */
void InitParticlesAoS(ParticleAoS* particles, uint32_t const);

/**
 * @brief Updates particle positions linearly without physics or collisions
 * @param particles Pointer to the first element of the AoS array
 * @param count The total number of particles to update
 * @param delta The time passed since the last frame
 */
void UpdateParticlesAoS_Simple(ParticleAoS* particles, uint32_t count, float delta);

/**
 * @brief Updates particle positions while applying gravity, drag, and screen-boundary collisions
 * @param particles Pointer to the first element of the AoS array
 * @param count The total number of particles to update
 * @param delta The time passed since the last frame
 */
void UpdateParticlesAoS_Physics(ParticleAoS* particles, uint32_t count, float delta);

/**
 * @brief Renders all particles to the screen
 * @param particles Pointer to the first element of the AoS array
 * @param count The total number of particles to draw
 */
void DrawParticlesAoS(const ParticleAoS* particles, uint32_t count);

/**
 * @brief Safely frees an AoS array and sets the pointer to NULL.
 */
void DestroyParticlesAoS(ParticleAoS** particles);

#endif
