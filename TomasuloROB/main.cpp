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
int pointerHead = 0;
int pointerIssued = 0;
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
          vector<RRegisters>& rRegs,
          vector<ROB> &rBuff);

int execute (vector<Instruction>& instr,
          vector<ReservationStation>& reserStations,
          vector<FPointRegister>& fPRegs,
          vector<RRegisters>& rRegs,
          vector<ROB> &rBuff);

int writeBack (vector<Instruction>& instr,
          vector<ReservationStation>& reserStations,
          vector<FPointRegister>& fPRegs,
          vector<RRegisters>& rRegs,
          vector<ROB> &rBuff,
          CommonDataBus &cDB);

int commit (vector<Instruction>& instr,
          vector<ReservationStation>& reserStations,
          vector<FPointRegister>& fPRegs,
          vector<RRegisters>& rRegs,
          vector<ROB> &rBuff);




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
    
    vector<ROB> reorderBuffer = {RoB0, RoB1, RoB2, RoB3, RoB4, RoB5 };
    printROB (reorderBuffer);
    //
    //#######################################################################
    
    //########################################################################
    //
    CommonDataBus commonDataBus = CommonDataBus ();
    
    //
    //########################################################################
    
    cout << "Comienzo de la simulacion: "<<endl;
    cout<< "-------------------------------------------------"<<endl<<endl;
   
    do
    {   
       GLOBAL_CLOCK++;
       issue (instructionsVector, functionalUnits,fPointRegisters,
              rRegisters, reorderBuffer);
       execute (instructionsVector, functionalUnits,fPointRegisters,
              rRegisters, reorderBuffer);
       writeBack (instructionsVector, functionalUnits,fPointRegisters,
              rRegisters, reorderBuffer, commonDataBus);
       commit (instructionsVector, functionalUnits, fPointRegisters,
               rRegisters, reorderBuffer);
       
       printTimingTable (instructionsVector);
       printROB (reorderBuffer);
       printFPRegisters (fPointRegisters);
       printFunctionalUnits (functionalUnits);
       cout<< "Variables globales: "<<endl;
       cout<<"Pointer Head: "<< pointerHead << " Pointer Issued: "<< pointerIssued << endl;
       
       if (totalInstFinished == instructionsVector.size () )
           finish = true;
       cout << "----------------------------------------------------"<<endl;
       cout << endl << endl;
       
    }while (!finish);
    
    return 0;
}


