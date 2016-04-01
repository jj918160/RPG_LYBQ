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
class PathManager;
class Animation_itools;
class SLGMapView;
class SLGCharacter:public Sprite
{
public:
 
    static SLGCharacter*create(const std::string filename,SLGMapView*map);
    virtual bool init(const std::string filename,SLGMapView*map);
    //已自己为中心，绘制攻击范围
    void drawMovieRange();
    void setTilePosition(int x,int y,bool goPosition=true);
    cocos2d::Vec2 getTilePosition(int x,int y);
    inline int getTileX(){return _tilex;};
    inline int getTileY(){return _tiley;};
    void goDestnation(std::vector<Vec2>p);
    void setPathManager(PathManager*p);
    Vector<FiniteTimeAction*> initActioninterval(std::vector<Vec2>vpn,float speed);
    static float SpeedRatio;
private :
    
    //攻击和伤害模块  扩展需要添加两个地方  一个enum  一个getRange函数  一个intToenum函数
    enum class Attack{
        type1,//4面
        type2,//8方
        type3//小♦️
    };
    enum class hurt{
        type1,//单体
        type2,//十字
    };
    std::vector<Vec2> getAttackRange(SLGCharacter::Attack type);
    std::vector<Vec2> gethurtRange(SLGCharacter::hurt type);
    SLGCharacter::Attack AttakintToenum(int type);
    SLGCharacter::hurt HurtintToenum(int type);
    
    SLGCharacter::Attack _AttakType;
    SLGCharacter::hurt _HurtType;

    
    
    //瓦片地图相关模块
    PathManager*_pathManager;
    int _tilex; //瓦片单位坐标 6,8
    int _tiley;
    SLGMapView*map;

    
    
    
    //动画模块
    void change_animation(Vec2 v1,Vec2 v2);
    Animation_itools*itool;
    enum class Direction{
        down,left,right,up
    };
    Action*animate;
    SLGCharacter::Direction _direction;
    void loading_animation();
    void walk(SLGCharacter::Direction direction);
    void attack(SLGCharacter::Direction direction);
    void dieAnimation(SLGCharacter::Direction direction);
    std::string enumToString(SLGCharacter::Direction direction);
    
    
    
    //属性和配置模块
    std::string imageSource;//图片核心不同字符串
    int _moveRange;//范围
    bool _moved;//是否已经行动
    float _speed;//移动速度
    int _hp;
    int _mp;
    int _exp;
    virtual ~SLGCharacter();
    
};
#endif /* defined(__RPG_LYBQ__SLGCharacter__) */
