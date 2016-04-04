//
//  SLGMapView.h
//  RPG_LYBQ
//
//  Created by mac on 16-3-29.
//
//

#ifndef __RPG_LYBQ__SLGMapView__
#define __RPG_LYBQ__SLGMapView__

#include <stdio.h>
#include "cocos2d.h"
#define PERTILEWIDTH 64
#define PERTILEHEIGHT 64
class SLGMapView : public cocos2d::Layer
{
public:
    cocos2d::TMXTiledMap* _tileMap;
    cocos2d::TMXLayer*_movecost;
    void removeSwitch();
    
    
 
    static SLGMapView* create(const std::string filename);
    virtual bool init(const std::string filename);
    
    float size_width; //地图的宽高
    float size_height; //地图的宽高
    cocos2d::Size winsize;
    cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 pos);
    
    cocos2d::Vec2 tileCoordToPosition(cocos2d::Vec2 pos);
    int _ememyNum;
    int _myNum;
    std::vector<cocos2d::Vec2>pointOfenemy;
    std::vector<cocos2d::Vec2>pointOfmy;
    
};

#endif /* defined(__RPG_LYBQ__SLGMapView__) */
