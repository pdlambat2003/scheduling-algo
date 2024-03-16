// SHORTEST JOB FIRST SCHEDULING
// non preemptive

#include <iostream>
using namespace std;

// class to represent processes as objects
class process
{
public:
    // times related to each process
    int p_id, arrival_time, burst_time;                  // provided by user
    int waiting_time, turn_around_time, completion_time; // to be calculated
    bool executed;                                       // to record if process is executed

    void set_data(int id, int at, int bt)
    {
        p_id = id;
        arrival_time = at;
        burst_time = bt;
        executed = false;
    }

    void calculate_time(int ct); // ct is completion time
};

// to search process to be executed
int give_process(process p[], int p_size, int ct) // ct represents current time
{
    int bt = 1000, least = -1; // least stores p_id and bt is upper bound of burst_time
    int i = p_size - 1;        // traverse from last to have fcfs in case of similarity
    while (i >= 0)
    {
        if (!p[i].executed && p[i].arrival_time <= ct && p[i].burst_time < bt)
        {
            bt = p[i].burst_time; // least burst_time found till now
            least = i;            // p_id of least burst_time
        }
        i--;
    }

    return least; // index of process with least burst_time and ready to be executed
}

void process ::calculate_time(int ct)
{
    completion_time = ct;

    turn_around_time = ct - arrival_time;
    waiting_time = turn_around_time - burst_time;

    executed = true;
}

void execute_process(process p[], int p_size)
{
    int current_time = 0, current_process, check = 0;

    while (check < p_size)
    {
        current_process = give_process(p, p_size, current_time); // get the index of process to be executed

        if (current_process == -1) // for empty cpu
        {
            current_time++; // increase time
            continue;
        }

        // executing process
        current_time += p[current_process].burst_time;

        // calculating wt and tat
        p[current_process].calculate_time(current_time);

        check++;
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
    int p_size; // number of processes
    cout << "\n\t\t\tSHORTEST JOB FIRST SCHEDULING" << endl;
    cout << "Enter the number of processes: ";
    cin >> p_size;

    process p[p_size];
    int pid, at, bt; // process id, burst time, arrival time

    // loop to set the variables of process objects
    cout << "Enter the details for processes :" << endl;
    for (int i = 0; i < p_size; i++)
    {
        cout << "Enter process ID, arrival time and burst time for process " << i + 1 << ": ";
        cin >> pid >> at >> bt;
        p[i].set_data(pid, at, bt);
    }

    // CALCULATE and DISPLAY
    execute_process(p, p_size);
    display_table(p, p_size);

    return 0;
}