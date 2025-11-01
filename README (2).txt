README (Undergraduate-Friendly) - MSCS Major Sorting, String-Only
=================================================================

This project sorts students in a line by major using **strings only**.
Required order: **U → CS → M → SDS**

We use a simple **four-bucket** method:
1) Walk once through the input and put each string into one of four temporary vectors.
2) Copy those four vectors back into the original vector in the required order.

- Time:  O(n)
- Space: O(n)
- Stable inside each major (we keep each student's original label and order).

Files
-----
- `major_sort.h` — Header-only C++ implementation (very basic C++).
- `tests.cpp`    — Small test program (no frameworks).

Build & Run (local or GitHub Codespaces)
----------------------------------------
1) Open a terminal in the folder with these files.
2) Compile:
   g++ -std=gnu++17 -O2 -Wall -Wextra tests.cpp -o tests
3) Run:
   ./tests

You should see several [PASS] lines and finally:
   Done running tests.

How to Use in Your Code
-----------------------
Example:
    #include "major_sort.h"
    #include <vector>
    #include <string>
    #include <iostream>
    using namespace showcase;

    int main() {
        std::vector<std::string> line;
        line.push_back("M");
        line.push_back("U");
        line.push_back("CS");
        line.push_back("U");

        bool ok = sortMajorsBucket(line);
        if (!ok) {
            std::cout << "Found an unknown major label.\n";
            return 1;
        }

        // Expected: U, U, CS, M (labels are preserved exactly)
        for (size_t i = 0; i < line.size(); i++) {
            std::cout << line[i] << (i + 1 < line.size() ? " " : "\n");
        }
        return 0;
    }

Label Rules
-----------
- Accepted labels: "U", "CS", "M", "SDS"
- Case-insensitive and spaces at the edges are okay (e.g., "  cs", "sds  ", "u").
- If an unknown label appears (like "BIO"), `sortMajorsBucket` returns **false** and **leaves the input unchanged**.

Upload and Test in GitHub Codespaces
------------------------------------
1) Create a new GitHub repository and upload `major_sort.h` and `tests.cpp`.
2) On the repo page, click **Code → Codespaces → Create codespace on main**.
3) In the Codespaces terminal:
   g++ -std=gnu++17 -O2 -Wall -Wextra tests.cpp -o tests
   ./tests
4) You should see the tests pass messages and "Done running tests."

Troubleshooting
---------------
- If `g++` is not found (rare in Codespaces), run:
   sudo apt-get update && sudo apt-get install -y g++
- Make sure your inputs are only "U", "CS", "M", "SDS" (with any capitalization, spaces allowed).
