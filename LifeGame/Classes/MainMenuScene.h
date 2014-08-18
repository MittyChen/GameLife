#ifndef __MainMenuScene_SCENE_H__
#define __MainMenuScene_SCENE_H__

#include "cocos2d.h"

 
class MainMenuScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);


	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void touchAudioButton( cocos2d::Ref *pSender);
	void touchAudioEffeectButton( Ref *pSender);

private:
	enum UI_WIDGET_TAG
	{
		MENU_AUDIOS,
		EXIT_GAME_BUTTON,
		AUDIO_BG_BUTTON,
		AUDIO_EFFECT_BUTTON
	};

};

#endif // __MainMenuScene_SCENE_H__
