//
//  BaseScene.h
//  LifeGame
//
//  Created by hack on 14-8-25.
//
//

#ifndef __LifeGame__BaseScene__
#define __LifeGame__BaseScene__

#include <iostream>
#include "cocos2d.h"
#include "ConstSceneID.h"

using namespace cocos2d;
class BaseScene : public cocos2d::Layer
{
public:
    virtual bool init();
 
    void layersFadeIn(Scene* mscene);
    void goScene(BASE_SCENE_ID mid);
    
    
};


#endif /* defined(__LifeGame__BaseScene__) */
