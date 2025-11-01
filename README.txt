README (Super Simple Version)
==============================

Goal
----
Sort a list of strings so that all **U** come first, then **CS**, then **M**, then **SDS**.
We assume every string is exactly one of: "U", "CS", "M", "SDS".

Files
-----
- `major_sort.h` — beginner-level header with a single function:
    - `showcase::sortMajors(std::vector<std::string>& line)`
- `tests.cpp` — simple tests that print **"Pass"** if the result is ordered,
  or print the resulting order if it is not.

Build & Run
-----------
```bash
g++ -std=gnu++17 -O2 -Wall -Wextra tests.cpp -o tests
./tests
```

Expected Output
---------------
A bunch of lines that say **"Pass"** (one per test).  
If a test fails, it will print the final order of the strings instead.

How it Works (Very Simple)
--------------------------
We make four temporary lists: one for "U", one for "CS", one for "M", and one for "SDS".  
We go through the input once and put each string into the right list, then copy them back in the order U, CS, M, SDS.

No special cases like spaces or lowercase are handled in this version (keep inputs exactly as "U", "CS", "M", "SDS").
