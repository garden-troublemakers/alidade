#ifndef _IMOVEABLE_HPP_
#define _IMOVEABLE_HPP_

#define NOWHERE	0
#define UP 		1
#define DOWN 	2
#define LEFT 	3
#define RIGHT 	4

class IMoveable {
	public :
		virtual ~IMoveable() {}
		// Will be called when a move key is pressed
		// @TODO : method can be defined here and then the interface IMoveable should be Moveable (not virtual pure)
		virtual void setMovement(unsigned int) = 0;
		// Will be called at each frame.
		virtual void move() = 0;
};

#endif // _IMOVEABLE_HPP_
