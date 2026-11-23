# Test Cases (starter: run each one and record PASS/FAIL)

| Test Case | Input | Expected Output | Result |
|---|---|---|---|
| Add Road | ID 101, valid fields | "Road added successfully." | |
| Duplicate ID | Add ID 101 again | "A road with ID 101 already exists." | |
| Invalid menu input | Type `abc` at a menu | "Invalid input..." and ask again | |
| Invalid traffic level | Enter 9 | Re-asks (valid range 1-3) | |
| Search Road | ID 101 | Road displayed | |
| Search nonexistent | ID 99999 | "Road not found." | |
| Update Road | ID 101, new details | "Road updated." | |
| Delete Road | ID 101, confirm y | "Road deleted." | |
| Delete cancelled | ID 101, confirm n | "Cancelled." record kept | |
| View empty list | View with no records | "No roads recorded." | |
| Array full | Add 51 roads | "Road storage is full..." on the 51st | |
| Sort Roads | Several roads, unsorted IDs | Records in ascending ID | |
| Linear search | Existing ID | Found + number of checks | |
| Binary search | Existing ID | Found with fewer checks | |
| Sort by name / status | Several roads | Alphabetical order | |
| Matrix display | Option 1 in matrix menu | 4x4 matrix shown | |
| Matrix row processing | Option 2 | Connections per district | |
| Add/remove connection | Districts 1 and 2 | Matrix updated both ways | |
| Dynamic array growth | Add 6 utilities | "grew from 5 to 10 records" message | |
| Statistics | After adding data | Counts match the records | |
| Request status | Change Pending to Resolved | Resolved count goes up | |
