#ifndef TFIDFVECTORIZER_H
#define TFIDFVECTORIZER_H

#include <string>
#include <vector>
#include <map>

class TfidfVectorizer {
public:
    void fit(const std::vector<std::string>& texts);
    std::vector<std::map<std::string, double>> transform(const std::vector<std::string>& texts);

private:
    std::map<size_t, std::map<std::string, int>> term_frequencies;
    std::map<std::string, int> document_frequencies;
    size_t document_count;
};

#endif
