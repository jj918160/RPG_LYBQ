
#include "Player_Base.h"
#include "UI_Layer.h"
#include "Animation_itools.h"
#include "Talking_Rush.h"
#define PI 3.1415926

Player_Base*Player_Base::create(const char*pic,const char*name){
    Player_Base *pRet = new(std::nothrow) Player_Base();
    if (pRet && pRet->init(pic,name))
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
void Player_Base::set_chineseName(std::string name){
    _chineseName=name;
}
bool Player_Base::init(const char*pic,const char*name){
    if (!Sprite::init()) {
        return false;
    }
    _chineseName="梅长苏";
    _name=name;
    loadanimation(pic);
    Texture2D*p=TextureCache::getInstance()->getTextureForKey(pic);
    this->initWithFile(pic,Rect(0,0,p->getContentSize().width/4,p->getContentSize().height/4));
    deriction=0;
    
    PhysicsBody*box=PhysicsBody::createBox(this->getContentSize());
    this->setPhysicsBody(box);
    box->setRotationEnable(false);
    box->setGroup(-1);
    scheduleUpdate();
    return true;
}
void Player_Base::set_Image(const char*pic,int hang,int lie){
    Texture2D*p=TextureCache::getInstance()->getTextureForKey(pic);
    
    
    this->initWithFile(pic,Rect(p->getContentSize().width*lie/4,p->getContentSize().height*hang/4,p->getContentSize().width/4,p->getContentSize().height/4));
    
}
void Player_Base::update(float dt){
    Talking_Rush*tk=(Talking_Rush*)this->getParent()->getChildByTag(1);
    if (tk&&!this->getChildByTag(6)&&tk->_name==this->_chineseName) {
        auto sp=Sprite::create();
        Animation*animation=AnimationCache::getInstance()->getAnimation("talk");
        Animate*a=Animate::create(animation);
        sp->runAction(a);
        sp->setPosition(this->getContentSize().width/2,this->getContentSize().height+20);
        this->addChild(sp,1,6);
    }
    if (tk&&this->getChildByTag(6)&&tk->_name!=this->_chineseName) {
        this->removeChildByTag(6);
    }
    if (!tk&&this->getChildByTag(6)) {
        this->removeChildByTag(6);
    }
    
    
    this->setZOrder(640-this->getPositionY());
    if (_active) {
        UI_Layer*t=UI_Layer::getInstance();
        this->setPosition(this->getPosition()+t->_delay/10);
        float an=t->get_angle();
        if (t->_delay.getLengthSq()<600) {
            deriction=0;
            stopAllActions();
            return;
        }
        if (an<PI/2&&an>=0&&deriction!=1)
        {
            deriction=1;
            stopAllActions();
            walk(_name+"right_up");
            
        }
        else if (an<PI&&an>=PI/2&&deriction!=2)
        {
            deriction=2;
            stopAllActions();
            walk(_name+"left_up");
        }
        else if (an<-PI/2&&an>=-PI&&deriction!=3)
        {
            deriction=3;
            stopAllActions();
            walk(_name+"left_down");
        }
        else if (an<0&&an>=-PI/2&&deriction!=4)
        {
            deriction=4;
            stopAllActions();
            walk(_name+"right_down");
        }
    }
    
}

void Player_Base::walk(std::string direction){
    AnimationCache* ac=AnimationCache::getInstance();
    
    Animation *a=ac->getAnimation(direction);
    Animate* animate=Animate::create(a);
    this->runAction(animate);
}
void Player_Base::loadanimation(const char*pic){
    AnimationCache* ac=AnimationCache::getInstance();
    Animation*runxdown=itools->makeAnimationfrommixpicture(pic,4,4,1,1,4,1,0.1f,true,-1);
    
    ac->addAnimation(runxdown,_name+"left_down");
    CCLOG("animate:%s",(_name+"left_down").c_str());
    Animation*goxleft=itools->makeAnimationfrommixpicture(pic,4,4,1,2,4,2,0.1f,true,-1);
    ac->addAnimation(goxleft,_name+"left_up");
    Animation*goxright=itools->makeAnimationfrommixpicture(pic,4,4,1,3,4,3,0.1f,true,-1);
    ac->addAnimation(goxright,_name+"right_down");
    Animation*goxup=itools->makeAnimationfrommixpicture(pic,4,4,1,4,4,4,0.1f,true,-1);
    ac->addAnimation(goxup,_name+"right_up");
    
}