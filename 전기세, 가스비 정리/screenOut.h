#pragma once

#ifndef __SCREENOUT_H__
#define __SCREENOUT_H__

#include "gasInfo.h"
#include "elecInfo.h"

void showMenu();
void showGasInfo(gasInfo* gas);
void showElecInfo(elecInfo* elec);

const char* printGasPay();
const char* printNoGasPay();

#endif