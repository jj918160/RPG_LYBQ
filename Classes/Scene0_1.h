//
//  Scene0_1.h
//  RPG_LYBQ
//
//  Created by mac on 15-11-15.
//
//

#ifndef __RPG_LYBQ__Scene0_1__
#define __RPG_LYBQ__Scene0_1__

#include <stdio.h>
#include "Player_Base.h"
#include "cocos2d.h"
USING_NS_CC;
class Animation_itools;

/*
 剧场1: 第一步 行动
 第二步:对话      step1;
 第三步:任务一 操作wz   step2
 第四步:任务二 操作LS   step3
 第五步:任务三 操作LS   step4
 
 
 */
class Scene0_1:public Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(Scene0_1);
   // virtual void update(float dt);
    void step_1(float dt);
    void step_2(float dt);
    void step_3(float dt);
    void step_4(float dt);
private:
   
   // char* loadmsg(const char* filepath);
    Animation_itools*itools;
    int main_step;
    bool talk_over;
    bool touch_oneP(Vec2 pot);
    void loadAnimation();
    Vector<Player_Base*>vec;
   
};

#endif /* defined(__RPG_LYBQ__Scene0_1__) */
