// Directions.h

#ifndef _DIRECTIONS_h
#define _DIRECTIONS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	
class Directions
{
	public:
		enum Direction
		{
			UP, DOWN, LEFT, RIGHT
		};
};
#else
	#include "WProgram.h"
#endif


#endif

