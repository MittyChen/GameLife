#ifndef __MainMenuScene_SCENE_H__
#define __MainMenuScene_SCENE_H__

#include "cocos2d.h"
#include "BaseScene.h"

class MainMenuScene : public BaseScene
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

	virtual void update(float delta);
	void touchAudioButton( cocos2d::Ref *pSender);
	void touchAudioEffeectButton( Ref *pSender);

};

#endif // __MainMenuScene_SCENE_H__
