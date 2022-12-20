#pragma once

#ifndef __ELECINFO_H__
#define __ELECINFO_H__

#define ELECYMD_LEN 30

typedef struct __elecInfo {
	char startElec[ELECYMD_LEN];
	char endElec[ELECYMD_LEN];
	int elecBill;	//Àü±â¼¼
	int inputPayElecBill;
}elecInfo;

#endif