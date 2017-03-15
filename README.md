# DualColorScope
arduino script to simultaneously trigger a camera and light source to create a cheap dual color microscope.
## General idea
The goal is to simultaneously record brightfield and fluorescence images at fast (>50Hz) framerates for each channel. (A particular application is recording fast muscular contractions and a fluorescent marker). With LEDs, instead of using a shutter, one can rapidly flicker the LED on and off to quickly change illumination. Simultaneously triggering the camera allows recording the two frames at maximum speed. The speed is limited by the read-out speed of the camera and illumination requirements. In this setup, we use a red LED to illuminate the brightfield image, a green LED to excite red fluorescence and a longpass filter to disciminate excitation and emission wavelengths. The longpass filter creates the following effect:
### Red illumination
All light passes through the sample and into the filter. The wavelength of 620nm exceeds the cutoff wavelegth of the filter, such that all light passes through. The image is created by the different absorption in the sample.
### Green illumination
The light passes through the sample and excites ed fluorescent molecules. The excitation wavelength is blocked by the filter, such that only emission (red) can continue to the camera.


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

