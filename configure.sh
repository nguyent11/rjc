#!/bin/bash
# This script can be used to configure a development environment for this repository.

# This is not an exhaustive list of dependencies, but additional packages that I needed
# to install on top of whatever comes with a fresh install of Ubuntu 22.04 Server ARM64.

# Check for qt6 base
if dpkg -s qt6-base-dev &>/dev/null; then
    echo 'Qt6 Base (qt6-base-dev) is installed'
else
    echo 'qt6-base-dev is not installed'
    echo 'installing qt6-base-dev'
    sudo apt-get install -y qt6-base-dev
fi

# Check for qt6 multimedia
if dpkg -s qt6-multimedia-dev &>/dev/null; then
    echo 'Qt6 Multimedia (qt6-multimedia-dev) is installed'
else
    echo 'qt6-multimedia-dev is not installed'
    echo 'installing qt6-multimedia-dev'
    sudo apt-get install -y qt6-multimedia-dev
fi

# Check for opencv c++
if dpkg -s libopencv-dev &>/dev/null; then
    echo 'OpenCV (libopencv-dev) is installed'
else
    echo 'libopencv-dev is not installed'
    echo 'installing libopencv-dev'
    sudo apt-get install -y libopencv-dev
fi

# Check for OpenGL
if dpkg -s libgl1-mesa-dev﻿﻿ ﻿&>/dev/null; then
    echo 'OpenGL (libgl1-mesa-dev) is installed'
else
    echo 'libgl1-mesa-dev is not installed'
    echo 'installing libgl1-mesa-dev'
    sudo apt-get install -y libgl1-mesa-dev
fi
