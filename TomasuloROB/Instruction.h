/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Instruction.h
 * Author: leo
 *
 * Created on 17 de mayo de 2018, 23:16
 */

#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include "OperationsEnum.h"
#include "FPRegNames.h"
#include "RRegistersNames.h"

#include <iostream>


class Instruction {
public:
    Instruction();
    Instruction(FPRegNames RD, int RS, RRegistersNames RT,
                         OperationsEnum OPCODE);
    Instruction (FPRegNames RD, FPRegNames RS, FPRegNames RT,
                OperationsEnum OPCODE);
    virtual ~Instruction();
    FPRegNames getRd ();
    int getRsVal ();
    FPRegNames getRsFp();
    FPRegNames getRtFp ();
    RRegistersNames getRtR ();
    OperationsEnum getOpCode ();
    int getIssueClock ();
    int getExecuteClockBegin ();
    int getExecuteClockEnd ();
    int getWriteBackClock ();
    void setIssueClock (int clk);
    void setExecuteClockBegin (int clk);
    void setExecuteClockEnd (int clk);
    void setWriteBackClock (int clk);
    void toPrint();
private:
    FPRegNames rd; //destino siempre es un FP
    int rs_val; //rs puede ser un valor de offset
    RRegistersNames rt_r; //si se usa valor de offset rt es un R register
    FPRegNames rs_fp; //Si la instruccion es de R-Type  rs es un FPReg
    FPRegNames rt_fp; //Si la instruccion es de R-type rt es un FPReg
    OperationsEnum opCode; //opCode de la instruccion, permite diferenciar
                            //entre R-types y Loads/Stores
    int issueClock;
    int executeClockBegin;
    int executeClockEnd;
    int writeBackClock;

};

#endif /* INSTRUCTION_H */

