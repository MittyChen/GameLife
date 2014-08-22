#include "MainMenuScene.h"
#include "GameScene.h"
#include "CommonUtils.h"
#include "ConstUITags.h"

USING_NS_CC;
using namespace CocosDenshion;
Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    } 

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	bool audioIsOn = UserDefault::getInstance()->getBoolForKey("AUDIO_ON");
	bool audioEffectIsOn = UserDefault::getInstance()->getBoolForKey("AUDIO_EFFECT_ON");


	auto titleText = LabelTTF::create("LIFE GAME", "epson1", 80 * visibleSize.height / 480);

	auto  titleTextLabel = MenuItemLabel::create(
		titleText,
		CC_CALLBACK_1(MainMenuScene::touchAudioButton, this));
	
	titleTextLabel->setTag(UI_WIDGET_TAG::AUDIO_TITLE_LABEL);
	titleTextLabel->setColor(Color3B(0.0f,128.0f,255.0f));
	titleTextLabel->setPosition(Vec2(origin.x + visibleSize.width/2,   origin.y + visibleSize.height/2 +  titleTextLabel->getContentSize().height));
	//this->addChild(titleText, 1);


	/*auto mTopLayer = LayerColor::create(ccc4(100,100,255,255));
			mTopLayer->setZOrder(-1);
			this->addChild(mTopLayer);*/
	
	auto startText = LabelTTF::create("Touch Screen", "epson1", 30* visibleSize.height / 480);
	auto startTextLabel = MenuItemLabel::create(
		startText,
		CC_CALLBACK_1(MainMenuScene::touchAudioButton, this));

	startTextLabel->setColor(Color3B(0.0f,128.0f,255.0f));
	startTextLabel->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height*1/4 ));
	 startTextLabel->setTag(UI_WIDGET_TAG::AUDIO_TOUCH_START);
	startTextLabel->runAction( CCRepeatForever::create(Sequence::create(FadeOut::create(1.0f),FadeIn::create(1.0f),NULL)));

		const char* onOrCloseStr = "";
		if(audioIsOn)
		{
			onOrCloseStr = "Audio:ON";
		}else{
			onOrCloseStr = "Audio:OFF";
		}
		auto audioText = LabelTTF::create(onOrCloseStr, "epson1", 30* visibleSize.height / 480);
		auto audioTextLabel = MenuItemLabel::create(
			audioText,
			CC_CALLBACK_1(MainMenuScene::touchAudioButton, this));

		audioTextLabel->setColor(Color3B(0.0f,128.0f,255.0f));
		audioTextLabel->setAnchorPoint(Vec2(0.5f,0.5f));
		audioTextLabel->setPosition(Vec2(startTextLabel->getPosition().x,   startTextLabel->getPosition().y + 2*audioTextLabel->getContentSize().height));
		audioTextLabel->setTag(UI_WIDGET_TAG::AUDIO_BG_BUTTON);





		const char* onOrCloseEffectStr = "";
		if(audioEffectIsOn)
		{
			onOrCloseEffectStr = "Effect:ON";
		}else{
			onOrCloseEffectStr = "Effect:OFF";
		}
		auto audioEffectText = LabelTTF::create(onOrCloseEffectStr, "epson1", 30* visibleSize.height / 480);
		auto audioEffectLabel = MenuItemLabel::create(
			audioEffectText,
			CC_CALLBACK_1(MainMenuScene::touchAudioEffeectButton, this));
		audioEffectLabel->setColor(Color3B(0.0f,128.0f,255.0f));
		audioEffectLabel->setAnchorPoint(Vec2(0.5f,0.5f));
		audioEffectLabel->setPosition(Vec2(audioTextLabel->getPosition().x,   audioTextLabel->getPosition().y + 2*audioEffectLabel->getContentSize().height));
		audioEffectLabel->setTag(UI_WIDGET_TAG::AUDIO_EFFECT_BUTTON);
	
		CommonUtils::initNightShaders();
		CommonUtils::setNightGLprogram(audioEffectLabel);
		auto menu = Menu::create(startTextLabel, titleTextLabel,audioTextLabel,audioEffectLabel,NULL);
		menu->setPosition(Vec2(0,origin.y + visibleSize.height/2));
		menu->setTag(UI_WIDGET_TAG::MENU_AUDIOS);
		this->addChild(menu, 1);
		menu->runAction(MoveTo::create(4.0f,Vec2::ZERO));
		/*menu->runAction(CCRepeatForever::create((Sequence::create(MoveTo::create(1.0f,Vec2(menu->getPosition().x+10 , menu->getPosition().y))
		,MoveTo::create(1.0f,Vec2(menu->getPosition().x-10 , menu->getPosition().y)),NULL))));*/

	//Sound Block
	{
		if(audioIsOn)
		{
			CommonUtils::playBackgrondMusic();
		} 
	}


	{//touch event
		auto event =EventListenerTouchOneByOne::create();
		event->onTouchBegan = CC_CALLBACK_2(MainMenuScene::onTouchBegan,this);
		event->onTouchCancelled = CC_CALLBACK_2(MainMenuScene::onTouchCancelled,this);
		event->onTouchEnded = CC_CALLBACK_2(MainMenuScene::onTouchEnded,this);
		event->onTouchMoved = CC_CALLBACK_2(MainMenuScene::onTouchMoved,this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(event,this);
	}



	{
		scheduleUpdate();
	}
	
    return true;
}


void MainMenuScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
		MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
		return;
#endif

		Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
}




bool MainMenuScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	CCLOG("HelloWorld::onTouchBegan");
	Scene* gamesc =  GameScene::createScene();
	Director::getInstance()->replaceScene(gamesc);
	return true;
}

void MainMenuScene::onTouchMoved(Touch *touch, Event *unused_event)
{
	
}

void MainMenuScene::onTouchEnded(Touch *touch, Event *unused_event)
{

}

void MainMenuScene::onTouchCancelled(Touch *touch, Event *unused_event)
{

}



void MainMenuScene::touchAudioButton( Ref *pSender)
{
   auto mlabel = (MenuItemLabel*)(this->getChildByTag(UI_WIDGET_TAG::MENU_AUDIOS)->getChildByTag(AUDIO_BG_BUTTON));

	bool audioIsOn = CCUserDefault::getInstance()->getBoolForKey("AUDIO_ON");

	CommonUtils::playButtonTouchMusic();
	 
	if(audioIsOn)
	{
		mlabel->setString("Audio:OFF");
		if(!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			CommonUtils::playBackgrondMusic();
		}else{
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic(); 
		}
	}else{
		mlabel->setString("Audio:ON");
		if(!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			CommonUtils::playBackgrondMusic();
		}else{
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic(); 
		}
	}
	CCUserDefault::getInstance()->setBoolForKey("AUDIO_ON", !audioIsOn);
	CCUserDefault::getInstance()->flush();
}


void MainMenuScene::touchAudioEffeectButton( Ref *pSender)
{
 auto mlabel = (MenuItemLabel*)(this->getChildByTag(UI_WIDGET_TAG::MENU_AUDIOS)->getChildByTag(AUDIO_EFFECT_BUTTON));
	bool audioEffectIsOn = CCUserDefault::getInstance()->getBoolForKey("AUDIO_EFFECT_ON");

	CommonUtils::playButtonTouchMusic();

	
	if(!audioEffectIsOn)
	{ 
		mlabel->setString("Effect:ON");
		CommonUtils::setEffectMusicShouldPlay(true);
		SimpleAudioEngine::getInstance()->resumeAllEffects();
	}else{ 
		mlabel->setString("Effect:OFF");
		CommonUtils::setEffectMusicShouldPlay(false);
		SimpleAudioEngine::getInstance()->pauseAllEffects();
	}
	CCUserDefault::getInstance()->setBoolForKey("AUDIO_EFFECT_ON", !audioEffectIsOn);

	CCUserDefault::getInstance()->flush();
}

void MainMenuScene::update( float delta )
{
	 
}
