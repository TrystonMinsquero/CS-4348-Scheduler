//
// Created by Tryston Minsquero on 10/28/2021.
//

#ifndef CS_4348_PROCESS_H
#define CS_4348_PROCESS_H
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <random>

using namespace std;

struct Process {
    //Working
    int w; //time waiting
    int e; //time spent executing;
    int diskIOBlockTime;
    int diskIOTimeBlocked;

    //Given
    char id;
    int arrivalTime;
    int serviceTime;
    int diskIOPeriod;
    int diskIOInterval;
    int diskIOTimeTotal;
    int diskIOActivity;

    //Performance;
    int finishTime;
    int responseTime;
    int turnAroundTime;
    double ratio;

    Process(char id, int arrivalTime, int serviceTime, int diskIOTimeTotal, int diskIOActivity = -1) {
        this->id = id;
        this->arrivalTime = arrivalTime;
        this->serviceTime = serviceTime;
        this->diskIOTimeTotal = diskIOTimeTotal;

        if(diskIOTimeTotal > 0) {
            this->diskIOActivity = diskIOActivity < 0 ? diskIOTimeTotal : diskIOActivity;
            diskIOPeriod = this->diskIOActivity == 0 ? 0 : diskIOTimeTotal / this->diskIOActivity;
            diskIOInterval = serviceTime / (this->diskIOActivity + diskIOPeriod);
        }
        else {
            this->diskIOActivity = 0;
            diskIOPeriod = 0;
            diskIOInterval = 0;
        }
        
        w = 0;
        e = 0;
        diskIOTimeBlocked = 0;
        diskIOBlockTime = diskIOTimeTotal <= 0 ? -1 : e + diskIOInterval;
    }
    
    void service(int timeCompleted) {
        finishTime = timeCompleted;
        turnAroundTime = finishTime - arrivalTime;
        ratio = (double)turnAroundTime / serviceTime;
    }

    bool static compareByID(const Process &a, const Process &b)
    {
        return a.id < b.id;
    }

    //compare by shortest time remaining
    bool static compareBySRT(const Process&a, const Process &b)
    {
        return a.serviceTime - a.e < b.serviceTime - b.e;
    }

    bool static compareByRatio(const Process&a, const Process &b)
    {
        double ratioA = (double)(a.w + a.serviceTime) / a.serviceTime;
        double ratioB = (double)(b.w + b.serviceTime) / b.serviceTime;
        return ratioA > ratioB;
    }

};

vector<Process> static generateProcesses(int n, int totalServiceTime) {
    vector<Process> processes;
    vector<int> serviceTimes (n);
    srand(time(NULL));
    int serviceTimeAccumulated = 0;
    int i = 0;
    while(serviceTimeAccumulated < totalServiceTime) {
        if(i >= n)
            i = 0;
        int serviceTimeRemaining = totalServiceTime - serviceTimeAccumulated;

        int serviceTime = serviceTimeRemaining == 1 ? 1 : rand() % 2 + 1;
        serviceTimes[i] += serviceTime;
        serviceTimeAccumulated += serviceTime;
        i++;
    }

    for(int i = 0; i < n; i++) {
        processes.push_back(Process((char)((int)'A' + i), i * 2, serviceTimes[i], 0));
    }
    return processes;
}