int issue (vector<Instruction>& instr,
          vector<ReservationStation>& reserStations,
          vector<FPointRegister>& fPRegs,
          vector<RRegisters>& rRegs,
          vector<ROB> &reorderBuffer)
{
    bool banderaIssue = false;
    int indexToROB = 0;
    int indexToReser = 0;
    
    
    //IMPORTANTE SACAR LA BANDERA FINISH
    //Ya se hizo issue de todas las instrucciones del vector 
    if (instructionsIssued >= instr.size ()) 
        return 0;


    
    OperationsEnum operando = instr [instructionsIssued].getOpCode();
    
    if (operando == OperationsEnum::MUL || operando == OperationsEnum::DIV)
    {
        for (int i = 0; i < reserStations.size(); i++)
        {
            if (reserStations [i].getType() == OperationsEnum::MUL &&
                !reserStations [i].isBusy() && !reorderBuffer[pointerIssued].isBusy())
            {
                banderaIssue = true;
                indexToReser = i;
                indexToROB = pointerIssued;
                reserStations [i].setOperation(operando);
                pointerIssued = (pointerIssued + 1) % reorderBuffer.size();
                instructionsIssued++;
                break;
            }
        }
    }
    else if (operando == OperationsEnum::ADD || operando == OperationsEnum::SUB)
    {
        for (int i = 0; i < reserStations.size (); i++)
        {
            if (reserStations [i].getType() == OperationsEnum::ADD &&
                !reserStations [i].isBusy() && !reorderBuffer [pointerIssued].isBusy())
            {
                banderaIssue = true;
                indexToReser = i;
                indexToROB = pointerIssued;
                reserStations [i].setOperation(operando);
                pointerIssued = (pointerIssued + 1) % reorderBuffer.size();
                instructionsIssued++;
                break;
            }
        }
    }
    else
    {
        for (int i = 0; i < reserStations.size (); i++)
        {
            if (reserStations[i].getType() == OperationsEnum::LOAD &&
                !reserStations[i].isBusy() && !reorderBuffer[pointerIssued].isBusy())
            {
                 banderaIssue = true;
                indexToReser = i;
                indexToROB = pointerIssued;
                reserStations [i].setOperation(operando);
                pointerIssued = (pointerIssued + 1) % reorderBuffer.size();
                instructionsIssued++;
                break;
            }
        }
    }
     
    if (!banderaIssue)
        return 1;
    
    
    FPRegNames name_rd = instr [instructionsIssued - 1].getRd();
    
    if (operando != OperationsEnum::LOAD)
    {
        FPRegNames name_rs = instr [instructionsIssued - 1].getRsFp();
        FPRegNames name_rt = instr [instructionsIssued - 1].getRtFp();
        for (int i = 0; i < fPRegs.size(); i++)
        {
            if (name_rs == fPRegs[i].getName())
            {
                if (!fPRegs [i].isBusy())
                {
                    reserStations [indexToReser].setVj(fPRegs[i].getValue());
                    reserStations [indexToReser].setQj(ROBNames::UNDEF);
                }
                else
                {
                    for (int j = 0; j < reorderBuffer.size(); j++)
                    {
                        if (reorderBuffer [j].getDestination() == name_rs)
                        {
                            if (reorderBuffer [j].isDone())
                            {
                                reserStations [indexToReser].setVj
                                (reorderBuffer [j].getResult());
                                reserStations [indexToReser].setQj(ROBNames::UNDEF);
                            }
                            else
                            {
                                reserStations [indexToReser].setQj(reorderBuffer [j].getName());
                            }
                        }
                    }
                }
            }
            if (name_rt == fPRegs [i].getName())
            {
                if (!fPRegs [i].isBusy()) 
                {
                    reserStations [indexToReser].setVk(fPRegs[i].getValue());
                    reserStations [indexToReser].setQk(ROBNames::UNDEF);
                } 
                else 
                {
                    for (int j = 0; j < reorderBuffer.size(); j++) 
                    {
                        if (reorderBuffer [j].getDestination() == name_rt) 
                        {
                            if (reorderBuffer [j].isDone()) 
                            {
                                reserStations [indexToReser].setVk
                                        (reorderBuffer [j].getResult());
                                reserStations [indexToReser].setQk(ROBNames::UNDEF);
                            } else 
                            {
                                reserStations [indexToReser].setQk(reorderBuffer [j].getName());
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        RRegistersNames offset_register = instr [instructionsIssued - 1].getRtR();
        int immediate = instr [instructionsIssued - 1].getRsVal();
        for (int i = 0; i < rRegs.size(); i++) 
        {
            if (offset_register == rRegs[i].getRegisterName()) {
                reserStations [indexToReser].setVj(rRegs[i].getRegisterValue());
                reserStations [indexToReser].setAddress(immediate);
            }
        }
    }
    reserStations [indexToReser].setIndexToInstruction(instructionsIssued - 1);
    reserStations [indexToReser].setBusy(true);
    reserStations [indexToReser].setIssueLatency(0);
    reserStations [indexToReser].setDestiny(reorderBuffer[indexToROB].getName());
    instr [instructionsIssued -1].setIssueClock(GLOBAL_CLOCK);
    for (int i = 0; i < fPRegs.size (); i++)
    {
        if (name_rd == fPRegs [i].getName())
        {
            fPRegs [i].setBusy(true);
            fPRegs [i].setTag(reorderBuffer[indexToROB].getName());
        }
    }
    reorderBuffer [indexToROB].setDestination(name_rd);
    reorderBuffer [indexToROB].setInstructionAssociated(instructionsIssued -1);
    reorderBuffer [indexToROB].setDone(false);
    reorderBuffer [indexToROB].setBusy(true);
    
    
    return 2;
}

int execute (vector<Instruction>& instr,vector<ReservationStation>& reserStations,
          vector<FPointRegister>& fPRegs, vector<RRegisters>& rRegs,
          vector<ROB> &rBuff)
{
    for (int i = 0; i < reserStations.size(); i++) 
    {
        if (reserStations [i].isBusy()) 
        {
            if (reserStations [i].getIssueLatency() >= ISSUE_LATENCY) 
            {
                if (reserStations [i].getQj() == ROBNames::UNDEF &&
                        reserStations [i].getQk() == ROBNames::UNDEF)
                {
                    if (instr [reserStations[i].getIndexOfInstruction()].getExecuteClockBegin() == 0)
                        instr [reserStations [i].getIndexOfInstruction()].setExecuteClockBegin(GLOBAL_CLOCK);

                    //aumento en 1 la latencia
                    reserStations [i].setLatency(reserStations [i].getLatency() + 1);
                    switch (reserStations [i].getOperation()) 
                    {
                        case (OperationsEnum::ADD):
                            if (reserStations [i].getLatency() == ADD_LATENCY) 
                            {
                                reserStations [i].calculateResult();
                                instr [reserStations [i].getIndexOfInstruction()].
                                        setExecuteClockEnd(GLOBAL_CLOCK);
                            }
                            break;
                        case (OperationsEnum::SUB):
                            if (reserStations [i].getLatency() == SUB_LATENCY) 
                            {
                                reserStations [i].calculateResult();
                                instr [reserStations [i].getIndexOfInstruction()].
                                        setExecuteClockEnd(GLOBAL_CLOCK);
                            }
                            break;
                        case (OperationsEnum::MUL):
                            if (reserStations [i].getLatency() == MULT_LATENCY) 
                            {
                                reserStations [i].calculateResult();
                                instr [reserStations [i].getIndexOfInstruction()].
                                        setExecuteClockEnd(GLOBAL_CLOCK);
                            }
                            break;
                        case (OperationsEnum::DIV):
                            if (reserStations [i].getLatency() == DIV_LATENCY) 
                            {
                                reserStations [i].calculateResult();
                                instr [reserStations [i].getIndexOfInstruction()].
                                        setExecuteClockEnd(GLOBAL_CLOCK);
                            }
                            break;
                        case (OperationsEnum::LOAD):
                            if (reserStations [i].getLatency() == LOAD_LATENCY) 
                            {

                                reserStations [i].executeLoad();
                                instr [reserStations [i].getIndexOfInstruction()].
                                        setExecuteClockEnd(GLOBAL_CLOCK);
                            }
                            break;
                        default:
                            break;
                    }
                }
            } 
            else 
            {
                reserStations [i].setIssueLatency(reserStations [i].
                        getIssueLatency() + 1);
            }
        }
    }

}

int writeBack (vector<Instruction>& instr,
          vector<ReservationStation>& reserStations,
          vector<FPointRegister>& fPRegs,
          vector<RRegisters>& rRegs,
          vector<ROB> &rBuff,
          CommonDataBus &cDB)
{
    for (int i = 0; i < reserStations.size() ; i++)
    {
        //check if result is ready
        if (reserStations [i].isReady())
        {
            //and 1 cycle of WB of delay happen
            if (reserStations [i].getWriteBackLatency() >= WB_LATENCY 
                && cDB.isAvailable())
            {
                if (instr [reserStations [i].getIndexOfInstruction()].getWriteBackClock() == 0)
                    instr [reserStations [i].getIndexOfInstruction()].setWriteBackClock(GLOBAL_CLOCK);
                
                cDB.setResult(reserStations [i].getResult());
                cDB.setAvailable(false);
                cDB.setDestiny(reserStations[i].getDestiny());
                
                //Grabar en el ROB Correspondiente el resultado
                //obtenido en la estacion de reserva asociada.
                for (int x = 0; x < rBuff.size(); x++)
                {
                    if (rBuff [x].getName() == cDB.getDestiny())
                    {
                        rBuff [x].setResult(cDB.getResult());
                        rBuff [x].setDone(true);
                    }
                }
                
                for (int x = 0; x < reserStations.size(); x++)
                {
                    if (reserStations [x].getQj() == cDB.getDestiny())
                    {
                        reserStations [x].setVj(cDB.getResult());
                        reserStations [x].setQj(ROBNames::UNDEF);
                    }
                    if (reserStations [x].getQk () == cDB.getDestiny())
                    {
                        reserStations [x].setVk (cDB.getResult());
                        reserStations [x].setQk (ROBNames::UNDEF);
                    }
                }
                //resetear la estacion  de reserva asi se libera
                reserStations [i].flush();
               // totalInstFinished++;
                
            }
            else
            {
                reserStations [i].setWriteBackLatency(reserStations [i].getWriteBackLatency() + 1);
            }
        }
    }
    //liberamos el CDB AQUI ASI SE UTILIZA SOLO UNA VEZ
    cDB.setAvailable(true);
    cDB.setResult(0);
    cDB.setDestiny(ROBNames::UNDEF);
}

int commit (vector<Instruction>& instr,
          vector<ReservationStation>& reserStations,
          vector<FPointRegister>& fPRegs,
          vector<RRegisters>& rRegs,
          vector<ROB> &rBuff)
{
    for (int i = 0; i < rBuff.size(); i++)
    {
        if (rBuff [i].isDone())
        {
            if (rBuff [i].getCommitLatency() >= COMMIT_LATENCY && i == pointerHead )
            {
                if (instr [rBuff [i].getInstructionAssociated()].getCommitClock() == 0)
                    instr [rBuff [i].getInstructionAssociated()].setCommitClock(GLOBAL_CLOCK);
                
                FPRegNames aux = rBuff [i].getDestination();
                for (int j = 0; j < fPRegs.size (); j++)
                {
                    if (fPRegs [j].getName() == aux)
                    {
                        fPRegs [j].setBusy(false);
                        fPRegs [j].setValue(rBuff [i].getResult());
                        fPRegs [j].setTag(ROBNames::UNDEF);
                    }
                }
                rBuff [i].setBusy(false);
                rBuff [i].setDone(false);
                rBuff [i].setCommitLatency(0);
                rBuff [i].setResult(0);
                rBuff [i].setDestination(FPRegNames::NON);
                totalInstFinished++;
                pointerHead = (pointerHead + 1) % rBuff.size();
                break; //para que no se comiteen varias en el mismo ciclo
            }
            else
            {
                rBuff [i].setCommitLatency(rBuff [i].getCommitLatency() + 1);
            }
        }
    }
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
