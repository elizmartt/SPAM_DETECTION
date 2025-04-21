#include "LogisticRegression.h"
#include <cmath>

void LogisticRegression::fit(const std::vector<std::map<std::string, double>>& X, const std::vector<int>& y) {
    weights.clear();
    for (const auto& doc : X[0]) weights[doc.first] = 0.0;
    bias = 0.0;

    double learning_rate = 0.01;
    int epochs = 100;

    for (int epoch = 0; epoch < epochs; ++epoch) {
        for (size_t i = 0; i < X.size(); ++i) {
            double z = bias;
            for (const auto& pair : X[i])
                z += weights[pair.first] * pair.second;

            double prediction = sigmoid(z);
            double error = y[i] - prediction;

            bias += learning_rate * error;
            for (const auto& pair : X[i])
                weights[pair.first] += learning_rate * error * pair.second;
        }
    }
}

std::vector<int> LogisticRegression::predict(const std::vector<std::map<std::string, double>>& X) {
    std::vector<int> predictions;
    for (const auto& doc : X) {
        double z = bias;
        for (const auto& pair : doc)
            z += weights[pair.first] * pair.second;
        predictions.push_back(sigmoid(z) >= 0.5 ? 1 : 0);
    }
    return predictions;
}

double LogisticRegression::sigmoid(double z) {
    return 1.0 / (1.0 + std::exp(-z));
}
