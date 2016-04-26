#include "GameLayer.hpp"
#include "SimpleAudioEngine.h"


using namespace cocos2d;
using namespace CocosDenshion;

GameLayer::~GameLayer() {

}

CCScene* GameLayer::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

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
	if (!CCLayer::init()) {
		return false;
	}

	//get screen size
	_screenSize = CCDirector::sharedDirector()->getWinSize();

	createGameScreen();

	resetGame();

	//listen for touches
	this->setTouchEnabled(true);

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

void GameLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* event) {

}

void GameLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* event) {

}

void GameLayer::createGameScreen() {

	CCSprite * quickSprite = CCSprite::create("blank.png");
	quickSprite->setTextureRect(CCRectMake(0, 0, 100, 100));
	quickSprite->setColor(ccc3(255, 255, 255));

	quickSprite->setPosition(ccp(_screenSize.width * 0.5, _screenSize.height * 0.5));
	this->addChild(quickSprite);

	/*_gameBatchNode = CCSpriteBatchNode::create("blank.png", 200);
	this->addChild(_gameBatchNode, kMiddleground);

	_terrain = Terrain::create();
	_gameBatchNode->addChild(_terrain, kMiddleground);

	_player = Player::create();
	_gameBatchNode->addChild(_player, kBackground);*/

}