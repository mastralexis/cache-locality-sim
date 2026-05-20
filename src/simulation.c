#include "simulation.h"
#include "common.h"
#include "particle_aos.h"
#include "particle_soa.h"
#include "raylib.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void InitSimulation(SimulationState* simState, SimulationMode selectedMode, uint32_t particleCount)
{
    simState->mode = selectedMode;
    simState->particleCount = particleCount;
    simState->lastPhysicsLoopUpdate = 0.0;

    switch (selectedMode) 
    {
        case MODE_AOS:
            simState->data.aos = (ParticleAoS*) malloc(particleCount * sizeof(ParticleAoS));
            if (simState->data.aos == NULL) 
            {
                fprintf(stderr, "Error initializes AoS array\n");
                exit(1);
            }
            // InitParticlesAoS(simState->data.aos, particleCount);
            break;
        case MODE_SOA:
            // InitParticlesSoA($simState->data.soa, particleCount);
            break;
        default:
            break;
    }
}

void UpdateSimulation(SimulationState* simState, float delta)
{
    double startTime = GetTime();
    // update physics
    double endTime = GetTime();
    simState->lastPhysicsLoopUpdate = endTime - startTime;
}

void DrawSimulation(const SimulationState* simState)
{
    switch (simState->mode) 
    {
        case MODE_AOS:
            // draw aos
            break;
        case MODE_SOA:
            //draw soa
            break;
        default:
            break;
    }
}

void CleanSimulation(SimulationState* simState)
{
    switch (simState->mode) 
    {
        case MODE_AOS:
            if (simState->data.aos != NULL)
            {
                free(simState->data.aos);
                simState->data.aos = NULL;
            }
            break;
        case MODE_SOA:
            // free all arrays of soa
            break;
        default:
            break;
    }
    simState->mode = MODE_MENU;
    simState->particleCount = 0;
}
