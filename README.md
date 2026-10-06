# Smart Delivery Planning – Fractional Knapsack

**Subject:** Analysis of Algorithms (AOA) – PBLE 1
**Language:** C
**Technique:** Greedy Method (Fractional Knapsack)

## Problem
A delivery vehicle has a fixed carrying capacity. Each package has a value and a weight.
A whole package or a fraction of it may be loaded. Find the maximum total value that fits.

## Approach
1. Calculate Value/Weight ratio for every package.
2. Sort packages in decreasing order of ratio.
3. Take whole packages while they fit; take a fraction of the next package to fill the remaining capacity.
4. Display the selected packages, total weight used and maximum value.

## Menu
1. Enter Package Details
2. Display Package Details
3. Calculate Value/Weight Ratio
4. Sort Packages by Ratio
5. Find Maximum Value
6. Display Selected Packages
7. Exit

## How to Run
```bash
gcc fractional_knapsack.c -o fractional_knapsack
./fractional_knapsack
```
Use the options in order: 1 → 3 → 4 → 5 → 6.

## Test Case
**Input:** capacity = 15

| Package | Value | Weight | Value/Weight |
|---------|-------|--------|--------------|
| 1 | 40 | 5  | 8  |
| 2 | 30 | 10 | 3  |
| 3 | 50 | 5  | 10 |
| 4 | 20 | 4  | 5  |

**Sorted order:** P3, P1, P4, P2

**Selection:** full P3, full P1, full P4, 0.10 of P2

**Output:** Total weight used = 15 / 15, **Maximum value = 113**

## Time Complexity
- Ratio calculation: O(n)
- Sorting (selection sort used here): O(n²)  (O(n log n) with merge/quick sort)
- Greedy selection: O(n)

Sorting dominates, so overall **O(n²)** (or O(n log n) with an efficient sort). Space: O(n).
