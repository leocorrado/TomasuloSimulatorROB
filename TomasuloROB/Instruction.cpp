/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Instruction.cpp
 * Author: leo
 * 
 * Created on 17 de mayo de 2018, 23:16
 */

#include "Instruction.h"

Instruction::Instruction() {
    rd = FPRegNames::NON;
    rs_val = 0;
    rt_r = RRegistersNames::NON;
    rs_fp = FPRegNames::NON;
    rt_fp = FPRegNames::NON;
    
    opCode = OperationsEnum::UNDEF;
    issueClock = 0;
    executeClockBegin = 0;
    executeClockEnd = 0;
    writeBackClock = 0;
}

Instruction::Instruction(FPRegNames RD, int RS, RRegistersNames RT,
                         OperationsEnum OPCODE) {
    rd = RD;
    rs_val = RS;
    rs_fp = FPRegNames::NON;
    rt_r = RT;
    rt_fp = FPRegNames::NON;
    opCode = OPCODE;
    issueClock = 0;
    executeClockBegin = 0;
    executeClockEnd = 0;
    writeBackClock = 0;
}

Instruction::Instruction (FPRegNames RD, FPRegNames RS, FPRegNames RT,
                OperationsEnum OPCODE)
{
    rd = RD;
    rs_fp = RS;
    rt_fp = RT;
    rs_val = 0;
    rt_r = RRegistersNames::NON;
    opCode = OPCODE;
    issueClock = 0;
    executeClockBegin = 0;
    executeClockEnd = 0;
    writeBackClock = 0;
}

Instruction::~Instruction() {
}

int Instruction::getExecuteClockBegin()
{
    return executeClockBegin;
}

int Instruction::getExecuteClockEnd()
{
    return executeClockEnd;
}

int Instruction::getIssueClock()
{
    return issueClock;
}

OperationsEnum Instruction::getOpCode()
{
    return opCode;
}

FPRegNames Instruction::getRd()
{
    return rd;
}

int Instruction::getRsVal()
{
    return rs_val;
}
    
FPRegNames Instruction::getRsFp()
{
    return rs_fp;
}


FPRegNames Instruction::getRtFp()
{
    return rt_fp;
}

RRegistersNames Instruction::getRtR ()
{
    return rt_r;
}

int Instruction::getWriteBackClock()
{
    return writeBackClock;
}

void Instruction::setExecuteClockBegin(int clk)
{
    executeClockBegin = clk;
}

void Instruction::setExecuteClockEnd(int clk)
{
    executeClockEnd = clk;
}

void Instruction::setIssueClock(int clk)
{
    issueClock = clk;
}

void Instruction::setWriteBackClock(int clk)
{
    writeBackClock = clk;
}

void Instruction::toPrint ()
{
    if (this->getOpCode() == OperationsEnum::LOAD)
    {
        std::cout << this->getOpCode() << " " << this->getRd() << " "
                << this->getRsVal() << " + " << this->getRtR() << std::endl;             
    }
    else
    {
        std::cout  << this->getOpCode() << " " << this->getRd() << " " 
                << this->getRsFp() << " " << this->getRtFp() << std::endl;
    }
}