/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ROB.h
 * Author: leo
 *
 * Created on 23 de mayo de 2018, 00:32
 */

#ifndef ROB_H
#define ROB_H
#include "FPRegNames.h"
#include "ROBnames.h"

#include <iostream>
#include <iomanip>  
#include <string>


class ROB {
public:
    ROB();
    ROB (ROBNames nam);
    virtual ~ROB();
    FPRegNames getDestination ();
    float getResult ();
    bool isDone();
    bool isBusy ();
    int getInstructionAssociated ();
    ROBNames getName();
    int getCommitLatency ();
    void setDestination (FPRegNames dest);
    void setResult (float resul);
    void setDone (bool don);
    void setBusy (bool bus);
    void setInstructionAssociated (int instr);
    void setName (ROBNames nam);
    void setCommitLatency (int commLat);
    void toPrint ();
    
private:
    FPRegNames destiny;
    ROBNames name;
    int instructionAssociated;
    float result;
    bool done;
    bool busy;
    int commitLatency;
    
};

#endif /* ROB_H */

