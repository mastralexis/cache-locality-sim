#include <stdbool.h>
#include <stdio.h>
#include <raylib.h>

#include "menu.h"
#include "common.h"
#include "simulation.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

static void formatNumber(uint32_t num, char* buf, size_t bufSize)
{
    if (num >= 1000000)   snprintf(buf, bufSize, "%uM", num / 1000000);
    else if (num >= 1000) snprintf(buf, bufSize, "%uk", num / 1000);
    else                  snprintf(buf, bufSize, "%u", num);
}

void InitMenuState(MenuState* state)
{
    state->selectedMode = MODE_AOS;
    state->selectedParticleCount = PARTICLES_MED;
    state->isStartPressed = false;
    state->guiModeToggle = 0;
    state->guiPhysicsToggle = 0;
    state->guiCountToggle = 1;
    state->physicsEnabled = false;
    state->simdEnabled = false;
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

    if (menuState->selectedMode == MODE_SOA)
    {
        if (IsSimdSupported()) 
        {
            GuiCheckBox((Rectangle){ centerX + 180, 220, 20, 20 }, " Enable SIMD", &menuState->simdEnabled);
        }
        else
        {
            // greyed out text explaining why it cant be clicked
            DrawText("SIMD Not Supported", centerX + 180, 220, 20, GRAY);
            menuState->simdEnabled = false;
        }
    }
    else 
    {
        menuState->simdEnabled = false;
    }
    // -------------------------------------

    DrawCenteredText("Select Physics Complexity:", 290, 20, DARKGRAY);
    GuiToggleGroup((Rectangle){ centerX - 160, 320, 160, 40 }, "No Collisions;Gravity and Wall Checking", &menuState->guiPhysicsToggle);
    menuState->physicsEnabled = (menuState->guiPhysicsToggle == 1);

    DrawCenteredText("Select Workload:", 400, 20, DARKGRAY);

    // string generation for the Toggle Group
    char lowStr[16], medStr[16], highStr[16];
    char toggleText[128];
    
    if (!menuState->physicsEnabled) 
    {
        formatNumber(PARTICLES_LOW, lowStr, sizeof(lowStr));
        formatNumber(PARTICLES_MED, medStr, sizeof(medStr));
        formatNumber(PARTICLES_HIGH, highStr, sizeof(highStr));
 
        snprintf(toggleText, sizeof(toggleText), "%s;%s;%s", lowStr, medStr, highStr);
        GuiToggleGroup((Rectangle){ centerX - 150, 430, 100, 40 }, toggleText, &menuState->guiCountToggle);
 
        if (menuState->guiCountToggle == 0)      menuState->selectedParticleCount = PARTICLES_LOW;
        else if (menuState->guiCountToggle == 1) menuState->selectedParticleCount = PARTICLES_MED;
        else if (menuState->guiCountToggle == 2) menuState->selectedParticleCount = PARTICLES_HIGH;
    }
    else
    {
        formatNumber(PARTICLES_LOW_WITH_PHYSICS, lowStr, sizeof(lowStr));
        formatNumber(PARTICLES_MED_WITH_PHYSICS, medStr, sizeof(medStr));
        formatNumber(PARTICLES_HIGH_WITH_PHYSICS, highStr, sizeof(highStr));

        snprintf(toggleText, sizeof(toggleText), "%s;%s;%s", lowStr, medStr, highStr);
        GuiToggleGroup((Rectangle){ centerX - 150, 430, 100, 40 }, toggleText, &menuState->guiCountToggle);
 
        if (menuState->guiCountToggle == 0)      menuState->selectedParticleCount = PARTICLES_LOW_WITH_PHYSICS;
        else if (menuState->guiCountToggle == 1) menuState->selectedParticleCount = PARTICLES_MED_WITH_PHYSICS;
        else if (menuState->guiCountToggle == 2) menuState->selectedParticleCount = PARTICLES_HIGH_WITH_PHYSICS;
    }

    if (GuiButton((Rectangle){ centerX - 180, 520, 360, 60 }, "START SIMULATION")) 
    {
        menuState->isStartPressed = true;
    }
}
