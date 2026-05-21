#ifndef APP_H
#define APP_H

#include "menu.h"
#include "simulation.h"

typedef struct AppContext AppContext;
typedef void (*ScreenUpdateFunc)(AppContext* appContext, float delta);
typedef void (*ScreenRenderFunc)(AppContext* appContext);

struct AppContext
{
    MenuState menuState;
    SimulationState simState;
    ScreenUpdateFunc update;
    ScreenRenderFunc render;
};

void SwitchToMenuScreen(AppContext* appContext);
void SwitchToSimulationScreen(AppContext* appContext);

#endif
