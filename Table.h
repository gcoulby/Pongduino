// Table.h

#ifndef _TABLE_h
#define _TABLE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"

#include "Adafruit_SSD1306.h"
extern Adafruit_SSD1306 display;

class Table
{
	private:
		void DrawTopLine()
		{
			display.drawLine(0, 0, display.width() - 1, 0, WHITE);
		}
		void DrawBottomLine()
		{
			display.drawLine(0, display.height() - 1, display.width() - 1, display.height() - 1, WHITE);
		}
		void DrawNet()
		{
			display.drawLine(display.width() / 2, 0, display.width() / 2, display.height() - 1, WHITE);
		}

	public:
		void Draw()
		{
			DrawTopLine();
			DrawBottomLine();
			DrawNet();
		}
};

#else
	#include "WProgram.h"
#endif


#endif

