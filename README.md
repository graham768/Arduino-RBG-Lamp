# Arduino RBG Lamp

## Description

This lamp was made using an ESP8266, a NeoPixel ring (12 LEDs), and the [Blynk API](https://blynk.io/). The lamp can be controlled from the blynk app using a zeRGBa widget. Thanks to [WifiManager](https://github.com/tzapu/WiFiManager), wifi can be set up after deployment by connecting to an access point created by the lamp and entering wifi credentials.

## Installation

### Hardware and Blynk
- Attach the NeoPixel LED to any Ground (GRD) and 3 Volt (3v3) pins, and the Data input pin to GPIO 3 (RX)
- Download Blynk and create a new project
- Inside the project, add a zeRGBa widget with output set to `merge` so that color values are sent as an array of parameters across a single virtual port (in this case, V0).
- Under the new project settings, add a device and choose `ESP8266` for hardware model and `Wi-Fi` for connection type and make note of the `Auth Token` provided

### Software

- From the Arduino Library Manager, Install the following Libraries:
    + Adafruit_NeoPixel
    + ESP8266WiFi
    + ESP8266WebServer
    + Blynk
    + WiFiManager
- Inside the project repo, rename `secret.h.template` to `secret.h` and insert your Blynk Authorization Token in the provided field
- Review `app.ino` to make sure `NUMPIXELS` equals the number of LEDs on your NeoPixel, and the `PIXEL_PIN` is set to your NeoPixel Data Input pin
- Upload the sketch to your ESP8266 and connect to the `Lamp-WiFi` access point in your WiFi settings on an external device
- Scan for nearby WiFi or enter your WiFi name manually followed by your credentials.
- If everything succeeded, the LEDs should turn on. They can now be controlled by moving the cursor on the zeRGBa widget.

## Lagniappe 

You can turn on color fading by commenting out changeColor() and uncommenting colorFade() in BLYNK_WRITE() to transition colors much more smoothly.