#ifndef PARTICLE_SOA_H
#define PARTICLE_SOA_H

#include "common.h"

// Data Oriented Approach
typedef struct {
    float* posX;
    float* posY;
    float* velX;
    float* velY;
    float* mass;
    float* radius;
    Color* color;
} ParticleSystemSoA;

/**
 * @brief Allocates memory for all component arrays and initializes them
 * @param system Pointer to the SoA struct
 * @param count The total number of particles to allocate and initialize.
 */
void InitParticlesSoA(ParticleSystemSoA* system, uint32_t count);

/**
 * @brief Updates the physics by iterating through each array
 * @param system Pointer to the SoA struct
 * @param count The total number of particles to update
 * @param delta The time passed since the last frame
 */
void UpdateParticlesSoA(ParticleSystemSoA* system, uint32_t count, float deltaTime);

/**
 * @brief Renders all particles to the screen by reading from the necessary component arrays
 * @param system Pointer to the SoA struct
 * @param count The total number of particles to draw
 */
void DrawParticlesSoA(const ParticleSystemSoA* system, uint32_t count);

/**
 * @brief Frees the dynamically allocated memory for all internal component arrays
 * @param system Pointer to the SoA struct to clean up
 */
void FreeParticlesSoA(ParticleSystemSoA* system);

#endif
