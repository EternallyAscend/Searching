//
// Created by MagicBook on 2020/10/22.
//

#ifndef AI_SEARCHING_CHECKERBOARD_H
#define AI_SEARCHING_CHECKERBOARD_H

struct CheckerBoard {
    int length; // Length of the checkerboard.
    int height; // Height of the checkerboard.
    int *checkerBoard; // Store number position.
    int zeroPosition; // Store where is empty.
    int lastModified; // Store which moved before.
};

struct Method {
    int depth; // Store current searching depth.
    int score; // Using it in A or A* Algorithm.
    int nodeCounter; // Record all reached nodes.
    struct CheckerBoard *checkerBoard; // Current.
    struct Stack_C *method; // History with current.
};

void initEmptyMethod(struct Method* method);

int isNullMethod(struct Method* method);

struct Method* copyMethod(struct Method* method);

int destroyMethod(struct Method* method);

// Compare different method for sort by minHeap. -1 => left < right, 0 => equal, 1 => left > right.
int compareMethod(struct Method* left, struct Method* right);

// Copy a new checkerboard with same situation.
struct CheckerBoard* copyCheckerBoard(struct CheckerBoard* checkerBoard);

int checkNullCheckerBoard(struct CheckerBoard* checkerBoard);

// Check whether two checkerboard are equal, wrong input => -1, not equal => 0, equal => 1.
int checkEqualCheckerBoard(struct CheckerBoard* checkerBoard, struct CheckerBoard* target);

// Judge whether two checkerboard are same size, wrong input => -1, not equal => 0, equal => 1.
int judgeNotNullptrAndEqualSize(struct CheckerBoard* checkerBoard, struct CheckerBoard* target);

// Count different number of two checkerboard. Wrong input => -1.
int countDifferenceOfCheckerBoard(struct CheckerBoard* checkerBoard, struct CheckerBoard* target);

// Find position of empty block. Wrong input => -1;
void searchZeroInCheckerBoard(struct CheckerBoard* checkerBoard);

// Init the checkerboard without any useful value.
void initCheckerBoard(int length, int height, struct CheckerBoard* checkerBoard);

// Generate checkerboard with random value.
void initRandomCheckerBoard(int length, int height, struct CheckerBoard* checkerBoard);

// Print the checkerboard.
void printCheckerBoard(struct CheckerBoard* checkerBoard);

void setValueInCheckerBoard(int x, int y, int value, struct CheckerBoard* checkerBoard);

// Input value after init the checkerboard.
void inputValueInitCheckerBoard(struct CheckerBoard* checkerBoard);

// Get the block which can be moved.
int* getMoveAblePointsAndTargets(struct CheckerBoard* checkerBoard);

// Move the empty block to target.
void moveInCheckerBoard(struct CheckerBoard* checkerBoard, int target);

void destroyCheckerBoard(struct CheckerBoard* checkerBoard);

int findResultBacktracking(struct CheckerBoard* checkerBoard, struct CheckerBoard* target, struct Stack_C* stack);

void findResultByBacktracking(struct CheckerBoard* checkerBoard, struct CheckerBoard* target);

void testBacktracking_8();

void testBacktracking_15();

int findResultDFS(struct CheckerBoard* checkerBoard, struct CheckerBoard* target, struct Stack_C* stack);

void findResultByDFS(struct CheckerBoard* checkerBoard, struct CheckerBoard* target);

int findResultBFS(struct CheckerBoard* target, struct Queue_C* queue, struct Layer* layer, struct Stack_C* stack);

void findResultByBFS(struct CheckerBoard* checkerBoard, struct CheckerBoard* target);

void testBFS_8();

void testBFS_15();

int aAlgorithm(struct CheckerBoard* checkerBoard, struct CheckerBoard* target);

void testA_8();

void testA_15();

int aStarAlgorithm(struct CheckerBoard* checkerBoard, struct CheckerBoard* target);

void testAStar_8();

void testAStar_15();

void findResultHeuristicAAlgorithm(struct CheckerBoard* checkerBoard, struct CheckerBoard* target);

void findResultHeuristicAStarAlgorithm(struct CheckerBoard* checkerBoard, struct CheckerBoard* target);

void findResultByHeuristic(struct CheckerBoard* checkerBoard, struct CheckerBoard* target);

void findResultByRandom(struct CheckerBoard* checkerBoard, struct CheckerBoard* target);

#endif //AI_SEARCHING_CHECKERBOARD_H
