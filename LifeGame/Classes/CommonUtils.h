#ifndef __COMMON_UTILS_H__
#define __COMMON_UTILS_H__

#include "cocos2d.h"
using namespace cocos2d;
class CommonUtils
{
public:
	CommonUtils(void);
	~CommonUtils(void);
	static void preloadAudioResources();
	static void playBackgrondMusic();
	static void playButtonTouchMusic();
	static void setEffectMusicShouldPlay(bool val);
    static void changeScene(Scene * sceneOrigin,Scene * sceneTarget);
    static void changeScene(Layer * sceneOrigin,Layer * sceneTarget);
    
	static void initNightShaders();
	static void dispatchNightShaders();
	static void setNightGLprogram(cocos2d::Node* val);
private:
	static bool effectMusicShouldPlay;
	static float nightDarkRate;
	static cocos2d::GLProgramState* _glprogramstate;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	static cocos2d::EventListenerCustom* _backgroundListener;
#endif
	
};

#endif