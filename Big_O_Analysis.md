# Big-O Analysis

| Operation | Algorithm | Complexity | Where |
|---|---|---|---|
| Record traversal (view) | Sequential traversal | O(n) | every view function |
| Add record | Insert at the next free slot | O(1) | add functions |
| Delete record | Find, then shift left | O(n) | delete functions |
| Update record | Find by ID | O(n) | update functions |
| Linear search | Linear search | O(n) | search.cpp |
| Binary search | Binary search (sorted data) | O(log n) | search.cpp |
| Sort | Bubble sort | O(n^2); best case O(n) if already sorted | sorting.cpp |
| Matrix display | Nested loops | O(n^2) | matrix.cpp |
| Row processing (connections per district) | Nested loops | O(n^2) | matrix.cpp |
| Statistics | One loop per count | O(n) each | getHighTrafficCount, countStatus |
