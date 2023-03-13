#include "roundRobin.h"
void createAntrian(antrian &q)
{
    // membuat sebuah antrian kosong;
    q.head = NULL;
    q.tail = NULL;
}

bool isEmpty(antrian q)
{
    // jika antrian(priority) kosong maka tidak akan digunakan lagi
    return q.head == NULL and q.tail == NULL;
}

void createElement(infotype newTask, adr &task)
{
    task = new element;
    task->info = newTask;
    task->next = NULL;
}

void enqueue(antrian &q, adr task)
{
    /*insert last untuk menginputkan tugas ke antrian menurut prioritasnya
    pada algoritma round robin*/
    if (isEmpty(q))
    {
        q.head = task;
        q.tail = task;
        return;
    }
    q.tail->next = task;
    q.tail = task;
}

void dequeue(antrian &q, adr &task)
{
    /*delete first digunakan untuk menghapus task yang memiliki burst time = 0*/
    if (isEmpty(q))
    {
        cout << "Empty";
        return;
    }
    task = q.head;
    q.head = q.head->next;
    next(task) = nil;
    if (q.head == NULL)
    {
        q.tail = NULL;
    }
    /*if(q.head->info.burstTime == 0){
        task = q.head;
        q.head = task->next;
        task->next = NULL;
    }*/
}

void show(antrian q)
{
    // dibuat oleh david
    adr curr = q.head;
    while (curr != NULL)
    {
        cout << "id : " << curr->info.id << " burst time : " << curr->info.burstTime << endl;
        curr = curr->next;
    }
}

void executeTask(antrian q, int quantum)
{
    // dibuat oleh david
    int time = 0;
    adr task;
    while (q.head != NULL)
    {
        dequeue(q, task);
        if (task->info.burstTime > quantum)
        {
            task->info.burstTime -= quantum;
            time += quantum;
            enqueue(q, task);
        }
        else
        {
            time += task->info.burstTime;
        }
        cout << "TASK " << task->info.id << " EXECUTED" << endl;
    }
}

void updateWaitTime(antrian &q, int time)
{
    // dibuat oleh nadine
    adr p = head(q);
    while (p != nil)
    {
        info(p).waitTime = time;
        p = next(p);
    }
}

void mergeQueue(antrian &q1, antrian &q2)
{
    // dibuat oleh nadine
    // memindahkan isi q2 ke q1
    adr p;
    while (head(q2) != nil)
    {
        dequeue(q2, p);
        enqueue(q1, p);
    }
}
void showTask(antrian h, antrian m, antrian l, adr p, int time)
{
    cout << "================================================================\n";
    cout << "most recent task id=" << p->info.id << endl;
    cout << "High : \n";
    show(h);
    cout << "\nMid : \n";
    show(m);
    cout << "\nLow : \n";
    show(l);
    cout << "\ntime=" << time;
    cout << endl;
    cout << "----------------------------------------------------------------\n";
}
void executeTaskPrio(antrian &h, antrian &m, antrian &l, int quantum, int prioUp)
{
    // dibuat oleh nadine dan david
    int time = 0;
    int totalTAT = 0; // turn around time
    int totalWT = 0;  // wait time
    int taskCount = 0;
    int constPrio = prioUp;
    adr p;
    while (head(h) == nil && !(isEmpty(m) && isEmpty(l)))
    {
        mergeQueue(h, m);
        mergeQueue(m, l);
    }
    while (!isEmpty(h))
    {
        dequeue(h, p);
        updateWaitTime(h, time);
        updateWaitTime(m, time);
        updateWaitTime(l, time);
        if (info(p).burstTime > quantum)
        {
            prioUp = prioUp - quantum;
            info(p).burstTime -= (quantum);
            time += quantum;
            enqueue(h, p);
        }
        else
        {
            time += info(p).burstTime;
            prioUp = prioUp - p->info.burstTime;
            info(p).turnAroundTime = time;
            cout << "----------------------------------------------------------------\n";
            cout << "executed tat=" << info(p).turnAroundTime << " wt=" << info(p).waitTime << " id=" << info(p).id << endl;
            totalTAT += info(p).turnAroundTime;
            totalWT += info(p).waitTime;
            taskCount++;
        }
        showTask(h, m, l, p, time);

        cout << "prioUp time left : " << prioUp << endl;
        while ((prioUp <= 0 || isEmpty(h)) && !(isEmpty(m) && isEmpty(l)))
        {
            if (isEmpty(h))
            {
                prioUp -= constPrio;
            }
            prioUp += constPrio;

            cout << "prioUp time = 0 or priority queue is empty. shifting priority!" << endl
                 << endl;
            mergeQueue(h, m);
            mergeQueue(m, l);
        }
        cout << "================================================================\n";
    }
    cout << "Total Task: " << taskCount << endl;
    cout << "Total Turn Around Time: " << totalTAT << endl;
    cout << "Total Wait Time: " << totalWT << endl;
    cout << "Average Wait Time: " << float(totalWT) / float(taskCount) << endl;
    cout << "Average Turn Around Time: " << float(totalTAT) / float(taskCount) << endl;
    cout << "================================================================\n";
}