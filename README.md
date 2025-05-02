# Multi-threaded Sorting with Insertion Sort and Merging

This program implements a multi-threaded sorting algorithm that uses **Insertion Sort** to sort an array in parallel. It then merges the two sorted sub-arrays using a separate thread.

## Features

- **Parallel Sorting**: The array is divided into two halves, and each half is sorted using the Insertion Sort algorithm in separate threads.
- **Merge**: After sorting, a merge thread combines the two sorted halves into one sorted array.
- **Dynamic Array Size**: The program accepts any array size greater than or equal to 2.

## How It Works

1. The program takes the number of elements and the array values from the user.
2. The array is divided into two halves:
   - The first half (from index 0 to mid-1).
   - The second half (from mid to SIZE-1).
3. Two threads are created to perform Insertion Sort on each half of the array.
4. After both threads finish sorting, a third thread merges the two sorted halves into one sorted array.
5. The sorted array is printed as output.

