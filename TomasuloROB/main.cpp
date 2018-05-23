/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: leo
 *
 * Created on 16 de mayo de 2018, 20:23
 */

//#include <cstdlib>
#include "OperationsEnum.h"
#include "TagsReprise.h"
#include "RRegistersNames.h"
#include "FPRegNames.h"
#include "ROBnames.h"
#include "Instruction.h"
#include "ReservationStation.h"
#include "RRegisters.h"
#include "FPointRegister.h"
#include "CommonDataBus.h"
#include "ROB.h"


#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <cstdlib>
#include <sstream>
#include <iomanip>



//############################################
// Configuraciones de latencia
const int ADD_LATENCY = 2;
const int SUB_LATENCY = 2;
const int LOAD_LATENCY = 2;
const int MULT_LATENCY = 10;
const int DIV_LATENCY = 40;
const int ISSUE_LATENCY = 1;
const int WB_LATENCY = 1;
const int COMMIT_LATENCY = 1;
//
//###########################################
//###########################################
// Variables globales de control
int GLOBAL_CLOCK = 0;
int instructionsIssued = 0;
int totalInstFinished = 0;
bool finish = false;
//
//############################################

using namespace std;


//######################################################################
/*
 El sistema posee 6 registros FP y por ahora no soporta operaciones 
 de store.
 Se supone tambien que se utilizan hasta 6 registros de tipo R.
 Las instrucciones deben ser creadas en el main
 * 
 
 
 */
//#####################################################################
int issue (vector<Instruction>& instr,
          vector<ReservationStation>& reserStations,
          vector<FPointRegister>& fPRegs,
          vector<RRegisters>& rRegs);

int execute (vector<Instruction>& instr,
          vector<ReservationStation>& reserStations,
          vector<FPointRegister>& fPRegs,
          vector<RRegisters>& rRegs);

int writeBack (vector<Instruction>& instr,
          vector<ReservationStation>& reserStations,
          vector<FPointRegister>& fPRegs,
          vector<RRegisters>& rRegs);



void printFunctionalUnits ( vector<ReservationStation> );
void printRRegisters (vector <RRegisters>);
void printFPRegisters (vector <FPointRegister>);
void printInstructions (vector <Instruction>);
void printTimingTable(vector<Instruction>);
void printROB (vector<ROB>);

int main(int argc, char** argv) 
{
    //#######################################################################
    // Inicializacion de las instrucciones a ejecutar
    
    Instruction I0 = Instruction (FPRegNames::FP1, 34,  RRegistersNames::R2,
                                    OperationsEnum::LOAD);      
    Instruction I1 = Instruction (FPRegNames::FP2, 45, RRegistersNames::R3,
                                     OperationsEnum::LOAD);
    Instruction I2 = Instruction (FPRegNames::FP3, FPRegNames::FP2, 
                                  FPRegNames::FP4, OperationsEnum::MUL);
    Instruction I3 = Instruction (FPRegNames::FP5, FPRegNames::FP1,
                                  FPRegNames::FP2, OperationsEnum::SUB);
    Instruction I4 = Instruction (FPRegNames::FP0, FPRegNames::FP3, 
                                  FPRegNames::FP1, OperationsEnum::DIV);
    Instruction I5 = Instruction(FPRegNames::FP1, FPRegNames::FP5,
            FPRegNames::FP2, OperationsEnum::ADD);
    
    vector<Instruction> instructionsVector = {I0,I1,I2,I3,I4,I5};
    
    printInstructions (instructionsVector);
    
    
    
    //######################################################################
    //  Inicialización de las estaciones de Reserva
    
    ReservationStation ADD1 = ReservationStation (TagsReprise::ADD1, OperationsEnum::ADD);
    ReservationStation ADD2 = ReservationStation (TagsReprise::ADD2, OperationsEnum::ADD);
    ReservationStation ADD3 = ReservationStation (TagsReprise::ADD3, OperationsEnum::ADD);
    ReservationStation MUL1 = ReservationStation (TagsReprise::MUL1, OperationsEnum::MUL);
    ReservationStation MUL2 = ReservationStation (TagsReprise::MUL2, OperationsEnum::MUL);
    ReservationStation LOAD1 = ReservationStation (TagsReprise::LOAD1, OperationsEnum::LOAD);
    ReservationStation LOAD2 = ReservationStation(TagsReprise::LOAD2, OperationsEnum::LOAD);
    ReservationStation LOAD3 = ReservationStation(TagsReprise::LOAD3, OperationsEnum::LOAD);
    ReservationStation LOAD4 = ReservationStation(TagsReprise::LOAD4, OperationsEnum::LOAD);
    ReservationStation LOAD5 = ReservationStation(TagsReprise::LOAD5, OperationsEnum::LOAD);
    
    
    vector<ReservationStation> functionalUnits = {ADD1, ADD2, ADD3, 
                                          MUL1, MUL2, LOAD1,
                                          LOAD2, LOAD3, LOAD4,
                                           LOAD5};
    printFunctionalUnits (functionalUnits);
    
    //
    //########################################################################
    
    //#######################################################################
    //  Inicializacion de los R- Registers
    
    RRegisters R0 = RRegisters(RRegistersNames::R0);
    RRegisters R1 = RRegisters(RRegistersNames::R1);
    RRegisters R2 = RRegisters(RRegistersNames::R2);
    RRegisters R3 = RRegisters(RRegistersNames::R3);
    vector<RRegisters> rRegisters = {R0,R1,R2,R3};

    printRRegisters (rRegisters);
    //
    //#######################################################################

    //######################################################################
    //  Inicializacion de los FP- Registers
    // 
    
    FPointRegister F0 = FPointRegister (FPRegNames::FP0);
    FPointRegister F1 = FPointRegister (FPRegNames::FP1);
    FPointRegister F2 = FPointRegister (FPRegNames::FP2);
    FPointRegister F3 = FPointRegister (FPRegNames::FP3);
    FPointRegister F4 = FPointRegister (FPRegNames::FP4);
    FPointRegister F5 = FPointRegister (FPRegNames::FP5);


    vector<FPointRegister> fPointRegisters = {F0,F1,F2,F3, F4, F5};
    
    printFPRegisters (fPointRegisters);
    // 
    //########################################################################
    // INicializacion del ROB
    //
    ROB RoB0 = ROB (ROBNames::ROB0);
    ROB RoB1 = ROB (ROBNames::ROB1);
    ROB RoB2 = ROB (ROBNames::ROB2);
    ROB RoB3 = ROB (ROBNames::ROB3);
    ROB RoB4 = ROB (ROBNames::ROB4);
    ROB RoB5 = ROB (ROBNames::ROB5);
    
    vector<ROB> ReorderBuffer = {RoB0, RoB1, RoB2, RoB3, RoB4, RoB5 };
    printROB (ReorderBuffer);
    //
    //#######################################################################
    
    //########################################################################
    //
    CommonDataBus commonDataBus = CommonDataBus ();
    
    //
    //########################################################################
    
    cout << "Comienzo de la simulacion: "<<endl;
    cout<< "-------------------------------------------------"<<endl<<endl;
   
    /*
    do
    {   
       GLOBAL_CLOCK++;
       issue (instructionsVector, functionalUnits,fPointRegisters,rRegisters);
       execute (instructionsVector, functionalUnits,fPointRegisters,rRegisters);
       writeBack (instructionsVector, functionalUnits,fPointRegisters,rRegisters);
       
       
       printFPRegisters (fPointRegisters);
       printFunctionalUnits (functionalUnits);
       printTimingTable (instructionsVector);
       
       if (totalInstFinished == instructionsVector.size () )
           finish = true;
       cout << endl;
    }while (!finish);
    */
    return 0;
}


