#pragma once
#include "document.h"
#include "search_server.h"
#include <stack>

using std::deque;

class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server);
    template <typename DocumentPredicate>
    vector<Document> AddFindRequest(const string& raw_query, DocumentPredicate document_predicate) {
        mins += 1;
        if (mins > min_in_day_){
            if (requests_.front().isempty){
                cnt_empty_ -= 1;
            }
        }
        vector<Document> find_result = search_server_.FindTopDocuments(raw_query, document_predicate);
        bool count_reqs = find_result.empty();
        if (count_reqs){
            cnt_empty_ += 1;
        }
        requests_.push_back({raw_query, count_reqs});
        return find_result;
    }
    vector<Document> AddFindRequest(const string& raw_query, DocumentStatus status);
    vector<Document> AddFindRequest(const string& raw_query);
    int GetNoResultRequests() const;
private:
    struct QueryResult {
        string request;
        bool isempty;
    };
    deque<QueryResult> requests_;
    const static int min_in_day_ = 1440;
    int mins = 0;
    int cnt_empty_ = 0;
    const SearchServer& search_server_;
};