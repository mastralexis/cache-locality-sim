#include <raylib.h>
#include <stdbool.h>

#include "app.h"
#include "common.h"
#include "menu.h"
#include "simulation.h"
#include "results.h"
#include "ui.h"

//                     Menu Screen
// -------------------------------------------------------------
static void UpdateMenu(AppContext* appContext, float delta)
{
    if (appContext->menuState.isStartPressed)
    {
        InitSimulation(
            &appContext->simState,
            appContext->menuState.selectedMode,
            appContext->menuState.selectedParticleCount,
            appContext->menuState.physicsEnabled,
            appContext->menuState.simdEnabled
        );
        appContext->menuState.isStartPressed = false;
        SwitchToSimulationScreen(appContext);
    }
}

static void RenderMenu(AppContext* appContext)
{
    UpdateAndDrawMenu(&appContext->menuState);
}
// -------------------------------------------------------------


//                     Simulation Screen
// -------------------------------------------------------------
static void UpdateSim(AppContext* appContext, float delta)
{
    UpdateSimulation(&appContext->simState, delta);

    // check for the 10 second timer
    // if true calculate the results 
    if (appContext->simState.totalElapsedTime >= BENCHMARK_DURATION_SECONDS)
    {
        if (appContext->simState.totalFrames > 0) 
        {
            appContext->simState.finalAverageTimeMs = 
                (appContext->simState.accumulatedPhysicsTime / appContext->simState.totalFrames) * MS_PER_SEC;
        }
        else 
        {
            appContext->simState.finalAverageTimeMs = 0.0;
        }
        CleanSimulation(&appContext->simState);  // clean up the memory
        SwitchToResultsScreen(appContext);
    }

    if (IsKeyPressed(KEY_ESCAPE)) 
    {
        CleanSimulation(&appContext->simState);
        SwitchToMenuScreen(appContext);
    }
}

static void RenderSim(AppContext* appContext)
{
    ClearBackground(WHITE);
    DrawSimulation(&appContext->simState);
    DrawTelemetryUI(&appContext->simState);
}
// -------------------------------------------------------------

//                     Screen Switching
// -------------------------------------------------------------
void SwitchToMenuScreen(AppContext* context)
{
    context->update = UpdateMenu;
    context->render = RenderMenu;
}

void SwitchToSimulationScreen(AppContext* context)
{
    context->update = UpdateSim;
    context->render = RenderSim;
}

void SwitchToResultsScreen(AppContext* appContext)
{
    appContext->update = UpdateResults;
    appContext->render = RenderResults;
}
// -------------------------------------------------------------
