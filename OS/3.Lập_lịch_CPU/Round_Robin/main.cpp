#include "roundRobin.h"

int main()
{
    infotype task;
    string prio;
    int quantum = 0, prioUp;
    antrian high;
    createAntrian(high);
    adr highPriorityTask;
    antrian mid;
    createAntrian(mid);
    adr midPriorityTask;
    antrian low;
    createAntrian(low);
    adr lowPriorityTask;
    bool check = false;
    int more = 0;

    while (quantum <= 0)
    {
        cout << "waktu quantum : ";
        cin >> quantum;
    }

    cout << "Waktu change priority : ";
    cin >> prioUp;
    cout << endl;
    while (!check)
    {
        cout << "Masukkan id task : ";
        cin >> task.id;
        cout << "Masukkan burst time : ";
        cin >> task.burstTime;
        cout << "Prioritas [high/mid/low] : ";
        cin >> prio;
        if (prio == "high")
        {
            createElement(task, highPriorityTask);
            enqueue(high, highPriorityTask);
        }
        else if (prio == "mid")
        {
            createElement(task, midPriorityTask);
            enqueue(mid, midPriorityTask);
        }
        else if (prio == "low")
        {
            createElement(task, lowPriorityTask);
            enqueue(low, lowPriorityTask);
        }
        else
        {
            cout << "\n\tERROR" << endl;
            cout << "Pilihan prioritas antara lain : high/mid/low." << endl;
            cout << "Inputan anda : " << prio << endl
                 << endl;
        }
        cout << "New Task? [0/1] : ";
        cin >> more;
        cout << endl;
        if (more == 0)
        {
            check = true;
        }
    }
    cout << "====================================================\n";
    cout << "High : \n";
    show(high);
    cout << "\nMid : \n";
    show(mid);
    cout << "\nLow : \n";
    show(low);
    cout << "====================================================\n";
    cout << "\n";
    executeTaskPrio(high, mid, low, quantum, prioUp);
    return 0;
}