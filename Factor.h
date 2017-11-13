#ifndef FACTOR_H_INCLUDED
#define FACTOR_H_INCLUDED

#include <vector>
#include <string>
#include <algorithm>

class Factorization {

public:

    Factorization();

    ~Factorization();

    void CalculateFactorization(uint64_t number);

    uint64_t CalculateNumber(std::vector<uint64_t> factor);

    uint64_t CalculateNumber(std::string factor);

    std::string GetFactorizationString(uint64_t number);

    bool IsSimple(uint64_t number);

    void ShowFactor();

    uint64_t Test();

private:

    mutable std::vector <uint64_t> multipliers;

    uint64_t PollandAlgorithm(uint64_t number);

    uint64_t GCD(uint64_t num1, uint64_t num2);

    void CleaningFactor() {
        multipliers.clear();
    }

    void SortFactor() {
        sort(multipliers.begin(), multipliers.end());
    }

};

#endif // FACTOR_H_INCLUDED
