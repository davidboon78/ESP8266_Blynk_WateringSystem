# ESP8266_Blynk_WateringSystem

HARDWARE:
Component list with links for purchase, all parts other than the esp8266 and the water pump can be purchased at Creatron(https://www.creatroninc.com/).  The water pump they have there is 12v and would require an external power source.  

2x npn transistor 

https://www.amazon.ca/2N2222-Plastic-Encapsulate-Power-Transistors-600mA/dp/B00R1M3DA4/ref=sr_1_9?ie=UTF8&qid=1542933696&sr=8-9&keywords=npn+transistor
https://www.aliexpress.com/item/100PCS-LOT-in-line-2N2222A-triode-transistor-NPN-switching-transistors-TO-92-0-6A-30V-NPN/32624547567.html

1x ESP8266 Nodemcu

https://www.amazon.ca/J-DEAL%C2%AE-NodeMCU-Internet-ESP8266-Development/dp/B01F5ALLFM/ref=sr_1_1_sspa
https://www.aliexpress.com/item/1PCS-Wireless-Module-CH340-CP2102-NodeMcu-V3-Lua-WIFI-Internet-of-Things-development-board-based-ESP8266/32918576689.html

1x breadboard

https://www.amazon.ca/Solderless-Prototype-Breadboard-Points-Contacts/dp/B07871PGKX/ref=sr_1_19

1x moisture sensor

(can probably work with any moisture sensor that has an analog out, will probably not be making a digital version, will sooner be testing that it works with capacitive sensors)

https://www.amazon.ca/XCSOURCE-Moisture-Automatic-Watering-TE215/dp/B00ZR3B60I/ref=sr_1_1_sspa
https://www.aliexpress.com/item/Soil-Moisture-Sensor-Hygrometer-Module-for-Arduino-2560-UNO-1280-Free-Shipping-Wholesale/1398732669.html

1x 3.3v waterpump

(higher than 3.3v will require using an external power source, but would operate largely the same, have been unable to find such a pump anywhere but amazon)

https://www.amazon.ca/Arduino-Kits-Small-Water-Available/dp/B07B9FGMY9/ref=sr_1_1

Jumper wires

https://www.amazon.ca/SODIAL-Solderless-Flexible-Breadboard-Arduino/dp/B00KBPQYO0/ref=sr_1_15

https://www.aliexpress.com/item/Free-Shipping-140pcs-in-one-package-convenient-New-Solderless-Flexible-Breadboard-Jumper-wires-Cables-HOT-Sale/664098704.html

Optional: wire strippers, heat shrink tubing, nail polish

SIDENOTE EXPLANATION FOR THE NERDS:
A brief explanation of how I am using NPN transistors.  NPN Transistors have 3 pins, usually (with the flat side facing you) they are the collector, the base and the collector.  The base acts as a kind of multiplier for whatever is coming into the collector, and the result comes out of the emitter.  In this case I am using it as a switch for powering both the Soil Moisture Sensor and the Water Pump so as to conserve energy.  This also helps extend the life of the Soil Moisture Sensor as running electrical current causes oxidation of the sensors and eventually rust.  As you will see the code sets the pin to HIGH when we want the component to be powered.




SOFTWARE:

Install the CP210x_Universal_Windows_Driver.zip files from this repo to support the esp8266 nodemcu over usb

Install the IDE and setup the board
1) Install the Arduino IDE (https://www.arduino.cc/en/Main/Software)
2) Setup Arduino IDE for ESP use

  a) Download Arduino IDE.

  b) Open you IDE and click on "File -> Preferences".

  c) In  "Aditional Boards Manager URLs" add this line and click on "OK":
      "http://arduino.esp8266.com/stable/package_esp8266com_index.json"
      
  d) Go to "Tools -> Board -> Boards Manager", type "ESP8266" and install it.
  
  e) Go again to "Tools -> Board" and select "Generic ESP8266 Module".
  
Install the Blynk Library
  1) Download the Blynk Library zip file: https://github.com/blynkkk/blynk-library/releases/tag/v0.5.4
  2)  Install the library into the Arduino IDE:  “Sketch -> Include Library > Add Zip Library” and add the blynk library zip file you       just downloaded.
