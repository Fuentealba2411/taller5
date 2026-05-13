#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <chrono>
using namespace std::chrono;

int matrix[20][20];
int visited[20];
int N, minDist;

void bt(int cur, int end, int dist) {
    if (cur == end) {
        if (dist < minDist) minDist = dist;
        return;
    }
    for (int i = 0; i < N; i++) {
        if (matrix[cur][i] != 0 && visited[i] == 0) {
            visited[i] = 1;
            bt(i, end, dist + matrix[cur][i]);
            visited[i] = 0;
        }
    }
}

int main(int argc, char *argv[]) {
    N = atoi(argv[1]);
    srand(42);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrix[i][j] = rand() % 10 + 1;
    for (int i = 0; i < N; i++) visited[i] = 0;
    visited[0] = 1;
    minDist = INT_MAX;
    auto t1 = high_resolution_clock::now();
    bt(0, N - 1, 0);
    auto t2 = high_resolution_clock::now();
    printf("%d,1,%lld,%d\n", N, (long long)duration_cast<microseconds>(t2-t1).count(), minDist);
    return 0;
}
