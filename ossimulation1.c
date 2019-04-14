/*
       Design a scheduler that can schedule the processes arriving system at periodical
intervals. Every process is assigned with a fixed time slice t milliseconds. If it is not able to
complete its execution within the assigned time quantum, then automated timer generates an
interrupt. The scheduler will select the next process in the queue and dispatcher dispatches the
process to processor for execution. Compute the total time for which processes were in the queue
waiting for the processor. Take the input for CPU burst, arrival time and time quantum from the
user.
*/
#include<stdio.h>
#include <unistd.h>
#include<stdlib.h>

//Defining a structure for process
struct process
{
	int process_number , arrival_time , cpu_burst , turn_around_time , waiting_time , completion_time ;
};

float avg_turn_around_time=0 , avg_waiting_time=0;

int completed_processes=0 , queued_processes=0 , number_of_processes=0 , time_quantum=0 , total_time=0 , idle_time=0;

int main()
{
	printf("=============================================================================\n");
	printf("___________________________________________CPU SCHEDULER_____________________\n\n");
    printf("\t\t\t\t\tOS SIMULATION BASED-2\n\n");
    printf("\n NOTE: Please enter relavent values and negative values are not allowed \n If you enter wrong values results will not be correct");
    printf("\n If you enter incompatible values program will terminate\n");
    //Taking input of no of processes and time quantum
    printf("\nEnter the number of processes :  ");
    scanf("%d",&number_of_processes);
    printf("\nEnter the time quantum to be allocated :  ");
    scanf("%d",&time_quantum);
    if(number_of_processes<0 | time_quantum<0)
    	exit(1);
     
    //Declaring array of structures structures
    struct process available[number_of_processes];
    struct process completed[number_of_processes];
    struct process queue[number_of_processes];

    //Taking input about processes from user
    //declaring loop variable
    int i=0;
    for( i ; i<number_of_processes ; ++i )
    {

    	printf("\nprocess is : %d  \n",i);
        available[i].process_number=i;
   		printf("\nEnter arrivalTime  :");
   		scanf("%d",&available[i].arrival_time);
   		printf("\nEnter CPUburstTime  :");
   		scanf("%d",&available[i].cpu_burst);
        if (available[i].arrival_time<0 | available[i].cpu_burst<0)
        	exit(1);
        
    	//Initializing other values in structure
    	available[i].turn_around_time=0;
   		available[i].completion_time=0;
   		available[i].waiting_time=0;

    }

    //Print the entered processes
    printf("\nThe time quantum allocated is %d\n",time_quantum );
    printf("\n\n\t\t\t\t The processes are \n");
    printf("\n| Process number| Arrival time  |  CPU burst time  |\n");
    printf("-------------------------------------------------------------------------\n");
    for (i=0; i < number_of_processes; ++i)
    {
    	printf("|\t %d \t|\t %d \t|\t %d    \t|\n ",available[i].process_number,available[i].arrival_time,available[i].cpu_burst);
    }


    //calculating total time of execution

    i=0;//reset the loop variable
    int maxat=0;//maximum arrival time among processes
    int maxatp=0;//Process having maximum arrival time
    for (i; i<number_of_processes ; ++i)
    {
    	if(available[i].arrival_time>maxat)
    	{
    		maxat=available[i].arrival_time;
    		maxatp=i;
		}
    }

    //checking a condition for total time calculation 
    i=0;
    for (i; i<number_of_processes ; ++i)
    {
    	total_time += available[i].cpu_burst;
    }
    total_time += maxat;

    printf("\nTotal time of execution is : %d \n",total_time);

    //looping over total time
    int t=0;
    for ( i = 0 ,t=i; i <=total_time; ++i,++t)
    {
    	printf("\nAfter time %d second \n",i);
    	int j=0;

        //checking processes at time i and adding to queue
    	for (j=0;j<number_of_processes; ++j)
    	{
    		if (available[j].arrival_time==i)
    		{
    			printf("\nAdding process %d to queue",j);
    			queue[queued_processes]=available[j];
    			++queued_processes;
    		}
    	}

        printf("\nThe number of queued processes :%d\n",queued_processes );

    	//If current process is completed then adding it to completed array
    	if (queued_processes != 0)
    	{
    		if(queue[0].cpu_burst==0)
    	    {
    		    int mainpro;
    		    printf("\nProcess %d is completed\n",queue[0].process_number);
    		    for (j = 0; j < number_of_processes; ++j)
    		    {
    		    	if(queue[0].process_number==available[j].process_number)
    		    		mainpro=j;
    		    }
    		    queue[0].completion_time=i;
    		    queue[0].turn_around_time=i-queue[0].arrival_time;
    		    queue[0].waiting_time=queue[0].turn_around_time - available[mainpro].cpu_burst;
    		    completed[completed_processes]=queue[0];
    		    queue[0].cpu_burst = available[mainpro].cpu_burst;
    		    ++completed_processes;
    		    printf("\nNo of processes completed : %d \n",completed_processes);
    
    		    //Removing current process from queue
    	        for (j=0 ; j < queued_processes; ++j)
    	        {
    		        queue[j]=queue[j+1];
    	        }
    	        --queued_processes;
    	        if(queued_processes==0)
    	        {
    	        	++idle_time;
    	        }
    	        
    	        printf("\nProcesses in the queue : %d\n",queued_processes );
    	        if ((t%time_quantum)==0 & t!=0)
                {
                    printf("\nTime quantum expired \n");
                }
                else
                {
                	t-=(t%time_quantum);
                }
                if (completed_processes==number_of_processes)
                {
                    break;
                }
        	}
        	else
        	{
        		if ((t%time_quantum)==0 & t!=0)
                {
                    printf("\nTime quantum expired \n");
                    j=0;
                    struct process sample;
                    sample=queue[j];
                    for (j; j < queued_processes; ++j)
                    {
                        queue[j]=queue[j+1];
                    }
                    queue[j-1]=sample;
                }
        	}
    	}
    	else
        {
            if ((t%time_quantum)==0 & t!=0)
                {
                    printf("\nTime quantum expired \n");
                }
        }

    	//Executing current process for one second
    	if(queued_processes != 0 &queue[0].cpu_burst!=0)
    	{
    		printf("\nDecreasing burst time of %d process by 1 \n",queue[0].process_number );
    	    queue[0].cpu_burst-=1;
    	}
        if (queued_processes == 0)
        {
            idle_time += 1;
        }
    }

    printf("\n\n\t\t\t\t The completed processes are \n");
    printf("\nCpu will be idle for %d Seconds \n",idle_time );
    printf("\n| Process number| Arrival time  |  CPU burst time  |   Completion time  |  Turnaroundtime  |   Waiting time    | \n");
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");
    for (i=0; i < number_of_processes; ++i)
    {
    	static int total_turn_around_time=0;
    	static int total_waiting_time=0;

        int mainpro,j;
    		for (j = 0; j < number_of_processes; ++j)
    		{
    			if(completed[i].process_number==available[j].process_number)
    				mainpro=j;
    		}

    	printf("|\t%2d  \t|\t%2d  \t|\t%2d     \t|\t  %2d        | \t %2d            | \t %2d        |\n ",completed[i].process_number,completed[i].arrival_time,available[mainpro].cpu_burst,completed[i].completion_time,completed[i].turn_around_time,completed[i].waiting_time);
        total_turn_around_time += completed[i].turn_around_time;
        total_waiting_time += completed[i].waiting_time;
        if(i==(number_of_processes-1))
        {
        	avg_turn_around_time = (float) total_turn_around_time/number_of_processes;
        	avg_waiting_time = (float) total_waiting_time/number_of_processes;
        }

    }

    printf("\n The average turn around time of all processes is : %.3f \n",avg_turn_around_time );
    printf("\n The average waiting time of all processes is : %.3f \n", avg_waiting_time);
}
