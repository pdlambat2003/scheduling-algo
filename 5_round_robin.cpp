#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

// ROUND ROBIN SCHEDULING

// class to represent processes as objects
class process
{
public:
    // times related to each process
    int p_id, arrival_time, burst_time;                  // provided by user
    int waiting_time, turn_around_time, completion_time; // to be calculated
    bool entered;                                        // to record if process is executed
    int updated_burst_time;                              // to maintain the burst time after semi execution

    void set_data(int id, int at, int bt)
    {
        p_id = id;
        arrival_time = at;
        burst_time = bt;
        updated_burst_time = burst_time;
        entered = false;
    }

    void calculate_time(int ct); // ct is completion time
};

void process ::calculate_time(int ct)
{
    completion_time = ct;

    turn_around_time = ct - arrival_time;
    waiting_time = turn_around_time - burst_time;
}

// to search process to be executed
int give_process(process p[], int p_size, int ct, queue<int> &rq) // ct represents current time
{
    int static pEnter = 0;
    int id = -1; // id stores p_id
    int i = 0;

    if (pEnter == p_size)
    {
        if (!rq->empty())
        {
            int pr = rq->front();
            return pr;
        }
        return -1;
    }

    while (p[i].arrival_time < ct && i < p_size)
    {
        if (!p[i].entered)
        {
            rq.push(p[i].p_id);
            p[i].entered = true;
            pEnter++;
        }
        i++;
    }

    if (id == -1) // to deal the default case
    {
        return id;
    }

    int pr = rq->front();
    return pr;
}

void execute_process(process p[], int p_size, int tq)
{
    int current_time = 0, current_process, check = 0;
    queue<int> ready; // ready queue stores the process ready to be executed

    while (check < p_size)
    {
        current_process = give_process(p, p_size, current_time, ready); // get the index of process to be executed

        if (current_process == -1) // to deal with default caase
        {
            current_time++; // increase time
            continue;
        }

        // executing process
        p[current_process].updated_burst_time -= tq;
        current_time += tq;

        // calculating wt and tat
        if (p[current_process].updated_burst_time <= 0)
        {
            // correct the current_time if the burst time is negative
            current_time += p[current_process].updated_burst_time;

            p[current_process].calculate_time(current_time);
            check++;

            ready.pop(); // remove the current_process from ready queue after complete execution
            continue;    // to stop the further code from execution in particular iteration
        }

        // update the ready queue
        int temp = ready.front();
        ready.push(temp);
        // ready.push(ready.front());
        ready.pop();
    }
}

void display_table(process p[], int n)
{
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    // DISPLAY TABLE
    cout << "\n\t\t\t\tProcess Table\n";
    cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\t   Turnaround Time\t  Waiting Time\n";

    for (int i = 0; i < n; i++)
    {
        // taking sum to find average
        avg_waiting_time += p[i].waiting_time;
        avg_turnaround_time += p[i].turn_around_time;

        // display output
        cout << "   ";
        cout << p[i].p_id << "\t\t"
             << p[i].arrival_time << "\t\t"
             << p[i].burst_time << "\t\t"
             << p[i].completion_time << "\t\t\t"
             << p[i].turn_around_time << "\t\t\t"
             << p[i].waiting_time << endl;
    }
    cout << endl;
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    cout << "Average waiting time: " << avg_waiting_time << endl;
    cout << "Average turnaround time: " << avg_turnaround_time << endl;
}

int main()
{
    int p_size, time_quantum; // number of processes
    cout << "\n\t\t\tROUND ROBIN SCHEDULING" << endl;
    cout << "Enter the number of processes: ";
    cin >> p_size;
    cout << "Enter the time quantum : ";
    cin >> time_quantum;

    process p[p_size];
    int pid, at, bt; // process id, burst time, arrival time

    // loop to set the variables of process objects
    cout << "Enter the details for processes " << endl;
    for (int i = 0; i < p_size; i++)
    {
        cout << "Enter process ID, arrival time and burst time for process " << i + 1 << ": ";
        cin >> pid >> at >> bt;
        p[i].set_data(pid, at, bt);
    }

    // // Sort processes based on arrival time in ascending order
    sort(p, p + p_size, [](const process &p1, const process &p2)
         { return (p1.arrival_time < p2.arrival_time) || (p1.arrival_time == p2.arrival_time && p1.p_id < p2.p_id); });

    // CALCULATE AND DISPLAY
    execute_process(p, p_size, time_quantum);
    display_table(p, p_size);

    return 0;
}