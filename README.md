# Monitor
USB video application. Currently developed for senior capstone project. The goal is to have a camera application that uses OpenCV to process images before displaying to the user.

## Dependencies
(Note: Not a complete SBOM. These are only what I had to install.)
| Library        | Implementation     |
| -------------- | ------------------ |
| Qt6 Base       | qt6-base-dev       |
| Qt6 Multimedia | qt6-multimedia-dev |
| OpenCV C++     | libopencv-dev      |
| OpenGL         | libgl1-mesa-dev    |

## Instructions
```
> qmake6
> make
```

## Platform
This program is currently being developed on Ubuntu 22.04 for ARM64 and x86-64.
