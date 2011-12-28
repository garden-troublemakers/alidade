#include "Player.hpp"

using namespace std;
using namespace stein;

Player::Player(const Application * const application) : MoveableCamera(PLAYER_HEIGHT, application), m_movement() {
	m_life = 100;
}

Player::~Player() {

}

void Player::move() {
	MoveableCamera::move();
}

bool Player::shootPortal(size_t type) {
	return true;
}

size_t Player::getLife() {
	return m_life;
}
