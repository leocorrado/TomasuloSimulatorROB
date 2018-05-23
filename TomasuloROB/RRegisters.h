/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RRegisters.h
 * Author: leo
 *
 * Created on 18 de mayo de 2018, 00:01
 */

#ifndef RREGISTERS_H
#define RREGISTERS_H
#include "RRegistersNames.h"


#include <iostream>
#include <iomanip>  
#include <string>

class RRegisters {
public:
    RRegisters();
    RRegisters (int val, RRegistersNames nam);
    RRegisters (RRegistersNames nam);
    ~RRegisters();
    int getRegisterValue ();
    void setRegisterValue (int val);
    RRegistersNames getRegisterName ();
    void setRegisterName (RRegistersNames nam);
    void toPrint ();
  
private:
    RRegistersNames name;
    int value;
    
};

#endif /* RREGISTERS_H */

