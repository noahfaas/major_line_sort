README

The algorithm is built to sort a list of strings so that all U come first, then CS, then M, then SDS.
We assume every string is exactly one of: "U", "CS", "M", "SDS".

To run the tests, paste the following code into the terminal:

g++ -std=gnu++17 -O2 -Wall -Wextra tests.cpp -o tests
./tests

For each test, if it passes, it will output "Pass" into the terminal. If the test fails, it will output the end order of the line.
Each test should resolve to "Pass" in the output.