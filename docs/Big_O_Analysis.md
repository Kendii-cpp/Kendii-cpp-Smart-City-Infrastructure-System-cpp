# Big-O Analysis

| Operation | Algorithm | Complexity | Where |
|---|---|---|---|
| Record traversal (view) | Sequential traversal | O(n) | every view function |
| Add record | Insert at end of array | O(1) | add functions |
| Delete record | Find + shift left | O(n) | delete functions |
| Update record | Find by ID | O(n) | update functions |
| Linear search | Linear search | O(n) | search.cpp |
| Binary search | Binary search (sorted data) | O(log n) | search.cpp |
| Bubble sort | Bubble sort | O(n^2); best O(n) with swapped flag | sorting.cpp |
| Selection sort | Selection sort | O(n^2) always | sorting.cpp |
| Insertion sort | Insertion sort | O(n^2); best O(n) | sorting.cpp |
| Matrix display / row sums | Nested loops | O(n^2) | matrix.cpp |
| Matrix multiplication | Three nested loops | O(n^3) | matrix.cpp |
| Statistics | One loop per count | O(n) each | get...Count() functions |
| Grow dynamic array | Allocate, copy, delete[] | O(n) (rare) | utilities.cpp |
