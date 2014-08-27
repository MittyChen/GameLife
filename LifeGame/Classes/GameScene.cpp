#include "GameScene.h"
#include "CommonUtils.h"
#include "ConstUITags.h"
#include "MainMenuScene.h"
USING_NS_CC;
using namespace  ui;
//LifeGameGod* GameScene::god = NULL;
Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	 
//    god = NULL;
//    if(!god)
    


	auto startButon = LabelTTF::create("START", "epson1", 50 * visibleSize.height/480);

	auto  startButonLabel = MenuItemLabel::create(
		startButon,
		CC_CALLBACK_1(GameScene::menuTouchCallback, this));
	startButonLabel->setAnchorPoint(Vec2(0,0));
	startButonLabel->setTag(UI_WIDGET_TAG::GAME_SCENE_START);
	startButonLabel->setColor(Color3B(0.0f,128.0f,255.0f));
	startButonLabel->setPosition(Vec2(origin.x + visibleSize.height * 1.1 ,origin.y +visibleSize.height*4/5 ));
	
	auto pauseButton = LabelTTF::create("PAUSE", "epson1",50* visibleSize.height/480);
	auto pauseButtonLabel = MenuItemLabel::create(
		pauseButton,
		CC_CALLBACK_1(GameScene::menuTouchCallback, this));
	pauseButtonLabel->setAnchorPoint(Vec2(0,0));
	pauseButtonLabel->setColor(Color3B(0.0f,128.0f,255.0f));
	pauseButtonLabel->setPosition(Vec2(startButonLabel->getPosition().x, startButonLabel->getPosition().y - 2*pauseButtonLabel->getContentSize().height ));
	 pauseButtonLabel->setTag(UI_WIDGET_TAG::GAME_SCENE_PAUSE);
		 
		auto resumeButton = LabelTTF::create("RESUME", "epson1", 50* visibleSize.height/480);
		auto resumeButtonLabel = MenuItemLabel::create(
			resumeButton,
			CC_CALLBACK_1(GameScene::menuTouchCallback, this));
		resumeButtonLabel->setAnchorPoint(Vec2(0,0));
		resumeButtonLabel->setColor(Color3B(0.0f,128.0f,255.0f));
		resumeButtonLabel->setPosition(Vec2(pauseButtonLabel->getPosition().x, pauseButtonLabel->getPosition().y - 2*resumeButtonLabel->getContentSize().height ));
		resumeButtonLabel->setTag(UI_WIDGET_TAG::GAME_SCENE_RESUME);


		auto resetButton = LabelTTF::create("RESET", "epson1", 50* visibleSize.height/480);
		auto resetButtonLabel = MenuItemLabel::create(
			resetButton,
			CC_CALLBACK_1(GameScene::menuTouchCallback, this));
		resetButtonLabel->setAnchorPoint(Vec2(0,0));
		resetButtonLabel->setColor(Color3B(0.0f,128.0f,255.0f));
		resetButtonLabel->setPosition(Vec2(resumeButtonLabel->getPosition().x, resumeButtonLabel->getPosition().y - 2*resetButtonLabel->getContentSize().height ));
		resetButtonLabel->setTag(UI_WIDGET_TAG::GAME_SCENE_RESET);
		 

		auto backButton = LabelTTF::create("GO BACK", "epson1", 40* visibleSize.height/480);
		auto backButtonLabel = MenuItemLabel::create(
			backButton,
			CC_CALLBACK_1(GameScene::menuTouchCallback, this));
		backButtonLabel->setColor(Color3B(255.0f,255.0f,255.0f));
		backButtonLabel->setPosition(Vec2(origin.x + visibleSize.width - backButtonLabel->getContentSize().width/2 ,
			origin.y + backButtonLabel->getContentSize().height/2));
		backButtonLabel->setTag(UI_WIDGET_TAG::GAME_SCENE_GO_BACK);


        menu = Menu::create(startButonLabel, pauseButtonLabel,resumeButtonLabel,resetButtonLabel,backButtonLabel,NULL);
		menu->setPosition(Vec2(0,0));
		menu->setTag(UI_WIDGET_TAG::GAME_MENU);
		this->addChild(menu, 1);


	{//touch event
		auto event =EventListenerTouchOneByOne::create();
		event->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
		event->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled,this);
		event->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded,this);
		event->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved,this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(event,this);
	}
    
    {
        god =LifeGameGod::create();
        this->addChild(god);
    }
    
    scheduleUpdate();
    return true;
}



bool GameScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	CCLOG("GameScene::onTouchBegan");
	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event)
{
	
}

void GameScene::onTouchEnded(Touch *touch, Event *unused_event)
{

}

void GameScene::onTouchCancelled(Touch *touch, Event *unused_event)
{

}

void GameScene::menuTouchCallback( cocos2d::Ref* pSender )
{
	auto mLabel = (MenuItemLabel*) pSender;
	int tag = mLabel->getTag();

	switch (tag)
	{
		case UI_WIDGET_TAG::GAME_SCENE_START:
			god->gameStart();
			break;
		case UI_WIDGET_TAG::GAME_SCENE_PAUSE:
			god->gamePause();
			break;
		case UI_WIDGET_TAG::GAME_SCENE_RESUME:
			god->gameResume();
			break;
		case UI_WIDGET_TAG::GAME_SCENE_RESET:
			god->gameReset();
			break;
		case UI_WIDGET_TAG::GAME_SCENE_GO_BACK:
			{
				auto scene = MainMenuScene::createScene();
				Director::getInstance()->replaceScene(scene);
				break;
			}

	default:
		break;
	}

}

LifeGameGod * GameScene::getGodHandler()
{
    return god;
}

void GameScene::update(float delta)
{
}
