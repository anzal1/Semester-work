#include<bits/stdc++.h>
using namespace std;
int bufftime=9999;
vector<int>freq;
int flag =0;
int res=0;

    //test case
	// process_id = {0, 1, 2, 3, 4, 5, 6};
	//  arrival_time = {9, 1, 4, 5, 2, 30, 29};
	//  burst_time = {10, 2, 1, 5, 7, 3, 6};

class Process{
	public:
		int process_id;
		int arrival_time;
		int burst_time;
		int remaining_time;
		int completion_time = 0;
		int turn_around_time = -1;
		int waiting_time = -1;
		int response_time=-1;
		int start_time=0;
		int prev=0;
		
		Process(int p_id, int a_time, int b_time){
			this->process_id = p_id;
			this->arrival_time = a_time;
			this->burst_time = b_time;
			this->remaining_time = this->burst_time;
		}
		
		bool operator!=(Process& p){
			if (this->process_id == p.process_id) return false;
			return true;
		}
};

bool idSort(Process *a,Process *b){
    return a->process_id < b->process_id;
}

bool idexist(vector<Process>response,int id)
{   for(Process p:response)
{  
  if(id==p.process_id)
  {
	  return false;
  }
}
return true;
}

void print_table(int m,vector<Process> p,vector<Process>presp)
{
    int i;
    
    puts("+-----+------------+--------------+-----------------+-----------------+-----------------+-----------------+");
    puts("| PID | Burst Time | Arrival Time | Turnaround Time |   Waiting Time  | Completion Time |  Response Time  |");
    puts("+-----+------------+--------------+-----------------+-----------------+-----------------+-----------------+");
 
    for(i=0; i<m; i++) {
        printf("| %2d  |     %2d     |      %2d      |        %2d       |        %2d       |        %2d       |        %2d       |\n"
               , p[i].process_id, p[i].burst_time, p[i].arrival_time, p[i].turn_around_time,  p[i].waiting_time, p[i].completion_time, presp[i+res].response_time );
        puts("+-----+------------+--------------+-----------------+-----------------+-----------------+-----------------+");
    }
    cout<<"\n";
}

