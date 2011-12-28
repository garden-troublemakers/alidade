#ifndef _IMOVEABLE_HPP_
#define _IMOVEABLE_HPP_

#define FORWARD  0
#define RIGHT 	 1
#define BACKWARD 2
#define LEFT 	 3
#define NOWHERE	 5

#include <stein/Camera.hpp>

using namespace stein;

class IMoveable {
	protected :
		Vector3d m_position;
		Vector3d m_orientation;
		Vector2i m_nextMove;

	public :
		IMoveable(Vector) : m_position(), m_orientation(), m_nextMove() {
		
		}
		virtual ~IMoveable() {}
		/*
		*	Will be called when a move key is pressed.
		*	Resulting vector nextMove is 
		*	nextMove[FORWARD]	= 1; // forward, or -1 backward, or 0 for not moving in any of these directions.
		*	nextMove[RIGHT]		= 1; // To the right, or -1 to the left, or 0 for not moving in any of these directions.
		*
		*/
		virtual void setMovement(unsigned int to, bool add) {
			unsigned int axis = (to == FORWARD || to == BACKWARD) ? FORWARD : RIGHT;
			int moveValue = (to == axis) ? 1 : -1;
			// 1 
			if(add)
				nextMove[axis] = moveValue;
			else
				if(nextMove[axis] == moveValue)
					nextMove[axis] = 0;
			
		}
		// Will be called at each frame.
		virtual void move() = 0;
};

#endif // _IMOVEABLE_HPP_
