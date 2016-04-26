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


}

void GameLayer::onTouchesBegan(std::vector<Touch*> pTouches, Event* event) {

}

void GameLayer::onTouchesEnded(std::vector<Touch*> pTouches, Event* event) {

}

void GameLayer::createGameScreen() {

	Sprite * quickSprite = Sprite::create("blank.png");
	quickSprite->setTextureRect(Rect(0, 0, 100, 100));
	quickSprite->setColor(Color3B(255, 255, 255));

	quickSprite->setPosition(Vec2(_screenSize.width * 0.5, _screenSize.height * 0.5));
	this->addChild(quickSprite);

	/*_gameBatchNode = CCSpriteBatchNode::create("blank.png", 200);
	this->addChild(_gameBatchNode, kMiddleground);

	_terrain = Terrain::create();
	_gameBatchNode->addChild(_terrain, kMiddleground);

	_player = Player::create();
	_gameBatchNode->addChild(_player, kBackground);*/

}
