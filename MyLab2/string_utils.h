#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <algorithm>
#include <cctype>

// Возвращает копию строки в нижнем регистре
inline std::string toLowerCopy(const std::string& s) {
    std::string out = s;
    std::transform(out.begin(), out.end(), out.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return out;
}

// Сравнение без учёта регистра (равно)
inline bool iequals(const std::string& a, const std::string& b) {
    return toLowerCopy(a) == toLowerCopy(b);
}

// Лексикографическое сравнение без учёта регистра: возвращает -1, 0 или 1
inline int icompare(const std::string& a, const std::string& b) {
    std::string A = toLowerCopy(a);
    std::string B = toLowerCopy(b);
    if (A < B) return -1;
    if (A > B) return 1;
    return 0;
}

#endif // STRING_UTILS_H
