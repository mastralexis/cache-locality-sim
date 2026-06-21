#ifndef UI_H
#define UI_H

#include "simulation.h"

#define FRAME_TIME_WARNING_MS 16.0

/**
 * @brief Renders the UI HUD (FPS, Execution Time, Mode)
 * @param state Pointer to the global simulation state
 */
void DrawTelemetryUI(const SimulationState* state);

#endif
