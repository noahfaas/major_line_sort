#include "major_sort.h"
#include <iostream>
#include <vector>
#include <string>

using namespace showcase;

// Utility to print a vector (for debugging)
void print_vec(const std::vector<std::string>& v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i];
        if (i + 1 < v.size()) std::cout << ", ";
    }
    std::cout << "]";
}

// Compare two string vectors for equality
bool equal_vec(const std::vector<std::string>& a, const std::vector<std::string>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

// Check nondecreasing order by category using label_to_code
bool is_ordered_by_code(const std::vector<std::string>& v) {
    if (v.size() == 0) return true;
    for (size_t i = 1; i < v.size(); i++) {
        MajorCode prev, cur;
        if (!label_to_code(v[i-1], prev)) return false;
        if (!label_to_code(v[i], cur)) return false;
        if (prev > cur) return false;
    }
    return true;
}

// Simple test helper
void expect_true(bool cond, const std::string& name) {
    if (cond) std::cout << "[PASS] " << name << "\n";
    else      std::cout << "[FAIL] " << name << "\n";
}

void expect_eq(const std::vector<std::string>& got,
               const std::vector<std::string>& want,
               const std::string& name) {
    if (equal_vec(got, want)) {
        std::cout << "[PASS] " << name << "\n";
    } else {
        std::cout << "[FAIL] " << name << "\n  got:  ";
        print_vec(got);
        std::cout << "\n  want: ";
        print_vec(want);
        std::cout << "\n";
    }
}

int main() {
    // 1) Empty
    {
        std::vector<std::string> v;
        bool ok = sortMajorsBucket(v);
        expect_true(ok, "empty returns true");
        expect_eq(v, std::vector<std::string>{}, "empty stays empty");
    }

    // 2) Single
    {
        std::vector<std::string> v = {"U"};
        bool ok = sortMajorsBucket(v);
        expect_true(ok, "single returns true");
        expect_eq(v, std::vector<std::string>{"U"}, "single U");
    }

    // 3) Already sorted
    {
        std::vector<std::string> v = {"U","U","CS","CS","M","SDS"};
        bool ok = sortMajorsBucket(v);
        expect_true(ok, "already sorted ok");
        expect_eq(v, std::vector<std::string>{"U","U","CS","CS","M","SDS"}, "already sorted unchanged");
    }

    // 4) Reverse order
    {
        std::vector<std::string> v = {"SDS","M","CS","U"};
        bool ok = sortMajorsBucket(v);
        expect_true(ok, "reverse ok");
        expect_true(is_ordered_by_code(v), "reverse becomes ordered");
    }

    // 5) Alternating pattern
    {
        std::vector<std::string> v = {"U","SDS","CS","M","SDS","U","CS","M"};
        bool ok = sortMajorsBucket(v);
        expect_true(ok, "alternating ok");
        expect_true(is_ordered_by_code(v), "alternating becomes ordered");
    }

    // 6) All same
    {
        std::vector<std::string> v = {"M","M","M"};
        bool ok = sortMajorsBucket(v);
        expect_true(ok, "all same ok");
        expect_eq(v, std::vector<std::string>{"M","M","M"}, "all M unchanged");
    }

    // 7) Case + spaces
    {
        std::vector<std::string> v = {"  cs", "M", "sds  ", "u"};
        bool ok = sortMajorsBucket(v);
        expect_true(ok, "case+spaces ok");
        expect_eq(v, std::vector<std::string>{"u","  cs","M","sds  "}, "case + spaces grouped, labels preserved");
    }

    // 8) Paper example A
    {
        std::vector<std::string> v = {"M","U","CS","U"};
        bool ok = sortMajorsBucket(v);
        expect_true(ok, "paper A ok");
        expect_eq(v, std::vector<std::string>{"U","U","CS","M"}, "paper A expected order");
    }

    // 9) Paper example B
    {
        std::vector<std::string> v = {"M","CS","M","U","U","SDS","U"};
        bool ok = sortMajorsBucket(v);
        expect_true(ok, "paper B ok");
        expect_eq(v, std::vector<std::string>{"U","U","U","CS","M","M","SDS"}, "paper B expected order");
    }

    // 10) Paper example C
    {
        std::vector<std::string> v = {"U","U","U","U","CS","CS","SDS"};
        bool ok = sortMajorsBucket(v);
        expect_true(ok, "paper C ok");
        expect_eq(v, std::vector<std::string>{"U","U","U","U","CS","CS","SDS"}, "paper C expected order");
    }

    // 11) Unknown should fail without changing input
    {
        std::vector<std::string> v = {"U", "BIO", "CS"};
        std::vector<std::string> before = v;
        bool ok = sortMajorsBucket(v);
        expect_true(!ok, "unknown returns false");
        expect_eq(v, before, "unknown leaves input unchanged");
    }

    // 12) Random stress (small, readable)
    {
        std::vector<std::string> v = {"U","CS","M","SDS","u","cs","m","sds","  U","cs  "," M","sds "};
        // Make a larger test vector by repeating.
        std::vector<std::string> big;
        for (int i = 0; i < 100; i++) {
            for (size_t j = 0; j < v.size(); j++) big.push_back(v[j]);
        }
        bool ok = sortMajorsBucket(big);
        expect_true(ok, "random-ish stress ok");
        expect_true(is_ordered_by_code(big), "random-ish stress becomes ordered");
    }

    std::cout << "Done running tests.\n";
    return 0;
}
