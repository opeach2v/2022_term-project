#include "common.h"
#include "elecInfo.h"
#include "elecInfoAccess.h"
#include "elecManage.h"
#include "screenOut.h"

void inputElec() {
	char startElec[ELECYMD_LEN];
	char endElec[ELECYMD_LEN];
	int elecBill;	//전기세
	int inputPayElecBill = 0;
	int inputElec;

	while (1) {
		printf("(1) 계속하기   (2) 나가기 >>  ");
		scanf("%d", &inputElec);

		if (inputElec == 1) {
			printf("\n");
			break;
		}
		else if (inputElec == 2) {
			printf("돌아갑니다.\n");
			return;
		}
		else {
			printf("\n잘못된 입력입니다. 다시 입력해주세요.\n");
		}
		printf("\n");
	}

	printf("전기 정산 시작 날짜(YYYY-MM-DD) >> ");
	scanf("%s", startElec);
	printf("전기 정산 끝 날짜(YYYY-MM-DD) >> ");
	scanf("%s", endElec);
	printf("전기세 >> ");
	scanf("%d", &elecBill);
	printf("\n");

	while (1) {
		printf("(1) 가스비 납부   (2) 가스비 미납부 >> ");
		scanf("%d", &inputPayElecBill);
		if (inputPayElecBill == 1 || inputPayElecBill == 2) {
			printf("\n");
			break;
		}
		else printf("\n입력에 실패했습니다. 다시 입력하세요.\n");
	}

	if (addElecInfo(startElec, endElec, elecBill, inputPayElecBill) == 0) {
		printf("입력에 실패했습니다.\n");
		return;
	}
	printf("입력이 완료되었습니다\n");
}