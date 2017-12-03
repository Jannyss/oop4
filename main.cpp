#include <thread>
#include <iostream>
#include <string>
#include <fstream>
#include "Factor.h"
#include "ThreadWorker.h"

using namespace std;


int main()
{
    string comm="go";
    ThreadWorker worker("input.txt", "output.txt");
    //worker.OpenFiles("input.txt", "output.txt");
    //thread t(ThreadWorker::Calculate, ref(worker));
    while (worker.running) {
        cin >> comm;
        if (comm == "exit") {
            worker.ChangeState(comm);
            worker.running = false;
        }
    }
    worker.join();
}
