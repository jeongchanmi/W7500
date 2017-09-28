/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest
  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.
    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Social networks:            http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app
  Blynk library is licensed under MIT license
  This example code is in public domain.
 *************************************************************
  This example shows how to use Arduino.org Ethernet Shield 2 (W5500)
  to connect your project to Blynk.
  NOTE: You may have to install Arduino.ORG IDE to get it working:
          http://www.arduino.org/software
        Pins 10, 11, 12 and 13 are reserved for Ethernet module.
        DON'T use them in your sketch directly!
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include "mbed.h"
#include <SPI.h>
#include "EthernetInterface.h"
#include <BlynkSimpleEthernet2.h>


EthernetInterface eth0;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "f6e02fba337e45f19f9c51567323ea8d";




int main(void) {
    printf("Hello\r\n");
    uint8_t mac_addr[6] = {0x00, 0x08, 0xDC, 0xff, 0xff, 0x25};   
    eth0.init(mac_addr);
    eth0.connect();
    
    Blynk.begin(auth);
    
    printf("Blynk init!\r\n");
    while(1){
        Blynk.run();
    }    
}