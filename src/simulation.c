#include "simulation.h"
#include "particle_aos.h"
#include "particle_soa.h"
#include "raylib.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ALIGN64(size) (((size) + 63) & ~63)

// Wrappers to pass the correct data structure to the functions
// ------------------------------------------------------------
static void aos_update_simple(SimulationState* state, float delta) 
{
    UpdateParticlesAoS_Simple(state->data.aos, state->particleCount, delta);
}

static void aos_update_physics(SimulationState* state, float delta) 
{
    UpdateParticlesAoS_Physics(state->data.aos, state->particleCount, delta);
}

static void aos_render(const SimulationState* state) 
{
    uint32_t drawCount = (state->particleCount > 50000) ? 50000 : state->particleCount;
    DrawParticlesAoS(state->data.aos, drawCount);
}

static void aos_cleanup(SimulationState* state)
{
    if (state->data.aos != NULL) 
    {
        free(state->data.aos);
        state->data.aos = NULL;
    }
}

static void soa_update_simple(SimulationState* state, float delta) 
{
    UpdateParticlesSoA_Simple(&state->data.soa, state->particleCount, delta);
}
static void soa_update_physics(SimulationState* state, float delta) 
{
    UpdateParticlesSoA_Physics(&state->data.soa, state->particleCount, delta);
}

static void soa_render(const SimulationState* state)
{
    uint32_t drawCount = (state->particleCount > 50000) ? 50000 : state->particleCount;
    DrawParticlesSoA(&state->data.soa, drawCount);
}

static void soa_cleanup(SimulationState* state)
{
    if (state->data.soa.memoryBlock != NULL) 
    {
        free(state->data.soa.memoryBlock);
        state->data.soa.memoryBlock = NULL;
    }
}

void InitSimulation(SimulationState* simState, SimulationMode selectedMode, uint32_t particleCount, bool physicsEnabled)
{
    simState->mode = selectedMode;
    simState->particleCount = particleCount;
    simState->physicsEnabled = physicsEnabled;
    simState->lastPhysicsLoopUpdate = 0.0;
    simState->accumulatedPhusicsTime = 0.0;
    simState->totalElapsedTime = 0.0;
    simState->totalFrames = 0.0;
    SetRandomSeed(42);    // so the tests can be the same every time

    switch (selectedMode) 
    {
        case MODE_AOS:
            simState->data.aos = (ParticleAoS*) malloc(particleCount * sizeof(ParticleAoS));
            InitParticlesAoS(simState->data.aos, particleCount);
            if (physicsEnabled) simState->update = aos_update_physics;
            else                simState->update = aos_update_simple;
            simState->render   = aos_render;
            simState->cleanup  = aos_cleanup;
            break;
        case MODE_SOA:
            // mass allocation with alignment
            size_t posSize = ALIGN64(particleCount * sizeof(Vector2));
            size_t velSize = ALIGN64(particleCount * sizeof(Vector2));
            size_t colSize = ALIGN64(particleCount * sizeof(Color));
            size_t masSize = ALIGN64(particleCount * sizeof(float));
            simState->data.soa.memoryBlock = malloc(posSize + velSize + colSize + masSize);
            InitParticlesSoA(&simState->data.soa, particleCount);
            if (physicsEnabled) simState->update = soa_update_physics;
            else                simState->update = soa_update_simple;
            simState->render   = soa_render;
            simState->cleanup  = soa_cleanup;
            break;
        default:
            break;
    }
}

void UpdateSimulation(SimulationState* simState, float delta)
{
    double startTime = GetTime();
        simState->update(simState, delta);
    double endTime = GetTime();
    simState->lastPhysicsLoopUpdate = endTime - startTime;
    simState->accumulatedPhusicsTime += simState->lastPhysicsLoopUpdate;
    simState->totalElapsedTime += delta;
    simState->totalFrames++;
}

void DrawSimulation(const SimulationState* simState)
{
    simState->render(simState);
}

void CleanSimulation(SimulationState* simState)
{
    simState->cleanup(simState);
}
