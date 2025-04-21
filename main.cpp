#include <iostream>
#include "TfidfVectorizer.h"
#include "LogisticRegression.h"
#include "DataLoader.h"

int main() {
    std::string filename = "C:/Users/User/CLionProjects/untitled/spam_detection/mail_data.csv";
    auto data = loadData(filename);
    std::vector<std::string> messages = data.first;
    std::vector<int> categories = data.second;

    if (messages.empty()) return 1;

    size_t split_point = messages.size() * 0.8;
    std::vector<std::string> train_messages(messages.begin(), messages.begin() + split_point);
    std::vector<std::string> test_messages(messages.begin() + split_point, messages.end());
    std::vector<int> train_categories(categories.begin(), categories.begin() + split_point);
    std::vector<int> test_categories(categories.begin() + split_point, categories.end());

    TfidfVectorizer vectorizer;
    vectorizer.fit(train_messages);
    auto train_vectors = vectorizer.transform(train_messages);
    auto test_vectors = vectorizer.transform(test_messages);

    LogisticRegression model;
    model.fit(train_vectors, train_categories);
    auto predictions = model.predict(test_vectors);

    int correct = 0;
    for (size_t i = 0; i < predictions.size(); ++i)
        if (predictions[i] == test_categories[i]) correct++;

    std::cout << "Accuracy: " << static_cast<double>(correct) / predictions.size() << std::endl;

    std::vector<std::string> new_message = {"give me your contact info"};
    auto new_message_vector = vectorizer.transform(new_message);
    auto new_prediction = model.predict(new_message_vector);
    std::cout << "Prediction for new message: " << new_prediction[0] << std::endl;

    return 0;
}
