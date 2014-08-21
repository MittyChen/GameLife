#include "SplashScene.h" 
#include "MainMenuScene.h"
#include "CommonUtils.h"
#include "ConstUITags.h"
#include "LifeGameGod.h" 
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


	auto mlabel = LabelTTF::create("Do Not Touch Me", "epson1", 60);
	auto mtextLabel = MenuItemLabel::create(
		mlabel,
		CC_CALLBACK_1(SplashScene::touchWelcomeButton, this));


	mtextLabel->setColor(Color3B(0.0f,128.0f,255.0f));
	mtextLabel->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	mtextLabel->setTag(UI_WIDGET_TAG::WELCOME_LABEL);

	 auto menu = Menu::create( mtextLabel,NULL);
	 menu->setPosition(Vec2::ZERO);
	 menu->setTag(UI_WIDGET_TAG::WELCOME_MENU);
	 this->addChild(menu, 1);


	 FadeOut* mFade =  FadeOut::create(3.0f);
	 mtextLabel->runAction(mFade);
	 scheduleOnce(schedule_selector(SplashScene::goGameScene) , 3.0f);
	 
	/*auto sprite = Sprite::create("John_H_Conway_2001.png");
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(sprite, 0);
	FadeOut* mFade =  FadeOut::create(3.0f);
	sprite->runAction(mFade);
	scheduleOnce(schedule_selector(SplashScene::goGameScene) , 3.0f);*/


	CommonUtils::preloadAudioResources();

	return true;
}


 void SplashScene::goGameScene(float t)
 {
		auto scene = MainMenuScene::createScene();
		 Director::getInstance()->replaceScene(scene);
 }

 void SplashScene::touchWelcomeButton( cocos2d::Ref *pSender )
 {
	 auto mlabel = (MenuItemLabel*)(this->getChildByTag(UI_WIDGET_TAG::WELCOME_MENU)->getChildByTag(WELCOME_LABEL));
	 mlabel->setScale(5.0f);
	 mlabel->setString("@  @\n ### ");
 }
