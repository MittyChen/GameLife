//
//  LoadingScene.cpp
//  LifeGame
//
//  Created by hack on 14-8-25.
//
//

#include "LoadingScene.h"
#include "GameScene.h"
#include "ConstCells.h"

bool LoadingScene::isReady = false;
float LoadingScene::progressVal = 0.0f;

GameScene* LoadingScene::layer = NULL;

Scene* LoadingScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
    
	// 'layer' is an autorelease object
	auto layer = LoadingScene::create();
    
	// add layer as a child to scene
	scene->addChild(layer);
    
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LoadingScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}
    
    isReady = false;
    progressVal = 0.0f;
    
    
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
	auto mlabel = LabelTTF::create("Loading", "epson1", 20 * visibleSize.height / 480);
    mlabel->setPosition(Vec2(origin.x + visibleSize.width/2,   origin.y + visibleSize.height/2 +  mlabel->getContentSize().height));
    this->addChild(mlabel);
    
    auto mcommalabel = LabelTTF::create("...", "epson1", 20 * visibleSize.height / 480);
    mcommalabel->setPosition(Vec2(mlabel->getPosition().x + mlabel->getContentSize().width,  mlabel->getPosition().y));
    this->addChild(mcommalabel);
    
    mcommalabel->runAction( CCRepeatForever::create(Sequence::create(FadeOut::create(0.5f),FadeIn::create(0.5f),NULL)));
    
    
    gamescene = Scene::create();
    layer = GameScene::create();
    gamescene->addChild(layer);
    
    
    std::thread t1(&LoadingScene::thread_Create_GameScene,this);
    t1.detach();
    
    scheduleUpdate();
    
	return true;
}

void LoadingScene::update(float delta)
{
    if(isReady)
    { //资源加载完毕 切换界面
        goScene(GAME_SCENE);
        isReady = false;
    }
}

void LoadingScene::setProgress(float progress)
{
    progressVal = progress;
}
void LoadingScene::setIsReady(bool val)
{
    isReady = val;
}
//资源加载线程
void* LoadingScene::thread_Create_GameScene(void *arg)
{
    CCLOG("thread started...");
    isReady = true;
    return NULL;
}
