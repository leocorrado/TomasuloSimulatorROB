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
#include "ROBnames.h"


class CommonDataBus {
public:
    CommonDataBus();
    virtual ~CommonDataBus();
    bool isAvailable();
    void setAvailable(bool avail);
    void setDestiny (ROBNames dest);
    void setResult(float res);
    float getResult();
    ROBNames getDestiny();
private:
    float result;
    bool available;
    ROBNames destiny;

};

#endif /* COMMONDATABUS_H */

