/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ReservationStation.h
 * Author: leo
 *
 * Created on 16 de mayo de 2018, 23:18
 */

#ifndef RESERVATIONSTATION_H
#define RESERVATIONSTATION_H
#include "OperationsEnum.h"
#include "TagsReprise.h"


#include <iostream>
#include <iomanip>  
#include <string>
#include <cstdlib>


class ReservationStation {
public:
    ReservationStation();
    ReservationStation(TagsReprise nname, OperationsEnum typ);

    virtual ~ReservationStation();
    float getVj ();
    float getVk ();
    int getAddress ();
    TagsReprise getQj ();
    TagsReprise getQk ();
    TagsReprise getName ();
    OperationsEnum getOperation ();
    OperationsEnum getType ();
    bool    isBusy();
    bool isReady();
    int getIssueLatency ();
    int getWriteBackLatency ();
    int getLatency ();
    int getIndexOfInstruction ();
    float getResult();
    void setVj (float value);
    void setVk (float value);
    void setBusy (bool value);
    void setReady (bool value);
    void setQj (TagsReprise tagQj);
    void setQk (TagsReprise tagQk);
    void setOperation (OperationsEnum op);
    void setAddress (int addr);
    void setLatency (int lat);
    void setIssueLatency (int issueLat);
    void setWriteBackLatency (int writeBackLat);
    void setIndexToInstruction (int instruct);
    void calculateResult();
    void executeLoad();
    void flush ();
    void toPrint ();

private:
        OperationsEnum operation;
        TagsReprise    qj;
        TagsReprise    qk;
        float   vj;
        float   vk;
        bool    busy;
        TagsReprise name;
        OperationsEnum type;
        int address;
        int latency;
        int issueLatency;
        int writeBackLatency;
        int indexToInstruction;
        float result;
        bool ready;
};

#endif /* RESERVATIONSTATION_H */

