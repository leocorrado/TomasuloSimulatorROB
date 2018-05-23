/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ReservationStation.cpp
 * Author: leo
 * 
 * Created on 16 de mayo de 2018, 23:18
 */

#include "ReservationStation.h"

ReservationStation::ReservationStation() {
    operation = OperationsEnum::UNDEF;
    qj = TagsReprise::NON;
    qk = TagsReprise::NON;
    vj = 0.0;
    vk = 0.0;
    busy = false;
    name = TagsReprise::NON;
    type = OperationsEnum::UNDEF;
    address = 0;
    latency = 0;
    issueLatency = 0;
    writeBackLatency = 0;
    indexToInstruction = 1000;
    result = 0.0;
    ready = false;
}

ReservationStation::ReservationStation(TagsReprise nname, OperationsEnum typ)
{
    operation = OperationsEnum::UNDEF;
    qj = TagsReprise::NON;
    qk = TagsReprise::NON;
    vj = 0.0;
    vk = 0.0;
    busy = false;
    name = nname;
    type = typ;
    address = 0;
    latency = 0;
    issueLatency = 0;
    writeBackLatency = 0;
    indexToInstruction = 1000;
    result = 0.0;
    ready = false;
}



ReservationStation::~ReservationStation() {
}

float ReservationStation::getVj ()
{
    return vj;
}

float ReservationStation::getVk ()
{
    return vk;
}

int ReservationStation::getAddress ()
{
   return address; 
}


bool ReservationStation::isBusy()
{
    return busy;
}

bool ReservationStation::isReady()
{
    return ready;
}

TagsReprise ReservationStation::getQj() 
{
    return qj;
}

TagsReprise ReservationStation::getQk ()
{
    return qk;
}

OperationsEnum ReservationStation::getOperation()
{
    return operation;
}

OperationsEnum ReservationStation::getType ()
{
    return type;
}

int ReservationStation::getIssueLatency ()
{
    return issueLatency;
}

int ReservationStation::getWriteBackLatency ()
{
    return writeBackLatency;
}


int ReservationStation::getLatency ()
{
    return latency;
}

int ReservationStation::getIndexOfInstruction ()
{
    return indexToInstruction;
}

float ReservationStation::getResult()
{
    return result;
}



void ReservationStation::setBusy(bool value)
{
    this->busy = value;
}

void ReservationStation::setOperation(OperationsEnum op)
{
    this->operation = op;
}

void ReservationStation::setReady (bool value)
{
    ready = value;
}

void ReservationStation::setQj(TagsReprise tagQj)
{
    this->qj = tagQj;
}

void ReservationStation::setQk (TagsReprise tagQk)
{
    this->qk = tagQk;
}

void ReservationStation::setVj(float value)
{
    this->vj = value;
}

void ReservationStation::setVk (float value)
{
    this->vk = value;
}

TagsReprise ReservationStation::getName()
{
    return name;
}

void ReservationStation::setAddress (int addr)
{
    address = addr;
}

void ReservationStation::setLatency (int lat)
{
    latency = lat;
}

void ReservationStation::setIssueLatency (int issueLat)
{
    issueLatency = issueLat;
}

void ReservationStation::setWriteBackLatency (int writeBackLat)
{
    writeBackLatency = writeBackLat;
}

void ReservationStation::setIndexToInstruction (int instruct)
{
    indexToInstruction = instruct;
}

void ReservationStation::calculateResult()
{
    switch (this->getOperation())
    {
        case (OperationsEnum::ADD) :
            result = this->getVj() + this->getVk();
            break;
        case (OperationsEnum::SUB) :
            result = this->getVj() - this->getVk();
            
            break;
        case (OperationsEnum::MUL) :
            result = this->getVj() * this->getVk();
            break;
        case (OperationsEnum::DIV) :
            result = this->getVj() / this->getVk();
            break;
        default:
            break;
    }
    ready = true;
    latency = 0;
    issueLatency = 0;
}

void ReservationStation::executeLoad()
{
    address = address + (int) this->getVj();
    issueLatency = 0;
    latency = 0;
    ready = true;
    result  = 10 * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}
void ReservationStation::flush ()
{
    busy = false;
    ready = false;
    qk = TagsReprise::NON;
    qj = TagsReprise::NON;
    vj = 0;
    vk = 0;
    address = 0;
    writeBackLatency = 0;
}


void ReservationStation::toPrint()
{
    const int width = 6;
    const char separator = ' ';
    if (this->getType() != OperationsEnum::LOAD)
    {
    std::cout <<std::left<< "RS #: "<<std::setw(5)<<std::setfill(separator) 
            << name << "  Busy: " << busy << "  op: "<< 
            std::setw(9)<<std::setfill(separator) << operation << 
            "  Vj: " <<std::setprecision(5)<< std::setw(width)
            <<std::setfill(separator)<< vj << "  Vk: " <<
            std::setprecision(5)<< std::setw(width)<<std::setfill(separator)
            << vk << "  Qj: " <<std::setw(5)<<std::setfill(separator)<< qj <<
            "  Qk: " << std::setw(5) << std::setfill(separator) << qk << "\n";
    }
    else
    {
        std::cout <<std::left<< "RS #: " <<std::setw(5) <<std::setfill(separator)
                  << name << "  Busy: " << busy <<"  op: "<<  
                  std::setw(9)<<std::setfill(separator)<< operation 
                << "  Vj: " << std::setw(5) << 
            vj << " Address: " << address << " \n";
    }
}

