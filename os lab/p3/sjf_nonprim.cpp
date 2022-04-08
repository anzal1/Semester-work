#include <bits/stdc++.h>
using namespace std;

int bufftime=999;
int n;
int idle[10];
struct process
{
    int id;
    int burst_time;
    int arrival_time;
    int waiting_time;
    int turn_around_time;
    int completion_time;
};
process P[50];

bool btimeSort(process a,process b){
    return a.burst_time < b.burst_time; 
}
bool atimeSort(process a,process b){
    return a.arrival_time < b.arrival_time; 
} 
bool pidSort(process a,process b){
    return a.id < b.id; 
} 
bool ctSort(process a,process b){
    return a.completion_time < b.completion_time; 
} 
void SJF(int n)
{
    double total_waiting_time = 0.0;
    double total_turn_around_time = 0.0;
    double total_response_time = 0.0;
    double total_completion_time = 0.0;
    // sort(P,P+n,btimeSort);
    sort(P,P+n,atimeSort);
    if(P[0].arrival_time!=0)
    {
        bufftime=P[0].arrival_time;
    } 
    // cout<<bufftime<<endl;
    
    int ttime=0,i;
    int j,tArray[n];
    for(i=0;i<n;i++){
        j=i;
        while(P[j].arrival_time<=ttime&&j!=n){
            j++;
        }
        sort(P+i,P+j,btimeSort);
        tArray[i]=ttime;
        ttime+=P[i].burst_time;
        if(i==j)
        {   if(i!=n){
            idle[i]=abs(P[i+1].arrival_time-ttime);}
        }
    }
    tArray[i] = ttime;


    for(i=0; i<n; i++)
    {
        P[i].completion_time=tArray[i+1]+bufftime;
        total_completion_time+=tArray[i+1]+bufftime;
        P[i].turn_around_time=tArray[i]-P[i].arrival_time+P[i].burst_time+bufftime;
        total_turn_around_time+=tArray[i]-P[i].arrival_time+P[i].burst_time+bufftime;
        P[i].waiting_time=tArray[i]-P[i].arrival_time+bufftime;
        total_waiting_time+=tArray[i]-P[i].arrival_time+bufftime;
        
    }
    cout<<fixed<<setprecision(2);
    cout<<"Average Waiting Time: "<<(total_waiting_time/n)<<"\n";
    cout<<"Average Turn Around Time: "<<(total_turn_around_time/n)<<"\n";
    cout<<"Average Completion Time: "<<(total_completion_time/n)<<"\n";
    cout<<"Average Response Time: "<<(total_waiting_time/n)<<"\n";
    cout<<"\n";

    return;
}



void print_table(process P[], int n)
{
    int i;
    sort(P,P+n,pidSort);
    puts("+-----+------------+--------------+-----------------+-----------------+-----------------+-----------------+");
    puts("| PID | Burst Time | Waiting Time | Turnaround Time |   Arrival Time  | Completion Time |  Response Time  |");
    puts("+-----+------------+--------------+-----------------+-----------------+-----------------+-----------------+");
 
    for(i=0; i<n; i++) {
        printf("| %2d  |     %2d     |      %2d      |        %2d       |        %2d       |        %2d       |        %2d       |\n"
               , P[i].id, P[i].burst_time, P[i].waiting_time, P[i].turn_around_time,  P[i].arrival_time, P[i].completion_time, P[i].waiting_time );
        puts("+-----+------------+--------------+-----------------+-----------------+-----------------+-----------------+");
    }
    cout<<"\n";
}

void print_gantt_chart(process P[], int n)
{   sort(P,P+n,ctSort);
    cout<<"\n";
    int i, j;
    
    if(bufftime!=0){
    //-----------------------------------------------
    printf(" ");
    // for(i=0; i<n; i++) {
        for(j=0; j<bufftime; j++) printf("--");
        printf(" ");
    // }
    // printf("\n|");
    //-----------------------------------------------
    }

    if(bufftime==0){
    printf(" ");
    }
    for(i=0; i<n; i++) {
        for(j=0; j<P[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n|");

    if(bufftime!=0){
    //-----------------------------------------------
    // for(i=0; i<n; i++) {
        for(j=0; j<bufftime - 1; j++) printf(" ");
        printf("I%d", bufftime);
        for(j=0; j<bufftime - 1; j++) printf(" ");
        printf("|");
    // }
    // printf("\n ");
    //-----------------------------------------------
    }


    for(i=0; i<n; i++) {
        for(j=0; j<P[i].burst_time - 1; j++) printf(" ");
        printf("P%d", P[i].id);
        for(j=0; j<P[i].burst_time - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");

    if(bufftime!=0){
    //-----------------------------------------------
    // for(i=0; i<n; i++) {
        for(j=0; j<bufftime; j++) printf("--");
        printf(" ");
    // }
    // printf("\n");
    //-----------------------------------------------
    }

    
    for(i=0; i<n; i++) {
        for(j=0; j<P[i].burst_time; j++) printf("--");
        printf(" ");
    }
    printf("\n");

    if(bufftime!=0){
    //-----------------------------------------------
    printf("0");
    // for(i=0; i<n; i++) {
        for(j=0; j<bufftime; j++) printf("  ");
        // if(bufftime > 9) printf("\b"); 
        // printf("%d", bufftime);
 
    // }
    // printf("\n");
    //-----------------------------------------------
    }
    
    printf("%d",bufftime);
    for(i=0; i<n; i++) {
        for(j=0; j<P[i].burst_time; j++) printf("  ");
        if(P[i].completion_time > 9) printf("\b"); 
        printf("%d", P[i].completion_time);
 
    }
    printf("\n");
 
}
 
 
int main()
{
    cout<<"Number of Processes: ";
    cin>>n;
 
    cout<<"Process Ids:\n";
    for(int i=0; i<n; i++) cin>>P[i].id;
 
    cout<<"Process Burst Times:\n";
    for(int i=0; i<n; i++) cin>>P[i].burst_time;
 
    cout<<"Process Arrival Times:\n";
    for(int i=0; i<n; i++) cin>>P[i].arrival_time;
    
    SJF(n);
    print_table(P,n);
    print_gantt_chart(P,n);

    cout<<'\n';
    for(int i=0;i<10;i++)
    {

            cout<<idle[i]<<endl;

    }
 
    return 0;
}





