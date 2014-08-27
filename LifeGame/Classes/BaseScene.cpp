//
//  BaseScene.cpp
//  LifeGame
//
//  Created by hack on 14-8-25.
//
//

#include "BaseScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "SplashScene.h"

USING_NS_CC;
// on "init" you need to initialize your instance
bool BaseScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}
    
	return true;
}
void BaseScene::layersFadeIn(Scene * mscene)
{
    
    Vector<Node*> mlaysers = mscene->getChildren();
    
    for( int i = 0; i < mlaysers.size(); i++ )
    {
        mlaysers.at(i)->runAction(FadeIn::create(2));
    }
}
void BaseScene::goScene(BASE_SCENE_ID mid)
{

    switch (mid) {
        case SPLASH_SCREEN:
        {
            auto scene = SplashScene::createScene();
            Director::getInstance()->replaceScene(scene);
            break;
        }
        case MAIN_MENU_SCREEN:
        {
            auto scene = MainMenuScene::createScene();
            Director::getInstance()->replaceScene(scene);
            break;
        }

        case GAME_SCENE:
        {
            auto scene = GameScene::createScene();
            Director::getInstance()->replaceScene(scene);
            break;

        }
        case LOADING_SCENE:
        {
            auto scene = LoadingScene::createScene();
            Director::getInstance()->replaceScene(scene);
            break;
            
        }
        default:
            break;
    }
    
}



