//
// Created by Tryston Minsquero on 10/18/2021.
//

#include "Scheduler.h"

Scheduler::Scheduler(const vector<Process> &processes) {
    this->processes = processes;
    printProcesses(processes);
}

void Scheduler::FCFS() {
    reset();
    while (processesCompleted.size() < processes.size())
    {
        onBoardNewProcesses();
        if(!readyQueue.empty())
        {
            setActiveProcess();
            if(!blockDiskIO())
                incrementTime();
            serviceProcess();
        }
    }
    printOutput("First Come First Serve");
}

void Scheduler::roundRobin(int q) {
    reset();
    int timeSpentOnProcess = 0;
    while (processesCompleted.size() < processes.size()) {
        onBoardNewProcesses();
        if (!readyQueue.empty()) {
            //Preemptively check to see if needs to change process
            if (timeSpentOnProcess >= q && readyQueue.size() > 1) {
                readyQueue.push_back(readyQueue.front());
                readyQueue.erase(readyQueue.begin());
                timeSpentOnProcess = 0;
            }
            setActiveProcess();
            if(!blockDiskIO()){
                incrementTime();
                timeSpentOnProcess++;
            }
            else
                timeSpentOnProcess = 0;
            if (serviceProcess())
                timeSpentOnProcess = 0;
        }
    }
    printOutput( "Round Robin (" + to_string(q) + ")");
}

void Scheduler::SRT() {
    reset();

    while (processesCompleted.size() < processes.size()) {
        if(onBoardNewProcesses())
            sortReadyQueueBySRT();
        if (!readyQueue.empty()) {
            setActiveProcess();
            if(!blockDiskIO())
                incrementTime();
            serviceProcess();
        }
    }
    printOutput("Shortest Remaining Time");
}

void Scheduler::HRRN() {
    reset();
    while (processesCompleted.size() < processes.size()) {
        onBoardNewProcesses();
        if (!readyQueue.empty()) {
            setActiveProcess();
            if(!blockDiskIO())
                incrementTime();
            if(serviceProcess())
                sortByGreatestRatio();
        }
    }
    printOutput("Highest Response Ratio Next");


}
void Scheduler::reset() {
    time = 0;
    readyQueue = {}; //uses a queue instead of using w, same functionality
    activeProcess = nullptr;
    processesCompleted = {};
    displayGraph = getDisplayGraph(processes);
}

bool Scheduler::onBoardNewProcesses() {
    bool added = false;
    for(Process process : processes)
        if(process.arrivalTime == time){
            readyQueue.push_back(process);
            added = true;
        }
    return added;
}

void Scheduler::setActiveProcess() {
    activeProcess = &readyQueue.front();

    if(activeProcess->e == 0) {
        activeProcess->responseTime = time - activeProcess->arrivalTime;
    }
}

bool Scheduler::blockDiskIO() {

    if(activeProcess->diskIOBlockTime == activeProcess->e && activeProcess->diskIOTimeBlocked < activeProcess->diskIOTimeTotal)
    {
        //update active process data
        activeProcess->diskIOTimeBlocked += activeProcess->diskIOPeriod;
        activeProcess->diskIOBlockTime += activeProcess->diskIOInterval;
        //increase time
        time += activeProcess->diskIOPeriod;
        //update display graph
        for(int i = 0; i < activeProcess->diskIOPeriod; i++)    //should never iterated when period == 1
            displayGraph[activeProcess->id - (int)'A'][time + i] = '-';

        //mark other processes as waiting
        for (Process& process : readyQueue)
            if (activeProcess->id != process.id)
                process.w++;

        //move to back of queue
        readyQueue.push_back(*activeProcess);
        readyQueue.erase(readyQueue.begin());
        return true;
    }
    return false;
}

void Scheduler::incrementTime() {
    activeProcess->e++;
    time++;
    displayGraph[activeProcess->id - (int)'A'][time] = '*';

    for (Process& process : readyQueue)
        if (activeProcess->id != process.id)
            process.w++;
}

bool Scheduler::serviceProcess() {

    if(activeProcess->e < activeProcess->serviceTime)
        return false;
    activeProcess->service(time);
    processesCompleted.push_back(*activeProcess);
    readyQueue.erase(readyQueue.begin());
    activeProcess = nullptr;
    return true;
}

void Scheduler::printOutput(const string& algoName) {
    cout << algoName << " Output: " << endl;
    printDisplayGraph(displayGraph);
    printProcessesPerformance(processesCompleted);
}

void Scheduler::sortByGreatestRatio() {
    sort(readyQueue.begin(), readyQueue.end(), Process::compareByRatio);
}

void Scheduler::sortReadyQueueBySRT() {
    sort(readyQueue.begin(), readyQueue.end(), Process::compareBySRT);
}





