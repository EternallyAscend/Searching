#define QUIT 9
#include <stdio.h>
#include <stdlib.h>
#include "CheckerBoard.h"

// Here is only test logic, algorithms are in CheckerBoard.h / CheckerBoard.c in detail.

void printTitle() {
	printf(" __________________\n");
    printf(" AI Searching Test.\n");
    printf(" ------------------\n");
    printf(" [0] Example Cases.\n");
    printf(" [1] Back Tracking.\n");
    printf(" [2] DFS Searching.\n");
    printf(" [3] BFS Searching.\n");
    printf(" [4]   A Algorithm.\n");
    printf(" [5] A * Algorithm.\n");
    printf(" [6] Input Test A*.\n");
    printf(" [7] Random Use A*.\n");
	printf(" [8] Visible A, A*.\n");
    printf(" [9] Exit the Test.\n");
    printf(" ------------------\n");
}

int main() {
    printf(" Nankai University.\n");
    printf(" 1813045 YuHailong.");
    system("cls");
    printTitle();
	printf(" Please select: ");
    int operator;
    scanf("%d", &operator);
    while (QUIT != operator) {
        switch (operator) {
            case 0:
                printf(" Run Example Cases.\n");
                testing();
                break;
            case 1:
                printf(" Run Back Tracking.\n");
                testBackTracking();
                break;
            case 2:
                printf(" Run DFS Searching.\n");
                testDFS();
                break;
            case 3:
                printf(" Run BFS Searching.\n");
                testBFS();
                break;
            case 4:
                printf(" Run A Algorithm.  \n");
                testA();
                break;
            case 5:
                printf(" Run A* Algorithm. \n");
                testAStar();
                break;
            case 6:
                printf(" Run Input Test A*.\n");
                testInputAStar();
                break;
            case 7:
                printf(" Run Random Use A*.\n");
                testRandomAStar();
                break;
			case 8:
				printf(" Run Visible A / A*.\n");
				testHeuristicVisible();
				break;
            default:
                // printf("Wrong command, please check.\n");
                // printTitle();
                printf(" Wrong command, run default example.\n");
                testing();
                break;
        }
		printTitle();
		printf(" Please select: ");
        scanf("%d", &operator);
        // operator = QUIT;
    }
    printf(" Exit the Test.\n");
    return 0;
}
