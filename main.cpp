#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>

using namespace std;

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

//Above are all the functions needed for quicksort

void heapify(int arr[], int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2*i + 1; // left = 2*i + 1
    int r = 2*i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}
void heapSort(int arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i=n-1; i>0; i--)
    {
        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}


void insertion_sort(int array[], int size){
    int i, key, j;
    for (i = 1; i < size; i++)
    {
        key = array[i];
        j = i - 1;

        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}

void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for(int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r]

    // Initial index of first subarray
    int i = 0;

    // Initial index of second subarray
    int j = 0;

    // Initial index of merged subarray
    int k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of
    // L[], if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {

        // Same as (l+r)/2, but avoids
        // overflow for large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}



int main() {

    // int arr[] = { 12, 11, 13, 5, 6 };
    // int n = sizeof(arr) / sizeof(arr[0]);
    int arraySize, len;
    int iterNum = 3;
    double sortTime[4][6] = {0};

    for(int iter = 0; iter < iterNum; iter++) {
        for (arraySize = 10, len=0; arraySize <= 1000000; arraySize *= 10, len++) {
            // initialize random seed
            srand (time(NULL));

            // int arraySize = 10;
            int* arr = new int[arraySize];

            for( int sortMethod = 0; sortMethod < 4; sortMethod++) {
                // New random value array of length "arraySize"
                for (int i = 0; i < arraySize; i++) {
                    arr[i] = rand();
                    //arr[i] = rand()%(arraySize*10);
                }

                auto start = chrono::high_resolution_clock::now();
                ios_base::sync_with_stdio(false);
                switch(sortMethod) {
                    case 0: // Insertion Sort
                        insertion_sort(arr, arraySize);
                        break;
                    case 1: // Quick Sort
                        quickSort(arr, 0, arraySize - 1);
                        break;
                    case 2: // Heapsort
                        heapSort(arr, arraySize);
                        break;
                    case 3: // Merge Sort
                        heapSort(arr, arraySize);
                        break;
                }
                auto end = chrono::high_resolution_clock::now();
                double timeTaken = chrono::duration_cast<chrono::nanoseconds>(end - start).count;
                sortTime[sortMethod][len] += timeTaken;
            }

        }
    }

    cout << endl << "Execution Time in nanosecond:" <<endl;
    cout << "Length\t\tInsertSort\tQuickSort\tHeapSort\tMergeSort" << endl;
    for (arraySize = 10, len=0; arraySize <= 1000000; arraySize *= 10, len++) {
        cout << arraySize;
        for( int sortMethod = 0; sortMethod < 4; sortMethod++) {
            sortTime[sortMethod][len] /= <double>iterNum;
            cout << "\t" << sortTime[sortMethod][len] << setprecision(2);
        }
        cout << endl;
    }




    //     n = arraySize;

    // printArray(arr, n);
    // quickSort(arr, 0, n - 1);
    // printArray(arr, n);
    // insertion_sort(arr, n);
    // heapSort(arr, n);


    return 0;
}
