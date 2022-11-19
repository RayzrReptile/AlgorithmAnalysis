// Peyton Adkins Z23553314
// Programming Project 2022
// November 12, 2022

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <chrono>
#define MAX 100000 //100000
#define M 5 //5
#define INCREMENT 10000 //10000

using namespace std;
using namespace chrono;

typedef float* FloatPTR;

void ALG1(int* A, int n, int i);
void ALG2(int* A, int n, int i);
void ALG3(int* A, int n, int i);

void INSERTION_SORT(int* A, int n);
void HEAP_SORT(int* A, int n);
void BUILD_MAX_HEAP(int* A, int n);
void MAX_HEAPIFY(int* A, int heapSize, int i);
int RANDOMIZED_SELECT(int* A, int p, int r, int i);
int RANDOMIZED_PARTITION(int* A, int p, int r);
int PARTITION(int* A, int p, int r);

int main()
{
    FloatPTR* totalTime1 = new FloatPTR[M+1];
    for (int i=1; i<= M; i++) {
        totalTime1[i] = new float[MAX+1];
    }
    FloatPTR* totalTime2 = new FloatPTR[M+1];
    for (int i=1; i<= M; i++) {
        totalTime2[i] = new float[MAX+1];
    }
    FloatPTR* totalTime3 = new FloatPTR[M+1];
    for (int i=1; i<= M; i++) {
        totalTime3[i] = new float[MAX+1];
    }

    int* A = new int[MAX+1];

    time_t seedTime = time(NULL);
    srand((seedTime)); // allows for fresh random numbers

    // main m iterations
    for (int k=1; k <= M; k++) {

        cout << endl << "_ _ _ _ _ _ _ _ INTERATION M = " << k << " _ _ _ _ _ _ _ _" << endl;

        // initialization of array A
        for (int j=1; j <= MAX; j++) {
            A[j] = rand();
        }

        // each n iterations
        for (int n = INCREMENT; n <= MAX; n += INCREMENT) {

            cout << endl << "* * * * * ITERATION N = " << n << " * * * * *" << endl;

            int i = floor(2 * n / 3);

            // ALG1
            int* B = new int[n+1];
            for (int j=1; j <= n; j++) {
                B[j] = A[j];
            }
            auto startTime1 = steady_clock::now();
            ALG1(B, n, i);
            auto stopTime1 = steady_clock::now();
            float time1 = duration<float>(stopTime1 - startTime1).count();
            totalTime1[k][n] = time1;
            cout << "Time in seconds (float): " << totalTime1[k][n] << endl;

            // ALG2
            int* C = new int[n+1];
            for (int j=1; j <= n; j++) {
                C[j] = A[j];
            }
            auto startTime2 = steady_clock::now();
            ALG2(C, n, i);
            auto stopTime2 = steady_clock::now();
            float time2 = duration<float>(stopTime2 - startTime2).count();
            totalTime2[k][n] = time2;
            cout << "Time in seconds (float): " << totalTime2[k][n] << endl;

            // ALG3
            int* D = new int[n+1];
            for (int j=1; j <= n; j++) {
                D[j] = A[j];
            }
            auto startTime3 = steady_clock::now();
            ALG3(D, n, i);

            //
            /*
            cout << endl << "ARRAY D:" << endl;
            for (int j=1; j <= n; j++) {
                cout << "D[" << j << "] - " << D[j] << endl;
            }
            */
            auto stopTime3 = steady_clock::now();
            float time3 = duration<float>(stopTime3 - startTime3).count();
            totalTime3[k][n] = time3;
            cout << "Time in seconds (float): " << totalTime3[k][n] << endl;

            delete[] B;
            delete[] C;
            delete[] D;
        }

    }

    float* aveTime1 = new float[MAX+1];
    float* aveTime2 = new float[MAX+1];
    float* aveTime3 = new float[MAX+1];

    // average calculations
    for (int n = INCREMENT; n <= MAX; n += INCREMENT) { 

        aveTime1[n] = 0;
        aveTime2[n] = 0;
        aveTime3[n] = 0;

        for (int g=1; g<= M; g++) {
            aveTime1[n]+= totalTime1[g][n];
            aveTime2[n]+= totalTime2[g][n];
            aveTime3[n]+= totalTime3[g][n];

            aveTime1[n] /= M;
            aveTime2[n] /= M;
            aveTime3[n] /= M;
        }
    }

    cout << endl << "RESULTS IN MILLISECONDS: " << endl;
    for (int n = INCREMENT; n <= MAX; n += INCREMENT) { 
        cout << " - - - n = " << n << " - - - " << endl;
        cout << "ALG1: " << aveTime1[n]*1000 << endl;
        cout << "ALG2: " << aveTime2[n]*1000 << endl;
        cout << "ALG3: " << aveTime3[n]*1000 << endl;
    }

    // freeing memory
    for (int g=0; g<=M; g++) {
        delete[] totalTime1[g];
        delete[] totalTime2[g];
        delete[] totalTime3[g];
    }

    delete[] totalTime1;
    delete[] totalTime2;
    delete[] totalTime3;
    delete[] aveTime1;
    delete[] aveTime2;
    delete[] aveTime3;

    delete[] A;

    return 0;
} 