void static printProcessesPerformance(std::vector<Process> &completedProcesses) {

    sort(completedProcesses.begin(), completedProcesses.end(), Process::compareByID);

    int w = 5;
    cout << "  Process Performance:" << endl;
    cout << setprecision(3) << left;
    cout << setw(w) << "Process id" << " | ";
    cout << setw(w) << "Finish Time" << " | ";
    cout << setw(w) << "Response Time" << " | ";
    cout << setw(w) << "Turnaround Time" << " | ";
    cout << setw(w) << "Ta/Ts Ratio" << " | ";
    cout << endl;
    cout << setfill('-') << setw(w * 15) << "" << endl;
    cout << right << setfill(' ');
    w = 6;
    int responseTimeTotal = 0;
    int turnaroundTimeTotal = 0;
    double ratioTotal = 0;
    int total = 0;
    for (Process process : completedProcesses) {
        cout << setw(w) << process.id << setw(w) << "|";
        cout << setw(w + 1) << process.finishTime << setw(w + 1) << "|";
        cout << setw(w + 2) << process.responseTime << setw(w + 2) << "|";
        cout << setw(w + 3) << process.turnAroundTime << setw(w + 3) << "|";
        cout << setw(w + 1) << process.ratio << setw(w + 1) << "|";
        responseTimeTotal += process.responseTime;
        turnaroundTimeTotal += process.turnAroundTime;
        ratioTotal += process.ratio;
        total++;
        cout << endl;
    }
    cout << setfill('-') << setw((w - 1) * 15) << "" << endl;
    cout << right << setfill(' ');
    cout << setw(w + 1) << "Mean" << setw(w - 1) << "|";
    cout << setw(w + 1) << " " << setw(w + 1) << "|";
    cout << setw(w + 2) << (double) responseTimeTotal / total << setw(w + 2) << "|";
    cout << setw(w + 3) << (double) turnaroundTimeTotal / total << setw(w + 3) << "|";
    cout << setw(w + 1) << (double) ratioTotal / total << setw(w + 1) << "|";
    cout << endl << "Throughput: " << (double)turnaroundTimeTotal / completedProcesses.size();
    cout << endl << endl;
}

void static printProcesses(const vector<Process>& processes) {
    
    int w = 5;
    cout << "Given processes: " << endl;
    cout << setprecision(2) << left;
    cout << setw(w) << " Process id " << " | ";
    cout << setw(w) << "Arrival Time" << " | ";
    cout << setw(w) << "Service Time" << " | ";
    cout << setw(w) << "Disk IO Time (Total)" << " | ";
    cout << setw(w) << "Disk IO Activity" << " | ";
    cout << endl;
    cout << setfill('-') << setw(w * 17) << "" << endl;
    cout << right << setfill(' ');
    w = 7;
    for(Process process : processes){
        cout << setw(w) << process.id << setw(w) << "|";
        cout << setw(w + 1) << process.arrivalTime << setw(w) << "|";
        cout << setw(w + 1) << process.serviceTime << setw(w) << "|";
        cout << setw(w + 5) << process.diskIOTimeTotal << setw(w + 4) << "|";
        cout << setw(w + 3) << process.diskIOActivity << setw(w + 2) << "|";
        cout << endl;
    }
    cout << endl;
}

vector<vector<char>> static getDisplayGraph(const vector<Process>& processes) {
    int expectedFinishTime = 0;
    for (Process process : processes)
        expectedFinishTime += process.serviceTime + process.diskIOTimeTotal;
    vector<vector<char>> displayGraph(processes.size(), vector<char>(expectedFinishTime + 1, ' '));
    for (int i = 0; i < processes.size(); i++) {
        displayGraph[i][0] = (processes[i].id);
    }
    return displayGraph;
}

void static printDisplayGraph(const vector<vector<char>> &matrix) {
    int const maxTimeWidth = 39;
    cout << "  Graph" << endl;

    int time = 0;
    int graphNum = 0;
    while(time < matrix[0].size()) {
        graphNum++;
        //Print time stamps
        cout << "   ";
        while(time < maxTimeWidth * graphNum && time < matrix[0].size()) {
            cout << setw(3) << time;
            time++;
        }
        cout << endl;
        //print matrix from
        for (const vector<char> &row : matrix) {
            for (int i = maxTimeWidth * (graphNum - 1); i <= time; i++) {
                if(i == maxTimeWidth * (graphNum - 1))
                    cout << setw(3) << row[0];
                else if(i < row.size())
                    cout << setw(3) << row[i];
            }
            cout << endl;
        }
    }
}


#endif //CS_4348_PROCESS_H
