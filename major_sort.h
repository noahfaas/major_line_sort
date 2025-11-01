#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include <cctype>

// MSCS Showcase major ordering (string-only, four-line bucket approach)
// Required order: U -> CS -> M -> SDS
// Complexity: O(n) time, O(n) extra space. Stable within each major.
namespace showcase {

enum MajorCode : int { U = 0, CS = 1, M = 2, SDS = 3 };

inline std::string trim_copy(const std::string& s) {
    size_t b = 0, e = s.size();
    while (b < e && std::isspace(static_cast<unsigned char>(s[b]))) ++b;
    while (e > b && std::isspace(static_cast<unsigned char>(s[e-1]))) --e;
    return s.substr(b, e - b);
}

inline std::string upper_copy(const std::string& s) {
    std::string out; out.reserve(s.size());
    for (unsigned char c : s) out.push_back(static_cast<char>(std::toupper(c)));
    return out;
}

// Map string label to category using the paper's four codes (case-insensitive):
// "U", "CS", "M", "SDS". Surrounding whitespace allowed.
inline MajorCode code_of(const std::string& raw) {
    std::string t = upper_copy(trim_copy(raw));
    if (t == "U") return MajorCode::U;
    if (t == "CS") return MajorCode::CS;
    if (t == "M") return MajorCode::M;
    if (t == "SDS") return MajorCode::SDS;
    throw std::invalid_argument("Unknown major label: '" + raw + "'");
}

// String-only algorithm. Stable: preserves original label text and within-category order.
inline void sortMajorsBucket(std::vector<std::string>& line) {
    std::vector<std::string> u, cs, m, sds;
    u.reserve(line.size()); cs.reserve(line.size()); m.reserve(line.size()); sds.reserve(line.size());
    for (const auto& s : line) {
        switch (code_of(s)) {
            case MajorCode::U:   u.push_back(s); break;
            case MajorCode::CS:  cs.push_back(s); break;
            case MajorCode::M:   m.push_back(s); break;
            case MajorCode::SDS: sds.push_back(s); break;
        }
    }
    size_t k = 0;
    for (const auto& s : u)   line[k++] = s;
    for (const auto& s : cs)  line[k++] = s;
    for (const auto& s : m)   line[k++] = s;
    for (const auto& s : sds) line[k++] = s;
}

} // namespace showcase
