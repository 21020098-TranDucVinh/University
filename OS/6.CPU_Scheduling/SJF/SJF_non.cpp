#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class Process {
public:
    string name;
    int arrivalTime;
    int burstTime;

    Process(string name, int arrivalTime, int burstTime) {
        this->name = name;
        this->arrivalTime = arrivalTime;
        this->burstTime = burstTime;
    }
};

bool compare_arrival(Process p1, Process p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

bool compare_burst(Process p1, Process p2) {
    return p1.burstTime < p2.burstTime;
}

class Scheduler {
public:
    vector<Process> processes;

    Scheduler(vector<Process> processes) {
        this->processes = processes;
    }

    void sjf_nonpreemptive() {
        sort(processes.begin(), processes.end(), compare_arrival);
        int n = processes.size();

        vector<int> wt(n, 0), tat(n, 0);
        int total_wt = 0, total_tat = 0;
        int current_time = processes[0].arrivalTime;

        for (int i = 0; i < n; i++) {
            if (current_time < processes[i].arrivalTime) {
                current_time = processes[i].arrivalTime;
            }
            int min_burst_time = processes[i].burstTime;
            int shortest_process_index = i;
            for (int j = i + 1; j < n && processes[j].arrivalTime <= current_time; j++) {
                if (processes[j].burstTime < min_burst_time) {
                    min_burst_time = processes[j].burstTime;
                    shortest_process_index = j;
                }
            }
            swap(processes[i], processes[shortest_process_index]);

            wt[i] = current_time - processes[i].arrivalTime;
            tat[i] = processes[i].burstTime + wt[i];
            total_wt += wt[i];
            total_tat += tat[i];
            current_time += processes[i].burstTime;
        }

        // In ra bảng thời gian chờ đợi và thời gian hoàn thành của các tiến trình
        cout << setw(10) << left << "Process" << setw(15) << left << "Arrival Time" << setw(15) << left << "Burst Time" << setw(15) << left << "Waiting Time" << setw(20) << left << "Turnaround Time" << endl;
        for (int i = 0; i < n; i++) {
            cout << setw(10) << left << processes[i].name << setw(15) << left << processes[i].arrivalTime << setw(15) << left << processes[i].burstTime << setw(15) << left << wt[i] << setw(20) << left << tat[i] << endl;
        }

        // Tính trung bình thời gian chờ đợi và thời gian hoàn thành
        double avg_wt = static_cast<double>(total_wt) / n;
        double avg_tat = static_cast<double>(total_tat) / n;
        cout << "Average waiting time: " << avg_wt << endl;
        cout << "Average turnaround time: " << avg_tat << endl;
        }
};

int main() {
    vector<Process> processes = {
    Process("P1", 0, 6),
    Process("P2", 1, 8),
    Process("P3", 2, 7),
    Process("P4", 3, 3),
    Process("P5", 4, 4)
        };
    Scheduler scheduler(processes);
    scheduler.sjf_nonpreemptive();

    return 0;
}


