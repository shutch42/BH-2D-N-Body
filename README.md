# Barnes-Hut 2D N-Body Solution
## Summary:
This is the Barnes-Hut solution to the N-Body problem written in C++. It's much faster than my previous solution, and it renders in real-time using the freeGLUT library.

## Implementation:
- Masses are stored inside of the Body class
- Bodies are loaded into a vector/list to represent the system of masses
- For every time step, the position and velocity of each mass is re-calculated and overwritten in the vector of bodies
- These calculations are estimated using an quadTree, which shortens the number of calculations by grouping masses together
- After the position and velocity are calculated, masses are displayed using points in openGL
- This runs infinitely, or until a mass escapes the area that the octTree covers

## Results:
### 1,500 Mass Simulation:
![Sim](https://github.com/shutch42/BH-2D-N-Body/blob/master/Captures/BH-Sim.gif)  

### With QuadTree Displayed:
![Quad](https://github.com/shutch42/BH-2D-N-Body/blob/master/Captures/BH-QuadTree.gif)

## Future Improvements:
- Add multithreading
- Implement in 3D
- Add controls to zoom/move around in simulation
- Collision Handling
- Allow quadTree to expand/collapse to simulation size, rather than keeping it a static size
