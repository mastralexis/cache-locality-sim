#ifndef UI_H
#define UI_H

#include "simulation.h"

/**
 * @brief Renders the UI HUD (FPS, Execution Time, Mode)
 * @param state Pointer to the global simulation state
 */
void DrawTelemetryUI(const SimulationState* state);

#endif
