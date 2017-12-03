#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <chrono>
#include <condition_variable>

#include "ThreadWorker.h"
#include "Factor.h"

using namespace std;

ThreadWorker::ThreadWorker(string inFilename, string outFilename) {
    running = true;
    ThreadWorker::OpenFiles(inFilename, outFilename);
    t = thread(&ThreadWorker::Calculate, this);
}

ThreadWorker::~ThreadWorker() {}

void ThreadWorker::OpenFiles(string inFilename, string outFilename) {
    inputFile.open(inFilename);
    outputFile.open(outFilename, ios_base::out);
}

void ThreadWorker::Calculate() {
    mutex lock;
    unique_lock<mutex> locker(lock);
    //recursive_mutex _lock;
    //lock_guard<recursive_mutex> locker(_lock);
    while ((running) and (!inputFile.eof()) and (state != "exit")) {
        if (state == "exit") {
            checkVar.wait(locker);
            running = false;
            inputFile.close();
            outputFile.close();
        }
        else {
            uint64_t newNum;
            inputFile >> newNum;
            Factorization factor;
            this_thread::sleep_for(chrono::seconds(5));
            if (factor.IsSimple(newNum))
                outputFile << "It's a prime number" << endl;
            else {
                outputFile << factor.GetFactorizationString(newNum);
                outputFile << endl;
            }
        }
    }
    running = false;
}

void ThreadWorker::ChangeState(string command) {
    state = command;
}

void ThreadWorker::join() {
    if (t.joinable()) t.join();
}
