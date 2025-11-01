#include <vector>
#include <string>

namespace showcase {

inline void sortMajors(std::vector<std::string>& line) {
    std::vector<std::string> u;
    std::vector<std::string> cs;
    std::vector<std::string> m;
    std::vector<std::string> sds;

    for (size_t i = 0; i < line.size(); i++) {
        if (line[i] == "U") {
            u.push_back(line[i]);
        } else if (line[i] == "CS") {
            cs.push_back(line[i]);
        } else if (line[i] == "M") {
            m.push_back(line[i]);
        } else if (line[i] == "SDS") {
            sds.push_back(line[i]);
        }
    }

    size_t k = 0;
    for (size_t i = 0; i < u.size(); i++)   line[k++] = u[i];
    for (size_t i = 0; i < cs.size(); i++)  line[k++] = cs[i];
    for (size_t i = 0; i < m.size(); i++)   line[k++] = m[i];
    for (size_t i = 0; i < sds.size(); i++) line[k++] = sds[i];
    }
}
