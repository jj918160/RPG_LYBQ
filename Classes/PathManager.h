//
//  PathManager.h
//  RPG_LYBQ
//
//  Created by mac on 16-3-30.
//
//

#ifndef __RPG_LYBQ__PathManager__
#define __RPG_LYBQ__PathManager__

#include <stdio.h>
#include "cocos2d.h"
class SLGMapView;
class Gird:public cocos2d::Ref{
    CC_SYNTHESIZE(int, _x, X);
    CC_SYNTHESIZE(int, _y, Y);
    CC_SYNTHESIZE(bool, _pass, Pass);
    CC_SYNTHESIZE(int, _velue, Value);
public:
    
    static Gird*create(float hang,float lie) //行，左到右，含0，列，上到下
    {
        Gird *pRet = new(std::nothrow) Gird();
        if (pRet && pRet->init(hang,lie))
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
        
    }
    virtual bool init(float x,float y)
    {
        
        _x=x;
        _y=y;
        _pass=false;
        parent=nullptr;
        return true;
    }
    Gird*parent;
};

class PathManager:public cocos2d::Node{
public:
    static PathManager*create(SLGMapView*map);
    virtual bool init(SLGMapView*map);
    void findRange(Gird*orige,int range,std::vector<cocos2d::Vec2>attackPoint);  //第x+1列  第y＋1行
    void checkFour(Gird*p,int costeLess);
        
    std::vector<cocos2d::Vec2> getPathWay(int startx, int starty,int endx,int endy);
    void drawRange(std::vector<cocos2d::Vec2>vec,int x,int y);
    void drawAttackRange(std::vector<cocos2d::Vec2>vec,int x,int y);
    void show();
    Gird*getGirdByXY(int x,int y);
    void removeAllRange();
private:
    
    cocos2d::Vec2 intSize;
    SLGMapView*map;
    std::vector<std::vector<int>>vecOfmoveCost;
    std::vector<cocos2d::Vector<Gird*>>canMove;
    cocos2d::Vector<cocos2d::Sprite*>GirdSprites;
    
};
#endif /* defined(__RPG_LYBQ__PathManager__) */
