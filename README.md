# RJCamera
USB video application. Currently developed for senior capstone project. The goal is to have a camera application that uses OpenCV to process images before displaying to the user.

## Dependencies
(Note: Not a complete SBOM. These are only what I had to install based on a clean install of Ubuntu 22.04 Server.)

### Linux
| Library        | Implementation     |
| -------------- | ------------------ |
| Qt6 Base       | qt6-base-dev       |
| Qt6 Multimedia | qt6-multimedia-dev |
| OpenCV C++     | libopencv-dev      |
| OpenGL         | libgl1-mesa-dev    |

## Instructions
### Build from source
To build from source, we recommend using Qt's build system, qmake, and make.
* To generate a Makefile (only need to run once):
    ```
    qmake6
    ```
* To compile:
    ```
    make
    ```

For simplicity, a runfile is provided.
```
bash run.sh
```

A script is provided to set up the environment with some of the required packages on Linux systems using apt-get.
```
bash configure.sh
```

### Running
* Linux
    ```
    ./rjc
    ```

## Platform
This program is currently being developed on Ubuntu 22.04 for ARM64 and x86-64.
