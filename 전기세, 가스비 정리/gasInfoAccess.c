#include "common.h"
#include "gasInfo.h"
#include "gasInfoAccess.h"
#include "gasManage.h"
#include "screenOut.h"

int addGasInfo(char* startGas, char* endGas, int costGas, int inputPayCostGas) {
	gasInfo *pGas;
	if (numOfGas >= LIST_COSTGAS) return 0;	//�Է� ����

	pGas = (gasInfo*)malloc(sizeof(gasInfo));
	strcpy(pGas->startGas, startGas);	//���ڿ� ��¼�� �����
	strcpy(pGas->endGas, endGas);
	pGas->costGas = costGas;
	pGas->inputPayCostGas = inputPayCostGas;
	
	totalGas += costGas;
	gasList[numOfGas++] = pGas;

	avg_Gas = (double)totalGas / numOfGas;

	StoreGasListToFile();

	return numOfGas, totalGas, avg_Gas;
}

//��ü ������ Ȯ��
void showAllGas() {
	int i;

	if (numOfGas == 0) {
		printf("�Է¹��� ������ �����ϴ�.\n");
		return;
	}
	printf("\n������������������������������������ü �����񦬦���������������������������\n");
	for (i = 0; i < numOfGas; i++) {
		showGasInfo(gasList[i]);
	}

	printf(" �� ������ ���: %.0lf��\n", avg_Gas);
	MAX_MIN_Gas();
}

//������ �ִ�, �ּڰ� ���
void MAX_MIN_Gas() {
	int i;
	int maxGas = 0, minGas = 0;

	char maxGasDayStart[GASYMD_LEN];
	char maxGasDayEnd[GASYMD_LEN];
	char minGasDayStart[GASYMD_LEN];
	char minGasDayEnd[GASYMD_LEN];

	maxGas = gasList[0]->costGas;
	strcpy(maxGasDayStart, gasList[0]->startGas);
	strcpy(maxGasDayEnd, gasList[0]->endGas);

	minGas = gasList[0]->costGas;
	strcpy(minGasDayStart, gasList[0]->startGas);
	strcpy(minGasDayEnd, gasList[0]->endGas);

	for (i = 1; i < numOfGas; i++) {
		if (maxGas < gasList[i]->costGas) {
			maxGas = gasList[i]->costGas;
			strcpy(maxGasDayStart, gasList[i]->startGas);
			strcpy(maxGasDayEnd, gasList[i]->endGas);
		}
	}
	for (i = 1; i < numOfGas; i++) {
		if (minGas > gasList[i]->costGas) {
			minGas = gasList[i]->costGas;
			strcpy(minGasDayStart, gasList[i]->startGas);
			strcpy(minGasDayEnd, gasList[i]->endGas);
		}
	}

	printf(" �� �ְ� ������: %d��", maxGas);
	printf("  (%s ~ %s)\n", maxGasDayStart, maxGasDayEnd);
	printf(" �� ���� ������: %d��", minGas);
	printf("  (%s ~ %s)\n", minGasDayStart, minGasDayEnd);
}

