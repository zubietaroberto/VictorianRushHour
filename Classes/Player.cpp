#include "Player.hpp"

#define ACCELERATION 0.5

Player::~Player() {

}

Player::Player() {
	_screenSize = Director::getInstance()->getWinSize();
	_floatingTimerMax = 2;
	_floatingTimer = 0;
	_speed = PLAYER_INITIAL_SPEED;
	_maxSpeed = PLAYER_INITIAL_SPEED;
	_floating = false;
	_nextPosition = Vec2(0, 0);
	_nextPosition.y = _screenSize.height * 0.6f;
	_state = kPlayerMoving;
	_jumping = false;
	_hasFloated = false;
}

Player * Player::create() {

	Player * player = new Player();
	if (player && player->initWithFile("blank.png")) {
		player->autorelease();
		player->setSize();
		player->initPlayer();
		return player;
	}
	CC_SAFE_DELETE(player);
	return NULL;
}


void Player::update(float dt) {
	if (_speed + ACCELERATION <= _maxSpeed){
		_speed += ACCELERATION;
	} else {
		_speed = _maxSpeed;
	}

	_vector.x = _speed;

	switch(_state){

		case kPlayerMoving:
			_vector.y -= FORCE_GRAVITY;
			if (_hasFloated) _hasFloated = false;
			break;

		case kPlayerFalling:
			if(_floating){
				_vector.y -= FLOATING_GRAVITY;
				_vector.x *= FLOATING_FRICTION;
			} else {
				_vector.y -= FORCE_GRAVITY;
				_vector.x *= AIR_FRICTION;
			}
			break;

		case kPlayerDying:
			_vector.y -= FORCE_GRAVITY;
			_vector.x = -_speed;
			this->setPositionX(this->getPositionX() + _vector.x);
			break;
	}

	if (_jumping){
		_state = kPlayerFalling;
		_vector.y += PLAYER_JUMP * 0.25f;
		if (_vector.y > PLAYER_JUMP){
			_jumping = false;
		}

		if (_vector.y < -TERMINAL_VELOCITY){
			_vector.y = -TERMINAL_VELOCITY;
		}

		_nextPosition.y = this->getPositionY() + _vector.y;

		if (_floating){
			_floatingTimer += dt;
			if (_floatingTimer > _floatingTimerMax){
				_floatingTimer = 0;
				this->setFloating(false);
			}
		}
	}
}

void Player::reset() {

	_speed = PLAYER_INITIAL_SPEED;
	_maxSpeed = PLAYER_INITIAL_SPEED;
	_vector = Vec2(0, 0);
	this->setFloating(false);
	this->setRotation(0);
	_nextPosition.y = _screenSize.height * 0.6f;
	this->setPosition(Vec2(_screenSize.width * 0.2f, _nextPosition.y));
	_state = kPlayerMoving;
	_jumping = false;
	_hasFloated = false;
}

void Player::setFloating(bool value) {

	if (_floating == value) return;

	if (value && _hasFloated) return;

	_floating = value;

	if (value){
		_hasFloated = true;
		_vector.y += PLAYER_JUMP * 0.5f;
	}

}

void Player::initPlayer() {
	this->setAnchorPoint(Vec2(0.5f, 1.0f));
	this->setPosition(Vec2(_screenSize.width*0.2f, _nextPosition.y));

	_height = 228;
	_width = 180;
	this->setTextureRect(Rect(0, 0, _width, _height));
	this->setColor(Color3B(255, 255, 255));
}