void ALG1(int* A, int n, int i) {
    cout << endl << "ALGORITHM 1 TESTING" << endl << endl;

    INSERTION_SORT(A, n);
    cout << "RESULT of " << i << "th smallest value: " << A[i] << endl;
};

void INSERTION_SORT(int* A, int n) {
    int key;
    int i;
    for (int j=2; j<=n; j++) {
        key = A[j];
        i = j - 1;
        while (i > 0 && A[i] > key) {
            A[i+1] = A[i];
            i--;
        }

        A[i+1] = key;
    }
};

void ALG2(int* A, int n, int i) {
    cout << endl << "ALGORITHM 2 TESTING" << endl << endl;

    HEAP_SORT(A, n);
    cout << "RESULT of " << i << "th smallest value: " << A[i] << endl;
};

void HEAP_SORT(int* A, int n) {
    int heapSize = n;
    int temp;
    BUILD_MAX_HEAP(A, n);

    for (int x=n; x>=2; x--) {
        temp = A[1];
        A[1] = A[x];
        A[x] = temp;
        heapSize--;
        MAX_HEAPIFY(A, heapSize, 1);
    }
};

void BUILD_MAX_HEAP(int* A, int n) {
    int heapSize = n;
    int f = floor(heapSize/2);
    for (int i=f; i>=1; i--) {
        MAX_HEAPIFY(A, heapSize, i);
    }
};

void MAX_HEAPIFY(int* A, int heapSize, int i) {
    int left = 2 * i;
    int right = 2 * i;
    right++;
    int largest;
    int temp;

    if (left <= heapSize && A[left] > A[i]) {
        largest = left;
    }
    else {
        largest = i;
    }
    if (right <= heapSize && A[right] > A[largest]) {
        largest = right;
    }
    if (largest != i) {
        temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        MAX_HEAPIFY(A, heapSize, largest);
    }
};

void ALG3(int* A, int n, int i) {
    cout << endl << "ALGORITHM 3 TESTING" << endl << endl;

    int x = RANDOMIZED_SELECT(A, 1, n, i);

    cout << "RESULT of " << i << "th smallest value: " << x << endl;
};

int RANDOMIZED_SELECT(int* A, int p, int r, int i) {

    if (p == r) {
        return A[p];
    }
    int q = RANDOMIZED_PARTITION(A, p, r);
    int k = q - p + 1;
    if (i == k) {
        return A[q];
    }
    else if (i < k) {
        return RANDOMIZED_SELECT(A, p, q - 1, i);
    }
    else {
        return RANDOMIZED_SELECT(A, q + 1, r, i - k);
    }
};

int RANDOMIZED_PARTITION(int* A, int p, int r) {
    int i = rand()%(r - p + 1) + p;
    int temp = A[i];
    A[i] = A[r];
    A[r] = temp;
    return PARTITION(A, p, r);
};

int PARTITION(int* A, int p, int r) {
    int x = A[r];
    int i = p - 1;
    int temp;
    for (int j=p; j <= r - 1; j++) {
        if (A[j] <= x) {
            i++;
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    temp = A[i+1];
    A[i+1] = A[r];
    A[r] = temp;

    return i+1;
};