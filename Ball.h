// Ball.h

#ifndef _BALL_h
#define _BALL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"

#include "Directions.h"
#include "Player.h"
#include "Adafruit_SSD1306.h"
extern Player player1;
extern Player ai;
extern Adafruit_SSD1306 display;

class Ball
{
private:
	double _xPosition;
	double _yPosition;
	int _initX;
	int _initY;
	double _ballSpeed;
	int _ballSize = 2;
	int _verticalDirection = Directions::UP;
	int _horizontalDirection = Directions::LEFT;

public:
	Ball(int x, int y, int ballSpeed)
	{
		_xPosition = x;
		_initX = x;
		_yPosition = y;
		_initY = y;
		_ballSpeed = ballSpeed;
	}

	double GetBallSpeed() { return _ballSpeed; }
	void SetBallSpeed(double s) { _ballSpeed = s; }

	double GetX() { return _xPosition; }
	void SetX(double x) { _xPosition = x; }

	double GetY() { return _yPosition; }
	void SetY(double y) { _yPosition = y; }

	int GetBallSize() { return _ballSize; }

	int GetVerticalDirection() { return _verticalDirection; }
	void SetVerticalDirection(int d) { _verticalDirection = d; }

	int GetHorizontalDirection() { return _horizontalDirection; }
	void SetHorizontalDirection(int d) { _horizontalDirection = d; }

	void Reset()
	{
		SetX(_initX);
		SetY(_initY);
	}

	void Draw()
	{
		display.fillRect(_xPosition, _yPosition, _ballSize, _ballSize, WHITE);
	}

	int Move()
	{
		if (_yPosition > 0 && _yPosition < display.height())
		{
			if (GetVerticalDirection() == Directions::UP)
			{
				_yPosition = (_yPosition - (_ballSpeed - 0.5) > 1) ? _yPosition - (_ballSpeed - 0.5) : 1;
				if (_yPosition < 3)
					SetVerticalDirection(Directions::DOWN);
			}
			else
			{
				_yPosition = (_yPosition + _ballSpeed < display.height() - 1) ? _yPosition + _ballSpeed : display.height() - 1;
				if (_yPosition > display.height() - 3)
					SetVerticalDirection(Directions::UP);
			}
		}

		if (_xPosition >= 0 && _xPosition <= display.width())
		{
			if (GetHorizontalDirection() == Directions::LEFT)
			{
				_xPosition = _xPosition - (_ballSpeed + 0.5);

				if (_xPosition < 2 && (_yPosition >(player1.GetY() - 2) && _yPosition < (player1.GetY() + player1.PaddleSize) + 1))
				{
					SetHorizontalDirection(Directions::RIGHT);
					ChangeBallSpeed(player1);
				}
				else if (_xPosition < 1 && !(_yPosition >(player1.GetY() - 2) && _yPosition < (player1.GetY() + player1.PaddleSize) + 1))
				{
					delay(200);
					return 2;
				}
			}
			else
			{
				_xPosition = _xPosition + (_ballSpeed + 0.5);

				if (_xPosition > display.width() - 4 && (_yPosition > (ai.GetY() - 2) && _yPosition < (ai.GetY() + ai.PaddleSize) + 1))
				{
					SetHorizontalDirection(Directions::LEFT);
				}
				else if (_xPosition > display.width() - 3 && !(_yPosition > (ai.GetY() - 2) && _yPosition < (ai.GetY() + ai.PaddleSize) + 1))
				{
					delay(200);
					return 1;
				}
			}
		}

		return 0;
	}

	void ChangeBallSpeed(Player p)
	{
		if (p.GetDirection() == _verticalDirection)
		{
			_ballSpeed += 0.2;
		}
		else
		{
			if(_ballSpeed > 0.8)
				_ballSpeed -= 0.2;
		}
	}

};



#else
	#include "WProgram.h"
#endif


#endif

