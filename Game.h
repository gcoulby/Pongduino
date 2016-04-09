// Game.h

#ifndef _GAME_h
#define _GAME_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"

#include "Directions.h"
#include "Player.h"
#include "Ball.h"
#include "Adafruit_SSD1306.h"
extern Player player1;
extern Player ai;
extern Ball ball;
extern Table table;

extern int p1Up;
extern int p1UpiVal;

extern int p1Down;
extern int p1DowniVal;

extern Adafruit_SSD1306 display;

class Game
{
private:
	double _gameSpeed = 1;
	String _name = "Pongduino!";

	void MoveAI()
	{
		if (ball.GetY() < (ai.GetY() + ai.PaddleSize / 2) && ai.GetY() >= 0)
		{
			if (ai.GetY() > 1)
			{
				ai.SetDirection(Directions::UP);
				ai.SetY(ai.GetY() - ai.GetAiSpeed());
			}
		}
		else if (ball.GetY() - 2 > ai.GetY() && (ai.GetY() + ai.PaddleSize) <= display.height())
		{
			if (ai.GetY() < display.height() - 1)
			{
				ai.SetDirection(Directions::DOWN);
				ai.SetY(ai.GetY() + ai.GetAiSpeed());
			}
		}
	}

	void MovePlayer()
	{
		if (p1UpiVal == 0)
		{
			if (player1.GetY() > 1)
			{
				player1.SetY(player1.GetY() - 1);
				player1.SetDirection(Directions::UP);
			}
			digitalWrite(13, HIGH);
		}
		else if (p1DowniVal == 0)
		{
			if (player1.GetY() < display.height() - (player1.PaddleSize + 2))
			{
				player1.SetY(player1.GetY() + 1);
				player1.SetDirection(Directions::DOWN);
			}
			digitalWrite(13, HIGH);
		}
		else
		{
			digitalWrite(13, LOW);
		}
	}

	void CheckWin(int winner)
	{
		//Winning
		if (winner == 1)
		{
			player1.SetScore(player1.GetScore() + 1);
			ball.SetHorizontalDirection(Directions::LEFT);
			ball.Reset();
			ball.SetBallSpeed(_gameSpeed);
			if (player1.GetScore() == 10)
			{
				End("You Win!");
				Reset();
			}
			delay(100);
			loop();
		}
		else if (winner == 2)
		{
			ai.SetScore(ai.GetScore() + 1);
			ball.SetHorizontalDirection(Directions::LEFT);
			ball.Reset();
			ball.SetBallSpeed(_gameSpeed);
			if (ai.GetScore() == 10)
			{
				End("You Lose!");
				Reset();
			}
			delay(100);
			loop();
		}
	}
	void SetSpeed(double gameSpeed)
	{
		_gameSpeed = gameSpeed;
		ai.SetAiSpeed(gameSpeed);
		ball.SetBallSpeed(gameSpeed);
	}

public:

	double GetSpeed() { return _gameSpeed; }

	void Draw()
	{
		display.clearDisplay();
		table.Draw();
		player1.Draw();
		ai.Draw();
		ball.Draw();
		display.display();
	}

	void MoveActors()
	{
		//Read Input
		p1UpiVal = digitalRead(p1Up);
		p1DowniVal = digitalRead(p1Down);

		int winner = ball.Move();
		CheckWin(winner);
		MoveAI();
		MovePlayer();
	}

	void End(String message)
	{
		display.clearDisplay();
		display.setTextSize(2);
		display.setTextColor(WHITE);
		display.setCursor(12, 8);
		display.println(message);
		display.display();
		delay(2000);
	}

	void ShowSplash()
	{
		display.clearDisplay();
		display.setTextSize(2);
		display.setTextColor(WHITE);
		display.setCursor(8, 8);
		display.println(_name);
		display.display();
		delay(3000);
	}

	void SetGameSpeed()
	{
		display.clearDisplay();
		display.setTextSize(1);
		display.setTextColor(WHITE);
		display.setCursor(2, 2);
		display.println("Choose Game Speed:");
		display.println();
		display.setTextSize(2);
		display.setCursor(4, 15);
		display.println("1        2");
		display.display();
		
		p1UpiVal = digitalRead(p1Up);
		p1DowniVal = digitalRead(p1Down);

		if (p1UpiVal == 0)
		{
			SetSpeed(1.3);
			return;
		}
		else if (p1DowniVal == 0)
		{
			SetSpeed(1.8);
			return;
		}
		else
			SetGameSpeed();
	}

	void WaitingScreen()
	{
		display.clearDisplay();
		display.setTextSize(1);
		display.setTextColor(WHITE);
		display.setCursor(2, 15);
		display.println("Press button to Start");
		display.display();
		
		p1UpiVal = digitalRead(p1Up);
		p1DowniVal = digitalRead(p1Down);

		if (p1UpiVal == 0)
		{
			return;
		}
		else if (p1DowniVal == 0)
		{
			return;
		}
		else
			WaitingScreen();
	}
	void(*Reset) (void) = 0; // Resets the Program
};

#else
	#include "WProgram.h"
#endif


#endif

