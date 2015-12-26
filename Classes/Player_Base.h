//
//  Player_Base.h
//  RPG_LYBQ
//
//  Created by mac on 15-11-15.
//
//

#ifndef __RPG_LYBQ__Player_Base__
#define __RPG_LYBQ__Player_Base__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class Animation_itools;
class Player_Base:public Sprite
{
public:
    static Player_Base*create(const char*pic,const char*name);
    virtual bool init(const char*pic,const char*name);
    virtual void update(float dt);
    inline void set_active(bool act){_active=act;};
     void walk(std::string direction);
    void set_Image(const char*pic,int hang,int lie);
    void set_chineseName(std::string name);
    std::string get_chineseName(){return _chineseName;};
private:
    int deriction;
    std::string _name;
    std::string _chineseName;
    bool _active;
    float _speed;
    Animation_itools*itools;
    void loadanimation(const char*pic);
    
    
};
#endif /* defined(__RPG_LYBQ__Player_Base__) */
