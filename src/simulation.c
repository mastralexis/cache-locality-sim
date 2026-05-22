#include "simulation.h"
#include "particle_aos.h"
#include "particle_soa.h"
#include "raylib.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Wrappers to pass the correct data structure to the functions
// ------------------------------------------------------------
static void aos_update(SimulationState* state, float delta) 
{
    UpdateParticlesAoS(state->data.aos, state->particleCount, delta);
}

static void aos_render(const SimulationState* state) 
{
    uint32_t drawCount = (state->particleCount > 100000) ? 100000 : state->particleCount;
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

static void soa_update(SimulationState* state, float delta)
{
    UpdateParticlesSoA(&state->data.soa, state->particleCount, delta);
}

static void soa_render(const SimulationState* state)
{
    uint32_t drawCount = (state->particleCount > 100000) ? 100000 : state->particleCount;
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

void InitSimulation(SimulationState* simState, SimulationMode selectedMode, uint32_t particleCount)
{
    simState->mode = selectedMode;
    simState->particleCount = particleCount;
    simState->lastPhysicsLoopUpdate = 0.0;
    simState->accumulatedPhusicsTime = 0.0;
    simState->totalElapsedTime = 0.0;
    simState->totalFrames = 0.0;

    switch (selectedMode) 
    {
        case MODE_AOS:
            simState->data.aos = (ParticleAoS*) malloc(particleCount * sizeof(ParticleAoS));
            InitParticlesAoS(simState->data.aos, particleCount);
            simState->update   = aos_update;
            simState->render   = aos_render;
            simState->cleanup  = aos_cleanup;
            break;
        case MODE_SOA:
            // mass allocation
            size_t totalBytes = (particleCount * sizeof(Vector2)) + // pos
                                (particleCount * sizeof(Vector2)) + // vel
                                (particleCount * sizeof(Color)) +   // color
                                (particleCount * sizeof(float));    // mass
            simState->data.soa.memoryBlock = malloc(totalBytes);
            InitParticlesSoA(&simState->data.soa, particleCount);
            simState->update   = soa_update;
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
