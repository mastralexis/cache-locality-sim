#include "menu.h"
#include "common.h"
#include "raylib.h"
#include <stdbool.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

void InitMenuState(MenuState* state)
{
    state->selectedMode = MODE_AOS;
    state->selectedParticleCount = 100000;  // for now
    state->isStartPressed = false;
    state->guiModeToggle = 0;
    state->guiCountToggle = 1;
}

void UpdateAndDrawMenu(MenuState* menuState)
{
    ClearBackground(RAYWHITE);
    DrawText(
        PROJECTNAME,
        400,
        100,
        40,
        DARKGRAY
    );

    DrawText(
        "Select Memory Layout:",
        400,
        250,
        20,
        DARKGRAY
    );
    GuiToggleGroup(
        (Rectangle){ 400, 280, 180, 40 },
        "AoS (OOP);SoA (DOD)",
        &menuState->guiModeToggle
    );

    if (menuState->guiModeToggle == 0) menuState->selectedMode = MODE_AOS;
    else menuState->selectedMode = MODE_SOA;

    DrawText(
        "Select Workload:",
        400,
        360,
        20,
        DARKGRAY
    );
    GuiToggleGroup(
        (Rectangle){ 400, 390, 120, 40 },
        "10,000;100,000;1,000,000",
        &menuState->guiCountToggle
    );

    if (menuState->guiCountToggle == 0) menuState->selectedParticleCount =      PARTICLES_LOW;
    else if (menuState->guiCountToggle == 1) menuState->selectedParticleCount = PARTICLES_MED;
    else if (menuState->guiCountToggle == 2) menuState->selectedParticleCount = PARTICLES_HIGH;

    if (GuiButton((Rectangle){ 400, 500, 365, 60 }, "START SIMULATION")) 
    {
        menuState->isStartPressed = true;
    }
}
