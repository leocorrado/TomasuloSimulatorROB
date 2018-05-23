/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TagsReprise.h
 * Author: leo
 *
 * Created on 17 de mayo de 2018, 01:31
 */

#ifndef TAGSREPRISE_H
#define TAGSREPRISE_H
#include <ostream>
enum class TagsReprise : unsigned int { ADD1 = 1 ,
                                        ADD2 = 2,
                                        ADD3 = 3,
                                        MUL1 = 4,
                                        MUL2 = 5,
                                        LOAD1 = 6,
                                        LOAD2 = 7,
                                        LOAD3 = 8,
                                        LOAD4 = 9,
                                        LOAD5 = 10,
                                        LOAD6 = 11,
                                        NON = 12};

inline std::ostream& operator<<(std::ostream& os, TagsReprise e)
 {
     switch(e)
    {
         case TagsReprise::ADD1 : 
            os << "ADD1";    
            break;
         case TagsReprise::ADD2 : 
            os << "ADD2"; 
            break;
         case TagsReprise::ADD3 : 
            os << "ADD3";  
            break;
         case TagsReprise::MUL1 : 
            os << "MUL1"; 
             break;
         case TagsReprise::MUL2 : 
            os << "MUL2";   
            break;
         case TagsReprise::LOAD1 :
            os << "LOAD1";
            break;
         case TagsReprise::LOAD2 :
            os << "LOAD2";
            break;
        case TagsReprise::LOAD3 :
            os << "LOAD3";
            break;
        case TagsReprise::LOAD4 :
            os << "LOAD4";
            break;
        case TagsReprise::LOAD5 :
            os << "LOAD5";
            break;
        case TagsReprise::LOAD6 :
            os << "LOAD6";
            break; 
         case TagsReprise::NON :
             os << "NON";
             break;
        default    : os.setstate(std::ios_base::failbit);
    }
    return os;
 }

#endif /* TAGSREPRISE_H */

