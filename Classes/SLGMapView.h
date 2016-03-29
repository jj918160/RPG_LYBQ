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

class SLGMapView : public cocos2d::Layer
{
public:
    cocos2d::TMXTiledMap* _tileMap;
 
    static SLGMapView* create(const std::string filename);
    virtual bool init(const std::string filename);
    
    float size_width;
    float size_height;
    cocos2d::Size winsize;
    cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 pos);
    
    cocos2d::Vec2 tileCoordToPosition(cocos2d::Vec2 pos);
    int _ememyNum;
    int _myNum;
    std::vector<cocos2d::Vec2>pointOfenemy;
    std::vector<cocos2d::Vec2>pointOfmy;
    
};

#endif /* defined(__RPG_LYBQ__SLGMapView__) */
