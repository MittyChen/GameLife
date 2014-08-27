//
//  LoadingScene.h
//  LifeGame
//
//  Created by hack on 14-8-25.
//
//

#ifndef __LifeGame__LoadingScene__
#define __LifeGame__LoadingScene__

#include <iostream>

#include "cocos2d.h"

#include "BaseScene.h"

class GameScene;

class LoadingScene : BaseScene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
    virtual void update(float delta);
	CREATE_FUNC(LoadingScene);
    static void setProgress(float progress);
    static void setIsReady(bool val);
    static void* thread_Create_GameScene(void *arg);
    int  goloadData();
private:
    static bool isReady;
    static float progressVal;
    pthread_t th_socket;
    Scene* gamescene ;
    static GameScene* layer;
};


#endif /* defined(__LifeGame__LoadingScene__) */