int issue (vector<Instruction>& instr,
          vector<ReservationStation>& reserStations,
          vector<FPointRegister>& fPRegs,
          vector<RRegisters>& rRegs)
{
    
    
}



void printFunctionalUnits (vector<ReservationStation> functionalUnits)
{
    cout << "Estado de las estaciones de reserva" << endl;
    for (int i = 0; i < functionalUnits.size(); i++)
    {
        functionalUnits [i].toPrint();   
    }
    cout<<endl;
}

void printRRegisters (vector <RRegisters> rRegisters)
{
    cout << "Estado de los R- Registers" << endl;
    for (int i = 0; i < rRegisters.size(); i++)
    {
        rRegisters[i].toPrint();
    }
    cout<<endl;
}

void printFPRegisters (vector <FPointRegister> fPointRegisters)
{
    cout << "Estado de los FP Registers" << endl;
    for (int i = 0; i < fPointRegisters.size(); i++)
    {
        fPointRegisters [i].toPrint();
    }
    cout << endl;
}

void printInstructions (vector <Instruction> INSTRUCTIONS)
{
    cout << "Instrucciones a Ejecutar" << endl;
    for (int i = 0; i < INSTRUCTIONS.size(); i++)
    {
        INSTRUCTIONS [i].toPrint();
    }
    cout << endl;
}

void printTimingTable(vector<Instruction> INST)
{
    char separator    = ' ';
    const int width     = 10;
    char lineSeperator = '-';
    const int lineWidth = 30;

    // Define column labels
    cout << left << setw(width) << setfill(separator) << "Inst";
    cout << left << setw(width) << setfill(separator) << "Issue";
    cout << left << setw(width) << setfill(separator) << "Execute";
    cout << left << setw(width) << setfill(separator) << "WB";
    cout << left << setw(width) << setfill(separator) << "Commit";
    cout << left << setw(width) << setfill(separator) << "SystemClock"
    << endl;
    cout << right << setw(width*6) << setfill(separator) << GLOBAL_CLOCK;
    cout << endl;
    cout << left << setw(lineWidth) << setfill(lineSeperator);
    cout << endl;
    // Define Row Labels and values
    for(int i=0;i<INST.size();i++)
    {
        cout << left  << setw(width) << setfill(separator) << i;
        cout << left << setw(width) << setfill(separator) << INST[i].getIssueClock();
        cout << INST[i].getExecuteClockBegin() <<  "-";
        cout << left << setw(width) << setfill(separator)  << INST[i].getExecuteClockEnd();
        cout << left << setw(width) << setfill(separator) << INST[i].getWriteBackClock();
        cout << left << setw(width) << setfill(separator) << INST[i].getCommitClock();
        cout << endl;
    }
}

void printROB (vector<ROB> ROBuff)
{
    for (int i = 0; i < ROBuff.size(); i++)
    {
        ROBuff [i].toPrint();
    }
    cout<<endl;
}
