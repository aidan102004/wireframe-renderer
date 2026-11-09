# wireframe-renderer
A small 3D wireframe renderer written in C++ with SDL2. It takes a shape (vertices + edges), applies a preset animation to it (rotation in x,y,z), projects it onto a 2D screen with perspective, and draws the edges as lines.

## how it works
Each frame, every vertex goes through this pipeline:
```
3D vertex -> rotate -> perspective project -> screen coordinates -> draw lines
```
### 1. Rotation
 
Rotation is done with the standard rotation matrices.
 
**Around Y**
 
```
x' =  x·cosθ + z·sinθ
z' = -x·sinθ + z·cosθ
```
 
**Around X**
 
```
y' = y·cosθ - z·sinθ
z' = y·sinθ + z·cosθ
```
 
**Around Z**
 
```
x' = x·cosθ - y·sinθ
y' = x·sinθ + y·cosθ
```
 
The angle increases by `angle += speed * dt` each frame, where `dt` is the delta time in seconds, so the spin speed is independent of frame rate.
 
### 2. Perspective projection
 
Objects further from the camera should look smaller. The camera sits `d` units back from the origin (`d = 2.0`), and we divide by depth which includes the z component:
 
```
depth = z + d
x_proj = x / depth
y_proj = y / depth
```
 
### 3. Screen mapping
 
Projected coordinates are roughly in the range [-1, 1] with the origin in the middle and Y pointing up. SDL has the origin at the top-left with Y pointing down, so I scaled it, fliped Y and centred:
 
```
screen_x =  x_proj * SCALE + width / 2
screen_y = -y_proj * SCALE + height / 2
```
 
### Included Shapes
 
- Cube
- Triangle (2D)
- Regular polygon (n sides, 2D)
- Square pyramid
- Tetrahedron
- Octahedron
- Triangular prism
- Icosahedron
The icosahedron is generated rather than hand-written: its 12 vertices come from the golden ratio `φ = (1 + √5) / 2`, at positions like `(±1, ±φ, 0)` and their cyclic permutations. Edges are found automatically by connecting every pair of vertices whose squared distance is 4.
To switch shapes, change the line `Shape shape = make_pyramid();` in `main.cpp`.
 
## Building
 
Requires SDL2 and CMake.
 
```bash
mkdir build && cd build
cmake ..
cmake --build .
./wireframe
```
 

