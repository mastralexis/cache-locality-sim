#ifndef COMMON_H
#define COMMON_H

#include <raylib.h>
#include <stdint.h>
#include <stdbool.h>

#define AVX_LANE_COUNT 8

#define PARTICLES_LOW 50000     // 3.2 mb
#define PARTICLES_MED 500000    // 32 mb
#define PARTICLES_HIGH 2000000  // 128 mb
#define PARTICLES_LOW_WITH_PHYSICS 50000
#define PARTICLES_MED_WITH_PHYSICS 500000
#define PARTICLES_HIGH_WITH_PHYSICS 2000000

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define UNCAPPED 0
#define BENCHMARK_DURATION_SECONDS 10.0
#define PROJECTNAME "Cache Locality Simulation"

#define GRAVITY_Y 98.0f
#define DRAG 0.999f
#define SEED 42
#define BOUNCE_DAMPENING 0.8f
#define MAX_RENDER_PARTICLES 50000
#define PARTICLE_MASS_MIN 1.0f
#define PARTICLE_MASS_MAX 10.0f
#define VELOCITY_MIN -200
#define VELOCITY_MAX 200

#define MS_PER_SEC 1000.0

typedef enum {
    MODE_MENU = 0,
    MODE_AOS,
    MODE_SOA,
    MODE_RESULT
} SimulationMode;

#endif // !COMMON_H

