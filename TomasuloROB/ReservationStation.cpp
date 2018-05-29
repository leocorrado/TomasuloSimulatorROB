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
    qj = ROBNames::UNDEF;
    qk = ROBNames::UNDEF;
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
    destiny = ROBNames::UNDEF;
}

ReservationStation::ReservationStation(TagsReprise nname, OperationsEnum typ)
{
    operation = OperationsEnum::UNDEF;
    qj = ROBNames::UNDEF;
    qk = ROBNames::UNDEF;
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
    destiny = ROBNames::UNDEF;
}



ReservationStation::~ReservationStation() {
}

/**
 * Retorna el valor del operando Vj de 
 * la estación de reserva.
 * 
 */
float ReservationStation::getVj ()
{
    return vj;
}

/**
 * Retorna el valor del operando Vk de
 * la estación de reserva.
 *  
 */
float ReservationStation::getVk ()
{
    return vk;
}

/**
 * Retorna el valor del campo Address
 * de la estación de reserva, se utiliza 
 * para las operaciones LOAD.
 *  
 */
int ReservationStation::getAddress ()
{
   return address; 
}

/**
 * Retorna un booleano que representa si la estación
 * de reserva está ocupada. TRUE ocupada, FALSE libre.
 *  
 */
bool ReservationStation::isBusy()
{
    return busy;
}

/**
 * Retorna un booleano que representa si la estación de reserva
 * posee el resultado de la operación encomendada a realizar.
 *
 */
bool ReservationStation::isReady()
{
    return ready;
}

/**
 * Retorna la etiqueta Qj de la estación, esta etiqueta referencia a la
 * entrada del reorder Buffer de la cual espera que tenga su resultado listo.
 *  
 */
ROBNames ReservationStation::getQj() 
{
    return qj;
}

/**
 * Retorna la etiqueta Qk de la estación, esta etiqueta referencia a la entrada
 * del reorder BUffer de la cual espera que tenga su resultado listo.
 *
 */
ROBNames ReservationStation::getQk ()
{
    return qk;
}

/**
 * Retorna la etiqueta que referencia que entrada del reorder Buffer debe
 * guardarse el resultado.
 * 
 */
ROBNames ReservationStation::getDestiny()
{
    return destiny;
}

/**
 * Retorna la operación que está realizando la estación de reserva
 * puede ser LOAD, ADD, SUB, MUL, DIV.
 */
OperationsEnum ReservationStation::getOperation()
{
    return operation;
}

/**
 * Retorna el TIPO de operacion que soporta la estación de reserva, si la 
 * estación realiza multiplicaciones y divisiones el tipo es MUL, si realiza
 * sumas y restas es ADD y nos quedan las operaciones LOAD.
 * 
 */
OperationsEnum ReservationStation::getType ()
{
    return type;
}

/**
 * Retorna la latencia de Issue 
 * 
 */
int ReservationStation::getIssueLatency ()
{
    return issueLatency;
}

/**
 * Retorna la latencia de WriteBack
 *
 */
int ReservationStation::getWriteBackLatency ()
{
    return writeBackLatency;
}

/**
 * Retorna la latencia de ejecución.
 *  
 */
int ReservationStation::getLatency ()
{
    return latency;
}

/**
 * Retorna un entero que represeta el índice de la instruccion que está 
 * ejecutandose en esta estación de reserva.
 * Se utiliza para luego acceder el vector de instrucciones.
 */
int ReservationStation::getIndexOfInstruction ()
{
    return indexToInstruction;
}

/**
 * Retorna el resultado de la operación destinada a realizar.
 *
 */
float ReservationStation::getResult()
{
    return result;
}


/**
 * Setea el estado de la estación, si value es TRUE la estación está ocupada.
 * @param value
 */
void ReservationStation::setBusy(bool value)
{
    this->busy = value;
}

/**
 * Setea la operación que va a realizar la estación de reserva, este operando
 * será el OpCode de la instrucción.
 * @param op
 */
void ReservationStation::setOperation(OperationsEnum op)
{
    this->operation = op;
}

