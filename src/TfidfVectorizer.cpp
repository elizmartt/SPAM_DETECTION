#include "TfidfVectorizer.h"
#include <cctype>
#include <cmath>

void TfidfVectorizer::fit(const std::vector<std::string>& texts) {
    term_frequencies.clear();
    document_frequencies.clear();
    document_count = texts.size();

    for (size_t doc_id = 0; doc_id < texts.size(); ++doc_id) {
        std::map<std::string, int> term_freq;
        std::string text = texts[doc_id], word;

        for (char c : text) {
            if (std::isalpha(c)) word += std::tolower(c);
            else if (!word.empty()) {
                term_freq[word]++;
                word.clear();
            }
        }
        if (!word.empty()) term_freq[word]++;

        for (const auto& pair : term_freq) {
            term_frequencies[doc_id][pair.first] = pair.second;
            document_frequencies[pair.first]++;
        }
    }
}

std::vector<std::map<std::string, double>> TfidfVectorizer::transform(const std::vector<std::string>& texts) {
    std::vector<std::map<std::string, double>> tfidf_vectors;

    for (const auto& text : texts) {
        std::map<std::string, int> term_freq;
        std::map<std::string, double> tfidf_vector;
        std::string word;

        for (char c : text) {
            if (std::isalpha(c)) word += std::tolower(c);
            else if (!word.empty()) {
                term_freq[word]++;
                word.clear();
            }
        }
        if (!word.empty()) term_freq[word]++;

        for (const auto& pair : term_freq) {
            double tf = static_cast<double>(pair.second) / term_freq.size();
            double idf = std::log(static_cast<double>(document_count) / (document_frequencies[pair.first] + 1));
            tfidf_vector[pair.first] = tf * idf;
        }

        tfidf_vectors.push_back(tfidf_vector);
    }

    return tfidf_vectors;
}