//������ ����
void deleteGasInfo() {
	int i, deleteGasExit;
	char deleteStartGas[GASYMD_LEN];

	int matchingGas[LIST_COSTGAS];	//match÷�� ����� �迭
	int matchedCountGas = 0;
	int delGas = 0;

	while (1) {
		printf("(1) ����ϱ�   (2) ������ >>  ");
		scanf("%d", &deleteGasExit);

		if (deleteGasExit == 1) {
			printf("\n�����Ϸ��� ������ ���� ���� ��¥(YYYY-MM-DD) >> ");
			scanf("%s", deleteStartGas);
			break;
		}
		else if (deleteGasExit == 2) {
			printf("\n���ư��ϴ�.\n");
			return;
		}
		else {
			printf("\n�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
		}
		printf("\n");
	}

	for (i = 0; i < numOfGas; i++) {
		if (strcmp(gasList[i]->startGas, deleteStartGas) == 0) {	//�� ���ڿ��� ������
			matchingGas[matchedCountGas++] = i;
			totalGas -= gasList[i]->costGas;
		}
	}

	if (matchedCountGas == 0) {
		printf("\nã�� ��¥�� �������� �ʽ��ϴ�.\n");
		return;
	}
	else if (matchedCountGas == 1) {
		delGas = matchingGas[0];
	}

	//�ϳ��� ������ �̵�
	for (i = delGas; i < numOfGas - 1; i++) {
		free(gasList[delGas]);
		gasList[i] = gasList[i + 1];
	}
	numOfGas--;
	printf("\n������ �Ϸ�Ǿ����ϴ�.\n");

	avg_Gas = (double)totalGas / numOfGas;

	StoreGasListToFile();

	return avg_Gas;
}

//����, �̳��� ǥ�� ����
void changeGasPay() {
	int i, input_check, changePayCostGas;
	char changePayStartGas[GASYMD_LEN];

	int matchingPayGas[LIST_COSTGAS];	//match÷�� ����� �迭
	int matchedCountPayGas = 0;
	int chaGas = 0;

	while (1) {
		printf("(1) ����ϱ�   (2) ������ >>  ");
		scanf("%d", &input_check);

		if (input_check == 1) {
			printf("\n���η� ������ ������ ���� ���� ��¥(YYYY-MM-DD) >> ");
			scanf("%s", changePayStartGas);
			break;
		}
		else if (input_check == 2) {
			printf("\n���ư��ϴ�.\n");
			return;
		}
		else {
			printf("\n�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
		}
	}

	for (i = 0; i < numOfGas; i++) {
		if (strcmp(gasList[i]->startGas, changePayStartGas) == 0) {	//�� ���ڿ��� ������
			matchingPayGas[matchedCountPayGas++] = i;
		}
	}

	if (matchedCountPayGas == 0) {
		printf("\nã�� ��¥�� �������� �ʽ��ϴ�.\n");
		return;
	}
	else if (matchedCountPayGas == 1) {
		chaGas = matchingPayGas[0];
		if (gasList[chaGas]->inputPayCostGas == 1) {
			printf("\n�̹� ������ �����Դϴ�.\n");
			return;
		}
	}
	
	if (gasList[chaGas]->inputPayCostGas == 2) {
		while (1) {
			printf("\n������ �����ϼ̽��ϱ�?\n");
			printf("(1) ��   (2) �ƴϿ� >> ");
			scanf("%d", &changePayCostGas);
			if (changePayCostGas == 1) {
				gasList[chaGas]->inputPayCostGas = changePayCostGas;
				break;
			}
			else if (changePayCostGas == 2) {
				printf("\n�����ϰ� �ٽ� ������.\n");
				return;
			}
			else printf("\n�Է¿� �����߽��ϴ�. �ٽ� �Է��ϼ���.\n\n");
		}
	}
	printf("\n���η� ����Ǿ����ϴ�.\n");

	StoreGasListToFile();
}

//������ ���� ���Ͽ� ����
void StoreGasListToFile() {
	int i;
	FILE* gfp = fopen("GAS_FILE.dat", "wb");
	if (gfp == NULL) return;

	fwrite(&numOfGas, sizeof(int), 1, gfp);
	for (i = 0; i < numOfGas; i++) {
		fwrite(gasList[i], sizeof(gasInfo), 1, gfp);
	}
	fprintf(gfp, "%d ", totalGas);
	fprintf(gfp, "%lf ", avg_Gas);

	fclose(gfp);
}

//������ ���� ���Ϸκ��� ����
void LoadGasListFromFile() {
	int i;
	FILE *gfp = fopen("GAS_FILE.dat", "rb");
	if (gfp == NULL) return;

	fread(&numOfGas, sizeof(int), 1, gfp);
	for (i = 0; i < numOfGas; i++) {
		gasList[i] = (gasInfo*)malloc(sizeof(gasInfo));
		fread(gasList[i], sizeof(gasInfo), 1, gfp);
	}
	fscanf(gfp, "%d ", &totalGas);
	fscanf(gfp, "%lf ", &avg_Gas);

	fclose(gfp);
}

/*int addGasFile(char* gasFileName) {
	gasName* pGasName;
	if (numOfGasName >= LIST_GASNAME) return 0;	//�Է� ����

	pGasName = (gasName*)malloc(sizeof(gasName));
	strcpy(pGasName->gasFileName, gasFileName);

	FILE* gfp = fopen(pGasName->gasFileName, "wb");

	gasNameList[numOfGasName++] = pGasName;

	return numOfGasName;
}*/
/* ��ü ���� ���� ����Ʈ Ȯ�� �� �Է�
void showAllGasList() {
	int i;

	if (numOfGasName == 0) {
		printf("������ �����ϴ�.\n");
		return;
	}
	printf("\n������������������������������������ ����Ʈ��������������������������������\n");
	for (i = 0; i < numOfGasName; i++) {
		showGasFile(gasNameList[i]);
	}
}*/