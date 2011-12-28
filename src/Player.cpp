#include "Player.hpp"

Player::Player() : m_movement(), camera() {
	m_life = 100;
}

Player::~Player() {

}

void Player::move() {
	MoveableCamera::move();
}

bool Player::shootPortal(unsigned int type) {
	return true;
}

unsigned int Player::getLife() {
	return m_life;
}
