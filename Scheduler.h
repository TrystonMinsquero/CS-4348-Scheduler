//
// Created by Tryston Minsquero on 10/18/2021.
//

#ifndef CS_4348_SCHEDULER_H
#define CS_4348_SCHEDULER_H
#include <vector>
#include <queue>
#include "Process.h"

using namespace std;

class Scheduler {
public:
    Scheduler(const vector<Process> &processes);

    //First Come First Serve
    void FCFS();

    //Round Robin
    void roundRobin(int q);

    //Shortest Remaining Time
    void SRT();

    //Highest Ratio Response Next
    void HRRN();

private:
    std::vector<Process> processes;

    //Variables for algorithms during scheduling
    int time;
    Process* activeProcess;
    vector<Process> readyQueue;
    std::vector<Process> processesCompleted;
    std::vector<std::vector<char>> displayGraph;

    //resets all variables for a new algorithm to schedule
    void reset();

    //add process to queue if current time equals arrival time
    //returns true if process was added, otherwise returns false
    bool onBoardNewProcesses();

    //sets the current active process to the first process in the queue
    //and also sets response time if needed
    void setActiveProcess();

    //blocks the diskIO by idling the scheduler (by one second in given case)
    //if the active process is set to block diskIO at that current time in execution
    //returns true if blocked, otherwise false
    bool blockDiskIO();

    //increments time of active process and waits all other processes
    void incrementTime();

    //marks the current active process as done, and removes it from the queue when needed
    //returns true when marks and removes, otherwise returns false
    bool serviceProcess();

    //prints the graph and performance output
    void printOutput(const string& algoName);

    //sorts the current ready queue by greatest response ratio
    void sortByGreatestRatio();

    //sorts the current ready queue by shortest time remaining
    void sortReadyQueueBySRT();



};
#endif //CS_4348_SCHEDULER_H
