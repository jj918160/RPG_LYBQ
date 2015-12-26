//
//  UI_Layer.cpp
//  RPG_LYBQ
//
//  Created by mac on 15-11-15.
//
//

#include "UI_Layer.h"
#include "Player_Base.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#define PI 3.1415926

UI_Layer*UI_Layer::myui=nullptr;
UI_Layer*UI_Layer::getInstance(){
    if (myui==nullptr) {
        myui=UI_Layer::create();
    }
    return myui;
}
bool UI_Layer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    command_out=true;
    type=0;
    _angle=0;
    control=nullptr;
    auto rootNode = CSLoader::createNode("Layer.csb");
    addChild(rootNode,0,1);
    auto tol=MenuItemToggle::createWithCallback(CC_CALLBACK_1(UI_Layer::command_state_update,this),
                                                MenuItemImage::create("CG-1147.png", "CG-1147.png"),
                                                MenuItemImage::create("CG-1146.png", "CG-1146.png"),
                                                NULL);
    tol->setPosition(60,550);
    tol->setScale(2.f);
    auto menu=Menu::create(tol,NULL);
    menu->setPosition(0,0);
    this->addChild(menu);
    
    
    rockerBGR=50.f;
    auto listener=EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan=[&](Touch*touch,Event*event){
        if (!control) {
            CCLOG("45");
            return false;
        }
        control->set_active(true);
        rokerPosition=touch->getLocation();
        this->rockervisible(true,touch->getLocation());
                return true;
    };
    listener->onTouchMoved=[=](Touch*touch,Event*event){
        Vec2 point=touch->getLocation();
        float angle=getRad(point);
        _angle=angle;
       
          auto target=static_cast<Sprite*>(rootNode->getChildByTag(8));
        if (sqrt(pow((rokerPosition.x-point.x),2)+pow((rokerPosition.y-point.y),2))>=rockerBGR){
            target->setPosition(getAnglePosition(rockerBGR, angle)+rokerPosition);
        }else{
            target->setPosition(target->getPosition()+touch->getDelta());
        }
        
        if (angle<=PI/8&&angle>-PI/8) {
            type=1;
        }
        else if (angle>PI/8&&angle<=PI*3/8) {
            type=2;
        }
        else if (angle>PI*3/8&&angle<=PI*5/8) {
            type=3;
        }
        else if (angle>PI*5/8&&angle<=PI*7/8) {
            type=4;
        }
        else if (angle>PI*7/8||angle<=-PI*7/8) {
            type=5;
        }
        else if (angle>-PI*7/8&&angle<=-PI*5/8) {
            type=6;
        }
        else if (angle>-PI*5/8&&angle<=-PI*3/8) {
            type=7;
        }
        else if (angle>-PI*3/8&&angle<=-PI*1/8) {
            type=8;
        }
 _delay=target->getPosition()-rokerPosition;
    };
    listener->onTouchEnded=[&](Touch*touch,Event*event){
        type=0;
        _angle=0;
        _delay=Vec2::ZERO;
        this->rockervisible(false,Vec2::ZERO);
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void UI_Layer::command_state_update(Ref*psender){
    auto temp=this->getChildByTag(1)->getChildByTag(10);
    if (command_out) {
        temp->stopAllActions();
        temp->runAction(MoveTo::create(0.5,Vec2(-745,550)));
    
    }
    else {
        temp->stopAllActions();
        temp->runAction(MoveTo::create(0.5,Vec2(80,550)));
    }
    command_out=!command_out;
}

void UI_Layer::set_work(std::string renwu){
    ui::Text* text=(ui::Text*)this->getChildByTag(1)->getChildByTag(10)->getChildByTag(11);
    text->setString(renwu);
}
void UI_Layer::rockervisible(bool cansee,Vec2 position){
    Node*root=static_cast<Node*>(this->getChildByTag(1));
    root->getChildByTag(6)->setVisible(cansee);
    root->getChildByTag(6)->setPosition(position);
    root->getChildByTag(8)->setVisible(cansee);
    root->getChildByTag(8)->setPosition(position);
}

float UI_Layer::getRad(Vec2 pos1){
    float px1=pos1.x;
    float py1=pos1.y;
    float x=px1-rokerPosition.x;
    float y=py1-rokerPosition.y;
    float xie=sqrt(pow(x,2)+pow(y,2));
    float cosAngle=x/xie;
    float rad=acos(cosAngle);
    if (py1<rokerPosition.y) {
        rad=-rad;
    }
    
    return rad;
}



Vec2 UI_Layer::getAnglePosition(float r,float angle){
    return ccp(r*cos(angle),r*sin(angle));
}
