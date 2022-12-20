#include "common.h"
#include "gasInfo.h"
#include "gasInfoAccess.h"
#include "gasManage.h"
#include "elecInfoAccess.h"
#include "elecManage.h"
#include "screenOut.h"

//Github test_

enum { input_GAS = 1, show_Gas, change_PayGas, delete_Gas,
	input_ELEC, show_Elec, change_PayElec, delete_Elec, EXIT };	//showMenu용 열거형 상수 1~8

int main() {
	int inputMenu;

	LoadGasListFromFile();
	LoadElecListFromFile();

	while (1) {
		showMenu();
		scanf("%d", &inputMenu);
		if (inputMenu == EXIT) break;

		switch (inputMenu) {
		case input_GAS:
			inputGas();
			break;
		case show_Gas:
			showAllGas();
			break;
		case change_PayGas:
			changeGasPay();
			break;
		case delete_Gas:
			deleteGasInfo();
			break;
		case input_ELEC:
			inputElec();
			break;
		case show_Elec:
			showAllElec();
			break;
		case change_PayElec:
			changeElecPay();
			break;
		case delete_Elec:
			deleteElecInfo();
			break;
		default:
			break;
		}
		printf("\n");
	}
}