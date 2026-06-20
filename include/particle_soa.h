#ifndef PARTICLE_SOA_H
#define PARTICLE_SOA_H

#include "common.h"
#include "raylib.h"

// Data Oriented Approach
typedef struct {
    // Data used in the update loop
    float* posX;
    float* posY;
    float* velX;
    float* velY;

    // Data not used in the update loop
    float* accX;
    float* accY;
    Color* startColor;
    Color* endColor;
    float* startSize;
    float* endSize;
    float* rotation;
    float* angularVelocity;
    float* lifeTime;
    float* age;
    float* mass;
    float* drag;

    void*  memoryBlock;
} ParticleSystemSoA;


/**
 * @brief Allocates aligned memory for SoA components and initializes them
 * @param system Pointer to the SoA system structure
 * @param count Number of particles
 * @return true if successful, false if out of memory
 */
bool CreateParticlesSoA(ParticleSystemSoA* system, uint32_t count);

/**
 * @brief Allocates memory for all component arrays and initializes them
 * @param system Pointer to the SoA struct
 * @param count The total number of particles to allocate and initialize
 */
void InitParticlesSoA(ParticleSystemSoA* system, uint32_t count);

/**
 * @brief Linearly updates positions using standard scalar operations
 * @param system Pointer to the SoA struct
 * @param count The total number of particles to update
 * @param deltaTime The time passed since the last frame
 */
void UpdateParticlesSoA_Simple(ParticleSystemSoA* system, uint32_t count, float deltaTime);

/**
 * @brief Applies physics, gravity, and bounds-checking using standard scalar operations
 * @param system Pointer to the SoA struct
 * @param count The total number of particles to update
 * @param deltaTime The time passed since the last frame
 */
void UpdateParticlesSoA_Physics(ParticleSystemSoA* system, uint32_t count, float deltaTime);

/**
 * @brief Linearly updates positions utilizing AVX SIMD instructions (processing 8 at a time)
 * @param system Pointer to the SoA struct
 * @param count The total number of particles to update
 * @param delta The time passed since the last frame
 */
void UpdateParticlesSoA_Simple_SIMD(ParticleSystemSoA* system, uint32_t count, float delta);

/**
 * @brief Applies physics and bounds-checking utilizing branchless AVX SIMD instructions
 * @param system Pointer to the SoA struct
 * @param count The total number of particles to update
 * @param delta The time passed since the last frame
 */
void UpdateParticlesSoA_Physics_SIMD(ParticleSystemSoA* system, uint32_t count, float delta);

/**
 * @brief Renders all particles to the screen by reading from the necessary component arrays
 * @param system Pointer to the SoA struct
 * @param count The total number of particles to draw
 */
void DrawParticlesSoA(const ParticleSystemSoA* system, uint32_t count);

/**
 * @brief Safely frees the aligned memory block in the SoA system.
 */
void DestroyParticlesSoA(ParticleSystemSoA* system);

#endif
