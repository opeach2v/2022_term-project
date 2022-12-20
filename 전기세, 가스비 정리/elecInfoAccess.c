#include "common.h"
#include "elecInfo.h"
#include "elecInfoAccess.h"
#include "screenOut.h"

int addElecInfo(char* startElec, char* endElec, int elecBill, int inputPayElecBill) {
	elecInfo* pElec;
	if (numOfElec >= LIST_ELECBILL) return 0;	//�Է� ����

	pElec = (elecInfo*)malloc(sizeof(elecInfo));
	strcpy(pElec->startElec, startElec);	//���ڿ� ��¼�� �����
	strcpy(pElec->endElec, endElec);
	pElec->elecBill = elecBill;
	pElec->inputPayElecBill = inputPayElecBill;

	totalElec += elecBill;
	elecList[numOfElec++] = pElec;

	avg_Elec = (double)totalElec / numOfElec;

	StoreElecListToFile();

	return numOfElec;
}

//��ü ���⼼ Ȯ��
void showAllElec() {
	int i;

	if (numOfElec == 0) {
		printf("�Է¹��� ���⼼�� �����ϴ�.\n");
		return;
	}

	printf("\n������������������������������������ü ���⼼������������������������������\n");
	for (i = 0; i < numOfElec; i++) {
		showElecInfo(elecList[i]);
	}

	printf(" �� ���⼼ ���: %.0lf��\n", avg_Elec);
	MAX_MIN_Elec();
}

//���⼼ �ִ�, �ּڰ� ���
void MAX_MIN_Elec() {
	int i;
	int maxElec = 0, minElec = 0;

	char maxElecDayStart[GASYMD_LEN];
	char maxElecDayEnd[GASYMD_LEN];
	char minElecDayStart[GASYMD_LEN];
	char minElecDayEnd[GASYMD_LEN];

	maxElec = elecList[0]->elecBill;
	strcpy(maxElecDayStart, elecList[0]->startElec);
	strcpy(maxElecDayEnd, elecList[0]->endElec);

	minElec = elecList[0]->elecBill;
	strcpy(minElecDayStart, elecList[0]->startElec);
	strcpy(minElecDayEnd, elecList[0]->endElec);

	for (i = 1; i < numOfElec; i++) {
		if (maxElec < elecList[i]->elecBill) {
			maxElec = elecList[i]->elecBill;
			strcpy(maxElecDayStart, elecList[i]->startElec);
			strcpy(maxElecDayEnd, elecList[i]->endElec);
		}
		if (minElec > elecList[i]->elecBill) {
			minElec = elecList[i]->elecBill;
			strcpy(minElecDayStart, elecList[i]->startElec);
			strcpy(minElecDayEnd, elecList[i]->endElec);
		}
	}

	printf(" �� �ְ� ������: %d��", maxElec);
	printf("  (% s ~ % s)\n", maxElecDayStart, maxElecDayEnd);
	printf(" �� ���� ������: %d��", minElec);
	printf("  (% s ~ % s)\n", minElecDayStart, minElecDayEnd);
}

