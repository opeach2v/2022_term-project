#pragma once

#ifndef __GASINFO_H__
#define __GASINFO_H__

#define GASYMD_LEN 30

typedef struct __gasInfo {
	char startGas[GASYMD_LEN];
	char endGas[GASYMD_LEN];
	int costGas;	//°¡½ººñ
	int inputPayCostGas;
}gasInfo;

#endif