#ifndef PARTICLE_AOS_H
#define PARTICLE_AOS_H

#include <raylib.h>
#include "common.h"

// Represents a single particle "object"
typedef struct {
    // Data used in the update loops
    Vector2 pos;            // 8 bytes
    Vector2 vel;            // 8 bytes

    // Other data not used in the update loop
    Vector2 acceleration;   // 8 bytes
    Color startColor;       // 4 bytes
    Color endColor;         // 4 bytes
    float startSize;        // 4 bytes
    float endSize;          // 4 bytes
    float rotation;         // 4 bytes
    float angularVelocity;  // 4 bytes
    float lifeTime;         // 4 bytes
    float age;              // 4 bytes
    float mass;             // 4 bytes
    float drag;             // 4 bytes
} ParticleAoS;              // Total of 64 bytes

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
void InitParticlesAoS(ParticleAoS* particles, uint32_t count);

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
