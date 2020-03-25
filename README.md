# RC-car
The car can be controlled remotely using the Blynk app. There is also a sensor that measures the brightness and shows it on the OLED and on the Blynk app. If the brightness is too low, 2 yellow LEDs on the front and 2 red LEDs on the back of the car will light up. The Blynk app has 4 buttons to move forward, backward, left and right.

I used 6 AA batteries in series to power the servos and 5 AA batteries in series to power the VIN pin.

Used parts:
- ESP32 Microcontroller
- BH1750 (digital lux sensor)
- 11 Alkaline batteries AA 1,5V
- L293D Motor Driver IC
- 3 lego mindstorms servos
- I2C OLED display
- 10µF capacitor
- 220 ohm resistor

Pins:
- VIN
- 3.3V
- GND
- D4
- D12
- D14
- D15
- D18
- D19
- D27

RC car Blynk app.png
- D21 SDA
- D22 SCL
- EN
