//
//  FightScene0_1.h
//  RPG_LYBQ
//
//  Created by mac on 16-3-29.
//
//

#ifndef __RPG_LYBQ__FightScene0_1__
#define __RPG_LYBQ__FightScene0_1__

#include "cocos2d.h"

class FightScene0_1 : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(FightScene0_1);
};

#endif /* defined(__RPG_LYBQ__FightScene0_1__) */
