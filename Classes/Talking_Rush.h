//
//  Talking_Rush.h
//  animate_homework
//
//  Created by mac on 15-7-31.
//
//

#ifndef __animate_homework__Talking_Rush__
#define __animate_homework__Talking_Rush__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class Talking_Rush:public Layer{
public:
    //适合独白和2人对话，需要传头像，person＝1为独白。
    virtual bool init(std::vector<std::string>talk,char*player_filename,char*npc_filename,int preson);
    static Talking_Rush* create(std::vector<std::string>talk,char*player_filename,char*npc_filename,int preson);
    
    //适合多人对话，自动捕捉头像
    virtual bool init(std::vector<std::string>talk);
    
    static Talking_Rush* create(std::vector<std::string>talk);


    std::string _name;
    bool over;
    int count_page;
    int re_page;
};
#endif /* defined(__animate_homework__Talking_Rush__) */
