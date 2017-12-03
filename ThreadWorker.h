#ifndef THREADWORKER_H_INCLUDED
#define THREADWORKER_H_INCLUDED
#pragma once
#include <fstream>
#include <string>
#include <condition_variable>
#include <thread>

class ThreadWorker {

public:

    ThreadWorker(std::string inFilename, std::string outFilename);

    ~ThreadWorker();

    void OpenFiles(std::string inFilename, std::string outFilename) ;

    void Calculate();

    void ChangeState( std::string command);

    bool running = false;

    void join();

private:

    std::ifstream inputFile;

    std::ofstream outputFile;

    std::thread t;

    std::string state="go";

    std::condition_variable checkVar;

};

#endif // THREADWORKER_H_INCLUDED
