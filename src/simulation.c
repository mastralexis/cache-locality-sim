#include "simulation.h"
#include "particle_aos.h"
#include "particle_soa.h"
#include "raylib.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Wrappers to pass the correct data structure to the functions
// ------------------------------------------------------------
static void aos_update(SimulationState* state, float delta) 
{
    // UpdateParticlesAoS(state->data.aos, state->particleCount, delta);
}

static void aos_render(const SimulationState* state) 
{
    // DrawParticlesAoS(state->data.aos, state->particleCount);
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
    // UpdateParticlesSoA(&state->data.soa, state->particleCount, delta);
}

static void soa_render(const SimulationState* state)
{
    // DrawParticlesSoA(&state->data.soa, state->particleCount);
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

    switch (selectedMode) 
    {
        case MODE_AOS:
            // InitParticlesAoS(simState->data.aos, particleCount);
            simState->update   = aos_update;
            simState->render   = aos_render;
            simState->cleanup  = aos_cleanup;
            break;
        case MODE_SOA:
            // InitParticlesSoA($simState->data.soa, particleCount);
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
}

void DrawSimulation(const SimulationState* simState)
{
    simState->render(simState);
}

void CleanSimulation(SimulationState* simState)
{
    simState->cleanup(simState);
    simState->mode = MODE_MENU;
    simState->particleCount = 0;
}
