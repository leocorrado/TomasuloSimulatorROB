/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CommonDataBus.h
 * Author: leo
 *
 * Created on 20 de mayo de 2018, 21:09
 */

#ifndef COMMONDATABUS_H
#define COMMONDATABUS_H
#include "TagsReprise.h"

class CommonDataBus {
public:
    CommonDataBus();
    virtual ~CommonDataBus();
    bool isAvailable();
    void setAvailable(bool avail);
    void setName (TagsReprise nam);
    void setResult(float res);
    float getResult();
    TagsReprise getName();
private:
    float result;
    bool available;
    TagsReprise name;

};

#endif /* COMMONDATABUS_H */

