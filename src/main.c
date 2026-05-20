#include "raylib.h"
#include "common.h"
#include "menu.h"
#include "simulation.h"
#include "ui.h"
#include <stdio.h>

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, PROJECTNAME);

    SetTargetFPS(UNCAPPED);

    SimulationState simState = {0};
    MenuState menuState = {0};
    InitMenuState(&menuState);
    SimulationMode currentMode = MODE_MENU;

    while (!WindowShouldClose()) 
    {
        float delta = GetFrameTime();

        if (currentMode == MODE_MENU)
        {
            BeginDrawing();
                UpdateAndDrawMenu(&menuState);
            EndDrawing();
            
            if (menuState.isStartPressed)
            {
		// change currentMode to the selectedMode 
		// InitSimulation
            }
        }
        else
        {
            // Do simulation update loop
        }

    }

    // cleanup
    CloseWindow();

    return 0;
}
