# CS-4348-Scheduler
**About:** A program to simulate different short term scheduling algortithms

The scheduler is a class that holds a list of processes to be ran. And different methods per algorithm

### Analyisis for each algorithm:

#### First Come First Serve (FCFS)
- **Possibilty of Starvation:**
  This can get close when the first processes put in the queue processes are very long, however, the processes will be worked on eventually so there is no possibility. 
  
- **Effect of context switching overhead on throughput:**
  For no disk IO blocking there is no context switching and will have negative impact on throughput the longer the beginning processes. However, the implementation of disk IO 
  blocking will increase the throughput when there is disk IO blocks. Either way throughtput is not emphasized in this algorithm.
  
- **Fairness:**
  The algorithm is mostly fair, treats short processes and IO bounds processes poorly.


#### Round Robin
- **Possibilty of Starvation:**
  No possibility of starvation because the process will be worked very soon with a low quantum.
  
- **Effect of context switching overhead on throughput:**
  The throughput can be low if the time slice quantum is too low. Also, IO bound processes are not effected very much.

- **Fairness:**
  very fair, every process is treated the same.


#### Shortest Remaining Time (SRT)
- **Possibilty of Starvation:**
  possible for long processes and shorter processes keep being queued.
  
- **Effect of context switching overhead on throughput:**
  throughput is very high because the algorithm tries to finish as many processes as it can by processes the closest one to complete.

- **Fairness:**
  Not fair to long processes, but little effect on IO bound processes.


#### Highest Response Ratio Next (HRRN)
- **Possibilty of Starvation:**
  No possibility of starvation because selection function takes wait time into conisideration.
  
- **Effect of context switching overhead on throughput:**
  has a high throughput because it also tries to take the service time into consideration by doing the shorter processes

- **Fairness:**
  It's a good balance because it prevents starvation while also priortizing shorter process to increase throughput.

