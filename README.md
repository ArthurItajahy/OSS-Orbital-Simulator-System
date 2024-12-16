# OSS - Orbital Simulator System

**ORBIT (Orbital Simulator System)** is a 3D graphical simulator designed to model orbits and simulate real-world physics. It provides an interactive environment to visualize and analyze orbital mechanics in a dynamic and visually engaging way.

## Features
- **3D Graphics:** Leverages modern OpenGL for immersive visualizations.
- **Real Physics Simulation:** Accurate representation of orbital mechanics based on physics principles.
- **Interactive Controls:** Rotate, zoom, and pan to explore the simulation in detail.
- **Customizability:** Adapt the simulation parameters to suit different scenarios and experiments.

## Getting Started
### Prerequisites
- A C++ compiler with support for C++11 or later.
- OpenGL 3.3 or later.
- Required libraries:
  - GLFW
  - GLAD
  - GLM

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/your-repo/orb
   cd ORB
   ```
2. Install the required dependencies:
   - On Linux (Ubuntu/Debian):
     ```bash
     sudo apt install libglfw3-dev libglm-dev
     ```
   - On MacOS (with Homebrew):
     ```bash
     brew install glfw glm
     ```
   - On Windows (with vcpkg):
     ```bash
     ./vcpkg install glfw3 glm
     ```
3. Build the project:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

### Running the Simulator
Execute the generated binary:
```bash
./oss
```

## Controls
- **W/S:** Rotate the scene along the X-axis.
- **A/D:** Rotate the scene along the Y-axis.
- **Mouse:** Use future implementations for zoom and pan (work in progress).

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request for review.

## License
This project is licensed under the [MIT License](LICENSE).

---

Embark on a journey to explore the cosmos with **ORB**, your gateway to understanding orbital dynamics!

