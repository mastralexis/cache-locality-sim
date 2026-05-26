#include "simulation.h"
#include "particle_aos.h"
#include "particle_soa.h"
#include "raylib.h"
#include <mm_malloc.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)
    #include <immintrin.h>
    #define AVX_SUPPORTED 1
#else
    #define AVX_SUPPORTED 0
#endif

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
    DestroyParticlesAoS(&state->data.aos);
}

static void soa_update_simple(SimulationState* state, float delta) 
{
    UpdateParticlesSoA_Simple(&state->data.soa, state->particleCount, delta);
}

static void soa_update_physics(SimulationState* state, float delta) 
{
    UpdateParticlesSoA_Physics(&state->data.soa, state->particleCount, delta);
}

static void soa_update_physics_simd(SimulationState* state, float delta) 
{
    UpdateParticlesSoA_Physics_SIMD(&state->data.soa, state->particleCount, delta);
}

static void soa_update_simple_simd(SimulationState* state, float delta) 
{
    UpdateParticlesSoA_Simple_SIMD(&state->data.soa, state->particleCount, delta);
}

static void soa_render(const SimulationState* state)
{
    uint32_t drawCount = (state->particleCount > 50000) ? 50000 : state->particleCount;
    DrawParticlesSoA(&state->data.soa, drawCount);
}

static void soa_cleanup(SimulationState* state)
{
    DestroyParticlesSoA(&state->data.soa);
}

void InitSimulation(SimulationState* simState, SimulationMode selectedMode, uint32_t particleCount, bool physicsEnabled, bool simdEnabled)
{
    simState->mode = selectedMode;
    simState->particleCount = particleCount;
    simState->physicsEnabled = physicsEnabled;
    simState->lastPhysicsLoopUpdate = 0.0;
    simState->accumulatedPhysicsTime = 0.0;
    simState->totalElapsedTime = 0.0;
    simState->totalFrames = 0.0;
    SetRandomSeed(42);    // so the tests can be the same every time

    switch (selectedMode) 
    {
        case MODE_AOS:
            if (!CreateParticlesAoS(&simState->data.aos, particleCount))
            {
                fprintf(stderr, "Failed to allocate memory for AoS particles\n");
                exit(EXIT_FAILURE);
            }
            if (physicsEnabled) simState->update = aos_update_physics;
            else                simState->update = aos_update_simple;
            simState->render   = aos_render;
            simState->cleanup  = aos_cleanup;
            break;
        case MODE_SOA:
            if (!CreateParticlesSoA(&simState->data.soa, particleCount))
            {
                fprintf(stderr, "Failed to allocate memory for SoA particles\n");
                exit(EXIT_FAILURE);
            }
            if (physicsEnabled) simState->update = simdEnabled ? soa_update_physics_simd : soa_update_physics;
            else                simState->update = simdEnabled ? soa_update_simple_simd : soa_update_simple;
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
    simState->accumulatedPhysicsTime += simState->lastPhysicsLoopUpdate;
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
