# Cache Locality Simulation: Data-Oriented Design vs. OOP in C

## Overview
This repository contains the code, data, and academic paper for my semester assignment. The project investigates the performance differences between **Data-Oriented Design** and traditional **Object-Oriented Programming** paradigms within a high-performance C environment.

By simulating a large-scale Particle System using [Raylib](https://www.raylib.com/) library, this project visualizes and measures the impact of memory layout on CPU cache efficiency.

Specifically, it compares:
*   **AoS (Array of Structures):** The traditional OOP approach, known for frequent CPU cache misses in large datasets.
*   **SoA (Structure of Arrays):** The DOD approach, optimized for data locality, hardware prefetching, and minimal L1/L2 cache misses.

## Features
*   **Live Rendering:** Visualizing large systems of particles/objects in real-time using Raylib.
*   **Real-time Paradigm Swapping:** Instantly switch the physics engine between the AoS and SoA implementations.
*   **Live Profiling:** On-screen telemetry displaying Frames Per Second and execution time  for the physics update loop.

## Repository Structure
*   `src/`: C source code for the simulation, UI, and physics engines.
*   `include/`: C header files defining the AoS and SoA memory structures.
*   `docs/`: Contains the LaTeX source code for the final scientific paper and the PowerPoint presentation used for the live exam.

## Tech Stack & Tools
*   **Language:** C (C99/C11)
*   **Graphics & Windowing:** [Raylib](https://www.raylib.com/) for real-time visualization and basic input handling.
*   **Build System:** CMake
*   **Profiling:** 
    *   `Valgrind (Cachegrind)`: Used to measure L1/LL cache misses and instruction reads to scientifically prove the benefits of data locality.
    *   `gprof`: Used for execution time profiling of the physics update loops.
*   **Documentation:** LaTeX (for the accompanying scientific paper).

## Prerequisites
To compile, run, and profile this project, you will need:
*   A C compiler (GCC or Clang)
*   CMake (3.15 or highter)
*   [Valgrind](https://valgrind.org/) (specifically for running the cachegrind benchmarks).

*(Raylib does **not** need to be pre-installed. The CMake build system will automatically fetch and compile the correct version of Raylib for your operating system).*
## Building and Running
1. Clone this repository:
```bash
git clone https://github.com/mastralexis/cache-locality-sim.git
cd cache-locality-sim
```
2. Compile the project using CMake:
```bash
cmake -B build
cmake --build build
```

3. Run the executable:
```bash
./build/cache-locality-sim
```

## Controls
To be implemented

### Team Members

| Ονοματεπώνυμο         | Email                    |
|-----------------------|--------------------------|
| Αρβανίτης Σπυρίδων    | <it2023003@hua.gr>       |
| Πολίτης Αλέξιος       | <it2023100@hua.gr>       |
| Ξηρομερίτης Δημήτριος | <it2023052@hua.gr>       |

## License
MIT License. See [LICENSE](LICENSE) for more information.
