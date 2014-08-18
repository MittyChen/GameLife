#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h"



class SplashScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();  
	 void goGameScene(float t);
	CREATE_FUNC(SplashScene);
};

#endif // __SPLASH_SCENE_H__