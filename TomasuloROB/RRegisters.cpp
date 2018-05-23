/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RRegisters.cpp
 * Author: leo
 * 
 * Created on 18 de mayo de 2018, 00:01
 */

#include "RRegisters.h"

RRegisters::RRegisters() 
{
    value = 1000;
    name = RRegistersNames::NON;
}

RRegisters::RRegisters (int val, RRegistersNames nam)
{
    value = val;
    name = nam;

}

RRegisters::RRegisters (RRegistersNames nam)
{
    value = 1000;
    name = nam;
}




RRegisters::~RRegisters() {
}

int RRegisters::getRegisterValue ()
{
    return value;
}


void RRegisters::setRegisterValue (int val)
{
    value = val;
}

RRegistersNames RRegisters::getRegisterName ()
{
    return name;
}
void RRegisters::setRegisterName (RRegistersNames nam)
{
    name = nam;
}

void RRegisters::toPrint ()
{
    std::cout << "RRegister #: " << this->getRegisterName()
              << " Value: " << this->getRegisterValue () << std::endl;
}