/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FPointRegister.h
 * Author: leo
 *
 * Created on 18 de mayo de 2018, 00:21
 */

#ifndef FPOINTREGISTER_H
#define FPOINTREGISTER_H
#include "FPRegNames.h"
#include "ROBnames.h"

#include <iostream>
#include <iomanip>


class FPointRegister {
public:
    FPointRegister();
    FPointRegister (float val, FPRegNames nam);
    FPointRegister (FPRegNames nam);
    virtual ~FPointRegister();
    void setValue (float val);
    bool isBusy();
    float getValue ();
    ROBNames getTag();
    FPRegNames getName();
    void setName (FPRegNames nam);
    void setTag (ROBNames obj);
    void setBusy (bool bus);
    void toPrint();
private:
    float value;
    ROBNames tag;
    bool busy;
    FPRegNames name;
    
};

#endif /* FPOINTREGISTER_H */

