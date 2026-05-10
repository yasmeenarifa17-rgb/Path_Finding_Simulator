# Path_Finding_Simulator
This simulator implements the A (A-Star) Search Algorithm*, a widely used pathfinding technique that combines the benefits of Dijkstra's algorithm and Greedy Best-First Search. It calculates the "best" path by considering both the actual distance from the start and an estimated distance to the destination (heuristic).
# 🚀 Advanced Pathfinding Visualizer (C++ & SFML)

A high-performance, interactive AI project that visualizes the **A* Search Algorithm** in real-time. Built as a part of my 1st-year BTech (AIML) curriculum to master algorithm efficiency and graphics programming.

## 🌈 Visual Experience
Unlike static pathfinders, this simulator provides a dynamic look at how AI explores a grid.
- **Real-time Expansion**: Watch the "frontier" of the search grow across the screen.
- **Interactive Wall Building**: Use your mouse to draw complex mazes and watch the AI find a way through.
- **Color-Coded Feedback**: 
  - 🟩 **Green**: Start point
  - 🟥 **Red**: Goal
  - 🟦 **Blue**: Explored nodes (Closed Set)
  - 🟨 **Yellow**: The final optimized shortest path

## 🛠️ Technical Highlights
- **Algorithm**: A* (A-Star) with Manhattan Heuristic.
- **Performance**: Efficient priority queue implementation for $O(N \log N)$ complexity.
- **Graphics**: Hardware-accelerated rendering using **SFML**.
- **Memory Management**: Structured using custom `Node` pointers for path reconstruction.

## 🚀 How to Run
1. Install **SFML** for your compiler (GCC/Clang/MSVC).
2. Compile: `g++ main.cpp -o visualizer -lsfml-graphics -lsfml-window -lsfml-system`
3. Launch: `./visualizer`
4. **Controls**:
   - **Left Click**: Draw walls/obstacles.
   - **Spacebar**: Begin the pathfinding animation.

     AUTHOR- MOHAMMAD ARIFA YASMEEN

---
*Created with ❤️ for the C++ and AIML Community.*
