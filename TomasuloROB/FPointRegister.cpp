/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FPointRegister.cpp
 * Author: leo
 * 
 * Created on 18 de mayo de 2018, 00:21
 */

#include "FPointRegister.h"

FPointRegister::FPointRegister() 
{
    value = 10;
    tag = ROBNames::UNDEF;
    busy = false;
    name = FPRegNames::NON;
}

FPointRegister::FPointRegister (float val, FPRegNames nam)
{
    value = val;
    tag = ROBNames::UNDEF;
    busy = false;
    name = nam;
}

FPointRegister::FPointRegister(FPRegNames nam)
{
    value = 10;
    tag = ROBNames::UNDEF;
    busy = false;
    name = nam;
}


FPointRegister::~FPointRegister() {
}

void FPointRegister::setTag(ROBNames obj)
{
    tag = obj;
}

void FPointRegister::setBusy(bool bus)
{
    busy = bus;
}

void FPointRegister::setValue(float val)
{
    value = val;
}

void FPointRegister::setName(FPRegNames nam)
{
    name = nam;
}

float FPointRegister::getValue()
{
    return value;
}

ROBNames FPointRegister::getTag()
{
    return tag;
}

bool FPointRegister::isBusy()
{
    return busy;
}

FPRegNames FPointRegister::getName()
{
    return name;
}

void FPointRegister::toPrint() 
{
    char separator = ' ';
    const int width = 6;
    
    std::cout<< "FP Register #: " << name << " Value:" << std::setprecision(5)
            << std::setw (width)<< std::setfill(separator) << value
            << "\tBusy: " << busy << " Qi: " 
            << tag << std::endl;
}
