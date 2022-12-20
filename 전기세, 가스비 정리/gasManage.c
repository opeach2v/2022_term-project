#include "common.h"
#include "gasInfo.h"
#include "gasInfoAccess.h"
#include "screenOut.h"


void inputGas() {
	char startGas[GASYMD_LEN];
	char endGas[GASYMD_LEN];
	int costGas = 0;	//������
	int inputPayCostGas = 0;
	int input_Gas;

	while (1) {
		printf("(1) ����ϱ�   (2) ������ >>  ");
		scanf("%d", &input_Gas);

		if (input_Gas == 1) {
			printf("\n");
			break;
		}
		else if (input_Gas == 2) {
			printf("���ư��ϴ�.\n");
			return;
		}
		else {
			printf("\n�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
		}
		printf("\n");
	}

	printf("���� ���� ���� ��¥(YYYY-MM-DD) >> ");
	scanf("%s", startGas);
	printf("���� ���� �� ��¥(YYYY-MM-DD) >> ");
	scanf("%s", endGas);
	printf("������ >> ");
	scanf("%d", &costGas);
	printf("\n");

	while (1) {
		printf("(1) ������ ����   (2) ������ �̳��� >> ");
		scanf("%d", &inputPayCostGas);
		if (inputPayCostGas == 1 || inputPayCostGas == 2) {
			printf("\n");
			break;
		}
		else printf("\n�Է¿� �����߽��ϴ�. �ٽ� �Է��ϼ���.\n");
	}

	if (addGasInfo(startGas, endGas, costGas, inputPayCostGas) == 0) {
		printf("�Է¿� �����߽��ϴ�.\n");
		return;
	}

	printf("�Է��� �Ϸ�Ǿ����ϴ�\n");
}

/* void inputGasFile() {
	char gasFileName[GASNAME_LEN];
	int inputFGas;

	while (1) {
		printf("(1) ����ϱ�   (2) ������ >>  ");
		scanf("%d", &inputFGas);

		if (inputFGas == 1) {
			printf("\n");
			break;
		}
		else if (inputFGas == 2) {
			printf("���ư��ϴ�.\n");
			return;
		}
		else {
			printf("\n�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
		}
		printf("\n");
	}

	printf("���ο� ������ ���� �̸� �Է� >> ");
	scanf("%s", gasFileName);
	printf("\n");

	if (addGasFile(gasFileName) == 0) {
		printf("�Է¿� �����߽��ϴ�.\n");
		return;
	}

	printf("�Է��� �Ϸ�Ǿ����ϴ�\n");
} */