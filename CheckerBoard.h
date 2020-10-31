//
// Created by MagicBook on 2020/10/24.
//

#pragma warning(disable:4996)

#ifndef AI_SEARCHING_CHECKERBOARD_H
#define AI_SEARCHING_CHECKERBOARD_H

#include "Layer.h"
#include "Method.h"
#include "Random.h"
#include "Stack_C.h"
#include "Queue_C.h"
#include "MinHeap_C.h"

struct CheckerBoard {
    int length; // Length of the checkerboard.
    int height; // Height of the checkerboard.
    int *checkerBoard; // Store number position.
    int zeroPosition; // Store where is empty.
    int lastModified; // Store which moved before.
};

// If checkerBoard->checkerBoard is NULL, it will free the checkerBoard.
int checkNullCheckerBoard(struct CheckerBoard* checkerBoard);

// Destroy the checkerBoard and the pointer.
void destroyCheckerBoard(struct CheckerBoard* checkerBoard);

struct CheckerBoard* copyCheckerBoard(struct CheckerBoard* checkerBoard);

// Find position of empty block. Wrong input => -1;
int searchZeroInCheckerBoard(struct CheckerBoard* checkerBoard);

// Init new empty checkerBoard with `struct CheckerBoard* = initCheckerBoard(length, height);`
struct CheckerBoard* initEmptyCheckerBoard(int length, int height);

// Generate checkerboard with random value.
struct CheckerBoard* initRandomCheckerBoard(int length, int height);

// Calculate the reverse pair in a checkerBoard. Wrong => -1.
int calculateReversePair(struct CheckerBoard* checkerBoard);

// Generate a paired checkerBoard from an existed one.
struct CheckerBoard* initRandomCheckerBoardWithOneExist(struct CheckerBoard* checkerBoard);

// Generate a pair of checkerBoard with random value.
void initTwoRandomCheckerBoard(int length, int height, struct CheckerBoard** origin, struct CheckerBoard** target);

// Judge whether two checkerboard are same size, wrong input => -1, not equal => 0, equal => 1.
int judgeNotNullptrAndEqualSize(struct CheckerBoard* origin, struct CheckerBoard* target);

// Check whether two checkerboard are equal, wrong input => -1, not equal => 0, equal => 1.
int checkEqualCheckerBoard(struct CheckerBoard* origin, struct CheckerBoard* target);

// Count different number of two checkerboard. Wrong input => -1.
int countDifferenceOfCheckerBoard(struct CheckerBoard* origin, struct CheckerBoard* target);

// Print the checkerboard.
void printCheckerBoard(struct CheckerBoard* checkerBoard);

// The x and y is from range(0, length) and range(0, height);
void setValueInCheckerBoard(int x, int y, int value, struct CheckerBoard* checkerBoard);

// Input value after init the checkerboard.
void inputValueInitCheckerBoard(struct CheckerBoard** checkerBoard);

// Get the block which can be moved.
int* getMoveAblePointsAndTargets(struct CheckerBoard* checkerBoard);

// Move the empty block to target.
void moveInCheckerBoard(struct CheckerBoard* checkerBoard, int target);

// ======== Method and Test. ========
int findResultBacktracking(struct CheckerBoard* origin, struct CheckerBoard* target, struct Stack_C* stack);

void findResultByBacktracking(struct CheckerBoard* origin, struct CheckerBoard* target);

void testBacktracking_8();

void testBacktracking_15();

int findResultDFS(struct CheckerBoard* checkerBoard, struct CheckerBoard* target, struct Stack_C* stack);

void findResultByDFS(struct CheckerBoard* checkerBoard, struct CheckerBoard* target);

void testDFS_8();

void testDFS_15();

int findResultBFS(struct CheckerBoard* target, struct Queue_C* queue, struct Layer* layer, struct Stack_C* stack);

void findResultByBFS(struct CheckerBoard* checkerBoard, struct CheckerBoard* target);

void testBFS_8();

void testBFS_15();

int aAlgorithm(struct CheckerBoard* checkerBoard, struct CheckerBoard* target);

void findResultHeuristicAAlgorithm(struct CheckerBoard* checkerBoard, struct CheckerBoard* target);

void testA_8();

void testA_15();

int aStarAlgorithm(struct CheckerBoard* checkerBoard, struct CheckerBoard* target);

void findResultHeuristicAStarAlgorithm(struct CheckerBoard* checkerBoard, struct CheckerBoard* target);

void testAStar_8();

void testAStar_15();

// Visible A and A*.
void findResultByHeuristic(struct CheckerBoard* checkerBoard, struct CheckerBoard* target, int(*getScore(struct CheckerBoard*, struct CheckerBoard*)));

void getVisible();

void testing();

void testBackTracking();

void testDFS();

void testBFS();

void testA();

void testAStar();

void testInputAStar();

void testRandomAStar();

void echoResult(struct Stack_C* stack);

void testHeuristicVisible();

#endif //AI_SEARCHING_CHECKERBOARD_H
