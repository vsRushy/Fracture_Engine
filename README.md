# Fracture Engine

## Information

This is a 3D game engine made for educational purposes.

- Link to GitHub Repository: https://github.com/vsRushy/Fracture_Engine

- Link to Webpage: https://vsrushy.github.io/Fracture_Engine

- Link to Release section: https://github.com/vsRushy/Fracture_Engine/releases

## Features

- **(1)** .FBX, .PNG, .DDS drag, dropping and loading. An FBX file can be load inside the application by just dropping it, with its texture format being either .PNG or .DDS. Furthermore, if selected the game object by right-clicking it on the hierarchy panel and and dropping a texture to the window, it will be applied to the current object.

- **(2)** Panel system, which is used to see information about the engine and configure it. For example, creating an empty game object, selecting the game object you want from the hierarchy panel, and many more options. REMEMBER: The Renderer collapsing header has advanced options to view additional things on the screen, related to the 3D models.

- **(3)** Game object system, including its hierarchy system.

- **(4)** Game object transform system.

- **(5)** Component system. For now, it supports:
    - Transform component
    - Mesh component
    - Material component

- **(6)** Camera editor controls:
    - Move camera's XY axis position (RIGHT-CLICK)
    - Orbit camera (ALT + LEFT-CLICK)
    - Free movement (RIGHT-CLICK(hold) + AWSD)
    - Focus current selected object (F)
    - Duplicate camera's movement speed (SHIFT(hold))
    
- **(7)** Configuration file loading. You can change the configuration file in JSON format in order to load the Engine in a more personalized way.

## Known issues

- **#1** Game Object transform doesn't work very well when changing parameters.

- **#2** To use an inspector header, the other ones need to be collapsed(closed).

## Disclaimer

This build is for the first assignment of the subject. There are additional systems which are under testing and weren't required to be in the current build.

## Innovation

## External tools

- Glew

- ImGui

- DevIL

- Assimp

- Parson

- MathGeoLib

- Par shapes

- PCG

- PhyFS

**Note:** You can check the exact version of the libraries in the about panel, inside the game engine.

## Credits

- Gerard Marcos Freixas

- Martí Torras Isanta

## License

MIT License

Copyright (c) 2019 Fracture Engine Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
