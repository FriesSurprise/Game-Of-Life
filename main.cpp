#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc51-cpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#define SIZE 15

bool hasAlive(bool (&arr)[SIZE][SIZE]){
    for (auto & i : arr){
        for (auto & j : i){
            if (j)
                return true;
        }
    }
    return false;
}

void prepareGOL(bool (&arr)[SIZE][SIZE]){
    srand(time(nullptr));
    for (auto & i : arr){
        for (auto & j : i){
            j = (rand() % 2 == 0); // NOLINT(cert-msc50-cpp)
        }
    }
}

void printArr(const bool (&arr)[SIZE][SIZE]){
    for (auto & i : arr){
        for (auto & j : i){
            std::cout<<j<<' ';
        }
        std::cout<<"\n";
    }
}

int getNeighbors(const bool (&arr)[SIZE][SIZE], const int row, const int col){
    int counter{0};
    for (int i = row - 1; i < row + 2; ++i){
        for (int j = col - 1; j < col + 2; ++j){
            if (i >= 0 && j >= 0 && row < SIZE && col < SIZE)
                counter += arr[i][j];
        }
    }
    return counter - arr[row][col];
}

bool logic(const bool (&arr)[SIZE][SIZE], const int row, const int col){
    //if cell is alive and has too many or few neighbors to survive, should be false in array.
    if (arr[row][col] && getNeighbors(arr, row, col) > 2 || getNeighbors(arr, row, col) < 3)
        return false;
    //if cell is dead and has 3 neighbors, should become true in array.
    if (!arr[row][col] && getNeighbors(arr, row, col) == 3)
        return true;
    return false;
}

void update(bool (&arr)[SIZE][SIZE]){
    bool shifter[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j) {
            shifter[i][j] = logic(arr, i, j);
        }
    }
    std::swap(arr, shifter);
    printArr(arr);
}

int main() {
    bool arr[SIZE][SIZE];
    prepareGOL(arr);
    int runCount{};
    while (hasAlive(arr) && runCount < 10){
        update(arr);
        ++runCount;
        std::cout<<'\n';
    }
    return 0;
}

