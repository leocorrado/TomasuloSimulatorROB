/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FPRegNames.h
 * Author: leo
 *
 * Created on 19 de mayo de 2018, 18:25
 */

#ifndef FPREGNAMES_H
#define FPREGNAMES_H

#include <ostream>
enum class FPRegNames : unsigned int { FP0 = 1 ,
                                        FP1 = 2,
                                        FP2 = 3,
                                        FP3 = 4,
                                        FP4 = 5,
                                        FP5 = 6,
                                        NON = 7};
                                            
inline std::ostream& operator<<(std::ostream& os, FPRegNames e)
 {
     switch(e)
    {
         case FPRegNames::FP0 : 
            os << "FP0";    
            break;
         case FPRegNames::FP1 : 
            os << "FP1"; 
            break;
         case FPRegNames::FP2 : 
            os << "FP2";  
            break;
         case FPRegNames::FP3 : 
            os << "FP3"; 
             break;
         case FPRegNames::FP4 : 
            os << "FP4";   
            break;
         case FPRegNames::FP5 :
            os << "FP5";
            break;
         case FPRegNames::NON :
            os << "NON";
            break;
        default    : os.setstate(std::ios_base::failbit);
    }
    return os;
 }



#endif /* FPREGNAMES_H */

