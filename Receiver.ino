/*
 * *****************************************************************
 * *                                                               *
 * *                         include Zone                          *
 * *                                                               *
 * *****************************************************************
 */
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1331.h"
#include <SPI.h>
#include <LoRa.h>



/*
 * *****************************************************************
 * *                                                               *
 * *                          define Zone                          *
 * *                                                               *
 * *****************************************************************
 */

 //OLED Setting
#define sclk  7
#define mosi  6
#define cs    3
#define rst   5
#define dc    4

//LoRa connect Setting
#define NSS_PIN    10
#define NRESET_PIN 9
#define DIO0_PIN   2

#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

char text;
/*
 * *****************************************************************
 * *                                                               *
 * *                        variable Zone                          *
 * *                                                               *
 * *****************************************************************
 */

 Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, mosi, sclk, rst);

  /*
 * *****************************************************************
 * *                                                               *
 * *                          void Zone                            *
 * *                                                               *
 * *****************************************************************
 */

 void setup() {
  Serial.begin(9600);

  //************************* LoRa Setup **************************
  
  while (!Serial);

  Serial.println("LoRa Node - Receiver");

  LoRa.setPins(NSS_PIN, NRESET_PIN, DIO0_PIN);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while(1);
  }
  LoRa.setTimeout(100);

  
  //************************ OLED Setup***************************
  
  display.fillScreen(BLACK); //set background to black
  display.begin();

  //**************************************************************

  
 }//end void setup

void loop() {

  if (LoRa.parsePacket() > 0) {
    String text = LoRa.readString();
    display.fillScreen(BLACK);
    Serial.print("--->");
    Serial.println(text);
    Serial.print(LoRa.packetRssi());
     
    display.setCursor(1,0); //set position to Y=1, X=1
    display.print("Receiver Rx");

    display.fillScreen(BLACK);
    display.setCursor(1,10);
    display.print("TEXT Rx > ");
    display.print(text);
    display.setCursor(1,20);
    display.print("RSSI ---> ");
    display.print(LoRa.packetRssi());
  }
}//end void loop

