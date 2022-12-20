#include "common.h"
#include "gasInfo.h"
#include "gasInfoAccess.h"
#include "gasManage.h"
#include "elecInfo.h"
#include "screenOut.h"

void showMenu() {
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃      가스비 & 전기세 기록 프로그램      ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("    - - - - - - - 가 스 비 - - - - - - -   \n");
	printf("	1. 가스비 입력\n");
	printf("	2. 전체 가스비 확인\n");
	printf("	3. 가스비 미납부->납부 변경\n");
	printf("	4. 가스비 삭제\n");
	printf("    - - - - - - - 전 기 세 - - - - - - -   \n");
	printf("	5. 전기세 입력\n");
	printf("	6. 전체 전기세 확인\n");
	printf("	7. 전기세 미납부->납부 변경\n");
	printf("	8. 전기세 삭제\n");
	printf("    - - - - - - - - - - - - - - - - - - -  \n");
	printf("	9. 종료\n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf(" >> ");
}

void showGasInfo(gasInfo* gas) {
	printf("%s ~ %s\n", gas->startGas, gas->endGas);
	printf("가스비: %d원    ", gas->costGas);
	if (gas->inputPayCostGas == 1) {
		printf("%s\n", printGasPay());
	}
	else if (gas->inputPayCostGas == 2) {
		printf("%s\n", printNoGasPay());
	}
	printf("  - - - - - - - - - - - - - - - - - - -  \n");
}

void showElecInfo(elecInfo* elec) {
	printf("%s ~ %s\n", elec->startElec, elec->endElec);
	printf("전기세: %d원    ", elec->elecBill);
	if (elec->inputPayElecBill == 1) {
		printf("%s\n", printGasPay());
	}
	else if (elec->inputPayElecBill == 2) {
		printf("%s\n", printNoGasPay());
	}
	printf("  - - - - - - - - - - - - - - - - - - -  \n");
}

const char* printGasPay() {
	return "납부";
}
const char* printNoGasPay() {
	return "미납부";
}

/* void showFileMenu() {
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("	1. 새 파일 입력\n");
	printf("	2. 파일 불러오기\n");
	printf("	3. 종료\n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf(" >> ");
} */

/* void showGasFile(gasName* gasFName) {
	printf("   [%d] %s\n", numOfGasName, gasFName->gasFileName);
} */