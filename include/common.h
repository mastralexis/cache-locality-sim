#ifndef COMMON_H
#define COMMON_H

#include <raylib.h>
#include <stdint.h>

#define PARTICLES_LOW 50000     // 3.2 mb
#define PARTICLES_MED 500000    // 32 mb
#define PARTICLES_HIGH 2000000  // 128 mb
#define PARTICLES_LOW_WITH_PHYSICS 1000
#define PARTICLES_MED_WITH_PHYSICS 5000
#define PARTICLES_HIGH_WITH_PHYSICS 15000

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define UNCAPPED 0
#define BENCHMARK_DURATION_SECONDS 10.0
#define PROJECTNAME "Cache Locality Simulation"

typedef enum {
    MODE_MENU = 0,
    MODE_AOS,
    MODE_SOA,
    MODE_RESULT
} SimulationMode;

#endif // !COMMON_H

