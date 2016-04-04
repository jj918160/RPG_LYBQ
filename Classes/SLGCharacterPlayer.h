//
//  SLGCharacterPlayer.h
//  RPG_LYBQ
//
//  Created by mac on 16-4-3.
//
//

#ifndef __RPG_LYBQ__SLGCharacterPlayer__
#define __RPG_LYBQ__SLGCharacterPlayer__

#include <stdio.h>
#include "cocos2d.h"
#include "SLGCharacter.h"

class SLGCharacterPlayer:public SLGCharacter{
    public :
    static SLGCharacterPlayer*create(const std::string filename,SLGMapView*map,PathManager*pm);
    virtual bool init(const std::string filename,SLGMapView*map,PathManager*pm);
    void switchAttackTarget();//选择攻击目标
    void showRender();//展示命令界面 待命 攻击
    void removeRender();//删除攻击展示界面
    virtual void goDestnation(std::vector<Vec2>p);
    void replacing();
    
    int _tilexLastRound;
    int _tileyLastRound;
    void removeAttackBox();
    bool selectedSelf(Vec2 pot);
};

#endif /* defined(__RPG_LYBQ__SLGCharacterPlayer__) */
