# RenderForge

![C%2B%2B](https://img.shields.io/badge/C%2B%2B-0180CD?logo=cplusplus&logoColor=white)
![OpenGL](https://img.shields.io/badge/OpenGL-5586A4?logo=opengl&logoColor=white)
![SonarQube](https://img.shields.io/badge/SonarQube-549DD0?logo=data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCAxMjggMTI4Ij48cGF0aCBmaWxsPSIjZmZmZmZmIiBkPSJNMTEzLjE5IDEyNS45MzhoLTcuMTZDMTA2LjAzIDY4LjI5MyA1OC40NjQgMjEuMzk2IDAgMjEuMzk2di03LjE2MWM2Mi40MTYgMCAxMTMuMTkgNTAuMTA2IDExMy4xOSAxMTEuNzAzWm00Ljk1Mi0zOC40NDFjLTguNTk4LTM2LjE1MS0zNy44OTgtNjYuMzYyLTc0LjYyMy03Ni45MDNsMS42NDctNS43MzVjMzguNzYzIDExLjEzMyA2OS43MDIgNDMuMDI3IDc4Ljc3OCA4MS4yNTdabTUuNTA0LTMzLjk0MmMtOC44NTQtMTkuMzA5LTIzLjk0NC0zNi4xNDYtNDIuNDgtNDcuNDExbDIuNDgyLTQuMDgyQzEwMi45OTIgMTMuODE5IDExOC43NCAzMS4zOTkgMTI4IDUxLjU1NlptMCAwIi8+PC9zdmc+DQo=)

A C++ OpenGL renderer with three demo scenes, multiple shading models, light types and day/night skyboxes.

## Overview

RenderForge is a custom C++ OpenGL renderer I built as a project for my computer graphics course at university. Models load through Assimp. You can switch between four shading models (constant, Lambert, Phong, Blinn) and three light types (directional, point, spot).

## Tech stack

- **Languages:** C++, GLSL
- **API:** OpenGL
- **Libraries:** GLFW, GLEW, GLM, Assimp, SOIL, stb_image
- **Linter:** SonarQube

## Features

- Four shading models: constant, Lambert, Phong, Blinn
- Three light types: directional, point, spot (spotlight follows the camera)
- Moving fireflies with point lights
- Cubemap skybox with day/night switching per scene
- Model loading via Assimp with vertex position, normal, UV and tangent data
- Texture loading for grass, house, zombie, planets and the skybox
- Transformation system with composable translation, rotation, scale and dynamic rotation
- Observer pattern for camera updates
- Random placement of trees, bushes and zombies

## Scenes

- **Forest** - house, trees, bushes, wooden fence, grass, five zombies, three fireflies
- **Spheres** - four spheres, each rendered with a different shader
- **Planets** - Sun, Earth and Moon orbiting with a space skybox

## Controls

- `W`, `A`, `S`, `D` - move forward, left, back, right
- `F`, `B` - move up and down
- Left mouse button - look around
- `0`, `1`, `2` - switch scenes
- `Esc` - quit

## Screenshots

![Forest scene](https://raw.githubusercontent.com/mk-forge/render-forge/main/Screenshots/forest.png)
![Spotlight effect](https://raw.githubusercontent.com/mk-forge/render-forge/main/Screenshots/spotlight.png)
![Spheres scene](https://raw.githubusercontent.com/mk-forge/render-forge/main/Screenshots/spheres.png)
![Planets scene](https://raw.githubusercontent.com/mk-forge/render-forge/main/Screenshots/planets.png)

## Installation

1. Download the latest `RenderForge.zip` from [Releases](https://github.com/mk-forge/render-forge/releases).
2. Extract the ZIP.
3. Run `RenderForge.exe`.

## Building from source

Open `RenderForge.sln` in Visual Studio and build the project. Required libraries are included in the `libs/` folder.

## Credits

- [The Blender Cubemap Skybox Pack](https://drive.google.com/file/d/1V0KlEOLKjjEUAlfCeCxpo-6d4A6tWrdy/view?usp=sharing) by ZGnosis. Free for non-commercial use with attribution.
- [Lowpoly Firefly model](https://skfb.ly/pzZAB) by Caledhril. Licensed under [Creative Commons Attribution](http://creativecommons.org/licenses/by/4.0/).

## License

[MIT](LICENSE)