# Cache Locality Simulation: Data-Oriented Design vs. OOP in C

## Overview
This repository contains the code, data, and academic paper for the semester assignment on Systems Programming course in Harokopio University of Athens. The project investigates the performance differences between **Data-Oriented Design** and the data layouts encouraged by traditional **Object-Oriented Programming** within a high-performance C environment.

By simulating a large-scale Particle System using [Raylib](https://www.raylib.com/) library, this project visualizes and measures the impact of memory layout on CPU cache efficiency.

Specifically, it benchmarks two paradigms:
* **AoS (Array of Structures) - The OOP Memory Layout:** Data is grouped by object (entity). While intuitive for human modeling, this approach suffers from severe CPU cache-line bloat and frequent L1/L2 cache misses when processing large datasets sequentially.
* **SoA (Structure of Arrays) - The DOD Memory Layout:** Data is grouped by component. This approach optimizes for hardware prefetching and data locality, allowing for maximum cache utilization and the application of AVX SIMD instructions.

## Features
*   **Live Rendering:** Visualizing large systems of particles/objects in real-time using Raylib.
*   **Live Profiling:** On-screen telemetry displaying Frames Per Second and execution time  for the physics update loop.
* **SIMD Optimization:** Optional AVX intrinsic fallbacks for SoA layouts.

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
*   **Documentation:** LaTeX (for the accompanying scientific paper).

## Prerequisites
To compile, run, and profile this project, you will need:
*   A C compiler (GCC or Clang)
*   CMake (3.15 or higher)
*   [Valgrind](https://valgrind.org/) (specifically for running the cachegrind benchmarks).

*(Raylib does **not** need to be pre-installed. The CMake build system will automatically fetch and compile the correct version of Raylib for your operating system).*
## Building and Running
1. Clone this repository:
    ```bash
    git clone https://github.com/mastralexis/cache-locality-sim.git
    ```
2. Move inside the project:
    ```bash
    cd cache-locality-sim
    ```
3. Compile and run the project:
    - Linux / macOS / FreeBSD
    ```bash
    cmake -B build                      # Configure and Download dependencies
    ```
    ```bash
    cmake --build build                 # Compile
    ```
    ```bash
    ./build/cache-locality-sim          # Run
    ```

    - Windows
    ```powershell
    cmake -B build -G "MinGW Makefiles" # Configure and download dependencies (with MinGW)
    ```
    ```powershell
    cmake --build build                 # Compile
    ```
    ```powershell
    .\build\cache-locality-sim.exe      # Run
    ```

## Controls / Usage
Once the application is running, use the interactive GUI menu to select your desired memory layout, workload (particle count), and physics complexity. 
* **`Left Mouse Click`**: Interact with GUI toggles and buttons.
* **`ESC`**: Terminate the program.
* **`ENTER`**: Return to the main menu from the Results screen.

## Profiling with Cachegrind
To verify the cache locality claims, you can run the compiled binary through Valgrind's Cachegrind tool (Linux/macOS only):
```bash
valgrind --tool=cachegrind ./build/cache-locality-sim
```

### Team Members

| Ονοματεπώνυμο         | Email                    |
|-----------------------|--------------------------|
| Αρβανίτης Σπυρίδων    | <it2023003@hua.gr>       |
| Πολίτης Αλέξιος       | <it2023100@hua.gr>       |
| Ξηρομερίτης Δημήτριος | <it2023052@hua.gr>       |

## License
MIT License. See [LICENSE](LICENSE) for more information.
