/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RRegistersNames.h
 * Author: leo
 *
 * Created on 18 de mayo de 2018, 18:49
 */

#ifndef RREGISTERSNAMES_H
#define RREGISTERSNAMES_H

#include <ostream>
enum class RRegistersNames : unsigned int { R0 = 1 ,
                                            R1 = 2,
                                            R2 = 3,
                                            R3 = 4,
                                            R4 = 5,
                                            R5 = 6,
                                            NON = 7};
                                            
inline std::ostream& operator<<(std::ostream& os, RRegistersNames e)
 {
     switch(e)
    {
         case RRegistersNames::R0 : 
            os << "R1";    
            break;
         case RRegistersNames::R1 : 
            os << "R2"; 
            break;
         case RRegistersNames::R2 : 
            os << "R3";  
            break;
         case RRegistersNames::R3 : 
            os << "R4"; 
             break;
         case RRegistersNames::R4 : 
            os << "R5";   
            break;
         case RRegistersNames::R5 :
            os << "R6";
            break;
         case RRegistersNames::NON :
            os << "NON";
            break;
        default    : os.setstate(std::ios_base::failbit);
    }
    return os;
 }



#endif /* RREGISTERSNAMES_H */

