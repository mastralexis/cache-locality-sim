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
 * @brief Initializes an array of particles with random positions, velocities and colors
 * @param particles Pointer to the first element of the AoS array
 * @param count The total number of particle objects to Initialize
 */
void InitParticlesAoS(ParticleAoS* particles, uint32_t const);

/**
 * @brief Updates the physics of all particles
 * @param particles Pointer to the first element of the AoS array
 * @param count The total number of particles to update
 * @param delta The time passed since the last frame
 */
void UpdateParticlesAoS_Simple(ParticleAoS* particles, uint32_t count, float delta);
void UpdateParticlesAoS_Physics(ParticleAoS* particles, uint32_t count, float delta);

/**
 * @brief Renders all particles to the screen
 * @param particles Pointer to the first element of the AoS array
 * @param count The total number of particles to draw
 */
void DrawParticlesAoS(const ParticleAoS* particles, uint32_t count);

#endif
