#define QUIT 8
#include <stdio.h>
#include <stdlib.h>
#include "CheckerBoard.h"

// Here is only test logic, algorithms are in CheckerBoard.h / CheckerBoard.c in detail.

void printTitle() {
    printf("AI Searching Test.\n");
    printf("------------------\n");
    printf("[0] Example Cases.\n");
    printf("[1] Back Tracking.\n");
    printf("[2] DFS Searching.\n");
    printf("[3] BFS Searching.\n");
    printf("[4]   A Algorithm.\n");
    printf("[5] A * Algorithm.\n");
    printf("[6] Input Test A*.\n");
    printf("[7] Random Use A*.\n");
    printf("[8] Exit the Test.\n");
    printf("------------------\n");
}

void testAStar_temp() {
    struct CheckerBoard* origin = initEmptyCheckerBoard(3, 3);
    struct CheckerBoard* target = initEmptyCheckerBoard(3, 3);
    int cursor = 0;
    for (; cursor < 9; cursor++) {
        target->checkerBoard[cursor] = cursor;
    }
    int checker[9] = {1, 4, 2, 6, 3, 5, 7, 8, 0};
    for (cursor = 0; cursor < 9; cursor++) {
        origin->checkerBoard[cursor] = checker[cursor];
    }
    // origin->checkerBoard[0] = 3;
    // origin->checkerBoard[1] = 5;
    // origin->checkerBoard[2] = 2;
    // origin->checkerBoard[3] = 7;
    // origin->checkerBoard[4] = 1;
    // origin->checkerBoard[5] = 4;
    // origin->checkerBoard[6] = 8;
    // origin->checkerBoard[7] = 6;
    // origin->checkerBoard[8] = 0;
    searchZeroInCheckerBoard(origin);
    searchZeroInCheckerBoard(target);
//    printCheckerBoard(origin);
//    printf("\n");
//    printCheckerBoard(target);
//    findResultHeuristicAStarAlgorithm(origin, target);
//    findResultByDFS(origin, target);
//    findResultByBFS(origin, target);
//    findResultByBacktracking(origin, target);
}

int main() {
//    struct CheckerBoard* checkerBoard = NULL;
//    inputValueInitCheckerBoard(&checkerBoard);
//    printCheckerBoard(checkerBoard);
//    system("pause");
    printf("Nankai University.\n");
    printf("1813045 YuHailong.");
    system("cls");
    printTitle();
    int operator;
    scanf("%d", &operator);
    while (QUIT != operator) {
        switch (operator) {
            case 0:
                printf("Run Example Cases.\n");
                testing();
                break;
            case 1:
                printf("Run Back Tracking.\n");
                testBackTracking();
                break;
            case 2:
                printf("Run DFS Searching.\n");
                testDFS();
                break;
            case 3:
                printf("Run BFS Searching.\n");
                testBFS();
                break;
            case 4:
                printf("Run A Algorithm.  \n");
                testA();
                break;
            case 5:
                printf("Run A* Algorithm. \n");
                testAStar();
                break;
            case 6:
                printf("Run Input Test A*.\n");
                testInputAStar();
                break;
            case 7:
                printf("Run Random Use A*.\n");
                testRandomAStar();
                break;
            default:
                // printf("Wrong command, please check.\n");
                // printTitle();
                printf("Wrong command, run default example.\n");
                testing();
                break;
        }
        // scanf("%d", &operator);
        operator = QUIT;
    }
    printf("Exit the Test.\n");
    return 0;
}
