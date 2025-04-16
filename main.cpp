#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty())
            return 0;

        int maxArea = 0;
        vector<int> hist(matrix[0].size(), 0); // Histogram heights

        for (const vector<char>& row : matrix) {
            // Update the histogram heights
            for (int i = 0; i < row.size(); ++i) {
                hist[i] = row[i] == '0' ? 0 : hist[i] + 1;
            }
            // Calculate the largest rectangle area for the current histogram
            maxArea = max(maxArea, largestRectangleArea(hist));
        }

        return maxArea;
    }

private:
    int largestRectangleArea(const vector<int>& heights) {
        int maxArea = 0;
        stack<int> indexStack; // Stack to store indices of the histogram bars

        for (int i = 0; i <= heights.size(); ++i) {
            while (!indexStack.empty() &&
                   (i == heights.size() || heights[indexStack.top()] > heights[i])) {
                int height = heights[indexStack.top()];
                indexStack.pop();
                int width = indexStack.empty() ? i : i - indexStack.top() - 1;
                maxArea = max(maxArea, height * width);
            }
            indexStack.push(i);
        }

        return maxArea;
    }
};

int main() {
    Solution solution;

    // Example 1
    vector<vector<char>> matrix1 = {
        {'1', '0', '1', '0', '0'},
        {'1', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1'},
        {'1', '0', '0', '1', '0'}
    };
    cout << "Input: matrix = [[\"1\",\"0\",\"1\",\"0\",\"0\"],[\"1\",\"0\",\"1\",\"1\",\"1\"],[\"1\",\"1\",\"1\",\"1\",\"1\"],[\"1\",\"0\",\"0\",\"1\",\"0\"]]" << endl;
    cout << "Output: " << solution.maximalRectangle(matrix1) << endl;

    // Example 2
    vector<vector<char>> matrix2 = {
        {'0'}
    };
    cout << "Input: matrix = [[\"0\"]]" << endl;
    cout << "Output: " << solution.maximalRectangle(matrix2) << endl;

    // Example 3
    vector<vector<char>> matrix3 = {
        {'1'}
    };
    cout << "Input: matrix = [[\"1\"]]" << endl;
    cout << "Output: " << solution.maximalRectangle(matrix3) << endl;

    return 0;
}
