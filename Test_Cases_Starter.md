# Test Cases (run each one and record PASS/FAIL)

| Test Case | Input | Expected Output | Result |
|---|---|---|---|
| Add Road | ID 101, valid fields | "Road added." | |
| Duplicate ID | Add ID 101 again | "That ID already exists." | |
| Invalid menu input | Type abc at a menu | "Invalid input..." and asks again | |
| Invalid traffic level | Enter 9 | Asks again (valid range 1-3) | |
| Search Road | ID 101 | Road displayed | |
| Search nonexistent | ID 99999 | "Road not found." | |
| Update Road | ID 101, new details | "Road updated." | |
| Delete Road | ID 101 | "Road deleted." | |
| Delete nonexistent | ID 99999 | "Road not found." | |
| View empty list | View with no records | "No roads recorded." | |
| Array full | Add 51 roads | "Road storage is full." on the 51st | |
| Sort Roads | Several roads, unsorted IDs | Records in ascending ID | |
| Linear search (center) | Existing ID | Road displayed | |
| Binary search (center) | Existing ID | Road displayed | |
| Sort by name / status (center) | Several roads | Records in the right order | |
| Matrix display | Roads menu, option 7, then 1 | 4x4 matrix shown | |
| Matrix row processing | Option 2 in the matrix menu | Connections per district | |
| Dynamic array full | Choose size 2, add 3 utilities | "Utility storage is full." on the 3rd | |
| Pointer demo | Main menu option 8 | Address, dereferenced value shown | |
| Statistics | After adding data | Counts match the records | |
| Request status | Update a request to status 3 | Resolved count goes up | |
