#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 1000;
const int move_accept_x[] = {1, 1, -1, -1, 2, 2, -2, -2};
const int move_accept_y[] = {2, -2, 2, -2, 1, -1, 1, -1};

int n;
int m;
int start_position[2];
int grid[MAX_SIZE][MAX_SIZE];

// Get input data about size of grid
bool inputSizeGrid() {
    cin >> n >> m;
    if (((1 <= n) && (n <= MAX_SIZE)) && ((1 <= m) && (m <= MAX_SIZE))) {
        return true;
    } else {
        cout << "Error: Size of grid" << endl;
        return false;
    }
}

// Get input data about grid and transform to useful map
bool inputGrid() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char x;
            cin >> x;
            // 0 - empty pole, 1 - no access pole, 2 - end pole
            switch (x) {
                case '.':
                    grid[i][j] = 0;
                    break;
                case 'x':
                    grid[i][j] = 1;
                    break;
                case 'n':
                    grid[i][j] = 2;
                    break;
                case 'z':
                    grid[i][j] = 0;
                    start_position[0] = i;
                    start_position[1] = j;
                    break;
                default:
                    cout << "Error: Incorrect map";
                    return false;
            }

        }
    }
    return true;
}

// Get the number of steps, that need to do
int findWay() {
    int step_amount = 0;
    bool end = false;
    int point = 1;
    int index = 0;
    int access_pole[n * m][3];
    access_pole[0][0] = start_position[0];
    access_pole[0][1] = start_position[1];
    access_pole[0][2] = step_amount;
    while (index <= point) {
        step_amount = access_pole[index][2];
        for (int j = 0; j < sizeof(move_accept_x) / sizeof(int); j++) {
            int next_x = access_pole[index][1] + move_accept_x[j];
            int next_y = access_pole[index][0] + move_accept_y[j];
            // Check if move is in the grid space, no outside
            if (((0 <= next_x) && (next_x < m)) && ((0 <= next_y) && (next_y < n))) {
                // Check if landing pole is empty
                if ((grid[next_y][next_x] == 0) || (grid[next_y][next_x] == 2)) {
                        // Check if is on end pole
                        if (grid[next_y][next_x] == 2) {
                            step_amount = access_pole[index][2] + 1;
                            end = true;
                            index = point;
                            break;
                        }
                        // Save pole for next iteration
                        else {
                            bool empty = true;
                            // Check if poles was saved before
                            for (int z = 0; z < point; z++) {
                                if ((access_pole[z][0] == next_y) && (access_pole[z][1] == next_x)) {
                                    empty = false;
                                    break;
                                }
                            }
                            if (empty) {
                                access_pole[point][1] = next_x;
                                access_pole[point][0] = next_y;
                                point += 1;
                                access_pole[point][2] = step_amount + 1;
                            }
                        }


                }
            }
        }
        index += 1;
    }
    // If no way to end
    if (!end) {
        step_amount = 0;
    }
    return step_amount;
}

int main() {
    if (inputSizeGrid()) {
        if (inputGrid()) {
            int steps = findWay();
            if (steps >> 0) {
                cout << steps;
            } else {
                cout << "NIE";
            }
        }

    }
    return 0;
}
