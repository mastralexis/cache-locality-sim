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
    state->guiPhysicsToggle = 0;
    state->guiCountToggle = 1;
    state->physicsEnabled = false;
}

void UpdateAndDrawMenu(MenuState* menuState)
{
    ClearBackground(RAYWHITE);

    int screenWidth = GetScreenWidth();
    int centerX = screenWidth / 2;

    #define DrawCenteredText(text, y, fontSize, color) \
        DrawText(text, centerX - (MeasureText(text, fontSize) / 2), y, fontSize, color)
    
    DrawCenteredText(PROJECTNAME, 80, 40, DARKGRAY);

    DrawCenteredText("Select Memory Layout:", 180, 20, DARKGRAY);
    GuiToggleGroup((Rectangle){ centerX - 140, 210, 140, 40 }, "AoS (OOP);SoA (DOD)", &menuState->guiModeToggle);
    menuState->selectedMode = (menuState->guiModeToggle == 0) ? MODE_AOS : MODE_SOA;

    DrawCenteredText("Select Physics Complexity:", 290, 20, DARKGRAY);
    GuiToggleGroup((Rectangle){ centerX - 160, 320, 160, 40 }, "No Collisions;Gravity and Wall Checking", &menuState->guiPhysicsToggle);
    menuState->physicsEnabled = (menuState->guiPhysicsToggle == 1);

    DrawCenteredText("Select Workload:", 400, 20, DARKGRAY);
    
    if (!menuState->physicsEnabled) 
    {
        GuiToggleGroup((Rectangle){ centerX - 150, 430, 100, 40 }, "50k;500k;2M", &menuState->guiCountToggle);
        
        if (menuState->guiCountToggle == 0) menuState->selectedParticleCount = PARTICLES_LOW;
        else if (menuState->guiCountToggle == 1) menuState->selectedParticleCount = PARTICLES_MED;
        else if (menuState->guiCountToggle == 2) menuState->selectedParticleCount = PARTICLES_HIGH;
    } 
    else 
    {
        GuiToggleGroup((Rectangle){ centerX - 150, 430, 100, 40 }, "1k;5k;15k", &menuState->guiCountToggle);
        
        if (menuState->guiCountToggle == 0) menuState->selectedParticleCount = PARTICLES_LOW_WITH_PHYSICS;
        else if (menuState->guiCountToggle == 1) menuState->selectedParticleCount = PARTICLES_MED_WITH_PHYSICS;
        else if (menuState->guiCountToggle == 2) menuState->selectedParticleCount = PARTICLES_HIGH_WITH_PHYSICS;
    }

    if (GuiButton((Rectangle){ centerX - 180, 520, 360, 60 }, "START SIMULATION")) 
    {
        menuState->isStartPressed = true;
    }
}
