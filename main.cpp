#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
#include <random>

// TF-IDF Vectorizer (simplified)
class TfidfVectorizer {
public:
    void fit(const std::vector<std::string>& texts) {
        term_frequencies.clear();
        document_frequencies.clear();
        document_count = texts.size();

        for (size_t doc_id = 0; doc_id < texts.size(); ++doc_id) {
            std::map<std::string, int> term_freq;
            std::string text = texts[doc_id];
            std::string word;
            for (char c : text) {
                if (std::isalpha(c)) {
                    word += std::tolower(c);
                } else if (!word.empty()) {
                    term_freq[word]++;
                    word.clear();
                }
            }
            if (!word.empty()) {
                term_freq[word]++;
            }

            for (const auto& pair : term_freq) {
                term_frequencies[doc_id][pair.first] = pair.second;
                document_frequencies[pair.first]++;
            }
        }
    }

    std::vector<std::map<std::string, double>> transform(const std::vector<std::string>& texts) {
        std::vector<std::map<std::string, double>> tfidf_vectors;
        for (size_t doc_id = 0; doc_id < texts.size(); ++doc_id) {
            std::map<std::string, double> tfidf_vector;
            std::string text = texts[doc_id];
            std::map<std::string, int> term_freq;
            std::string word;
            for (char c : text) {
                if (std::isalpha(c)) {
                    word += std::tolower(c);
                } else if (!word.empty()) {
                    term_freq[word]++;
                    word.clear();
                }
            }
            if (!word.empty()) {
                term_freq[word]++;
            }

            for (const auto& pair : term_freq) {
                std::string term = pair.first;
                double tf = static_cast<double>(pair.second) / term_freq.size();
                double idf = std::log(static_cast<double>(document_count) / (document_frequencies[term] + 1));
                tfidf_vector[term] = tf * idf;
            }
            tfidf_vectors.push_back(tfidf_vector);
        }
        return tfidf_vectors;
    }

private:
    std::map<size_t, std::map<std::string, int>> term_frequencies;
    std::map<std::string, int> document_frequencies;
    size_t document_count;
};

// Logistic Regression (simplified)
class LogisticRegression {
public:
    void fit(const std::vector<std::map<std::string, double>>& X, const std::vector<int>& y) {
        weights.clear();
        for (const auto& doc : X[0]) {
            weights[doc.first] = 0.0;
        }
        bias = 0.0;

        double learning_rate = 0.01;
        int epochs = 100;

        for (int epoch = 0; epoch < epochs; ++epoch) {
            for (size_t i = 0; i < X.size(); ++i) {
                double z = bias;
                for (const auto& pair : X[i]) {
                    z += weights[pair.first] * pair.second;
                }
                double prediction = sigmoid(z);
                int actual = y[i];
                double error = actual - prediction;

                bias += learning_rate * error;
                for (const auto& pair : X[i]) {
                    weights[pair.first] += learning_rate * error * pair.second;
                }
            }
        }
    }

    std::vector<int> predict(const std::vector<std::map<std::string, double>>& X) {
        std::vector<int> predictions;
        for (const auto& doc : X) {
            double z = bias;
            for (const auto& pair : doc) {
                z += weights[pair.first] * pair.second;
            }
            predictions.push_back(sigmoid(z) >= 0.5 ? 1 : 0);
        }
        return predictions;
    }

private:
    std::map<std::string, double> weights;
    double bias;

    double sigmoid(double z) {
        return 1.0 / (1.0 + std::exp(-z));
    }
};

std::pair<std::vector<std::string>, std::vector<int>> loadData(const std::string& filename) {
    std::vector<std::string> messages;
    std::vector<int> categories;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return {messages, categories};
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string category, message;

        if (std::getline(ss, category, ',') && std::getline(ss, message)) {
            if (!message.empty() && message[0] == '"') {
                message = message.substr(1, message.length() - 2);
            }
            messages.push_back(message);
            categories.push_back(category == "spam" ? 1 : 0);
        }
    }

    file.close();
    return {messages, categories};
}

int main() {
    std::string filename = "C:/Users/Eliza/CLionProjects/SPAM_DETECTION/mail_data.csv"; // Replace with your file path
    auto data = loadData(filename);
    std::vector<std::string> messages = data.first;
    std::vector<int> categories = data.second;

    if (messages.empty()) {
        return 1;
    }

    size_t split_point = messages.size() * 0.8;
    std::vector<std::string> train_messages(messages.begin(), messages.begin() + split_point);
    std::vector<std::string> test_messages(messages.begin() + split_point, messages.end());
    std::vector<int> train_categories(categories.begin(), categories.begin() + split_point);
    std::vector<int> test_categories(categories.begin() + split_point, categories.end());

    TfidfVectorizer vectorizer;
    vectorizer.fit(train_messages);
    std::vector<std::map<std::string, double>> train_vectors = vectorizer.transform(train_messages);
    std::vector<std::map<std::string, double>> test_vectors = vectorizer.transform(test_messages);

    LogisticRegression model;
    model.fit(train_vectors, train_categories);
    std::vector<int> predictions = model.predict(test_vectors);

    int correct = 0;
    for (size_t i = 0; i < predictions.size(); ++i) {
        if (predictions[i] == test_categories[i]) {
            correct++;
        }
    }
    std::cout << "Accuracy: " << static_cast<double>(correct) / predictions.size() << std::endl;

    std::vector<std::string> new_message = {"give me your contact info"};
    std::vector<std::map<std::string, double>> new_message_vector = vectorizer.transform(new_message);
    std::vector<int> new_prediction = model.predict(new_message_vector);
    std::cout << "Prediction for new message: " << new_prediction[0] << std::endl;

    return 0;
}