void print_gantt_chart(vector<Process> gantt)
{   int y=gantt.size();
    cout<<"\n";
    int i, j;
    if(bufftime==9999)
    {
        bufftime=0;
    }
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
    for(i=flag; i<y; i++) {
        for(j=0; j<freq[i]; j++) printf("--");
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


    for(i=flag; i<y; i++) {
        for(j=0; j<freq[i] - 1; j++) printf(" ");
        if(gantt[i].process_id!=-1) {printf("P%d", gantt[i].process_id);}
        else {printf("IL");}
        for(j=0; j<freq[i] - 1; j++) printf(" ");
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

    
    for(i=flag; i<y; i++) {
        for(j=0; j<freq[i]; j++) printf("--");
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
    if(gantt[i].completion_time!=0)
	{
		printf("0");
	}
    printf("%d",bufftime);
    for(i=flag; i<y; i++) {
        for(j=0; j<freq[i]; j++) printf("  ");
        if(gantt[i].completion_time > 9) printf("\b"); 
        printf("%d", gantt[i].completion_time);
 
    }
    printf("\n");
 
}

int main(){
    int n;
	int tq;
	cout<<"\nEnter the no of processes :";
    cin>>n;
	cout<<"\nEnter the time quantum :";
    cin>>tq;
	int process_id[n] ;
	int arrival_time[n] ;
	int burst_time[n] ;
	cout<<"\nEnter the  process id :";
	for(int i=0;i<n;i++)
	{
      cin>>process_id[i];
	}
	cout<<"\nEnter the arrival time for each process :";
		for(int i=0;i<n;i++)
	{
		cin>>arrival_time[i];
	}
	cout<<"\nEnter the burst time for each process :";
		for(int i=0;i<n;i++)
	{
		cin>>burst_time[i];
	}

	
	vector<Process> process_list;
	
	queue<Process*> ready_queue;
	vector<Process> gantt;
    vector<Process> response;
	vector<Process> prinresp;

	Process idle(-1,0,0);


	for(int i=0; i<n; i++)
		process_list.push_back(Process(process_id[i], arrival_time[i], burst_time[i]));


// Bubble sort on arrival_time:
	for(int i=0; i<n; i++)
		for (int j=1; j<n-i; j++)
			if (process_list.at(j).arrival_time < process_list.at(j-1).arrival_time){
				Process temp = process_list.at(j);
				process_list.at(j) = process_list.at(j-1);
				process_list.at(j-1)= temp;
			}
			
	if(process_list.at(0).arrival_time > 0)
		{idle.completion_time = process_list.at(0).arrival_time;	
	 
		}
		else{flag=1;}
	gantt.push_back(idle);
	
	ready_queue.push(&process_list.at(0));
	
	while( !ready_queue.empty() ){
		Process* current = ready_queue.front();
		ready_queue.pop();
		
		if(current->remaining_time <= tq){
			current->completion_time = gantt.back().completion_time + current->remaining_time;
			current->remaining_time = 0;
		}
		else{
			current->completion_time = gantt.back().completion_time + tq;
			current->remaining_time = current->remaining_time - tq;
		}
		
		
		
		for(Process& p: process_list){
			if(p.arrival_time > gantt.back().completion_time && p.arrival_time <= current->completion_time ){
				ready_queue.push(&p);
				
			}
		}
		
		if(current->remaining_time != 0)
			ready_queue.push(current);
		
		gantt.push_back(*current);

		
		if (ready_queue.empty() )
			for (Process& p: process_list)
				if(p.remaining_time != 0 ){
					idle.arrival_time = gantt.back().completion_time;
					idle.completion_time = p.arrival_time;
					gantt.push_back(idle);
					ready_queue.push(&p);
					
					break;
				}
		
	}
	
	
	float total_turnaround_time=0.0;
    float total_waiting_time=0.0;
    float total_response_time=0.0;
    float total_completion_time=0.0;


	 for(Process p:gantt)
   {    

         response.push_back(p);

	
   }

   for(int i=0;i<response.size();i++)
   {
        if(response[i].process_id==-1)
		{
			res=1;
		}
		else{
			response[i].response_time=response[i-1].completion_time-response[i].arrival_time;
		}
   }
     
	 for(Process p:response)
    {    
   if(idexist(prinresp,p.process_id))
   {
        prinresp.push_back(p);
		if(p.response_time!=-1)
		{

		total_response_time += p.response_time;
		}
   }
   }

	reverse( gantt.begin(), gantt.end() );
	
	for(Process& p: process_list){
		p.turn_around_time = p.completion_time - p.arrival_time;
		p.waiting_time = p.turn_around_time - p.burst_time;
		p.response_time=p.start_time-p.arrival_time;
	    total_completion_time += p.completion_time;
	    total_turnaround_time += p.turn_around_time;
        total_waiting_time += p.waiting_time;
        
	
	}
	cout<<"\n";
	cout<<"\n";
	cout<<"Table"<<"\n";
	print_table(process_list.size(),process_list,prinresp);
	cout<<"\n";
	
	
	reverse( gantt.begin(), gantt.end() );
	

	for(int i=0;i<gantt.size();i++)
	{  
	            

      if(i==0)
	  {
         freq.push_back(gantt[i].completion_time);
	  }
	  else{
		  freq.push_back(gantt[i].completion_time-gantt[i-1].completion_time);
	  }
	  
	}

//   for(int x: freq)
//   {
// 	  cout<<x<<" ";
//   }
  int a =process_list.size();

	// cout<<"\n";
    cout<<"Average TurnAround time : "<<(total_turnaround_time/a)<<"\n";
    cout<<"Average Waiting time : "<<(total_waiting_time/a)<<"\n";
    cout<<"Average Response time : "<<(total_response_time/a)<<"\n";
	cout<<"Average Completion time : "<<(total_completion_time/a)<<"\n";
    cout << "\n\nGantt Chart:\n ";
    cout<<"\n";
	print_gantt_chart(gantt);

   
		
	
	// sort(response.begin(),response.end(),idSort);
	
  
  
  

  return 0;

}

