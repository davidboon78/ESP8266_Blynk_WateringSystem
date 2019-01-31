# ESP8266 Blynk Smart Watering System For Single Plants

HARDWARE:
Component list with links for purchase, all parts other than the esp8266 and the water pump can be purchased at Creatron(https://www.creatroninc.com/).  The water pump they have there is 12v and would require an external power source.  

1 x Mosfet transistor (FQP30N06)
https://www.aliexpress.com/item/10PCS-FQP30N06-FQP50N06-STP55NF06-STP65NF06-STP75NF75-LM317T-IRF3205-Transistor-TO-220-TO220-30N06-50N06-55NF06-65NF06/32866558477.html


1x npn transistor 

https://www.amazon.ca/2N2222-Plastic-Encapsulate-Power-Transistors-600mA/dp/B00R1M3DA4/ref=sr_1_9?ie=UTF8&qid=1542933696&sr=8-9&keywords=npn+transistor
https://www.aliexpress.com/item/100PCS-LOT-in-line-2N2222A-triode-transistor-NPN-switching-transistors-TO-92-0-6A-30V-NPN/32624547567.html

1x ESP8266 Nodemcu

https://www.amazon.ca/J-DEAL%C2%AE-NodeMCU-Internet-ESP8266-Development/dp/B01F5ALLFM/ref=sr_1_1_sspa
https://www.aliexpress.com/item/1PCS-Wireless-Module-CH340-CP2102-NodeMcu-V3-Lua-WIFI-Internet-of-Things-development-board-based-ESP8266/32918576689.html

1x breadboard

https://www.amazon.ca/Solderless-Prototype-Breadboard-Points-Contacts/dp/B07871PGKX/ref=sr_1_19

1x moisture sensor

(can probably work with any moisture sensor that has an analog out, will probably not be making a digital version, will sooner be testing that it works with capacitive sensors)
https://www.amazon.ca/Chinatera-Hygrometer-Detection-Moisture-arduino/dp/B00SZTZ7D8/ref=sr_1_7
https://www.aliexpress.com/item/Soil-Moisture-Sensor-Hygrometer-Module-for-Arduino-2560-UNO-1280-Free-Shipping-Wholesale/1398732669.html

1x 3.3-6v waterpump
(the vIn on the esp8266 12e unit will deliver 5v 2a out when unit is connected via usb)
https://www.amazon.ca/Arduino-Kits-Small-Water-Available/dp/B07B9FGMY9/ref=sr_1_1

Jumper wires

https://www.amazon.ca/SODIAL-Solderless-Flexible-Breadboard-Arduino/dp/B00KBPQYO0/ref=sr_1_15

https://www.aliexpress.com/item/Free-Shipping-140pcs-in-one-package-convenient-New-Solderless-Flexible-Breadboard-Jumper-wires-Cables-HOT-Sale/664098704.html

Optional: wire strippers, heat shrink tubing, nail polish

SIDENOTE EXPLANATION FOR THE NERDS:
A brief explanation of how I am using NPN transistors.  NPN Transistors have 3 pins, usually (with the flat side facing you) they are the collector, the base and the collector.  The base acts as a kind of gate for whatever is coming into the collector, and the result comes out of the emitter.  In this case I am using it as a switch for powering the Soil Moisture Sensor to conserve energy.  This also helps extend the life of the Soil Moisture Sensor as running electrical current causes oxidation of the sensors and eventually rust.  As you will see the code sets the pin to HIGH when we want the component to be powered.

Similarly we are using a MOSFET transistor for the waterpump, which are similar.  Further description to follow.





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
  
Before moving forward, setup Blynk on your phone and get it to send you an authentication token for your phone. This will be important in a few minutes.
  
 Loading the code onto the ESP:
 1) Download my .ino file and open the file.  
 2) find auth[] and change the value to the authentication token you were emailed
 3) find Blynk.begin and put your wifi router and password into the respective fields
 4) Connect your ESP8266 to your computer via micro usb
 5) Go to "Tools > Port" and select the port the ESP has been assigned to
 6) press the right arrow at the top left to load the code onto your ESP.
 7) if it doesn't work, try holding the 'flash' button as it starts to send
 
 
 
 
 Boomtech Smart irrigation blynk and device setup.
1) install blynk on your phone
2) start a new project, retrieve the Blynk token from your email.
3) plug in your device, if you look in your list of wifi routers you should now see “BoomTech Irrigation” as a choice.  Load that wifi, and in your browser go to http://10.0.0.1
4) enter your wifi information using the menu, and paste your blynk token into the text box below the password field.

Your device is now ready for you to setup your Blynk app.  You can look at the mappings to decide how you want to set up your app, but these are the essentials I recommend.

1) Notification
2) Value Display, input: V5, range 0 - 1023
3) Pump select: V9, range 0-3
4) Pumping Duration: V3, range 0-?? Seconds (up to you, I wouldn’t put it as more than 60 seconds)
5) Checkup timer: V2, range 1-24 hours, feel free to put it more than 24 hours if you don’t want it checking every day.
Default values:
Checkup timer: 12 hours
Pump duration (amount of time pump runs for): 15 seconds
Moisture Threshold: 785
(Note:  if moisture sensor is not connected, pumps will run as if on a timer.)
BLYNK App Receiving Values:
V1 - Threshold value the number the moisture reader must rise above before the pumps are triggered.
V2 - Minutes till next plant checkup
V3 - The current delay of the pump currently being selected
V5 - last sensor reading


BLYNK App Send Values:
V1 - Threshold Value
V2 - Interval sent in hours
V3 - Pumping duration for currently selected 

V8 - initiate checkup
V9 - Set which pump to control (Relates to V3, lowest 0, highest 3)
V10 - Activate low energy mode (CAUTION: Still experimental, devices turns itself off until it is time to check on the soil moisture, then returns to a deep sleep, makes blynk app unresponsive)
 
 
