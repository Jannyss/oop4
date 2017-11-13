
#include <iostream>
#include <string>
#include <fstream>
#include "Factor.h"

using namespace std;

int main()
{
    string filename;
    filename = "input.txt";
    ifstream inputfile(filename);
    ofstream outputfile;
    outputfile.open("output.txt", ios_base::out);
    while (!inputfile.eof()) {
        uint64_t newNum;
        inputfile >> newNum;
        Factorization factor;
        outputfile << factor.GetFactorizationString(newNum);
        outputfile << endl;
    }
}
