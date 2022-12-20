#pragma once

#ifndef __ELECINFOACCESS_H__
#define __ELECINFOACCESS_H__

#include "elecInfo.h"
#define LIST_ELECBILL 100

static elecInfo* elecList[LIST_ELECBILL];
static int numOfElec = 0;
static int totalElec = 0;	//Àü±â¼¼ ÃÑÇÕ
static double avg_Elec;

FILE* efp;

int addElecInfo(char* startElec, char* endElec, int elecBill, int inputPayElecBill);
void showAllElec();
void MAX_MIN_Elec();
void deleteElecInfo();
void changeElecPay();

void StoreElecListToFile();
void LoadElecListFromFile();

#endif