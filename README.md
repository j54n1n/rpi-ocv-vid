# rpi-ocv-vid
Raspberry Pi Camera with OpenCV Video Post Processing

## Pre-Requirements
* Make sure that you enabled the Pi Camera via `sudo raspi-config` and that at least 128MV of RAM is assigned to the GPU.
* The latest linux kernels for the Raspberry Pi should contain already the needed v4l2 driver. For testing purposes you can execute `modprobe bcm2835-v4l2` to load the module. A new device at `/dev/video0` should appear.
* For permanent loading of the module create a file at `/etc/modules-load.d/rpi-camera.conf` with the content `bcm2835-v4l2`. Save, exit and reboot.
* Install the OpenCV environment via `sudo apt-get install libopencv-dev`.
* Install CMake via `sudo apt-get install cmake`.

## Compiling
* Run `cmake .` and then normal `make` commands.

## Sources
* [Official V4L2 driver](https://www.raspberrypi.org/forums/viewtopic.php?f=43&t=62364)
* [Arch Linux Wiki - Raspberry Pi camera module]https://wiki.archlinux.org/index.php/Raspberry_Pi#Raspberry_Pi_camera_module
