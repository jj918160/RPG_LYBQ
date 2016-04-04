//
//  SLGCharacterManager.h
//  RPG_LYBQ
//
//  Created by mac on 16-4-2.
//
//

#ifndef __RPG_LYBQ__SLGCharacterManager__
#define __RPG_LYBQ__SLGCharacterManager__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class SLGCharacter;
class SLGMapView;
class SLGCharacterPlayer;
class SLGCharacterManager :public Node{
public:
    static SLGCharacterManager*create(SLGMapView*map);
    virtual bool init(SLGMapView*);
    SLGMapView*map;
    Vector<SLGCharacterPlayer*> quene;
    void pushBackPlayerCharacter(SLGCharacterPlayer*);
    void initTouchFunc();
    SLGCharacterPlayer*selected;
    SLGCharacterPlayer* selectedOther(Vec2 point);
    bool moving;
    void NextRound();
    bool attackView(SLGCharacter*attackfrom,Vec2 des);
    bool canMove;//标示是否允许移动 根据是否有moveRange来判断
};

#endif /* defined(__RPG_LYBQ__SLGCharacterManager__) */