//���⼼ ����
void deleteElecInfo() {
	int i, deleteElecExit;
	char deleteStartElec[GASYMD_LEN];

	int matchingElec[LIST_ELECBILL];	//match÷�� ����� �迭
	int matchedCountElec = 0;
	int delElec = 0;

	while (1) {
		printf("(1) ����ϱ�   (2) ������ >>  ");
		scanf("%d", &deleteElecExit);

		if (deleteElecExit == 1) {
			printf("\n�����Ϸ��� ���⼼ ���� ���� ��¥(YYYY-MM-DD) >> ");
			scanf("%s", deleteStartElec);
			break;
		}
		else if (deleteElecExit == 2) {
			printf("\n���ư��ϴ�.\n");
			return;
		}
		else {
			printf("\n�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
		}
		printf("\n");
	}

	for (i = 0; i < numOfElec; i++) {
		if (strcmp(elecList[i]->startElec, deleteStartElec) == 0) {	//�� ���ڿ��� ������
			matchingElec[matchedCountElec++] = i;
			totalElec -= elecList[i]->elecBill;
		}
	}

	if (matchedCountElec == 0) {
		printf("\nã�� ��¥�� �������� �ʽ��ϴ�.\n");
		return;
	}
	else if (matchedCountElec == 1) {
		delElec = matchingElec[0];
	}

	//�ϳ��� ������ �̵�
	for (i = delElec; i < numOfElec - 1; i++) {
		free(elecList[delElec]);
		elecList[i] = elecList[i + 1];
	}
	numOfElec--;
	printf("\n������ �Ϸ�Ǿ����ϴ�.\n");

	avg_Elec = (double)totalElec / numOfElec;

	StoreElecListToFile();

	return avg_Elec;
}

//����, �̳��� ǥ�� ����
void changeElecPay() {
	int i, input_check, changePayElecBill;
	char changePayStartElec[GASYMD_LEN];

	int matchingPayGas[LIST_ELECBILL];	//match÷�� ����� �迭
	int matchedCountPayGas = 0;
	int chaGas = 0;

	while (1) {
		printf("(1) ����ϱ�   (2) ������ >>  ");
		scanf("%d", &input_check);

		if (input_check == 1) {
			printf("\n���η� ������ ������ ���� ���� ��¥(YYYY-MM-DD) >> ");
			scanf("%s", changePayStartElec);
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

	for (i = 0; i < numOfElec; i++) {
		if (strcmp(elecList[i]->startElec, changePayStartElec) == 0) {	//�� ���ڿ��� ������
			matchingPayGas[matchedCountPayGas++] = i;
		}
	}

	if (matchedCountPayGas == 0) {
		printf("\nã�� ��¥�� �������� �ʽ��ϴ�.\n");
		return;
	}
	else if (matchedCountPayGas == 1) {
		chaGas = matchingPayGas[0];
		if (elecList[chaGas]->inputPayElecBill == 1) {
			printf("\n�̹� ������ �����Դϴ�.\n");
			return;
		}
	}

	if (elecList[chaGas]->inputPayElecBill == 2) {
		while (1) {
			printf("\n������ �����ϼ̽��ϱ�?\n");
			printf("(1) ��   (2) �ƴϿ� >> ");
			scanf("%d", &changePayElecBill);
			if (changePayElecBill == 1) {
				elecList[chaGas]->inputPayElecBill = changePayElecBill;
				break;
			}
			else if (changePayElecBill == 2) {
				printf("\n�����ϰ� �ٽ� ������.\n");
				return;
			}
			else printf("\n�Է¿� �����߽��ϴ�. �ٽ� �Է��ϼ���.\n\n");
		}
	}
	printf("\n���η� ����Ǿ����ϴ�.\n");

	StoreElecListToFile();
}

//������ ���� ���Ͽ� ����
void StoreElecListToFile() {
	int i;
	FILE* efp = fopen("ELEC_FILE.dat", "wb");
	if (efp == NULL) return;

	fwrite(&numOfElec, sizeof(int), 1, efp);
	for (i = 0; i < numOfElec; i++) {
		fwrite(elecList[i], sizeof(elecInfo), 1, efp);
	}
	fprintf(efp, "%d ", totalElec);
	fprintf(efp, "%lf ", avg_Elec);

	fclose(efp);
}

//������ ���� ���Ϸκ��� ����
void LoadElecListFromFile() {
	int i;
	FILE* efp = fopen("ELEC_FILE.dat", "rb");
	if (efp == NULL) return;

	fread(&numOfElec, sizeof(int), 1, efp);
	for (i = 0; i < numOfElec; i++) {
		elecList[i] = (elecInfo*)malloc(sizeof(elecInfo));
		fread(elecList[i], sizeof(elecInfo), 1, efp);
	}
	fscanf(efp, "%d ", &totalElec);
	fscanf(efp, "%lf ", &avg_Elec);

	fclose(efp);
}