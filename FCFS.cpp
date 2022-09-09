#include <iostream>
using namespace std;

int main(){
    int process;
    cout << "Input the number of processes" << endl;
    cin >> process;
    int burst[process], arr[process], turn_around[process], wait[process], service[process];
    int total_wait = 0, total_turn_around = 0;

    cout << "Input the arrival time" << endl;
    for(int i=0; i<process; i++){
        cin >> arr[i];
    }

    cout << "Input the burst time" << endl;
    for(int i=0; i<process; i++){
        cin >> burst[i];
    }

    service[0] = arr[0];
    wait[0] = 0;

    //for waiting time
    for(int i=1; i<process; i++){
        service[i] = service[i-1] + burst[i-1];
        wait[i] = service[i] - arr[i];
        if(wait[i]<0){
            wait[i]=0;
        }
    }
    //for turnaround time

    for(int i=0; i<process; i++){
        turn_around[i] = wait[i] + burst[i];
    }

    //average waiting time
    for(int i=0; i<process ;i++){
        total_wait+=wait[i];
    }
    float avg_wait_time = (float)total_wait/(float)process;

    //average turn_around time
    for(int i=0; i<process ;i++){
        total_turn_around+=turn_around[i];
    }
    float avg_turn_around_time = (float)total_turn_around/(float)process;

    cout << "Total wait time is " << total_wait << endl;
    cout << "Average wait time is " << avg_wait_time << endl; 
    cout << "Total turn around time is " << total_turn_around << endl;
    cout << "Average turn around time is " << avg_turn_around_time << endl;



}