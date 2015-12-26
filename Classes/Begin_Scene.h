//
//  Begin_Scene.h
//  RPG_LYBQ
//
//  Created by mac on 15-11-14.
//
//

#ifndef __RPG_LYBQ__Begin_Scene__
#define __RPG_LYBQ__Begin_Scene__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class Animation_itools;
class Begin_Scene : public Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Begin_Scene);
    
   void title_fadeout(float dt);
    virtual void onExit();
    void load_animation();
private:
      Vector<MenuItem*>vecfoeitem;
    int title_num;
     Animation_itools*itools;
    void create_bird(float dt,std::string name);
    void create_flower(float dt);
    void creat_botton(int );
    void callback1(Ref*);
};

#endif /* defined(__RPG_LYBQ__Begin_Scene__) */
