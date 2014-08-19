#include "CommonUtils.h"
#include "cocos2d.h"
#include "ConstPaths.h"
 
using namespace CocosDenshion;
using namespace cocos2d;

 bool CommonUtils::effectMusicShouldPlay = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
cocos2d::EventListenerCustom* CommonUtils::_backgroundListener = NULL;
#endif
 float CommonUtils::nightDarkRate = 0.0f;
 cocos2d::GLProgramState* CommonUtils::_glprogramstate =NULL;


CommonUtils::CommonUtils(void)
{
}


CommonUtils::~CommonUtils(void)
{
}

void CommonUtils::preloadAudioResources()
{
	effectMusicShouldPlay = UserDefault::getInstance()->getBoolForKey("AUDIO_EFFECT_ON");
 
	//资源加载
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(std::string(CCFileUtils::sharedFileUtils()->fullPathForFilename(GAME_BACKGROUND_MUSIC)).c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(std::string(CCFileUtils::sharedFileUtils()->fullPathForFilename(GAME_TOUCH_BUTTON_MUSIC)).c_str());

	//音量
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);  
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);  
}

void CommonUtils::playBackgrondMusic()
{
		if(!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			SimpleAudioEngine::getInstance()->playBackgroundMusic(FileUtils::sharedFileUtils()->fullPathForFilename(GAME_BACKGROUND_MUSIC).c_str(),true); 
		}
}

void CommonUtils::playButtonTouchMusic()
{ 
	if(effectMusicShouldPlay)
	{
		SimpleAudioEngine::getInstance()->playEffect(std::string(FileUtils::sharedFileUtils()->fullPathForFilename(GAME_TOUCH_BUTTON_MUSIC)).c_str());
	}
}

void CommonUtils::setEffectMusicShouldPlay(bool val)
{
	effectMusicShouldPlay = val;
}


void CommonUtils::initNightShaders()
{
	auto fileUtiles = FileUtils::getInstance();
	auto fragmentFullPath = fileUtiles->fullPathForFilename("night.fsh");
	auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
	auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
	glprogram->link();
	_glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);

	nightDarkRate =  0.1f;

	_glprogramstate->setUniformFloat("nightDegree",nightDarkRate);

	/*this->setGLProgramState(_glprogramstate);*/

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	_backgroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
		[this](EventCustom*)
	{
		glprogram->reset();
		glprogram->initWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
		glprogram->link();
		glprogram->updateUniforms();
	}
	);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backgroundListener, -1);
#endif


}
void CommonUtils::dispatchNightShaders()
{
	nightDarkRate = 0.0f;
	_glprogramstate =NULL;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	Director::getInstance()->getEventDispatcher()->removeEventListener(_backgroundListener);
#endif
}

void CommonUtils::setNightGLprogram(Node* val)
{
	val->setGLProgramState(_glprogramstate);
}
