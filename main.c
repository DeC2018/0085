#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* data;
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (int*)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push(Stack* stack, int value) {
    stack->data[++stack->top] = value;
}

int pop(Stack* stack) {
    return stack->data[stack->top--];
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int largestRectangleArea(int* heights, int heightsSize) {
    Stack* stack = createStack(heightsSize + 1);
    int maxArea = 0;
    
    for (int i = 0; i <= heightsSize; i++) {
        int h = (i == heightsSize) ? 0 : heights[i];
        while (!isEmpty(stack) && h < heights[stack->data[stack->top]]) {
            int height = heights[pop(stack)];
            int width = isEmpty(stack) ? i : i - stack->data[stack->top] - 1;
            if (height * width > maxArea) {
                maxArea = height * width;
            }
        }
        push(stack, i);
    }
    
    free(stack->data);
    free(stack);
    return maxArea;
}

int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize) {
    if (matrixSize == 0) return 0;
    
    int maxArea = 0;
    int* heights = (int*)malloc(matrixColSize[0] * sizeof(int));
    memset(heights, 0, matrixColSize[0] * sizeof(int));
    
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixColSize[i]; j++) {
            heights[j] = matrix[i][j] == '0' ? 0 : heights[j] + 1;
        }
        int area = largestRectangleArea(heights, matrixColSize[i]);
        if (area > maxArea) {
            maxArea = area;
        }
    }
    
    free(heights);
    return maxArea;
}

void printMatrix(char** matrix, int rows, int* cols) {
    printf("[");
    for (int i = 0; i < rows; i++) {
        if (i > 0) printf(",");
        printf("[");
        for (int j = 0; j < cols[i]; j++) {
            if (j > 0) printf(",");
            printf("\"%c\"", matrix[i][j]);
        }
        printf("]");
    }
    printf("]");
}

int main() {
    // Example 1
    char* matrix1[] = {
        "10100",
        "10111",
        "11111",
        "10010"
    };
    int cols1[] = {5, 5, 5, 5};
    int rows1 = 4;
    
    printf("Input: matrix = ");
    printMatrix(matrix1, rows1, cols1);
    printf("\nOutput: %d\n\n", maximalRectangle(matrix1, rows1, cols1));

    // Example 2
    char* matrix2[] = {"0"};
    int cols2[] = {1};
    int rows2 = 1;
    
    printf("Input: matrix = ");
    printMatrix(matrix2, rows2, cols2);
    printf("\nOutput: %d\n\n", maximalRectangle(matrix2, rows2, cols2));

    // Example 3
    char* matrix3[] = {"1"};
    int cols3[] = {1};
    int rows3 = 1;
    
    printf("Input: matrix = ");
    printMatrix(matrix3, rows3, cols3);
    printf("\nOutput: %d\n", maximalRectangle(matrix3, rows3, cols3));

    return 0;
}
