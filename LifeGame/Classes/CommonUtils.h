#ifndef __COMMON_UTILS_H__
#define __COMMON_UTILS_H__

#include "cocos2d.h"

class CommonUtils
{
public:
	CommonUtils(void);
	~CommonUtils(void);
	static void preloadAudioResources();
	static void playBackgrondMusic();
	static void playButtonTouchMusic();
	static void setEffectMusicShouldPlay(bool val);
	//static void drawPointsAroundGeometric(cocos2d::Vector<Vec2*> pointPositions);
	//enum   GEOMETRIC_TYPE
	//{
	//};
private:
	static bool effectMusicShouldPlay;
	
};

#endif