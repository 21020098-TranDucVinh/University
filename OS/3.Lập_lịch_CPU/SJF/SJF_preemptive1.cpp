#include <iostream>
#include <queue>
#include <string>
#include <iomanip>
using namespace std;
const int MOD = 1e9 + 7;

using ll = long long;

class Process
{
public:
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turn_around_time;
    int current_time;
    int ready_time;
    bool first_time = true;
    Process()
    {
    }
    Process(int process_id, int arrival_time, int burst_time, int waiting_time = 0, int turn_around_time = 0)
    {
        this->process_id = process_id;
        this->arrival_time = arrival_time;
        this->burst_time = burst_time;
        this->waiting_time = waiting_time;
        this->turn_around_time = turn_around_time;
        this->current_time = arrival_time;
        this->ready_time = arrival_time;
    }

    friend bool operator==(Process p1, Process p2)
    {
        return p1.process_id == p2.process_id;
    }
    friend bool operator!=(Process p1, Process p2)
    {
        return p1.process_id != p2.process_id;
    }
};

struct CompareArrivalTime
{
    bool operator()(const Process &p1, const Process &p2)
    {
        return p1.arrival_time > p2.arrival_time;
    }
};

struct CompareBurstTime
{
    bool operator()(const Process &p1, const Process &p2)
    {
        return p1.burst_time > p2.burst_time;
    }
};

struct CompareId
{
    bool operator()(const Process &p1, const Process &p2)
    {
        return p1.process_id > p2.process_id;
    }
};

class Scheduler
{
public:
    priority_queue<Process, vector<Process>, CompareArrivalTime> processes;
    priority_queue<Process, vector<Process>, CompareBurstTime> process_queue;
    int time_elapsed;
    Process current;

    Scheduler()
    {
        time_elapsed = 0;
    }

    void addProcess(Process process)
    {
        processes.push(process);
    }

    void schedule()
    {
        priority_queue<Process, vector<Process>, CompareId> finish_queue;
        while (processes.size() != 0 || process_queue.size() != 0)
        {
            while (processes.size() != 0 && processes.top().arrival_time <= time_elapsed)
            {
                Process process = processes.top();
                processes.pop();
                process_queue.push(process);
            }
            if (process_queue.size() != 0)
            {
                Process process = process_queue.top();
                process_queue.pop();
                if (process.first_time == true || current != process)
                {
                    if (process.first_time)
                    {
                        process.ready_time = time_elapsed - process.arrival_time;
                        process.first_time = false;
                    }
                    current = process;
                    cout << "Process " << process.process_id << " started at time " << time_elapsed << endl;
                }
                if (process.burst_time <= 1)
                {
                    process.waiting_time += time_elapsed - process.current_time;
                    time_elapsed += process.burst_time;
                    process.turn_around_time += time_elapsed - process.arrival_time;
                    finish_queue.push(process);
                    cout << "Process " << process.process_id << " finished at time " << time_elapsed << endl;
                }
                else
                {
                    process.burst_time--;
                    process.current_time++;
                    time_elapsed++;
                    process_queue.push(process);
                }
            }
            else
            {
                time_elapsed += 1;
                cout << "Idle at time " << time_elapsed << endl;
            }
        }
        cout << left << setw(20) << " " << left << setw(20) << "ready time" << left << setw(20) << "waiting time" << left << setw(20) << "turn around time" << endl;
        while (finish_queue.size())
        {
            Process process = finish_queue.top();
            finish_queue.pop();
            string process_id = "P" + to_string(process.process_id);
            cout << left << setw(20) << process_id << setw(20) << process.ready_time << left << setw(20) << process.waiting_time << left << setw(20) << process.turn_around_time << endl;
        }
    }
};

int main()
{
#ifndef ONLINE_JUDGE
#define ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    Scheduler schedule;
    schedule.addProcess(Process(1, 0, 3));
    schedule.addProcess(Process(2, 4, 8));
    schedule.addProcess(Process(3, 5, 5));
    schedule.addProcess(Process(4, 6, 2));
    schedule.schedule();

    return 0;
}