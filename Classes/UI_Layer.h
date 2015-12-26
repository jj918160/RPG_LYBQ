//
//  UI_Layer.h
//  RPG_LYBQ
//
//  Created by mac on 15-11-15.
//
//

#ifndef __RPG_LYBQ__UI_Layer__
#define __RPG_LYBQ__UI_Layer__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class Player_Base;
class UI_Layer:public Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // implement the "static create()" method manually
    static UI_Layer*getInstance();
    inline int get_type(){return type;};
    inline float get_angle(){return _angle;};
    Vec2 _delay;
    void set_control(Player_Base*bs){control=bs;};
    Player_Base* get_control(){return control;};
    void command_state_update(Ref*psender);
    void set_work(std::string renwu);
private:
    bool command_out;
     Player_Base*control;
    int type;
    float _angle;
     CREATE_FUNC(UI_Layer);
    void rockervisible(bool ,Vec2);
    float getRad(Vec2 pos1);
    Vec2 getAnglePosition(float r,float angle);
    Vec2 rokerPosition;
    float rockerBGR;
    static UI_Layer*myui;
};

#endif /* defined(__RPG_LYBQ__UI_Layer__) */
