// Parallel Reduction using OpenMP

#include <iostream>
#include <omp.h>          // OpenMP header
#include <climits>        // For INT_MAX, INT_MIN
using namespace std;

int main() {

  // ================= STATIC INPUT =================
  // Fixed array given directly in program

  int arr[] = {3, 1, 7, 2, 9, 4, 6, 8, 5}; // Input array
  int n = 9;                                // Size of array


  // ================= DYNAMIC INPUT =================
  // Uncomment this section if user input is required

  /*
  int n;

  cout << "Enter number of elements: ";
  cin >> n;

  int arr[n];

  cout << "Enter array elements: ";

  for(int i = 0; i < n; i++) {
      cin >> arr[i];
  }
  */


  int minVal = INT_MAX;     // Start with largest possible value
                             // So any smaller number can replace it

  int maxVal = INT_MIN;     // Start with smallest possible value

  long long sum = 0;        // Sum starts at 0
                             // long long is used because sum may become large


  // OpenMP Parallel Reduction
  // Work is divided among multiple threads

  #pragma omp parallel for reduction(min:minVal) \
                           reduction(max:maxVal) \
                           reduction(+:sum)

  for (int i = 0; i < n; i++) {

    // Find minimum value
    if (arr[i] < minVal)
        minVal = arr[i];

    // Find maximum value
    if (arr[i] > maxVal)
        maxVal = arr[i];

    // Calculate sum
    sum += arr[i];
  }

  // OpenMP combines all local thread results automatically


  // Calculate average
  double avg = (double)sum / n;


  // Display results
  cout << "Min: " << minVal << endl;
  cout << "Max: " << maxVal << endl;
  cout << "Sum: " << sum    << endl;
  cout << "Avg: " << avg    << endl;

  return 0;
}


// Compile:
// g++ -fopenmp reduction.cpp -o reduction

// Run:
// ./reduction
// OR
// reduction.exe

/*
Output:
Min: 1
Max: 9
Sum: 45
Avg: 5
*/