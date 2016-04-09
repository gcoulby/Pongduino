// Player.h

#ifndef _PLAYER_h
#define _PLAYER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"

#include "Adafruit_SSD1306.h"
extern Adafruit_SSD1306 display;

class Player
{
	private:
		int _xPosition;
		double _yPosition = 10;
		int _scorePosition = 0;
		int _score = 0;
		double _aiSpeed;
		int _direction;
		
		void DrawPaddle()
		{
			display.drawLine(_xPosition, _yPosition, _xPosition, _yPosition + PaddleSize, WHITE);
		}

		void DrawScore()
		{
			display.setTextSize(1);
			display.setTextColor(WHITE);
			display.setCursor(_scorePosition, 4);
			display.println(_score);
		}

	public:
		int PaddleSize = 8;

		Player(int x, int scorePosition, double aiSpeed = 0)
		{
			_xPosition = x;
			_scorePosition = scorePosition;
			_aiSpeed = aiSpeed;
		}

		int GetDirection() { return _direction; }
		void SetDirection(int d) { _direction = d; }

		double GetAiSpeed() { return _aiSpeed; }
		void SetAiSpeed(double aiSpeed) { _aiSpeed = aiSpeed / 1.43125; }

		int GetScore() { return _score; }
		void SetScore(int s) { _score = s; }

		int GetX() { return _xPosition; }
		void SetX(int x) { _xPosition = x; }

		double GetY() { return _yPosition; }
		void SetY(double y) { _yPosition = y; }

		void Draw()
		{
			DrawPaddle();
			DrawScore();
		}

};

#else
	#include "WProgram.h"
#endif

#endif

