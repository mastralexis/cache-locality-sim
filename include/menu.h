#ifndef MENU_H
#define MENU_H

#include "common.h"
#include <stdbool.h>


// Holds the choices the user makes in the menu
typedef struct {
    SimulationMode selectedMode;
    uint32_t selectedParticleCount;
    bool isStartPressed;
    int guiModeToggle;  
    int guiCountToggle;
} MenuState;

/**
 * @brief Initializes default values for the menu
 * @param state Pointer to the menu state
 */
void InitMenuState(MenuState* state);

/**
 * @brief Handles mouse/keyboard input and draws the interactive menu to the screen
 * @param state Pointer to the MenuState to update when the user makes a selection
 */
void UpdateAndDrawMenu(MenuState* state);

#endif
