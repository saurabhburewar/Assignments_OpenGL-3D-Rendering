# Assignments_OpenGL-3D-Rendering

## Install OpenGL (Linux)
For Installation - 
```
sudo apt-get install freeglut3-dev
```
For compilation - 
```
gcc filename.c -lGL -lGLU -lglut
OR
g++ filename.cpp -lGL -lGLU -lglut
```

## Object Rendering

Steps implemented in the code are as follows.

- Suitable camera and light position is chosen and coordinates are aligned.
- Oriented normals for each triangle calculated.
- Coordinates of the view frustum calculated.
- Coordinate tranformation through translation and rotation done.
- Z-buffer and phong shading not working.
- Ambient lighting done.
- Material applied to the object.
- Rendered the object.

Implemented using inbuilt functions in inbuilt.cpp.
Compile and Run - 
```
g++ inbuilt.cpp -lGL -lGLU -lglut
./a.out
```

Implemented from scratch in scratch.cpp (incomplete).
Compile and Run - 
```
g++ scratch.cpp -lGL -lGLU -lglut
./a.out
```
