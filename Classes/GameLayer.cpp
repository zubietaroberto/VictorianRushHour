#include "GameLayer.hpp"
#include "SimpleAudioEngine.h"


using namespace cocos2d;
using namespace CocosDenshion;

GameLayer::~GameLayer() {

}

Scene* GameLayer::scene()
{
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();

	// 'layer' is an autorelease object
	GameLayer *layer = GameLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init()) {
		return false;
	}

	//get screen size
	_screenSize = Director::getInstance()->getWinSize();

	createGameScreen();

	resetGame();

	// Build Multitouch event Listener
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(GameLayer::onTouchesBegan, this);
	listener->onTouchesEnded = CC_CALLBACK_2(GameLayer::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//create main loop
	this->schedule(schedule_selector(GameLayer::update));

	return true;
}

void GameLayer::resetGame() {

	_speedIncreaseInterval = 15;
	_speedIncreaseTimer = 0;

	_running = true;
}


void GameLayer::update(float dt) {

	if (!_running) return;

	if (_player->getPositionY() < -_player->getHeight() ||
			_player->getPositionX() < -_player->getWidth()*0.5f){

				_running=false;
				
		}

	_player->update(dt);
	_terrain->move(_player->getVector().x);

	if (_player->getState() != kPlayerDying){
		_terrain->checkCollision(_player);
	}
	_player->place();

	if (_player->getNextPosition().y > _screenSize.height * 0.6f){
		_gameBatchNode->setPositionY(
			(_screenSize.height * 0.6f - _player->getNextPosition().y) * 0.8f);
	} else {
		_gameBatchNode->setPositionY(0);
	}

	if(_terrain->getStartTerrain() && _player->getVector().x > 0){
		_speedIncreaseTimer += dt;
		if(_speedIncreaseTimer > _speedIncreaseInterval){
			_speedIncreaseTimer = 0;
			_player->setMaxSpeed(_player->getMaxSpeed() + 4);
		}
	}
}

void GameLayer::onTouchesBegan(std::vector<Touch*> pTouches, Event* event) {

	if (pTouches.size() < 1) return;
	Touch* touch = pTouches.front();

	if(!_running){
		if(_player->getState() == kPlayerDying){
			_terrain->reset();
			_player->reset();
			resetGame();
		}

		return;
	}

	if (touch){
		if(!_terrain->getStartTerrain()){
			_terrain->setStartTerrain(true);
			return;
		}

		if (_player->getState() == kPlayerFalling){
			_player->setFloating(_player->getFloating()? false : true);
		} else {
			if (_player->getState() != kPlayerDying) _player->setJumping(true);
			return;
		}
	}
}

void GameLayer::onTouchesEnded(std::vector<Touch*> pTouches, Event* event) {
	_player->setJumping(false);
}

void GameLayer::createGameScreen() {

	_gameBatchNode = SpriteBatchNode::create("blank.png", 200);
	this->addChild(_gameBatchNode, kMiddleground);

	_terrain = CustomTerrain::create();
	_gameBatchNode->addChild(_terrain, kMiddleground);

	_player = Player::create();
	_gameBatchNode->addChild(_player, kBackground);

}
