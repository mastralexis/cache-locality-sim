#include <raylib.h>
#include <raygui.h>

#include "results.h"

void UpdateResults(AppContext* appContext, float delta)
{
    if (IsKeyPressed(KEY_ENTER)) SwitchToMenuScreen(appContext);
}

void RenderResults(AppContext* appContext) 
{
    ClearBackground(RAYWHITE);
    DrawText("BENCHMARK RESULTS", 400, 150, 40, DARKGRAY);
    const SimulationState* sim = &appContext->simState;
    const char* modeText = (sim->mode == MODE_AOS) ? "Mode: Array of Structures" : "Mode: Structure of Arrays";
    DrawText(modeText, 400, 250, 20, DARKBLUE);
    DrawText(TextFormat("Particles: %u", sim->particleCount), 400, 290, 20, DARKBLUE);
    DrawText(TextFormat("Total Frames Computed: %u", sim->totalFrames), 400, 360, 20, DARKGRAY);
    DrawText(TextFormat("Average CPU Time: %.4f ms", sim->finalAverageTimeMs), 400, 400, 20, MAROON);
    if (GuiButton((Rectangle){ 400, 500, 300, 50 }, "RETURN TO MENU"))
    {
        SwitchToMenuScreen(appContext);
    }
}
