#ifndef SIMULATION_H
#define SIMULATION_H

#include "common.h"
#include "particle_aos.h"
#include "particle_soa.h"
#include <stdbool.h>

typedef struct SimulationState SimulationState;
typedef void (*PhysicsUpdateFn)(SimulationState* state, float deltaTime);
typedef void (*PhysicsDrawFn)(const SimulationState* state);
typedef void (*PhysicsCleanFn)(SimulationState* state);

struct SimulationState 
{
    SimulationMode mode;
    uint32_t particleCount;
    // to allocate one paradim at a time
    union {
        ParticleAoS* aos;
        ParticleSystemSoA soa;
    } data;

    PhysicsUpdateFn update;
    PhysicsDrawFn render;
    PhysicsCleanFn cleanup;

    // For the results screen
    double lastPhysicsLoopUpdate; // time for the current frame
    double accumulatedPhysicsTime;// sum of all frame times
    double totalElapsedTime;        // time since simulation started
    uint32_t totalFrames;           // how many frames have passed
    double finalAverageTimeMs;      // the final metric
    double timeAccumulator;
    bool simdEnabled;
    bool physicsEnabled;
};

/**
 * @brief Initializes the simulation for a SPECIFIC mode
 * @param state Pointer to the global simulation state
 * @param targetMode The mode chosen
 * @param initialCount The starting number of particles
 */
void InitSimulation(SimulationState* state, SimulationMode targetMode, uint32_t initialCount, bool physicsEnabled, bool simdEnabled);

/**
 * @brief Triggers the physics update for the active paradigm
 * @param state Pointer to the global simulation state
 * @param deltaTime The time passed since the last frame
 */
void UpdateSimulation(SimulationState* state, float deltaTime);

/**
 * @brief Delegates rendering to the active paradigm's draw function
 * @param state Pointer to the global simulation state
 */
void DrawSimulation(const SimulationState* state);

/**
 * @brief Safely frees the memory allocated for the active simulation
 * @param state Pointer to the global simulation state to clean up
 */
void CleanSimulation(SimulationState* state);

/**
 * @brief Checks if the CPU and compiler support AVX instructions
 * @return true if SIMD is supported, false otherwise
 */
bool IsSimdSupported(void);

#endif
