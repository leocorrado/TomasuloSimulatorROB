/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ROB.cpp
 * Author: leo
 * 
 * Created on 23 de mayo de 2018, 00:32
 */

#include "ROB.h"

ROB::ROB() 
{
    destiny = FPRegNames::NON;
    result = 0.0;
    done = false;
    busy = false;
    instructionAssociated = -1;
    name = ROBNames::UNDEF;
    commitLatency = 0;
}

ROB::ROB (ROBNames nam)
{
    destiny = FPRegNames::NON;
    result = 0.0;
    done = false;
    busy = false;
    instructionAssociated = -1;
    name = nam;
    commitLatency = 0;
}




ROB::~ROB() {
}

FPRegNames ROB::getDestination ()
{
    return destiny;
}

float ROB::getResult ()
{
    return result;
}

bool ROB::isDone()
{
    return done;
}

bool ROB::isBusy ()
{
    return busy;
}

int ROB::getInstructionAssociated ()
{
    return instructionAssociated;
}
    
ROBNames ROB::getName()
{
    return name;
}

int ROB::getCommitLatency ()
{
    return commitLatency;
}


void ROB::setDestination (FPRegNames dest)
{
    destiny = dest;
}

void ROB::setResult (float resul)
{
    result = resul;
}

void ROB::setDone (bool don)
{
    done = don;
}

void ROB::setBusy (bool bus)
{
    busy = bus;
}

void ROB::setInstructionAssociated (int instr)
{
    instructionAssociated = instr;
}

void ROB::setName(ROBNames nam)
{
    name = nam;
}
   
void  ROB::setCommitLatency (int commLat)
{
    commitLatency = commLat;
}


void ROB::toPrint()
{
    char separator = ' ';
    const int width = 6;
    std::cout << "ROB #:" << name << "\tResult: " << std::setw(width) << 
         std::setfill(separator) << result << " Destiny: " << std::setw(4) <<
            std::setfill(separator) << destiny << " Busy: " << busy <<
            " Ready " << done << std::endl;
}

