#include "MainMenuScene.h"
#include "GameScene.h"
#include "CommonUtils.h"

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


	auto titleText = LabelTTF::create("Life Game", "epson1", 80);
	titleText->setColor(Color3B(0.0f,128.0f,255.0f));
	titleText->setPosition(Vec2(origin.x + visibleSize.width/2,   origin.y + visibleSize.height/2 +  titleText->getContentSize().height));
	this->addChild(titleText, 1);

	auto startText = LabelTTF::create("Touch Screen", "epson1", 30);
	startText->setColor(Color3B(0.0f,128.0f,255.0f));
	startText->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height*1/4 ));
	this->addChild(startText, 1);
	startText->runAction( CCRepeatForever::create(Sequence::create(FadeOut::create(1.0f),FadeIn::create(1.0f),NULL)));


  //  auto closeItem = MenuItemImage::create(
  //                                         "CloseNormal.png",
  //                                         "CloseSelected.png",
  //                                         CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));
  //  
		//closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
  //                              origin.y + closeItem->getContentSize().height/2));
		//closeItem->setTag(UI_WIDGET_TAG::EXIT_GAME_BUTTON);



		const char* onOrCloseStr = "";
		if(audioIsOn)
		{
			onOrCloseStr = "Audio:ON";
		}else{
			onOrCloseStr = "Audio:OFF";
		}
		auto audioText = LabelTTF::create(onOrCloseStr, "epson1", 30);
		auto audioTextLabel = MenuItemLabel::create(
			audioText,
			CC_CALLBACK_1(MainMenuScene::touchAudioButton, this));

		audioTextLabel->setColor(Color3B(0.0f,128.0f,255.0f));
		audioTextLabel->setAnchorPoint(Vec2(0.5f,0.5f));
		audioTextLabel->setPosition(Vec2(startText->getPosition().x,   startText->getPosition().y + 2*audioText->getContentSize().height));
		 audioTextLabel->setTag(UI_WIDGET_TAG::AUDIO_BG_BUTTON);





		const char* onOrCloseEffectStr = "";
		if(audioEffectIsOn)
		{
			onOrCloseEffectStr = "Effect:ON";
		}else{
			onOrCloseEffectStr = "Effect:OFF";
		}
		auto audioEffectText = LabelTTF::create(onOrCloseEffectStr, "epson1", 30);
		auto audioEffectLabel = MenuItemLabel::create(
			audioEffectText,
			CC_CALLBACK_1(MainMenuScene::touchAudioEffeectButton, this));
		audioEffectLabel->setColor(Color3B(0.0f,128.0f,255.0f));
		audioEffectLabel->setAnchorPoint(Vec2(0.5f,0.5f));
		audioEffectLabel->setPosition(Vec2(audioTextLabel->getPosition().x,   audioTextLabel->getPosition().y + 2*audioEffectText->getContentSize().height));
		audioEffectLabel->setTag(UI_WIDGET_TAG::AUDIO_EFFECT_BUTTON);
	
		auto menu = Menu::create( audioTextLabel,audioEffectLabel,NULL);
		menu->setPosition(Vec2::ZERO);
		menu->setTag(UI_WIDGET_TAG::MENU_AUDIOS);
		this->addChild(menu, 1);

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

	bool audioIsOn = CCUserDefault::sharedUserDefault()->getBoolForKey("AUDIO_ON");

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
	CCUserDefault::sharedUserDefault()->setBoolForKey("AUDIO_ON", !audioIsOn);
	CCUserDefault::sharedUserDefault()->flush();
}


void MainMenuScene::touchAudioEffeectButton( Ref *pSender)
{
 auto mlabel = (MenuItemLabel*)(this->getChildByTag(UI_WIDGET_TAG::MENU_AUDIOS)->getChildByTag(AUDIO_EFFECT_BUTTON));
	bool audioEffectIsOn = CCUserDefault::sharedUserDefault()->getBoolForKey("AUDIO_EFFECT_ON");

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
	CCUserDefault::sharedUserDefault()->setBoolForKey("AUDIO_EFFECT_ON", !audioEffectIsOn);

	CCUserDefault::sharedUserDefault()->flush();
}