/**
 * Setea la variable ready para indicar si la estación de reserva ya tiene
 * su resultado listo para ser enviado.
 * @param value
 */
void ReservationStation::setReady (bool value)
{
    ready = value;
}

/**
 * Permite setear  Qj con la etiqueta tagQj.
 * @param tagQj
 */
void ReservationStation::setQj(ROBNames tagQj)
{
    this->qj = tagQj;
}

/**
 * Permite setear la variable qk con la etiqueta tagQk.
 * @param tagQk
 */
void ReservationStation::setQk (ROBNames tagQk)
{
    this->qk = tagQk;
}

/**
 * Setea la variable destiny de la estación de reserva con la etiqueta dest.
 * @param dest
 */
void ReservationStation::setDestiny(ROBNames dest)
{
    this->destiny = dest;
}

/**
 * Setea el valor de la variable vj con value.
 * @param value
 */
void ReservationStation::setVj(float value)
{
    this->vj = value;
}

/**
 * Setea el valor de la variable vk con value.
 * @param value
 */
void ReservationStation::setVk (float value)
{
    this->vk = value;
}

/**
 * Retorna el nombre de la estación de reserva.
 * @return 
 */
TagsReprise ReservationStation::getName()
{
    return name;
}

/**
 * Setea la variable address con addr.
 * @param addr
 */
void ReservationStation::setAddress (int addr)
{
    address = addr;
}

/**
 * Setea la variable latency con lat.
 * @param lat
 */
void ReservationStation::setLatency (int lat)
{
    latency = lat;
}

/**
 * Setea la variable issueLatency con issueLat
 * @param issueLat
 */
void ReservationStation::setIssueLatency (int issueLat)
{
    issueLatency = issueLat;
}

/**
 * Setea la variable writeBackLatency con writeBackLat.
 * @param writeBackLat
 */
void ReservationStation::setWriteBackLatency (int writeBackLat)
{
    writeBackLatency = writeBackLat;
}

/**
 * Setea la variable indexToInstruction con instruct.
 * @param instruct
 */
void ReservationStation::setIndexToInstruction (int instruct)
{
    indexToInstruction = instruct;
}

/**
 * Se ejecuta la operación que la estación de reserva tiene encomendada según
 * su OPERATION establecida por la instruccion.
 * Se setea la variable ready en TRUE para indicar que el resultado se ha 
 * calculado y se resetean las variables latency y IssueLatency.
 */
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

/**
 * Permite ejecutar la operación en caso de que esta sea un LOAD.
 */
void ReservationStation::executeLoad()
{
    address = address + (int) this->getVj();
    issueLatency = 0;
    latency = 0;
    ready = true;
    result  = 10 * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}

/**
 * Realiza un reseteo de la estación de reserva, esta función debe ser ejecutada
 * luego de la etapa de writeBack, se colocan todas las variables a 0 para 
 * que la estación esté libre para ser usada por otra instrucción.
 */
void ReservationStation::flush ()
{
    busy = false;
    ready = false;
    qk = ROBNames::UNDEF;
    qj = ROBNames::UNDEF;
    destiny = ROBNames::UNDEF;
    operation = OperationsEnum::UNDEF;
    vj = 0;
    vk = 0;
    address = 0;
    writeBackLatency = 0;
}

/**
 * Imprime en pantalla los datos más importantes de la estación de reserva.
 */
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
            "  Qk: " << std::setw(5) << std::setfill(separator) << qk << 
            "  Destiny: "<< std::setw(5) << std::setfill(separator) << destiny << "\n";
    }
    else
    {
        std::cout <<std::left<< "RS #: " <<std::setw(5) <<std::setfill(separator)
                  << name << "  Busy: " << busy <<"  op: "<<  
                  std::setw(9)<<std::setfill(separator)<< operation 
                << "  Vj: " << std::setw(5) << 
            vj << " Address: " << address << "  Destiny: "<< std::setw(5) 
                << std::setfill(separator) << destiny << "\n";
    }
}

