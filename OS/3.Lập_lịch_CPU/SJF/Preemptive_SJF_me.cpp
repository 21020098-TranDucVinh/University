#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Process
{
    int id;
    float arrivalTime;
    float burstTime;
    float remainingTime;
    float responseTime = -1;
    float waitingTime;
    float turnaroundTime = 0;

};

bool compareArrivalTime(Process p1, Process p2)
{
    return p1.arrivalTime < p2.arrivalTime;
}

bool compareRemainingTime(Process p1, Process p2)
{
    return p1.remainingTime < p2.remainingTime;
}

int main()
{
    int time = 0;
    // Nhập số tiến trình
    int n;
    cout << "Nhap so tien trinh: ";
    cin >> n;

    vector<Process> processes(n);
    float averageResponseTime = 0;
    float averageTurnaroundTime = 0;
    float averageWaitingTime = 0;
    float timeMax = 0;

    // Nhập thời gian đến và thời gian chạy của từng tiến trình
    cout << "Nhap thoi gian den va thoi gian chay cua tung tien trinh:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i + 1 << " = ";
        processes[i].id = i + 1;
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
        timeMax += processes[i].arrivalTime + processes[i].burstTime;
    }

    sort(processes.begin(), processes.end(), compareArrivalTime);
    while (time <= timeMax)
    {
        vector<Process> readyProcess;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= time && processes[i].remainingTime > 0)
            {
                readyProcess.push_back(processes[i]);
            }
        }
        if (readyProcess.size() != 0)
        {
            sort(readyProcess.begin(), readyProcess.end(), compareRemainingTime);
            for (int i = 0; i < n; i++)
            {
                if (readyProcess[0].id == processes[i].id)
                {
                    if(processes[i].responseTime == -1){
                        processes[i].responseTime = time - processes[i].arrivalTime;
                    }
                    processes[i].remainingTime --;
                }
                for(int j = 0; j < readyProcess.size(); j ++){
                    if (readyProcess[j].id == processes[i].id){
                        processes[i].turnaroundTime ++;
                    }
                }
            }
        }
        time ++;
    }

    for(int i = 0; i < n; i++){
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
    }

    // // In ra biểu đồ Gantt
    // cout << "\nBieu do Gantt:";
    // cout << "\nProcess\t\tStart time\tEnd time";
    // for (int i = 0; i < n; i++)
    // {
    //     cout << "\nP" << process[i] << "\t\t" << responseTime[i] << "\t\t" << turnaroundTime[i];
    // }

    // in ra bảng
    cout << "\n\nProcess\t\tArrival Time\tBurst Time\tResponse Time\tWaiting Time\tTurnaround Time";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (processes[j].id == i + 1)
            {
                cout << "\nP" << i + 1 << "\t\t" << processes[j].arrivalTime << "\t\t" << processes[j].burstTime << "\t\t" << processes[j].responseTime<< "\t\t" << processes[j].waitingTime << "\t\t" << processes[j].turnaroundTime;
                break;
            }
        }
    }

    // In ra thời gian trung bình
    for (int i = 0; i < n; i++)
    {
        averageResponseTime += processes[i].responseTime / n;
        averageTurnaroundTime += processes[i].turnaroundTime / n;
        averageWaitingTime += processes[i].waitingTime / n;
    }
    cout << "\nAverage Response Time = " << averageResponseTime;
    cout << "\nAverage Turnaround Time = " << averageTurnaroundTime;
    cout << "\nAverage Waiting Time = " << averageWaitingTime;
    return 0;
}