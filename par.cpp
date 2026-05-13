#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <chrono>
#include <omp.h>
using namespace std::chrono;

int matrix[20][20];
int N, minDist;

void bt(int cur, int end, int dist, int visited[]) {
    if (dist >= minDist) return;
    if (cur == end) {
        #pragma omp critical
        { if (dist < minDist) minDist = dist; }
        return;
    }
    for (int i = 0; i < N; i++) {
        if (matrix[cur][i] != 0 && visited[i] == 0) {
            visited[i] = 1;
            bt(i, end, dist + matrix[cur][i], visited);
            visited[i] = 0;
        }
    }
}

int main(int argc, char *argv[]) {
    N = atoi(argv[1]);
    int hilos = atoi(argv[2]);
    omp_set_num_threads(hilos);
    srand(42);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrix[i][j] = rand() % 10 + 1;
    minDist = INT_MAX;
    auto t1 = high_resolution_clock::now();
    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int i = 1; i < N; i++) {
                #pragma omp task firstprivate(i)
                {
                    int v[20] = {0};
                    v[0] = 1; v[i] = 1;
                    bt(i, N - 1, matrix[0][i], v);
                }
            }
        }
    }
    auto t2 = high_resolution_clock::now();
    printf("%d,%d,%lld,%d\n", N, hilos, (long long)duration_cast<microseconds>(t2-t1).count(), minDist);
    return 0;
}
