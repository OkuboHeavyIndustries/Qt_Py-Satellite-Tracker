# Qt_Py-Satellite-Tracker

The Qt Py Satellite tracker uses a Adafruit Qt Py SAMD21 board, Oak Dev Tech Power Pack,
BN-280 GPS unit, SSD1306 OLED and a small lithium battery.

It uses the GPS to check your current location and then calculates the position of 4 satellites
using TLEs and lights an indicater light if any of the satellites are 8 degrees above the horizon at your
cuurrent location.
The SSD displays local time, local latitude, longitude, altitude as well as number of GPS satellite locks.
The lower part of the display shows one of the 4 satellites being tracked every 15 seconds.  
It shows the satellite name, UTC date and time, satellite longitude and latitude, lcoation relative to your current location (azimuth and elevation).
It also shows TX and RX frequencies with calculated doppler.
