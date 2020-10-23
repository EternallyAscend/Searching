#include<stdio.h>
#include<stdlib.h>
#include"Queue_C.h"
#include"Stack_C.h"
#include"MinHeap_C.h"

int main(void) {
//	testQueue();
//	testStack();
//	testBacktracking_15();
//	system("pause");
	testBacktracking_8();
	system("pause");
	testBFS_15();
	system("pause");
//	testBFS_8();
//	system("pause");
//	testA_8();
//	system("pause");
	testA_15();
	system("pause");
//	testAStar_8();
//	system("pause");
	testAStar_15();
	system("pause");

	/*
	struct CheckerBoard* origin = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
	struct CheckerBoard* target = (struct CheckerBoard*)malloc(sizeof(struct CheckerBoard));
	initCheckerBoard(3, 3, origin);
	initCheckerBoard(3, 3, target);
	int cursor = 0;
	for (; cursor < 9; cursor++) {
		origin->checkerBoard[cursor] = cursor;
		target->checkerBoard[cursor] = 8 - cursor;
	}
	searchZeroInCheckerBoard(origin);
	searchZeroInCheckerBoard(target);
	printCheckerBoard(origin);
	printf("\n");
	printCheckerBoard(target);
	printf("\n %d %d\n", origin->zeroPosition, target->zeroPosition);
	findResultByDFS(origin, target);
	destroyCheckerBoard(origin);
	destroyCheckerBoard(target);
	*/

//	testMinHeap();
	return 0;
}