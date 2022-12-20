#include "common.h"
#include "gasInfo.h"
#include "gasInfoAccess.h"
#include "gasManage.h"
#include "elecInfo.h"
#include "screenOut.h"

void showMenu() {
	printf("��������������������������������������������������������������������������������������\n");
	printf("��      ������ & ���⼼ ��� ���α׷�      ��\n");
	printf("��������������������������������������������������������������������������������������\n");
	printf("    - - - - - - - �� �� �� - - - - - - -   \n");
	printf("	1. ������ �Է�\n");
	printf("	2. ��ü ������ Ȯ��\n");
	printf("	3. ������ �̳���->���� ����\n");
	printf("	4. ������ ����\n");
	printf("    - - - - - - - �� �� �� - - - - - - -   \n");
	printf("	5. ���⼼ �Է�\n");
	printf("	6. ��ü ���⼼ Ȯ��\n");
	printf("	7. ���⼼ �̳���->���� ����\n");
	printf("	8. ���⼼ ����\n");
	printf("    - - - - - - - - - - - - - - - - - - -  \n");
	printf("	9. ����\n");
	printf("��������������������������������������������������������������������������������������\n");
	printf(" >> ");
}

void showGasInfo(gasInfo* gas) {
	printf("%s ~ %s\n", gas->startGas, gas->endGas);
	printf("������: %d��    ", gas->costGas);
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
	printf("���⼼: %d��    ", elec->elecBill);
	if (elec->inputPayElecBill == 1) {
		printf("%s\n", printGasPay());
	}
	else if (elec->inputPayElecBill == 2) {
		printf("%s\n", printNoGasPay());
	}
	printf("  - - - - - - - - - - - - - - - - - - -  \n");
}

const char* printGasPay() {
	return "����";
}
const char* printNoGasPay() {
	return "�̳���";
}

/* void showFileMenu() {
	printf("��������������������������������������������������������������������������������������\n");
	printf("	1. �� ���� �Է�\n");
	printf("	2. ���� �ҷ�����\n");
	printf("	3. ����\n");
	printf("��������������������������������������������������������������������������������������\n");
	printf(" >> ");
} */

/* void showGasFile(gasName* gasFName) {
	printf("   [%d] %s\n", numOfGasName, gasFName->gasFileName);
} */