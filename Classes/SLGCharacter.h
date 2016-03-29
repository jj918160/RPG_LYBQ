//
//  SLGCharacter.h
//  RPG_LYBQ
//
//  Created by mac on 16-3-29.
//
//

#ifndef __RPG_LYBQ__SLGCharacter__
#define __RPG_LYBQ__SLGCharacter__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class Animation_itools;
class SLGMapView;
class SLGCharacter:public Sprite
{
public:
 
    static SLGCharacter*create(const std::string filename,SLGMapView*map);
    virtual bool init(const std::string filename,SLGMapView*map);
    //已自己为中心，绘制攻击范围
    void drawMovieRange();
    void setTilePosition(Vec2 intPosition);
    
    
private :
    SLGMapView*map;
    Animation_itools*itool;
    enum class Direction{
        down,left,right,up
    };
    SLGCharacter::Direction direction;
    std::string imageSource;//图片核心不同字符串
    int _moveRange;//范围
    bool _moved;//是否已经行动
    int _hp;
    int _mp;
    int _exp;
    void loading_animation();
    void walk(SLGCharacter::Direction direction);
    void attack(SLGCharacter::Direction direction);
    void dieAnimation(SLGCharacter::Direction direction);
    std::string enumToString(SLGCharacter::Direction direction);
    
};
#endif /* defined(__RPG_LYBQ__SLGCharacter__) */
