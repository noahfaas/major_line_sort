README - MSCS Major Sorting (String-Only)
========================================

This package implements the paper's **four-line (bucket) algorithm** for **string labels only**.
Accepted labels (case-insensitive, whitespace allowed): "U", "CS", "M", "SDS".
Target order: U → CS → M → SDS.
Complexity: **O(n) time**, **O(n) extra space**; stable within each major.

FILES
-----
- major_sort.h   : Header-only C++17 implementation (namespace `showcase`).
- tests.cpp      : String-only tests (12 total).

BUILD & RUN (local or GitHub Codespaces)
----------------------------------------
    g++ -std=gnu++17 -O2 -Wall -Wextra tests.cpp -o tests
    ./tests

Expected output:
    All tests passed.

USAGE
-----
    #include "major_sort.h"
    using namespace showcase;

    std::vector<std::string> line = {"M","U","CS","U"};
    sortMajorsBucket(line);
    // => {"U","U","CS","M"}

GITHUB CODESPACES QUICK START
-----------------------------
1) Create a GitHub repo and upload `major_sort.h`, `tests.cpp`, and `README.txt`.
2) Open the repo → **Code** → **Codespaces** → **Create codespace on main**.
3) In the terminal:
       g++ -std=gnu++17 -O2 -Wall -Wextra tests.cpp -o tests
       ./tests
4) You should see **All tests passed.**

TROUBLESHOOTING
---------------
- If `g++` is missing:
      sudo apt-get update && sudo apt-get install -y g++
- If you pass an unsupported label (e.g., "BIO"), the function throws `std::invalid_argument`.
