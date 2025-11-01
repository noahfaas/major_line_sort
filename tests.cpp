#include "major_sort.h"
#include <iostream>
#include <vector>
#include <string>

using namespace showcase;

// Print a vector on one line
void printVec(const std::vector<std::string>& v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i];
        if (i + 1 < v.size()) std::cout << ", ";
    }
    std::cout << "]\n";
}

// Check that all U's come first, then CS's, then M's, then SDS's.
// This does NOT map to numbers; it just checks the sequence directly.
bool isOrderedU_CSM_SDS(const std::vector<std::string>& v) {
    int phase = 0; // 0=U, 1=CS, 2=M, 3=SDS
    for (size_t i = 0; i < v.size(); i++) {
        const std::string& s = v[i];
        if (phase == 0) {
            if (s == "U") {
                // ok
            } else if (s == "CS") {
                phase = 1;
            } else if (s == "M") {
                phase = 2;
            } else if (s == "SDS") {
                phase = 3;
            } else {
                return false;
            }
        } else if (phase == 1) {
            if (s == "U") return false; // can't go back
            if (s == "CS") {
                // ok
            } else if (s == "M") {
                phase = 2;
            } else if (s == "SDS") {
                phase = 3;
            } else {
                return false;
            }
        } else if (phase == 2) {
            if (s == "U" || s == "CS") return false;
            if (s == "M") {
                // ok
            } else if (s == "SDS") {
                phase = 3;
            } else {
                return false;
            }
        } else { // phase == 3
            if (s == "U" || s == "CS" || s == "M") return false;
            if (s == "SDS") {
                // ok
            } else {
                return false;
            }
        }
    }
    return true;
}

// Run a single test: sort, then check order. Print "Pass" or the final order if not ordered.
void runTest(const std::vector<std::string>& input) {
    std::vector<std::string> v = input;
    sortMajors(v);
    if (isOrderedU_CSM_SDS(v)) {
        std::cout << "Pass\n";
    } else {
        printVec(v);
    }
}

int main() {
    // 1) empty
    runTest({});

    // 2) single
    runTest({"U"});
    runTest({"CS"});
    runTest({"M"});
    runTest({"SDS"});

    // 3) already sorted
    runTest({"U","U","CS","CS","M","SDS"});

    // 4) reverse order
    runTest({"SDS","M","CS","U"});

    // 5) alternating
    runTest({"U","SDS","CS","M","SDS","U","CS","M"});

    // 6) all same
    runTest({"M","M","M","M"});

    // 7) paper examples
    runTest({"M","U","CS","U"});
    runTest({"M","CS","M","U","U","SDS","U"});
    runTest({"U","U","U","U","CS","CS","SDS"});

    // 8) larger quick check
    std::vector<std::string> big;
    for (int i = 0; i < 200; i++) {
        big.push_back("U");
        big.push_back("CS");
        big.push_back("M");
        big.push_back("SDS");
        big.push_back("CS");
        big.push_back("U");
    }
    runTest(big);

    return 0;
}
