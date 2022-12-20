#include "common.h"
#include "elecInfo.h"
#include "elecInfoAccess.h"
#include "screenOut.h"

int addElecInfo(char* startElec, char* endElec, int elecBill, int inputPayElecBill) {
	elecInfo* pElec;
	if (numOfElec >= LIST_ELECBILL) return 0;	//입력 실패

	pElec = (elecInfo*)malloc(sizeof(elecInfo));
	strcpy(pElec->startElec, startElec);	//문자열 어쩌고 덮어쓰기
	strcpy(pElec->endElec, endElec);
	pElec->elecBill = elecBill;
	pElec->inputPayElecBill = inputPayElecBill;

	totalElec += elecBill;
	elecList[numOfElec++] = pElec;

	avg_Elec = (double)totalElec / numOfElec;

	StoreElecListToFile();

	return numOfElec;
}

//전체 전기세 확인
void showAllElec() {
	int i;

	if (numOfElec == 0) {
		printf("입력받은 전기세가 없습니다.\n");
		return;
	}

	printf("\n━━━━━━━━━━━━━━━━━전체 전기세━━━━━━━━━━━━━━━\n");
	for (i = 0; i < numOfElec; i++) {
		showElecInfo(elecList[i]);
	}

	printf(" ▶ 전기세 평균: %.0lf원\n", avg_Elec);
	MAX_MIN_Elec();
}

//전기세 최댓값, 최솟값 계산
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

	printf(" ▶ 최고 가스비: %d원", maxElec);
	printf("  (% s ~ % s)\n", maxElecDayStart, maxElecDayEnd);
	printf(" ▶ 최저 가스비: %d원", minElec);
	printf("  (% s ~ % s)\n", minElecDayStart, minElecDayEnd);
}

//전기세 삭제
void deleteElecInfo() {
	int i, deleteElecExit;
	char deleteStartElec[GASYMD_LEN];

	int matchingElec[LIST_ELECBILL];	//match첨자 저장용 배열
	int matchedCountElec = 0;
	int delElec = 0;

	while (1) {
		printf("(1) 계속하기   (2) 나가기 >>  ");
		scanf("%d", &deleteElecExit);

		if (deleteElecExit == 1) {
			printf("\n삭제하려는 전기세 정산 시작 날짜(YYYY-MM-DD) >> ");
			scanf("%s", deleteStartElec);
			break;
		}
		else if (deleteElecExit == 2) {
			printf("\n돌아갑니다.\n");
			return;
		}
		else {
			printf("\n잘못된 입력입니다. 다시 입력해주세요.\n");
		}
		printf("\n");
	}

	for (i = 0; i < numOfElec; i++) {
		if (strcmp(elecList[i]->startElec, deleteStartElec) == 0) {	//두 문자열이 같으면
			matchingElec[matchedCountElec++] = i;
			totalElec -= elecList[i]->elecBill;
		}
	}

	if (matchedCountElec == 0) {
		printf("\n찾는 날짜가 존재하지 않습니다.\n");
		return;
	}
	else if (matchedCountElec == 1) {
		delElec = matchingElec[0];
	}

	//하나씩 앞으로 이동
	for (i = delElec; i < numOfElec - 1; i++) {
		free(elecList[delElec]);
		elecList[i] = elecList[i + 1];
	}
	numOfElec--;
	printf("\n삭제가 완료되었습니다.\n");

	avg_Elec = (double)totalElec / numOfElec;

	StoreElecListToFile();

	return avg_Elec;
}

//납부, 미납부 표시 변경
void changeElecPay() {
	int i, input_check, changePayElecBill;
	char changePayStartElec[GASYMD_LEN];

	int matchingPayGas[LIST_ELECBILL];	//match첨자 저장용 배열
	int matchedCountPayGas = 0;
	int chaGas = 0;

	while (1) {
		printf("(1) 계속하기   (2) 나가기 >>  ");
		scanf("%d", &input_check);

		if (input_check == 1) {
			printf("\n납부로 변경할 가스비 정산 시작 날짜(YYYY-MM-DD) >> ");
			scanf("%s", changePayStartElec);
			break;
		}
		else if (input_check == 2) {
			printf("\n돌아갑니다.\n");
			return;
		}
		else {
			printf("\n잘못된 입력입니다. 다시 입력해주세요.\n");
		}
	}

	for (i = 0; i < numOfElec; i++) {
		if (strcmp(elecList[i]->startElec, changePayStartElec) == 0) {	//두 문자열이 같으면
			matchingPayGas[matchedCountPayGas++] = i;
		}
	}

	if (matchedCountPayGas == 0) {
		printf("\n찾는 날짜가 존재하지 않습니다.\n");
		return;
	}
	else if (matchedCountPayGas == 1) {
		chaGas = matchingPayGas[0];
		if (elecList[chaGas]->inputPayElecBill == 1) {
			printf("\n이미 납부한 상태입니다.\n");
			return;
		}
	}

	if (elecList[chaGas]->inputPayElecBill == 2) {
		while (1) {
			printf("\n가스비를 납부하셨습니까?\n");
			printf("(1) 네   (2) 아니오 >> ");
			scanf("%d", &changePayElecBill);
			if (changePayElecBill == 1) {
				elecList[chaGas]->inputPayElecBill = changePayElecBill;
				break;
			}
			else if (changePayElecBill == 2) {
				printf("\n납부하고 다시 오세요.\n");
				return;
			}
			else printf("\n입력에 실패했습니다. 다시 입력하세요.\n\n");
		}
	}
	printf("\n납부로 변경되었습니다.\n");

	StoreElecListToFile();
}

//가스비 정보 파일에 저장
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

//가스비 정보 파일로부터 읽음
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