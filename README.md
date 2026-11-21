# RenderForge

![C%2B%2B](https://img.shields.io/badge/C%2B%2B-0180CD?logo=cplusplus&logoColor=white)
![GLSL](https://img.shields.io/badge/GLSL-000000?logo=data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCA3MjMgNDU0LjMiPjxwYXRoIGZpbGw9IiNmZmYiIGQ9Ik03MjEuNyAzNDMuN0M2NTIuOSA0MDggNTMwLjIgNDUzLjMgMzkwLjEgNDUzLjMgMTc0LjcgNDUzLjMgMCAzNTIgMCAyMjcuMVMxNzQuNyAxIDM5MC4yIDFjMTQwLjYuMSAyNjMuNyA0NS41IDMzMi4yIDExMC4yLTYyLjgtMzguNi0xNTcuMy02MC45LTI2Mi44LTYwLjlzLTI0My4xIDM3LjQtMzAxLjIgOTIuNHE0LjgtMyAxMC4yLTUuNGMxMi01IDI1LjUtNy41IDQwLjYtNy41aDMuMWwzLjQuM2M2LjkgMCAxMy41LjggMTkuOCAyLjMgNy4xIDIuMSAxMy4yIDQuNiAxOC4yIDcuNSAxMC43IDUuNyAxOS41IDEzLjQgMjYuMyAyMy4xIDMuNSA0LjkgNi4xIDkuOCA3LjggMTQuOCAxLjcgNC43IDIuNiA5LjUgMi42IDE0LjZoLTM5Yy0uNS00LTIuNC04LjQtNS43LTEzLjMtMy4zLTQuNy04LjEtOC44LTE0LjMtMTIuMi01LjktMy4zLTEzLTQuOS0yMS4zLTQuOXMtNS41LjMtOC42LjhjLTIuNi40LTUuNyAxLTkuNCAyLjEtNS45IDIuMS0xMS41IDUuNS0xNi45IDEwLjRzLTkuOCAxMS45LTEzLjMgMjEuMWMtMy41IDkuNC01LjIgMjAuNC01LjIgMzNzMi4xIDI1LjUgNi4yIDM0LjhjNC4yIDkuNCA5LjUgMTYuMSAxNi4xIDIwLjMgNi42IDQuMyAxNC40IDcuMiAyMy40IDguNmw3IC41YzcuMSAwIDE0LTEuNSAyMC44LTQuNCA2LjYtMi45IDEyLjEtNy41IDE2LjYtMTMuOCA0LjMtNi4yIDcuNS0xNCA5LjQtMjMuMUgyMTN2LTMxLjVoNzcuN3YxMDAuNmgtMjZsLTMuOS0yMy40Yy02LjIgNy44LTEyLjcgMTMuOC0xOS41IDE3LjktNi40IDQuNS0xMy4yIDcuNC0yMC4zIDguNi03LjUgMS40LTE1LjEgMi4xLTIyLjkgMi4xcy0yMC4yLTIuMy0yOS45LTdjLS43LS4zLTEuMy0uNi0xLjktLjkgNjAuMSA1MS4xIDE2OC45IDg1LjIgMjkzLjIgODUuMnMxOTkuMy0yMS44IDI2Mi4xLTYwLjJaTTM0Ny41IDEzNC41aC0zNS4zdjE4Ni45aDExOC45di0zNC4xaC04My41VjEzNC40Wm0yMTkuNCA5MGMtNy41LTMuOC0xOC4zLTcuNC0zMi41LTEwLjdsLTE4LjItNC43LTI2LjUtNi41Yy05LjktMy4xLTE0LjgtOS41LTE0LjgtMTkuMnMzLjMtMTIuMiA5LjktMTUuOWM2LjYtMy42IDE0LTUuNSAyMi40LTUuNSAyNC4zIDAgMzcuMyA5LjMgMzkgMjcuOGgzNy40YzAtMy41LS4zLTYuOC0xLTEwLjEtLjUtMi40LTEuNy02LjEtMy40LTEwLjlxLTMuOS0xMC42NS0xMi0xOS41Yy01LjItNS43LTEyLjgtMTAuNS0yMi45LTE0LjMtOS41LTMuNi0yMS4xLTUuNS0zNC44LTUuNXMtMjcuMSAyLjMtMzcuNyA2LjhjLTEwLjYgNC4zLTE4LjYgMTEtMjQuMiAyMC01LjcgOS04LjYgMTktOC42IDI5LjlzMi43IDIyLjQgOC4xIDI5LjljNSA3LjMgMTIgMTIuOSAyMC44IDE2LjkgOS4yIDQuMiAxOS44IDcuNCAzMiA5LjZsMTcuOSA0LjIgMTkuOCA1LjVjMy42IDEuMiA2LjkgMy4zIDkuOSA2LjIgMi44IDIuOCA0LjIgNyA0LjIgMTIuNyAwIDE1LjMtMTMuNyAyMi45LTQxLjEgMjIuOWMtNiAwLTEyLjQtMS0xNy45LTMuMWMtNS43LTIuMy0xMC4yLTUuNi0xMy41LTEwLjEtMy42LTQuNS01LjUtMTAuMS01LjUtMTYuOUg0MzZjMCAyMC41IDcgMzYuMSAyMS4xIDQ2LjggMTMuNyAxMC42IDM0IDE1LjkgNjAuOCAxNS45YzYuNSAwIDEyLjUtMSAxOC44LTIuMSA3LjMtMS40IDE1LTQuMiAyMy4xLTguMyA4LjUtNC4zIDE1LjYtMTAuNyAyMS4zLTE5IDUuNS04LjUgOC4zLTE5LjEgOC4zLTMxLjdzLTEuOS0xOS4zLTUuNy0yNS43Yy0zLjgtNi4yLTkuNC0xMS40LTE2LjYtMTUuM1ptNzIuNiA2Mi45VjEzNC41aC0zNS4zdjE4Ni45aDExOC45di0zNC4xaC04My41WiIvPjwvc3ZnPg==)
![OpenGL](https://img.shields.io/badge/OpenGL-5586A4?logo=opengl&logoColor=white)
![SonarQube](https://img.shields.io/badge/SonarQube-549DD0?logo=data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCAxMjggMTI4Ij48cGF0aCBmaWxsPSIjZmZmZmZmIiBkPSJNMTEzLjE5IDEyNS45MzhoLTcuMTZDMTA2LjAzIDY4LjI5MyA1OC40NjQgMjEuMzk2IDAgMjEuMzk2di03LjE2MWM2Mi40MTYgMCAxMTMuMTkgNTAuMTA2IDExMy4xOSAxMTEuNzAzWm00Ljk1Mi0zOC40NDFjLTguNTk4LTM2LjE1MS0zNy44OTgtNjYuMzYyLTc0LjYyMy03Ni45MDNsMS42NDctNS43MzVjMzguNzYzIDExLjEzMyA2OS43MDIgNDMuMDI3IDc4Ljc3OCA4MS4yNTdabTUuNTA0LTMzLjk0MmMtOC44NTQtMTkuMzA5LTIzLjk0NC0zNi4xNDYtNDIuNDgtNDcuNDExbDIuNDgyLTQuMDgyQzEwMi45OTIgMTMuODE5IDExOC43NCAzMS4zOTkgMTI4IDUxLjU1NlptMCAwIi8+PC9zdmc+DQo=)

A C++ OpenGL renderer with three demo scenes, multiple shading models, light types and day/night skyboxes.

## Overview

RenderForge is a custom C++ OpenGL renderer I built as a project for my computer graphics course at university. Models load through Assimp. You can switch between four shading models (constant, Lambert, Phong, Blinn) and three light types (directional, point, spot).

## Tech stack

- **Languages:** C++, GLSL
- **Libraries:** OpenGL, GLFW, GLEW, GLM, Assimp, SOIL, stb_image
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