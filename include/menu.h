#ifndef MENU_H
#define MENU_H

#include "common.h"
#include <stdbool.h>


// Holds the choices the user makes in the menu
typedef struct {
    SimulationMode selectedMode;
    uint32_t selectedParticleCount;
    bool isStartPressed;
} MenuState;

/**
 * @brief Initializes every asset needed for the manu
 */
void InitMenu(void);

/**
 * @brief Handles mouse/keyboard input and draws the interactive menu to the screen
 * @param state Pointer to the MenuState to update when the user makes a selection
 */
void UpdateAndDrawMenu(MenuState* state);

#endif
