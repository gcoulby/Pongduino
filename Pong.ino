/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x32 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/


#include "Table.h"
#include "Directions.h"
#include "Player.h"
#include "Ball.h"
#include "Game.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_SSD1306.h"
#include <math.h>


#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

Game game;
Player player1(0, ((display.width() / 2) - 10));
Player ai(display.width() - 1, ((display.width() / 2) + 6), game.GetSpeed());
Ball ball(display.width() / 2, display.height() / 2, game.GetSpeed());

Table table;

int p1Up = 1;
int p1UpiVal;

int p1Down = 2;
int p1DowniVal;

void setup()   
{   
	Serial.begin(9600);

	pinMode(1, INPUT);
	pinMode(2, INPUT);
	pinMode(13, OUTPUT);

	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  
	game.ShowSplash();

	//game.SetGameSpeed();
	
	game.WaitingScreen();

	display.clearDisplay();
}



void loop() 
{
	p1UpiVal = digitalRead(p1Up);
	p1DowniVal = digitalRead(p1Down);

	if (p1UpiVal == 0 && p1DowniVal == 0)
	{
		delay(2000);
		p1UpiVal = digitalRead(p1Up);
		p1DowniVal = digitalRead(p1Down);
		if (p1UpiVal == 0 && p1DowniVal == 0)
		{
			game.Reset();
		}
	}
	game.MoveActors();
	game.Draw();
}