#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cstring>

#include "Factor.h"

using namespace std;

Factorization::Factorization() {}

Factorization::~Factorization() {}

uint64_t Factorization::PollandAlgorithm(uint64_t number) {
    if (number == 1) return number;
    if (number % 2 == 0) return 2;
    uint64_t x = (rand() %(number-2))+2;
    uint64_t y = x;
    uint64_t c = (rand() %(number-1))+1;
    uint64_t d = 1;
    while (d == 1){
        x = (ModularPow(x, 2, number) + c + number)%number;
        y = (ModularPow(y, 2, number) + c + number)%number;
        y = (ModularPow(y, 2, number) + c + number)%number;

        d = GCD(abs(x-y), number);
        if (d == number) return PollandAlgorithm(number);
    }
    return d;
}

uint64_t Factorization::ModularPow(uint64_t base, int exponent, uint64_t modulus)
{
    uint64_t result = 1;
    while (exponent > 0)
    {
        if (exponent & 1){
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}


void Factorization::CalculateFactorization(uint64_t number) {
    uint64_t pol = PollandAlgorithm(number);
    uint64_t newNumber = number / pol;
    if ((IsSimple(pol)) && (pol != 1)) multipliers.push_back(pol);
    else {
        CalculateFactorization(pol);
    }
    if (!IsSimple(newNumber)) {
        CalculateFactorization(newNumber);
    }
    else {
        if (newNumber != 1) multipliers.push_back(newNumber);
    }
}


bool Factorization::IsSimple(uint64_t number) {
    for (auto i = 2; i <= number / 2; i++) {
        if ((number % i) == 0) return false;
    }
    return true;
}


uint64_t Factorization::GCD(uint64_t num1, uint64_t num2) {
    while (num2 != 0) {
        uint64_t temp = num1 % num2;
        num1 = num2;
        num2 = temp;
    }
    return num1;
}


void Factorization::ShowFactor() {
    sort(multipliers.begin(), multipliers.end());
    for (int i = 0; i < multipliers.size(); i++) cout << multipliers[i] << endl;
}


string Factorization::GetFactorizationString(uint64_t number) {
    CleaningFactor();
    CalculateFactorization(number);
    SortFactor();
    string factor = "";
    for (auto i: multipliers) {
        factor.append(to_string(i));
        factor.append(" * ");
    }
    factor = factor.substr(0, factor.length() - 3);
//    if (CalculateNumber(factor) == number)
    return factor;
//    else
//        return "Can't decompose";
}


uint64_t Factorization::CalculateNumber(string factor) {
    uint64_t number = 1;
    size_t pos = factor.find(' ');
    while (pos != -1) {
        string str = factor.substr(0, pos);
        if (str != "*") {
                uint64_t newnum = stoul(str, nullptr, 0);
                number *= newnum;
        }
        factor.erase(factor.begin(), factor.begin() + pos+1);
        pos = factor.find(' ');
    }
    number *= stoul(factor, nullptr, 0);
    return number;
}


uint64_t Factorization::CalculateNumber(vector<uint64_t> factor) {
    uint64_t number = 1;
    for (auto i: factor) number *= i;
    return number;
}


uint64_t Factorization::Test() {
    return CalculateNumber(multipliers);
}
