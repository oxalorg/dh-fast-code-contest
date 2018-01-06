#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define N 1000000
#define RN 100

void multiSort(size_t size, double x[N], double y[N], long int rank[N]) {
    double xtemp, ytemp;
    long int rtemp;
    for (size_t i = 0; i < N; i++) {
    }
}

void swapli(long int* a, long int* b) {
    long int t = *a;
    *a = *b;
    *b = t;
}

void swapdouble(double* a, double* b) {
    double t = *a;
    *a = *b;
    *b = t;
}


int partition (long int arr[], int low, int high, double x[], double y[]) {
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swapli(&arr[i], &arr[j]);
            swapdouble(&x[i], &x[j]);
            swapdouble(&y[i], &y[j]);
        }
    }
    swapli(&arr[i + 1], &arr[high]);
    swapdouble(&x[i + 1], &x[high]);
    swapdouble(&y[i + 1], &y[high]);
    return (i + 1);
}

void quickSort(long int arr[], int low, int high, double x[], double y[]) {
    if (low < high)
    {
        int pi = partition(arr, low, high, x, y);
        quickSort(arr, low, pi - 1, x, y);  // Before pi
        quickSort(arr, pi + 1, high, x, y); // After pi
    }
}


int MAX_LINE_BUFF = 1024;

struct Point {
    double x[N];
    double y[N];
    long int rank[N];
} points;

struct Rect {
    double x1, x2, y1, y2;
} rects[RN];

int comp (const void * elem1, const void * elem2) {
    struct Point *f = (struct Point*)elem1;
    struct Point *s = (struct Point*)elem2;
    if (f->rank > s->rank)
        return 1;
    else if (f->rank < s->rank)
        return -1;
    return 0;
}

int main() {
    FILE *fp;
    char line[MAX_LINE_BUFF];

    // Get points
    fp = fopen("12345678-12345678-12345678-12345678-12345678-points.txt", "r");
    int i = 0;
    while(fgets(line, sizeof line, fp) != NULL) {
        char *tokLine = line;
        sscanf(tokLine, "%lf %lf %ld", &(points.x[i]), &(points.y[i]), &(points.rank[i]));
        /* printf("%f %f %f\n", x, y, rank); */
        i++;
    }
    fclose(fp);

    // get rekts
    fp = fopen("12345678-12345678-12345678-12345678-12345678-rects.txt", "r");
    i = 0;
    while(fgets(line, sizeof line, fp) != NULL) {
        char *tokLine = line;
        sscanf(tokLine, "%lf %lf %lf %lf", &(rects[i].x1), &(rects[i].x2), &(rects[i].y1), &(rects[i].y2));
        /* printf("%f %f %f\n", x, y, rank); */
        i++;
    }
    fclose(fp);

    long int count = 0;
    long int top[RN][20];
    for(int j = 0; j < RN; j++){
        for(i = 0; i < 20; i++){
            top[j][i] = -1;
        }
    }

    // sort points by rank
    /* qsort (points, sizeof(points)/sizeof(*points), sizeof(*points), comp); */
    quickSort(points.rank, 0, N-1, points.x, points.y);
    clock_t begin = clock();
    for(int j = 0; j < RN; j++) {
        count = 0;
        for(i = 0; i < N; i++) {
            if (points.x[i] >= rects[j].x1 && points.x[i] <= rects[j].x2 && \
                    points.y[i] >= rects[j].y1 && points.y[i] <= rects[j].y2) {
                /* top[j][count] = points.rank[i]; */
                count++;
                /* if (count >= 20) */
                /*     break; */
            }
        }
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    for(int j = 0; j < RN; j++){
        for(i = 0; i < 20; i++){
            if (top[j][i] != -1)
                printf("%ld ", top[j][i]);
        }
        printf("\n");
    }

    printf("%ld\n", count);
    printf("\nAVG: %f ms\nTOT: %f ms\n", 1000*time_spent/RN, time_spent*1000);

    return 0;
}

