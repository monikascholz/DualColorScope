# DualColorScope
arduino script to simultaneously trigger a camera and light source to create a cheap dual color microscope.
## General idea
The goal is to simultaneously record brightfield and fluorescence images at fast (>50Hz) framerates for each channel. (A particular application is recording fast muscular contractions and a fluorescent marker). With LEDs, instead of using a shutter, one can rapidly flicker the LED on and off to quickly change illumination. Simultaneously triggering the camera allows recording the two frames at maximum speed. The speed is limited by the read-out speed of the camera and illumination requirements. In this setup, we use a red LED to illuminate the brightfield image, a green LED to excite red fluorescence and a longpass filter to disciminate excitation and emission wavelengths. The longpass filter creates the following effect:
### Red illumination
All light passes through the sample and into the filter. The wavelength of 620nm exceeds the cutoff wavelegth of the filter, such that all light passes through. The image is created by the different absorption in the sample.
### Green illumination
The light passes through the sample and excites ed fluorescent molecules. The excitation wavelength is blocked by the filter, such that only emission (red) can continue to the camera.

## Setup
A basic microscope is modified with custom 3d-printed or lasercut fittings for the camera, LEDs and filter, a microcontroller and a camera. The red light source is placed below the stage to illuminate the sample from below. The green light source is placed orthogonal to the sample-camera axis. Since the longpass-filter is not perfect (0.01% transmission in the forbidden region), we need to arrange the excitation light at an angle to the camera. Otherwise, the small amount of tranmitted light creates a 'shadow' birghtfield image in the fluorescence channel. The camera is triggered in sync with the color-switches in the light source, such that each frame is illuminated by exactly one color.

## Parts

1. Arduino Uno R3 ($24.95)
2. High Flex 6 Pin Hirose Female HR10A-7P-6S Cable for Basler GIGE AVT CCD Camera ($39.99)
3. Adafruit NeoPixel NeoMatrix 8x8 - 64 RGB LED Pixel Matrix ($34.95)
4. Long Pass Filter, Cut-On Wavelength: 600 nm (eg. Thorlabs FEL0600, $73)
5. Basler camera eg. acA640-120um ($400+)
6. Breadboard-friendly 2.1mm DC barrel jack
7. 330 Ohm resistor
8. a few breadboard-pin wires to connect to Arduino

-> about $600 for a 60Hz dual color microscope.

## Issues and comments
1. At fast framerates the exposure time is limited by the frame rate. This leads to very low signals in the fluorescence channel. There are two solutions: A more expensive, dedicated camera for fluorescence applications with a high quantum efficiency at 600+nm, or to change the recording pattern from alternating frames to a series of fast brightfield frames followed by a longer-exposure fluorescence frame. The feasibility of this approach depends on the desired application.

2. LED PWM cycle: The Adafruit Neopixel LEDs have an internal clock that runs at 2ms. If the light-switch data comes in during the 'off' cycle of the LED, there will be a delay in the swicth by (at most) 2ms. Considering that the exposure time at 60Hz is 8 ms (60Hz in each channel = 16 ms for two frames), this presents a significant change in toltal illumination. The problem can be solved by using faster-clocking LEDs, or it can be improved in the analysis by performing histogram equalization on the images.
