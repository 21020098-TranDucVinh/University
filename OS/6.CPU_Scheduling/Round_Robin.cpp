#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Process structure
struct Process
{
    int pid;             // process ID
    int arrival_time;    // thời gian vào
    int burst_time;      // thời gian chạy
    int end_time;        // thời gian hoàn thành
    int turnaround_time; // tổng thời gian
    int waiting_time;    // thời gian chờ
    int remaining_time;
};

bool compare_arrivalTime(Process p1, Process p2)
{
    return p1.arrival_time < p2.arrival_time;
}

int main()
{
    int n;
    int quantum;
    vector<Process> processes;

    // Nhập số tiến trình
    cout << "Enter the number of processes and quantum: ";
    cin >> n >> quantum;

    // Nhập thông tin của các tiến trình
    for (int i = 0; i < n; i++)
    {
        Process p;
        p.pid = i + 1;
        cout << "Enter the arrival time and burst time for process " << p.pid << ": ";
        cin >> p.arrival_time >> p.burst_time;
        p.remaining_time = p.burst_time;
        processes.push_back(p);
    }

    // Sắp xếp tiến trình theo điều kiện
    sort(processes.begin(), processes.end(), compare_arrivalTime);

    // Tính toán thời gian theo đề
    int current_time = processes[0].arrival_time;
    int num_completed_processes = 0;

    while (num_completed_processes < n)
    {
        int change = 0;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0)
            {
                if (processes[i].remaining_time <= quantum)
                {
                    num_completed_processes++;
                    current_time += processes[i].remaining_time;
                    processes[i].end_time = current_time;
                    processes[i].turnaround_time = processes[i].end_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

                    processes[i].remaining_time = 0;
                    cout << "Finish time quantum, P" << i << " ,t=" << current_time << endl;
                }
                else
                {
                    current_time += quantum;
                    processes[i].remaining_time -= quantum;
                    cout << "Finish time quantum, P" << i << " ,t=" << current_time << endl;
                }
                change++;
            }
        }
        if (change == 0)
        {
            cout << "CPU idle ,t=" << current_time << endl;
            current_time++;
        }
    }

    // Tính trung bình thời gian chờ và thời gian tổng
    double avg_turnaround_time = 0.0, avg_waiting_time = 0.0;
    for (int i = 0; i < n; i++)
    {
        avg_turnaround_time += processes[i].turnaround_time;
        avg_waiting_time += processes[i].waiting_time;
    }
    avg_turnaround_time /= n;
    avg_waiting_time /= n;

    // Đưa ra kết quả
    cout << "PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++)
    {
        cout << processes[i].pid << "\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" << processes[i].end_time << "\t\t" << processes[i].turnaround_time << "\t\t" << processes[i].waiting_time << "\n";
    }
    cout << "Average turnaround time: " << avg_turnaround_time << "\n";
    cout << "Average waiting time: " << avg_waiting_time << "\n";

    return 0;
}