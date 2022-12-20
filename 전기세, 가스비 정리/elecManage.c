#include "common.h"
#include "elecInfo.h"
#include "elecInfoAccess.h"
#include "elecManage.h"
#include "screenOut.h"

void inputElec() {
	char startElec[ELECYMD_LEN];
	char endElec[ELECYMD_LEN];
	int elecBill;	//���⼼
	int inputPayElecBill = 0;
	int inputElec;

	while (1) {
		printf("(1) ����ϱ�   (2) ������ >>  ");
		scanf("%d", &inputElec);

		if (inputElec == 1) {
			printf("\n");
			break;
		}
		else if (inputElec == 2) {
			printf("���ư��ϴ�.\n");
			return;
		}
		else {
			printf("\n�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
		}
		printf("\n");
	}

	printf("���� ���� ���� ��¥(YYYY-MM-DD) >> ");
	scanf("%s", startElec);
	printf("���� ���� �� ��¥(YYYY-MM-DD) >> ");
	scanf("%s", endElec);
	printf("���⼼ >> ");
	scanf("%d", &elecBill);
	printf("\n");

	while (1) {
		printf("(1) ������ ����   (2) ������ �̳��� >> ");
		scanf("%d", &inputPayElecBill);
		if (inputPayElecBill == 1 || inputPayElecBill == 2) {
			printf("\n");
			break;
		}
		else printf("\n�Է¿� �����߽��ϴ�. �ٽ� �Է��ϼ���.\n");
	}

	if (addElecInfo(startElec, endElec, elecBill, inputPayElecBill) == 0) {
		printf("�Է¿� �����߽��ϴ�.\n");
		return;
	}
	printf("�Է��� �Ϸ�Ǿ����ϴ�\n");
}