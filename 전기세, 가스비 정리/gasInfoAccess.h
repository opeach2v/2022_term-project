#pragma once

#ifndef __GASINFOACCESS_H__
#define __GASINFOACCESS_H__

#include "gasInfo.h"
#define LIST_COSTGAS 100

static gasInfo* gasList[LIST_COSTGAS];
static int numOfGas;
static int totalGas;	//°¡½ººñ ÃÑÇÕ
static double avg_Gas;

FILE* gfp;

int addGasInfo(char* startGas, char* endGas, int costGas, int inputPayCostGas);
void showAllGas();
void MAX_MIN_Gas();
void deleteGasInfo();
void changeGasPay();

void StoreGasListToFile();
void LoadGasListFromFile();

#endif