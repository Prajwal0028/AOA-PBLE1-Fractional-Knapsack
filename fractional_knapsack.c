/*
 * AOA PBLE 1: Smart Delivery Planning - Fractional Knapsack
 * Greedy method: pick packages in decreasing order of Value/Weight ratio,
 * taking a fraction of the last package if it does not fit completely.
 */
#include <stdio.h>

#define MAX 50

/* Global arrays (parallel arrays, index i describes package i) */
int    id[MAX];          /* original package number          */
double value[MAX];       /* value / profit of the package    */
double weight[MAX];      /* weight of the package            */
double ratio[MAX];       /* value / weight                   */
double taken[MAX];       /* fraction of package selected     */
int    n = 0;            /* number of packages               */
double capacity = 0;     /* vehicle capacity                 */

int dataEntered = 0, ratioDone = 0, sortDone = 0, solved = 0;
double totalValue = 0, totalWeight = 0;

/* 1. Read package details */
void enterDetails(void) {
    int i;
    printf("Enter number of packages (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of packages.\n");
        while (getchar() != '\n');
        n = 0; dataEntered = 0;
        return;
    }
    for (i = 0; i < n; i++) {
        id[i] = i + 1;
        printf("Package %d - Value: ", i + 1);
        scanf("%lf", &value[i]);
        printf("Package %d - Weight: ", i + 1);
        scanf("%lf", &weight[i]);
        if (weight[i] <= 0 || value[i] < 0) {
            printf("Weight must be > 0 and value >= 0. Re-enter this package.\n");
            i--;
        }
    }
    do {
        printf("Enter vehicle capacity: ");
        scanf("%lf", &capacity);
        if (capacity <= 0) printf("Capacity must be positive.\n");
    } while (capacity <= 0);

    dataEntered = 1; ratioDone = 0; sortDone = 0; solved = 0;
    printf("Details stored successfully.\n");
}

/* 2. Display package details (and ratio if already calculated) */
void displayDetails(void) {
    int i;
    if (!dataEntered) { printf("Please enter package details first (option 1).\n"); return; }
    printf("\nVehicle capacity = %.2f\n", capacity);
    printf("%-10s %-10s %-10s %-12s\n", "Package", "Value", "Weight", "Value/Weight");
    for (i = 0; i < n; i++) {
        printf("%-10d %-10.2f %-10.2f ", id[i], value[i], weight[i]);
        if (ratioDone) printf("%-12.2f", ratio[i]);
        else           printf("%-12s", "-");
        printf("\n");
    }
}

/* 3. Calculate Value/Weight ratio of each package */
void calculateRatio(void) {
    int i;
    if (!dataEntered) { printf("Please enter package details first (option 1).\n"); return; }
    for (i = 0; i < n; i++)
        ratio[i] = value[i] / weight[i];
    ratioDone = 1; sortDone = 0; solved = 0;
    printf("\nValue/Weight ratios:\n");
    for (i = 0; i < n; i++)
        printf("Package %d: %.2f / %.2f = %.2f\n", id[i], value[i], weight[i], ratio[i]);
}

/* Swap helper: swaps all parallel arrays at positions a and b */
void swapPackages(int a, int b) {
    int ti; double td;
    ti = id[a];     id[a] = id[b];         id[b] = ti;
    td = value[a];  value[a] = value[b];   value[b] = td;
    td = weight[a]; weight[a] = weight[b]; weight[b] = td;
    td = ratio[a];  ratio[a] = ratio[b];   ratio[b] = td;
}

/* 4. Sort packages by decreasing ratio (selection sort, O(n^2)) */
void sortByRatio(void) {
    int i, j, maxIdx;
    if (!ratioDone) { printf("Please calculate ratios first (option 3).\n"); return; }
    for (i = 0; i < n - 1; i++) {
        maxIdx = i;
        for (j = i + 1; j < n; j++)
            if (ratio[j] > ratio[maxIdx]) maxIdx = j;
        if (maxIdx != i) swapPackages(i, maxIdx);
    }
    sortDone = 1; solved = 0;
    printf("\nPackages in decreasing order of Value/Weight ratio:\n");
    printf("%-10s %-10s %-10s %-12s\n", "Package", "Value", "Weight", "Value/Weight");
    for (i = 0; i < n; i++)
        printf("%-10d %-10.2f %-10.2f %-12.2f\n", id[i], value[i], weight[i], ratio[i]);
}

/* 5. Greedy selection: find maximum value */
void findMaxValue(void) {
    int i;
    double remaining;
    if (!sortDone) { printf("Please sort packages first (option 4).\n"); return; }

    remaining = capacity; totalValue = 0; totalWeight = 0;
    for (i = 0; i < n; i++) taken[i] = 0;

    printf("\nGreedy selection steps (capacity = %.2f):\n", capacity);
    for (i = 0; i < n && remaining > 0; i++) {
        if (weight[i] <= remaining) {            /* whole package fits */
            taken[i] = 1.0;
            remaining   -= weight[i];
            totalWeight += weight[i];
            totalValue  += value[i];
            printf("Take full Package %d -> value added %.2f, remaining capacity %.2f\n",
                   id[i], value[i], remaining);
        } else {                                  /* take a fraction */
            taken[i] = remaining / weight[i];
            totalValue  += value[i] * taken[i];
            totalWeight += remaining;
            printf("Take %.2f (%.2f%%) of Package %d -> value added %.2f, remaining capacity 0.00\n",
                   taken[i], taken[i] * 100, id[i], value[i] * taken[i]);
            remaining = 0;
        }
    }
    solved = 1;
    printf("\nMaximum value obtained = %.2f\n", totalValue);
}

/* 6. Display selected packages */
void displaySelected(void) {
    int i;
    if (!solved) { printf("Please find the maximum value first (option 5).\n"); return; }
    printf("\n%-10s %-10s %-10s %-12s\n", "Package", "Fraction", "Weight used", "Value gained");
    for (i = 0; i < n; i++)
        if (taken[i] > 0)
            printf("%-10d %-10.2f %-11.2f %-12.2f\n",
                   id[i], taken[i], weight[i] * taken[i], value[i] * taken[i]);
    printf("\nTotal weight used = %.2f / %.2f\n", totalWeight, capacity);
    printf("Maximum value     = %.2f\n", totalValue);
    printf("\nTime complexity: O(n^2) with the selection sort used here\n"
           "(O(n log n) if merge sort/quick sort is used). Ratio calculation and\n"
           "the greedy selection loop are each O(n), so sorting dominates.\n");
}

int main(void) {
    int choice;
    do {
        printf("\n===== Smart Delivery Planning - Fractional Knapsack =====\n");
        printf("1. Enter Package Details\n");
        printf("2. Display Package Details\n");
        printf("3. Calculate Value/Weight Ratio\n");
        printf("4. Sort Packages by Ratio\n");
        printf("5. Find Maximum Value\n");
        printf("6. Display Selected Packages\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {          /* non-numeric input */
            while (getchar() != '\n');
            choice = 0;
        }
        switch (choice) {
            case 1: enterDetails();    break;
            case 2: displayDetails();  break;
            case 3: calculateRatio();  break;
            case 4: sortByRatio();     break;
            case 5: findMaxValue();    break;
            case 6: displaySelected(); break;
            case 7: printf("Exiting program. Goodbye!\n"); break;
            default: printf("Invalid choice! Please enter a number from 1 to 7.\n");
        }
    } while (choice != 7);
    return 0;
}
