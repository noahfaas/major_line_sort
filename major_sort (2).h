#pragma once
// major_sort.h
// String-only solution for ordering MSCS majors in the line:
// Required order: U, then CS, then M, then SDS.
//
// This follows the "four lines (buckets)" idea from the paper:
//   1) Walk through the input once and put each label into one of four vectors.
//   2) Copy those four vectors back into the original vector in the right order.
//
// Time:  O(n)    (we look at each element a constant number of times)
// Space: O(n)    (we store up to n strings across the four temporary vectors)
//
// This header is written to be easy to read by students new to C++.
// It only uses basic C++ standard library features.

#include <vector>
#include <string>

namespace showcase {

// We'll use simple integer codes to represent the four categories.
enum MajorCode {
    U   = 0,  // Undeclared
    CS  = 1,  // Computer Science
    M   = 2,  // Mathematics
    SDS = 3   // Statistics and Data Science
};

// Make an uppercase copy of a string (ASCII only).
inline std::string to_upper_copy(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (size_t i = 0; i < s.size(); i++) {
        unsigned char c = static_cast<unsigned char>(s[i]);
        if (c >= 'a' && c <= 'z') out.push_back(static_cast<char>(c - 'a' + 'A'));
        else out.push_back(static_cast<char>(c));
    }
    return out;
}

// Remove spaces at the beginning and end of a string.
inline std::string trim_copy(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && (s[start] == ' ' || s[start] == '\t' || s[start] == '\n' || s[start] == '\r')) {
        start++;
    }
    size_t end = s.size();
    while (end > start) {
        char c = s[end - 1];
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') end--;
        else break;
    }
    return s.substr(start, end - start);
}

// Convert a label string to a MajorCode. We accept only "U", "CS", "M", "SDS"
// (case-insensitive; surrounding spaces are allowed).
// Returns true on success and writes the code to 'out'.
inline bool label_to_code(const std::string& label, MajorCode& out) {
    std::string t = to_upper_copy(trim_copy(label));
    if (t == "U")   { out = U;   return true; }
    if (t == "CS")  { out = CS;  return true; }
    if (t == "M")   { out = M;   return true; }
    if (t == "SDS") { out = SDS; return true; }
    return false; // unknown label
}

// Sort the vector of strings in-place using the four-bucket approach.
// The function returns true on success. If an unknown label is found,
// the function returns false and leaves the vector unchanged.
inline bool sortMajorsBucket(std::vector<std::string>& line) {
    // Make the four temporary buckets
    std::vector<std::string> u;
    std::vector<std::string> cs;
    std::vector<std::string> m;
    std::vector<std::string> sds;

    // We will not modify 'line' unless all labels are valid.
    // So we collect into buckets first, and if we hit an invalid label, we stop.
    for (size_t i = 0; i < line.size(); i++) {
        MajorCode code;
        if (!label_to_code(line[i], code)) {
            // Unknown label: fail without changing 'line'.
            return false;
        }
        if (code == U)       u.push_back(line[i]);
        else if (code == CS) cs.push_back(line[i]);
        else if (code == M)  m.push_back(line[i]);
        else                 sds.push_back(line[i]);
    }

    // Overwrite the original vector in the required order.
    size_t k = 0;
    for (size_t i = 0; i < u.size();   i++) line[k++] = u[i];
    for (size_t i = 0; i < cs.size();  i++) line[k++] = cs[i];
    for (size_t i = 0; i < m.size();   i++) line[k++] = m[i];
    for (size_t i = 0; i < sds.size(); i++) line[k++] = sds[i];

    return true;
}

} // namespace showcase
