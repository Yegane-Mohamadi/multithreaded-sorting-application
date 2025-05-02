#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int* arr;        
int* sorted_arr;  
int SIZE;          

typedef struct {
    int start;
    int end;
} Range;

void insertion_sort(int start, int end) {
    for (int i = start + 1; i <= end; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= start && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void* sort_thread(void* arg) {
    Range* range = (Range*) arg;
    insertion_sort(range->start, range->end);
    pthread_exit(NULL);
}

void* merge_thread(void* arg) {
    int mid = SIZE / 2;
    int left_end = mid - 1;
    int right_start = mid;

    //اگر تعداد فرد بود  نیمه راست بزرگ‌تره 
    if (SIZE % 2 != 0) {
        right_start = mid;
        left_end = mid - 1;
    }

    int i = 0, j = right_start, k = 0;

    while (i <= left_end && j < SIZE) {
        if (arr[i] < arr[j])
            sorted_arr[k++] = arr[i++];
        else
            sorted_arr[k++] = arr[j++];
    }

    while (i <= left_end)
        sorted_arr[k++] = arr[i++];
    while (j < SIZE)
        sorted_arr[k++] = arr[j++];

    pthread_exit(NULL);
}

int main() {
    printf("Enter number of elements: ");
    scanf("%d", &SIZE);

    if (SIZE < 2) {
        printf("Please enter a number >= 2.\n");
        return 1;
    }

    arr = (int*) malloc(SIZE * sizeof(int));
    sorted_arr = (int*) malloc(SIZE * sizeof(int));

    printf("Enter %d integers:\n", SIZE);
    for (int i = 0; i < SIZE; i++) {
        scanf("%d", &arr[i]);
    }

    pthread_t t1, t2, t_merge;
    Range* first_half = (Range*) malloc(sizeof(Range));
    Range* second_half = (Range*) malloc(sizeof(Range));

    int mid = SIZE / 2;

    // تقسیم عناصر با توجه به فرد/زوج بودن SIZE
    first_half->start = 0;
    first_half->end = mid - 1;

    second_half->start = mid;
    second_half->end = SIZE - 1;

    pthread_create(&t1, NULL, sort_thread, first_half);
    pthread_create(&t2, NULL, sort_thread, second_half);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_create(&t_merge, NULL, merge_thread, NULL);
    pthread_join(t_merge, NULL);

    printf("Sorted Array: ");
    for (int i = 0; i < SIZE; i++)
        printf("%d ", sorted_arr[i]);
    printf("\n");

    free(arr);
    free(sorted_arr);
    free(first_half);
    free(second_half);

    return 0;
}
