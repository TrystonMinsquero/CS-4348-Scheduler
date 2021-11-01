#include "Scheduler.h"
#include "fstream"


int main() {
    std::vector<Process> processes =
            {
                    Process('A', 0, 6, 1),   //A
                    Process('B', 2, 12, 2),  //B
                    Process('C', 4, 8, 1),   //C
                    Process('D', 6, 10, 0),  //D
                    Process('E', 8, 4, 2)    //E

            };

    std::vector<Process> processesExample =
            {
                    Process('A', 0, 3, 0),   //A
                    Process('B', 2, 6, 0),   //B
                    Process('C', 4, 4, 0),   //C
                    Process('D', 6, 5, 0),   //D
                    Process('E', 8, 2, 0)    //E
            };

    std::vector<Process> randomProcesses = generateProcesses(6, 20);
    printProcesses(processes);

    std::ofstream out("out.txt");
    std::cout.rdbuf(out.rdbuf());

    Scheduler scheduler = Scheduler(processes);
    scheduler.FCFS();
    scheduler.roundRobin(1);
    scheduler.roundRobin(4);
    scheduler.SRT();
    scheduler.HRRN();
    return 0;
}