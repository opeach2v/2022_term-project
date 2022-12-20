#include "common.h"
#include "gasInfo.h"
#include "gasInfoAccess.h"
#include "gasManage.h"
#include "screenOut.h"

int addGasInfo(char* startGas, char* endGas, int costGas, int inputPayCostGas) {
	gasInfo *pGas;
	if (numOfGas >= LIST_COSTGAS) return 0;	//입력 실패

	pGas = (gasInfo*)malloc(sizeof(gasInfo));
	strcpy(pGas->startGas, startGas);	//문자열 어쩌고 덮어쓰기
	strcpy(pGas->endGas, endGas);
	pGas->costGas = costGas;
	pGas->inputPayCostGas = inputPayCostGas;
	
	totalGas += costGas;
	gasList[numOfGas++] = pGas;

	avg_Gas = (double)totalGas / numOfGas;

	StoreGasListToFile();

	return numOfGas, totalGas, avg_Gas;
}

//전체 가스비 확인
void showAllGas() {
	int i;

	if (numOfGas == 0) {
		printf("입력받은 가스비가 없습니다.\n");
		return;
	}
	printf("\n━━━━━━━━━━━━━━━━━전체 가스비━━━━━━━━━━━━━━━\n");
	for (i = 0; i < numOfGas; i++) {
		showGasInfo(gasList[i]);
	}

	printf(" ▶ 가스비 평균: %.0lf원\n", avg_Gas);
	MAX_MIN_Gas();
}

//가스비 최댓값, 최솟값 계산
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

	printf(" ▶ 최고 가스비: %d원", maxGas);
	printf("  (%s ~ %s)\n", maxGasDayStart, maxGasDayEnd);
	printf(" ▶ 최저 가스비: %d원", minGas);
	printf("  (%s ~ %s)\n", minGasDayStart, minGasDayEnd);
}

//가스비 삭제
void deleteGasInfo() {
	int i, deleteGasExit;
	char deleteStartGas[GASYMD_LEN];

	int matchingGas[LIST_COSTGAS];	//match첨자 저장용 배열
	int matchedCountGas = 0;
	int delGas = 0;

	while (1) {
		printf("(1) 계속하기   (2) 나가기 >>  ");
		scanf("%d", &deleteGasExit);

		if (deleteGasExit == 1) {
			printf("\n삭제하려는 가스비 정산 시작 날짜(YYYY-MM-DD) >> ");
			scanf("%s", deleteStartGas);
			break;
		}
		else if (deleteGasExit == 2) {
			printf("\n돌아갑니다.\n");
			return;
		}
		else {
			printf("\n잘못된 입력입니다. 다시 입력해주세요.\n");
		}
		printf("\n");
	}

	for (i = 0; i < numOfGas; i++) {
		if (strcmp(gasList[i]->startGas, deleteStartGas) == 0) {	//두 문자열이 같으면
			matchingGas[matchedCountGas++] = i;
			totalGas -= gasList[i]->costGas;
		}
	}

	if (matchedCountGas == 0) {
		printf("\n찾는 날짜가 존재하지 않습니다.\n");
		return;
	}
	else if (matchedCountGas == 1) {
		delGas = matchingGas[0];
	}

	//하나씩 앞으로 이동
	for (i = delGas; i < numOfGas - 1; i++) {
		free(gasList[delGas]);
		gasList[i] = gasList[i + 1];
	}
	numOfGas--;
	printf("\n삭제가 완료되었습니다.\n");

	avg_Gas = (double)totalGas / numOfGas;

	StoreGasListToFile();

	return avg_Gas;
}

//납부, 미납부 표시 변경
void changeGasPay() {
	int i, input_check, changePayCostGas;
	char changePayStartGas[GASYMD_LEN];

	int matchingPayGas[LIST_COSTGAS];	//match첨자 저장용 배열
	int matchedCountPayGas = 0;
	int chaGas = 0;

	while (1) {
		printf("(1) 계속하기   (2) 나가기 >>  ");
		scanf("%d", &input_check);

		if (input_check == 1) {
			printf("\n납부로 변경할 가스비 정산 시작 날짜(YYYY-MM-DD) >> ");
			scanf("%s", changePayStartGas);
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

	for (i = 0; i < numOfGas; i++) {
		if (strcmp(gasList[i]->startGas, changePayStartGas) == 0) {	//두 문자열이 같으면
			matchingPayGas[matchedCountPayGas++] = i;
		}
	}

	if (matchedCountPayGas == 0) {
		printf("\n찾는 날짜가 존재하지 않습니다.\n");
		return;
	}
	else if (matchedCountPayGas == 1) {
		chaGas = matchingPayGas[0];
		if (gasList[chaGas]->inputPayCostGas == 1) {
			printf("\n이미 납부한 상태입니다.\n");
			return;
		}
	}
	
	if (gasList[chaGas]->inputPayCostGas == 2) {
		while (1) {
			printf("\n가스비를 납부하셨습니까?\n");
			printf("(1) 네   (2) 아니오 >> ");
			scanf("%d", &changePayCostGas);
			if (changePayCostGas == 1) {
				gasList[chaGas]->inputPayCostGas = changePayCostGas;
				break;
			}
			else if (changePayCostGas == 2) {
				printf("\n납부하고 다시 오세요.\n");
				return;
			}
			else printf("\n입력에 실패했습니다. 다시 입력하세요.\n\n");
		}
	}
	printf("\n납부로 변경되었습니다.\n");

	StoreGasListToFile();
}

//가스비 정보 파일에 저장
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

//가스비 정보 파일로부터 읽음
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
	if (numOfGasName >= LIST_GASNAME) return 0;	//입력 실패

	pGasName = (gasName*)malloc(sizeof(gasName));
	strcpy(pGasName->gasFileName, gasFileName);

	FILE* gfp = fopen(pGasName->gasFileName, "wb");

	gasNameList[numOfGasName++] = pGasName;

	return numOfGasName;
}*/
/* 전체 가스 파일 리스트 확인 후 입력
void showAllGasList() {
	int i;

	if (numOfGasName == 0) {
		printf("파일이 없습니다.\n");
		return;
	}
	printf("\n━━━━━━━━━━━━━━━━파일 리스트━━━━━━━━━━━━━━━━\n");
	for (i = 0; i < numOfGasName; i++) {
		showGasFile(gasNameList[i]);
	}
}*/