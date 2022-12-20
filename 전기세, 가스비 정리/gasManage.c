#include "common.h"
#include "gasInfo.h"
#include "gasInfoAccess.h"
#include "screenOut.h"


void inputGas() {
	char startGas[GASYMD_LEN];
	char endGas[GASYMD_LEN];
	int costGas = 0;	//가스비
	int inputPayCostGas = 0;
	int input_Gas;

	while (1) {
		printf("(1) 계속하기   (2) 나가기 >>  ");
		scanf("%d", &input_Gas);

		if (input_Gas == 1) {
			printf("\n");
			break;
		}
		else if (input_Gas == 2) {
			printf("돌아갑니다.\n");
			return;
		}
		else {
			printf("\n잘못된 입력입니다. 다시 입력해주세요.\n");
		}
		printf("\n");
	}

	printf("가스 정산 시작 날짜(YYYY-MM-DD) >> ");
	scanf("%s", startGas);
	printf("가스 정산 끝 날짜(YYYY-MM-DD) >> ");
	scanf("%s", endGas);
	printf("가스비 >> ");
	scanf("%d", &costGas);
	printf("\n");

	while (1) {
		printf("(1) 가스비 납부   (2) 가스비 미납부 >> ");
		scanf("%d", &inputPayCostGas);
		if (inputPayCostGas == 1 || inputPayCostGas == 2) {
			printf("\n");
			break;
		}
		else printf("\n입력에 실패했습니다. 다시 입력하세요.\n");
	}

	if (addGasInfo(startGas, endGas, costGas, inputPayCostGas) == 0) {
		printf("입력에 실패했습니다.\n");
		return;
	}

	printf("입력이 완료되었습니다\n");
}

/* void inputGasFile() {
	char gasFileName[GASNAME_LEN];
	int inputFGas;

	while (1) {
		printf("(1) 계속하기   (2) 나가기 >>  ");
		scanf("%d", &inputFGas);

		if (inputFGas == 1) {
			printf("\n");
			break;
		}
		else if (inputFGas == 2) {
			printf("돌아갑니다.\n");
			return;
		}
		else {
			printf("\n잘못된 입력입니다. 다시 입력해주세요.\n");
		}
		printf("\n");
	}

	printf("새로운 가스비 파일 이름 입력 >> ");
	scanf("%s", gasFileName);
	printf("\n");

	if (addGasFile(gasFileName) == 0) {
		printf("입력에 실패했습니다.\n");
		return;
	}

	printf("입력이 완료되었습니다\n");
} */