#include <stdio.h>
#include <raylib.h>

#include "ui.h"
#include "common.h"

void DrawTelemetryUI(const SimulationState* state)
{
    // semi-transparent background panel for readability
    DrawRectangle(10, 10, 340, 170, Fade(BLACK, 0.75f));
    DrawRectangleLines(10, 10, 340, 170, RAYWHITE);

    // determine the text for the current modes
    const char* modeText;
    if (state->mode == MODE_AOS) { modeText = "Architecture: AoS"; }
    else { modeText = state->simdEnabled ? "Architecture: SoA (SIMD)" : "Architecture: SoA (Scalar)"; }
    const char* physicsText = state->physicsEnabled ? "Physics: Gravity & Collision" : "No physics";

    // calculate CPU timings in milliseconds
    double currentFrameMs = state->lastPhysicsLoopUpdate * MS_PER_SEC;
    double avgTimeMs = 0.0;
    if (state->totalFrames > 0) {
        avgTimeMs = (state->accumulatedPhysicsTime / state->totalFrames) * MS_PER_SEC;
    }

    char buffer[128];

    // render the Data
    // FPS
    snprintf(buffer, sizeof(buffer), "FPS: %d", GetFPS());
    DrawText(buffer, 25, 20, 20, GREEN);

    // Mode
    DrawText(modeText, 25, 50, 20, WHITE);

    // Physics State
    DrawText(physicsText, 25, 80, 20, LIGHTGRAY);

    // Particle Count
    snprintf(buffer, sizeof(buffer), "Particles: %u", state->particleCount);
    DrawText(buffer, 25, 110, 20, WHITE);

    // CPU Times (Current vs Average)
    snprintf(buffer, sizeof(buffer), "CPU: %.2f ms (Avg: %.2f ms)", currentFrameMs, avgTimeMs);
    
    // Make the text turn red if the CPU is struggling (taking longer than 16ms per frame)
    Color cpuColor = (avgTimeMs > FRAME_TIME_WARNING_MS) ? RED : YELLOW;
    DrawText(buffer, 25, 140, 20, cpuColor);
}
