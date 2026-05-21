#include "app.h"
#include "menu.h"
#include "simulation.h"
#include <raylib.h>
#include <stdbool.h>

//                     Menu Screen
// -------------------------------------------------------------
static void UpdateMenu(AppContext* appContext, float delta)
{
    if (appContext->menuState.isStartPressed)
    {
        InitSimulation(
            &appContext->simState,
            appContext->menuState.selectedMode,
            appContext->menuState.selectedParticleCount
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
static void UpdateSimScreen(AppContext* appContext, float delta)
{
    UpdateSimulation(&appContext->simState, delta);
    if (IsKeyPressed(KEY_ESCAPE)) 
    {
        CleanSimulation(&appContext->simState);
        SwitchToMenuScreen(appContext);
    }
}

static void RenderSim(AppContext* appContext)
{
    DrawSimulation(&appContext->simState);
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
    context->update = UpdateSimScreen;
    context->render = RenderSim;
}
// -------------------------------------------------------------
