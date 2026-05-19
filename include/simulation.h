#ifndef SIMULATION_H
#define SIMULATION_H

#include "common.h"
#include "particle_aos.h"
#include "particle_soa.h"

typedef struct {
    SimulationMode mode;
    uint32_t particleCount;
    // to allocate one paradim at a time
    union {
        ParticleAoS* aos;
        ParticleSystemSoA soa;
    } data;

    double lastPhysicsLoopUpdate; // to compare AoS and SoA
} SimulationState;

/**
 * @brief Initializes the simulation for a SPECIFIC mode
 * @param state Pointer to the global simulation state
 * @param targetMode The mode chosen
 * @param initialCount The starting number of particles
 */
void InitSimulation(SimulationState* state, SimulationMode targetMode, uint32_t initialCount);

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

#endif
