#define QUIT 8
#include <stdio.h>
#include <stdlib.h>
#include "CheckerBoard.h"

void printTitle() {
    printf("AI Searching Test.\n");
    printf("------------------\n");
    printf("[0] Example Cases.\n");
    printf("[1] Back Tracking.\n");
    printf("[2] DFS Searching.\n");
    printf("[3] BFS Searching.\n");
    printf("[4]  A Algorithm. \n");
    printf("[5] A * Algorithm.\n");
    printf("[6] Input Test A*.\n");
    printf("[7] Random Use A*.\n");
    printf("[8] Exit the Test.\n");
    printf("------------------\n");
}

int main() {
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
                break;
            case 2:
                printf("Run DFS Searching.\n");
                break;
            case 3:
                printf("Run BFS Searching.\n");
                break;
            case 4:
                printf("Run A Algorithm.  \n");
                break;
            case 5:
                printf("Run A* Algorithm. \n");
                break;
            case 6:
                printf("Run Input Test A*.\n");
                break;
            case 7:
                printf("Run Random Use A*.\n");
                break;
            default:
                printTitle();
                break;
        }
        scanf("%d", &operator);
    }
    printf("Exit the Test.\n");
    exit(0);
    system("pause");


    int cursor = 0;
//    for (; cursor < 10; cursor++) {
//        testAStar_15();
//    }
    for (; cursor < 10; cursor++) {
        struct CheckerBoard *origin = NULL;
        struct CheckerBoard *target = NULL;
        initTwoRandomCheckerBoard(3, 4, &origin, &target);
        printCheckerBoard(origin);
        printCheckerBoard(target);
        findResultHeuristicAStarAlgorithm(origin, target);
//        findResultHeuristicAAlgorithm(origin, target);

    }
    return 0;
}
