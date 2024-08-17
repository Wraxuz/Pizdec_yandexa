#pragma once
#include <utility>
#include <iostream>

using std::ostream;
using namespace std::literals;

const int MAX_RESULT_DOCUMENT_COUNT = 5;

struct Document {
    Document();
    Document(int id, double relevance, int rating);
    int id = 0;
    double relevance = 0.0;
    int rating = 0;
};

enum class DocumentStatus {
    ACTUAL,
    IRRELEVANT,
    BANNED,
    REMOVED,
};

ostream& operator<<(ostream& out, const Document& document);