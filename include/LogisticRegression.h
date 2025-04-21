#ifndef LOGISTICREGRESSION_H
#define LOGISTICREGRESSION_H

#include <map>
#include <string>
#include <vector>

class LogisticRegression {
public:
    void fit(const std::vector<std::map<std::string, double>>& X, const std::vector<int>& y);
    std::vector<int> predict(const std::vector<std::map<std::string, double>>& X);

private:
    std::map<std::string, double> weights;
    double bias;
    double sigmoid(double z);
};

#endif
