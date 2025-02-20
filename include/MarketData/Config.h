/*
 * @Author: LeiJiulong
 * @Date: 2025-02-18 20:29:54
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-20 12:35:45
 * @Description: 
 */
#pragma once

#include <string>
#include <memory>

#include "SimpleIni.h"


class Config
{
public:
    Config(std::string path);
    virtual ~Config(){};
    CSimpleIniA* getIniPtr(){ return ini_.get();}
protected:
    std::unique_ptr<CSimpleIniA> ini_;
private:
    std::string configPath;

};

