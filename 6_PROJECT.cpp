// AIRPORT MANAGEMENT

#include <iostream>
#include <string>
#include <ctime>
using namespace std;

// class to represent airoplanes as objects
class process
{
public:
    string p_id;
    int arrival_time, burst_time, priority;              // provided by user
    int waiting_time, turn_around_time, completion_time; // to be calculated
    bool executed;                                       // to record if process is executed

    void set_data(string *p_id, int at, int bt)
    {
        this->p_id = *p_id;
        arrival_time = at;
        burst_time = bt;
        if (p_id->at(0) == 'I' || p_id->at(0) == 'i')
        {
            priority = 2;
        }
        else if (p_id->at(0) == 'D' || p_id->at(0) == 'd')
        {
            priority = 1;
        }
        else
        {
            priority = 0;
        }
        executed = false;
    }

    void calculate_time(int ct); // ct is completion time
};

void process ::calculate_time(int ct)
{
    completion_time = ct;

    turn_around_time = ct - arrival_time;
    waiting_time = turn_around_time - burst_time;

    executed = true;
}

// to search process to be executed
int give_process(process p[], int p_size, int ct) // ct represents current time
{
    int pr = -1, id = -1, bt = 1000;
    int i = p_size - 1;
    while (i >= 0)
    {
        if (!p[i].executed && p[i].arrival_time <= ct && p[i].priority >= pr)
        {
            if (pr == p[i].priority && p[i].burst_time >= bt) // skip the long process of same priority
            {
                i--;
                continue;
            }
            bt = p[i].burst_time;
            pr = p[i].priority;
            id = i;
        }
        i--;
    }

    return id; // index of process with least burst_time and ready to be executed
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
    cout << "\n\t\t\t\tFLIGHT CHART\n";
    cout << "Flight No.\tScheduled Arrival Time\tDeboarding Time\t  Holding Time\tCompletion Time\n";

    for (int i = 0; i < n; i++)
    {
        // taking sum to find average
        avg_waiting_time += p[i].waiting_time;
        avg_turnaround_time += p[i].turn_around_time;

        // display output
        cout << "   ";
        cout << p[i].p_id << "\t\t\t\t"
             << p[i].arrival_time << "\t\t"
             << p[i].burst_time << "\t\t"
             << p[i].waiting_time << "\t\t"
             << p[i].completion_time << endl;
    }
    cout << endl;
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    cout << "Estimated Average waiting time in this quarter : " << avg_waiting_time << endl;
    cout << "Estimated Average turnaround time in this quarter : " << avg_turnaround_time << endl;
    cout << "\t\tThe recipt is generated!!\nAll The Best!!";
}

int main()
{
    time_t now = time(0);
    char *dt = ctime(&now);
    int p_size; // number of processes
    cout << "\n\t\t\t\tAIRPORT MANAGEMENT PORTAL" << endl;
    cout << "\t\t\t\t\t\t\t\t\t" << dt << endl;
    cout << "Welcome Admin! to the CHATTRAPATI SHIVAJI MAHARAJ AIRPORT \n";
    cout << "This portal is related to scheduling the arriving flights \n";
    cout << "Enter the number of Aeroplanes arriving in this quarter : ";
    cin >> p_size;

    process p[p_size];
    string pid;
    int at, bt, priority; // process id, burst time, arrival time, priority

    // loop to set the variables of process objects
    cout << "Enter the details below :" << endl;
    cout << "NOTE :\n\tThe International Flight and the Distant Flights will be on priority\n"
         << "REMEMBER the Flight No. must be unique of 4 characters\n"
         << "If First character is 'i' it signifies the international flight i.e higher priority\n"
         << "If First character is 'd' it signifies the distant flight i.e next higher priority" << endl;
    for (int i = 0; i < p_size; i++)
    {
        cout << "Enter Flight No., Scheduled Arrival time, Deboarding time for the flight " << i + 1 << ": ";
        cin >> pid >> at >> bt;
        p[i].set_data(&pid, at, bt);
    }

    // CALCULATE and DISPLAY
    execute_process(p, p_size);
    display_table(p, p_size);

    return 0;
}
