#ifndef COMMON_H
#define COMMON_H

#include <raylib.h>
#include <stdint.h>

#define PARTICLES_LOW 10000
#define PARTICLES_MED 100000
#define PARTICLES_HIGH 1000000
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

