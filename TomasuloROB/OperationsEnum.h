/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OperationsEnum.h
 * Author: leo
 *
 * Created on 16 de mayo de 2018, 21:38
 */

#ifndef OPERATIONSENUM_H
#define OPERATIONSENUM_H

#include <ostream>

enum class OperationsEnum :  int { ADD = 1, SUB = 2, MUL = 3, DIV = 4,
                                    LOAD = 5, UNDEF = 6 };

inline std::ostream& operator<<(std::ostream& os, OperationsEnum obj)
 {
     switch(obj)
    {
         case OperationsEnum::DIV : 
            os << "DIV";    
            break;
         case OperationsEnum::LOAD : 
            os << "LD"; 
            break;
         case OperationsEnum::ADD : 
            os << "ADD";  
            break;
         case OperationsEnum::SUB : 
            os << "SUB"; 
             break;
         case OperationsEnum::MUL : 
            os << "MUL";   
            break;
         case OperationsEnum::UNDEF :
            os << "UNDEFINED";
            break;
        default    : os.setstate(std::ios_base::failbit);
    }
    return os;
 }
#endif /* OPERATIONSENUM_H */

