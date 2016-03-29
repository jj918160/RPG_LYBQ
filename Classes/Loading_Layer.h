//
//  Loading_Layer.h
//  RPG_LYBQ
//
//  Created by mac on 15-11-14.
//
//

#ifndef __RPG_LYBQ__Loading_Layer__
#define __RPG_LYBQ__Loading_Layer__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class Animation_itools;
class Loading_Layer:public Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Loading_Layer);
    virtual void update(float dt);
private:
    std::string loadmsg(const char* filepath);
    Animation_itools*itools;
    void step_2(float dt);
    bool talk_over;
    int main_step;
};
#endif /* defined(__RPG_LYBQ__Loading_Layer__) */
