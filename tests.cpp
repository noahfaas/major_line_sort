#include "major_sort.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <random>
#include <string>

using namespace showcase;

template <typename T>
void expect_eq(const std::vector<T>& a, const std::vector<T>& b, const char* msg) {
    if (a != b) {
        std::cerr << "Test failed: " << msg << "\nExpected: [";
        for (size_t i = 0; i < b.size(); ++i) std::cerr << b[i] << (i + 1 < b.size() ? ", " : "");
        std::cerr << "]\nGot: [";
        for (size_t i = 0; i < a.size(); ++i) std::cerr << a[i] << (i + 1 < a.size() ? ", " : "");
        std::cerr << "]\n";
        assert(false);
    }
}

// Helper to check nondecreasing by code_of without changing strings
void expect_ordered_by_code(const std::vector<std::string>& v, const char* msg) {
    for (size_t i = 1; i < v.size(); ++i) {
        assert(code_of(v[i-1]) <= code_of(v[i]) && msg);
    }
}

int main() {
    // 1) Empty
    { std::vector<std::string> v; sortMajorsBucket(v); expect_eq(v, std::vector<std::string>{}, "empty"); }

    // 2) Single
    { std::vector<std::string> v = {"U"}; sortMajorsBucket(v); expect_eq(v, std::vector<std::string>{"U"}, "single"); }

    // 3) Already sorted
    { std::vector<std::string> v = {"U","U","CS","CS","M","SDS"}; auto exp=v; sortMajorsBucket(v); expect_eq(v, exp, "already sorted"); }

    // 4) Reverse order
    { std::vector<std::string> v = {"SDS","M","CS","U"}; sortMajorsBucket(v); expect_ordered_by_code(v, "reverse -> ordered"); }

    // 5) Alternating
    { std::vector<std::string> v = {"U","SDS","CS","M","SDS","U","CS","M"}; sortMajorsBucket(v); expect_ordered_by_code(v, "alternating"); }

    // 6) All same
    { std::vector<std::string> v = {"M","M","M"}; auto exp=v; sortMajorsBucket(v); expect_eq(v, exp, "all same"); }

    // 7) Case and whitespace tolerance
    { std::vector<std::string> v = {"  cs", "M", "sds  ", "u"}; sortMajorsBucket(v);
      expect_eq(v, std::vector<std::string>{"u","  cs","M","sds  "}, "case + spaces"); }

    // 8) Paper example A
    { std::vector<std::string> v = {"M","U","CS","U"}; sortMajorsBucket(v);
      expect_eq(v, std::vector<std::string>{"U","U","CS","M"}, "paper A"); }

    // 9) Paper example B
    { std::vector<std::string> v = {"M","CS","M","U","U","SDS","U"}; sortMajorsBucket(v);
      expect_eq(v, std::vector<std::string>{"U","U","U","CS","M","M","SDS"}, "paper B"); }

    // 10) Paper example C
    { std::vector<std::string> v = {"U","U","U","U","CS","CS","SDS"}; sortMajorsBucket(v);
      expect_eq(v, std::vector<std::string>{"U","U","U","U","CS","CS","SDS"}, "paper C"); }

    // 11) Unknown should throw
    {
        bool threw = false;
        try { std::vector<std::string> v = {"BIO"}; sortMajorsBucket(v); }
        catch (const std::invalid_argument&) { threw = true; }
        assert(threw && "unknown label must throw");
    }

    // 12) Random stress (strings)
    {
        std::vector<std::string> pool = {"U","CS","M","SDS","u","cs","m","sds","  U","cs  "," M","sds "};
        std::mt19937 rng(123);
        std::uniform_int_distribution<size_t> d(0, pool.size()-1);
        std::vector<std::string> v(2000);
        for (auto& s : v) s = pool[d(rng)];
        sortMajorsBucket(v);
        expect_ordered_by_code(v, "random stress");
    }

    std::cout << "All tests passed.\n";
    return 0;
}
