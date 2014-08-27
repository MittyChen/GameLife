#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h"

#include "BaseScene.h"

class SplashScene : BaseScene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();  
	 void goGameScene(float t);
	CREATE_FUNC(SplashScene);
	void touchWelcomeButton( cocos2d::Ref *pSender );

};

#endif // __SPLASH_SCENE_H__
