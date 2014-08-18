#include "SplashScene.h" 
#include "MainMenuScene.h"
#include "CommonUtils.h"
USING_NS_CC;

using namespace  CocosDenshion;
Scene* SplashScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SplashScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
	auto sprite = Sprite::create("John_H_Conway_2001.png");
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(sprite, 0);
	FadeOut* mFade =  FadeOut::create(3.0f);
	sprite->runAction(mFade);
	scheduleOnce(schedule_selector(SplashScene::goGameScene) , 3.0f);

	CommonUtils::preloadAudioResources();

	return true;
}


 void SplashScene::goGameScene(float t)
 {
		auto scene = MainMenuScene::createScene();
		 Director::getInstance()->replaceScene(scene);
 }