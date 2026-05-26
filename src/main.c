#include "app.h"
#include "raylib.h"
#include "common.h"
#include "menu.h"
#include "simulation.h"
#include "ui.h"
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, PROJECTNAME);
    SetTargetFPS(UNCAPPED);

    // init app context and set starting screen to menu
    AppContext app = {0};
    InitMenuState(&app.menuState);
    SwitchToMenuScreen(&app);
    float delta;

    while (!WindowShouldClose()) 
    {
        delta = GetFrameTime();
        app.update(&app, delta);
        BeginDrawing();
            app.render(&app);
        EndDrawing();
    }

    if (app.simState.cleanup != NULL)
    {
        CleanSimulation(&app.simState);
    }

    // cleanup
    CloseWindow();

    return 0;
}
