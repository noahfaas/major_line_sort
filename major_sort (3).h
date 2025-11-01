#pragma once
// major_sort.h (BEGINNER VERSION)
// Very simple string-only sorting for majors in this exact order: U, CS, M, SDS.
// Assumptions:
//   - Input strings are exactly "U", "CS", "M", or "SDS".
//   - We don't handle extra spaces or different capitalization.
// Method:
//   - Make four temporary vectors and move through the list once,
//     pushing each string into the right bucket.
//   - Then copy the buckets back in the required order.

#include <vector>
#include <string>

namespace showcase {

inline void sortMajors(std::vector<std::string>& line) {
    std::vector<std::string> u;
    std::vector<std::string> cs;
    std::vector<std::string> m;
    std::vector<std::string> sds;

    // Put each item in its bucket
    for (size_t i = 0; i < line.size(); i++) {
        if (line[i] == "U") {
            u.push_back(line[i]);
        } else if (line[i] == "CS") {
            cs.push_back(line[i]);
        } else if (line[i] == "M") {
            m.push_back(line[i]);
        } else if (line[i] == "SDS") {
            sds.push_back(line[i]);
        } else {
            // If something else appears, just keep it at the end (optional).
            // For this beginner version, we won't do anything special.
            // We'll treat it like SDS (last), but tests won't include unknowns.
            sds.push_back(line[i]);
        }
    }

    // Copy back into original in order U, CS, M, SDS
    size_t k = 0;
    for (size_t i = 0; i < u.size(); i++)   line[k++] = u[i];
    for (size_t i = 0; i < cs.size(); i++)  line[k++] = cs[i];
    for (size_t i = 0; i < m.size(); i++)   line[k++] = m[i];
    for (size_t i = 0; i < sds.size(); i++) line[k++] = sds[i];
}

} // namespace showcase
