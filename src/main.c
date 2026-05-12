#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int fpsCap = 60;

    InitWindow(screenWidth, screenHeight, "test");

    SetTargetFPS(fpsCap);

    while (!WindowShouldClose()) {
        // update


        // draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Test Window", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    // de-initialization
    CloseWindow();

    return 0;
}
