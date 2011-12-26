#include "Player.hpp"

Player::Player() : m_movement(), camera() {
	m_life = 100;
}

Player::~Player() {

}

void Player::move() {
	// cf code FPS
	// update camera
}

void Player::setMovement(unsigned int to) {
	
}

bool Player::shootPortal(unsigned int type) {
	return true;
}

unsigned int Player::getLife() {
	return m_life;
}
