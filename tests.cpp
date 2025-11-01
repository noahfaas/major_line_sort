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
    // empty
    runTest({});

    // single element U
    runTest({"U"});

    // single element CS
    runTest({"CS"});

    // single element M
    runTest({"M"});
    
    // single element SDS
    runTest({"SDS"});

    // already sorted
    runTest({"U","U","CS","CS","M","SDS"});

    // reverse order
    runTest({"SDS","M","CS","U"});

    // alternating cycle
    runTest({"U","SDS","CS","M","SDS","U","CS","M"});

    // all same major
    runTest({"M","M","M","M"});

    // random order 1
    runTest({"M","U","CS","U"});

    // random order 2
    runTest({"M","CS","M","U","U","SDS","U"});

    // random order 3
    runTest({"U","U","U","U","CS","CS","SDS"});

    return 0;
}
