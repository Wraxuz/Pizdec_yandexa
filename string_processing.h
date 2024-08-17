#pragma once
#include <string>
#include <vector>
#include <set>
#include <utility>

using std::string;
using std::vector;
string ReadLine();

int ReadLineWithNumber();

vector<string> SplitIntoWords(const string& text);

template <typename StringContainer>
std::set<string> MakeUniqueNonEmptyStrings(const StringContainer& strings) {
    std::set<string> non_empty_strings;
    for (const string& str : strings) {
        if (!str.empty()) {
            non_empty_strings.insert(str);
        }
    }
    return non_empty_strings;
}