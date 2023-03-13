#ifndef ROUNDROBIN_H_INCLUDED
#define ROUNDROBIN_H_INCLUDED

#include <iostream>
#define head(p) p.head
#define tail(p) p.tail
#define info(p) p->info
#define next(p) p->next
#define nil NULL
using namespace std;

struct infotype
{
    string id;
    int burstTime, turnAroundTime, waitTime;
};
typedef struct element *adr;
struct element
{
    infotype info;
    adr next;
};
struct antrian
{
    adr head, tail;
};

void createAntrian(antrian &q);
void createElement(infotype newTask, adr &task);
void enqueue(antrian &q, adr task);
void dequeue(antrian &q, adr &task);
void show(antrian q);
void updateWaitTime(antrian &q, int time);
void mergeQueue(antrian &q1, antrian &q2);
void executeTaskPrio(antrian &h, antrian &m, antrian &l, int quantum, int prioUp);
void showTask(antrian h, antrian m, antrian l, adr p, int time);
#endif // ROUNDROBIN_H_INCLUDED