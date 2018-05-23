/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ROBnames.h
 * Author: leo
 *
 * Created on 22 de mayo de 2018, 23:51
 */

#ifndef ROBNAMES_H
#define ROBNAMES_H

#include <ostream>

enum class ROBNames :  int { ROB0 = 1, ROB1 = 2, ROB2 = 3, ROB3 = 4,
                             ROB4 = 5, ROB5 = 6, UNDEF = 7 };

inline std::ostream& operator<<(std::ostream& os, ROBNames obj) 
{
    switch (obj) {
        case ROBNames::ROB0:
            os << "ROB0";
            break;
        case ROBNames::ROB1:
            os << "ROB1";
            break;
        case ROBNames::ROB2:
            os << "ROB2";
            break;
        case ROBNames::ROB3:
            os << "ROB3";
            break;
        case ROBNames::ROB4:
            os << "ROB4";
            break;
        case ROBNames::ROB5 :
            os << "ROB5";
            break;
        case ROBNames::UNDEF:
            os << "NON";
            break;
        default: os.setstate(std::ios_base::failbit);
    }
    return os;
}
#endif /* ROBNAMES_H */

