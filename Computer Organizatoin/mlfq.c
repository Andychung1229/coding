//Note: Necessary header files are included
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define MAX_* constants
#define MAX_NUM_PROCESS 10
#define MAX_QUEUE_SIZE 10
#define MAX_PROCESS_NAME 5
#define MAX_GANTT_CHART 300

// Keywords (to be used when parsing the input)
#define KEYWORD_TQ0 "tq0"
#define KEYWORD_TQ1 "tq1"
#define KEYWORD_PROCESS_TABLE_SIZE "process_table_size"
#define KEYWORD_PROCESS_TABLE "process_table"

// Assume that we only need to support 2 types of space characters: 
// " " (space), "\t" (tab)
#define SPACE_CHARS " \t"

// Process data structure
// Helper functions:
//  process_init: initialize a process entry

//  process_table_print: Display the process table
struct Process {
    char name[MAX_PROCESS_NAME];
    int arrival_time ;
    int burst_time;
    int remain_time; // remain_time is needed in the intermediate steps of MLFQ 
};
void process_init(struct Process* p, char name[MAX_PROCESS_NAME], int arrival_time, int burst_time) {
strcpy(p->name, name);
    p->arrival_time = arrival_time;
    p->burst_time = burst_time;
    p->remain_time = 0;
}
void process_table_print(struct Process* p, int size) {
    int i;
    printf("Process\tArrival\tBurst\n");
    for (i=0; i<size; i++) {
        printf("%s\t%d\t%d\n", p[i].name, p[i].arrival_time, p[i].burst_time);
    }
}

// A simple GanttChart structure
// Helper functions:
//   gantt_chart_append: append one item to the end of the chart (or update the last item if the new item is the s>
//   gantt_chart_print: display the current chart
struct GanttChartItem {
    char name[MAX_PROCESS_NAME];
    int duration;
};
void gantt_chart_update(struct GanttChartItem chart[MAX_GANTT_CHART], int* n, char name[MAX_PROCESS_NAME], int duration){
    int i;
    i = *n;
    // The new item is the same as the last item
    if ( i > 0 && strcmp(chart[i-1].name, name) == 0) 
    {
        chart[i-1].duration += duration; // update duration
        //*n=i+1;//added by myself
    } 
    else
    {
        strcpy(chart[i].name, name);
        chart[i].duration = duration;
        *n = i+1;
    }
}
void gantt_chart_print(struct GanttChartItem chart[MAX_GANTT_CHART], int n) {
    int t = 0;
    int i = 0;
    printf("Gantt Chart = ");
    printf("%d ", t);
    for (i=0; i<n; i++) {
        t = t + chart[i].duration;     
        printf("%s %d ", chart[i].name, t);
    }
    printf("\n");
}

// Global variables
int tq0 = 0, tq1 = 0;
int process_table_size = 0;
struct Process process_table[MAX_NUM_PROCESS];



// Helper function: Check whether the line is a blank line (for input parsing)
int is_blank(char *line) {
    char *ch = line;
    while ( *ch != '\0' ) {
        if ( !isspace(*ch) )
            return 0;
        ch++;
    }
    return 1;
}
// Helper function: Check whether the input line should be skipped
int is_skip(char *line) {
    if ( is_blank(line) )
        return 1;
    char *ch = line ;
    while ( *ch != '\0' ) {
        if ( !isspace(*ch) && *ch == '#')
            return 1;
        ch++;
        }
    return 0;
}
// Helper: parse_tokens function
void parse_tokens(char **argv, char *line, int *numTokens, char *delimiter) {
    int argc = 0;

char *token = strtok(line, delimiter);
    while (token != NULL)
    {
        argv[argc++] = token;
        token = strtok(NULL, delimiter);
    }
    *numTokens = argc;
}
 
// Helper: parse the input file
void parse_input() {
    FILE *fp = stdin;
    char *line = NULL;
    ssize_t nread;
    size_t len = 0;
    char *two_tokens[2]; // buffer for 2 tokens
    int numTokens = 0, i=0;
    char equal_plus_spaces_delimiters[5] = "";
    char process_name[MAX_PROCESS_NAME];
    int process_arrival_time = 0;
    int process_burst_time = 0;

    strcpy(equal_plus_spaces_delimiters, "=");
    strcat(equal_plus_spaces_delimiters,SPACE_CHARS);

    while ( (nread = getline(&line, &len, fp)) != -1 ) {
        if ( is_skip(line) == 0)  {
            line = strtok(line,"\n");

            if (strstr(line, KEYWORD_TQ0)) {
                // parse tq0
                parse_tokens(two_tokens, line, &numTokens, equal_plus_spaces_delimiters);
                if (numTokens == 2) {
                    sscanf(two_tokens[1], "%d", &tq0);
                }
            } 
            else if (strstr(line, KEYWORD_TQ1)) {
                // parse tq0
                parse_tokens(two_tokens, line, &numTokens, equal_plus_spaces_delimiters);
                if (numTokens == 2) {
                    sscanf(two_tokens[1], "%d", &tq1);
                }
            }
            else if (strstr(line, KEYWORD_PROCESS_TABLE_SIZE)) {
                // parse process_table_size
            parse_tokens(two_tokens, line, &numTokens, equal_plus_spaces_delimiters);
                if (numTokens == 2) {
                    sscanf(two_tokens[1], "%d", &process_table_size);
                }
            } 
            else if (strstr(line, KEYWORD_PROCESS_TABLE)) {

                // parse process_table
                for (i=0; i<process_table_size; i++) {

                    getline(&line, &len, fp);
                    line = strtok(line,"\n");  

                    sscanf(line, "%s %d %d", process_name, &process_arrival_time, &process_burst_time);
                    process_init(&process_table[i], process_name, process_arrival_time, process_burst_time);

                }
            }

        }
         
    }
}
// Helper: Display the parsed values
void print_parsed_values() {
    printf("%s = %d\n", KEYWORD_TQ0, tq0);
    printf("%s = %d\n", KEYWORD_TQ1, tq1);
    printf("%s = \n", KEYWORD_PROCESS_TABLE);
    process_table_print(process_table, process_table_size);
}
void enqueue(struct Process* current,struct Process* queue[],int *n,int tq)
{
        int size=*n;
        
        queue[size]=current;
        queue[size]->remain_time=tq;
        
        (*n)++;
}

struct Process* dequeue(struct Process* queue[],int *n){
        struct Process* top=queue[0];
        int size=*n;
        if(size==1){
                queue[0]=NULL;
                (*n)--;
                return top;
        }
        for(int i=0;i<size-1;i++){
                queue[i]=queue[i+1];
                
        }
        queue[size]=NULL;
        (*n)--;
        return top;
}

// TODO: Implementation of MLFQ algorithm
void mlfq() {

    // Initialize the gantt chart
    struct GanttChartItem gantt_chart[MAX_GANTT_CHART];
    int chart_size = 0;
    // TODO: implement your MLFQ algorithm here

        int current=0;
        int overall=0;
        int count_t1=tq0;
        int count_t2=tq1;
        for(int i =0;i<process_table_size;i++){
                overall+=process_table[i].burst_time;
        }
         
        
        struct Process *queue0[MAX_NUM_PROCESS]={NULL};//create queue
        struct Process *queue1[MAX_NUM_PROCESS]={NULL};//create queue
        struct Process *queue2[MAX_NUM_PROCESS]={NULL};//create queue
        int s1=0;
        int s2=0;
        int s3=0;
        //assign the size of queue to check the queue size
//      printf("%d",s1);
while(current<overall){
                
                //printf("%s",process_table[0].name);
                for(int i =0;i<process_table_size;i++){
                        if(process_table[i].arrival_time==current){
                            //printf("%s",process_table[i].name);
                            struct Process *temp=&process_table[i];
                            //printf("%p",temp);
                                enqueue(&process_table[i],queue0,&s1,tq0); }  
                }
                

                if(queue0[0]!=NULL&&queue0[0]->remain_time==0){
                        struct Process* top=dequeue(queue0,&s1);
                        enqueue(top,queue1,&s2,tq1);
                        //printf(top.name);
                }
                if(queue1[0]!=NULL){
                if(queue1[0]->remain_time==0){
                        struct Process* top=dequeue(queue1,&s2);
                        
                        enqueue(top,queue2,&s3,30000);
                        //printf(top.name);
                }
                }
                /*printf("current: %d\n",current);
                printf("before;\n");
                printf("s1:%d s2:%d s3:%d\n",s1,s2,s3);
                printf("queue0:");
                for(int i=0;i<s1;i++){
                printf("%s ",queue0[i]->name);}
                for(int i=0;i<s1;i++){
                printf("%d ",queue0[i]->burst_time);}
                for(int i=0;i<s1;i++){
                printf("%d ",queue0[i]->remain_time);}
                printf("\nqueue1:");
                for(int i=0;i<s2;i++){
                printf("%s ",queue1[i]->name);}
                for(int i=0;i<s2;i++){
                printf("%d ",queue1[i]->burst_time);}
                for(int i=0;i<s2;i++){
                printf("%d ",queue1[i]->remain_time);}
                printf("\nqueue2:");
                for(int i=0;i<s3;i++){
                printf("%s ",queue2[i]->name);}
                printf("\n");
                for(int i=0;i<s3;i++){
                printf("%d ",queue2[i]->burst_time);}
                for(int i=0;i<s3;i++){
                printf("%d ",queue2[i]->remain_time);}*/
                
                if(s1>0){
                        queue0[0]->remain_time--;
                        queue0[0]->burst_time--;
                        //printf(queue0[0].name);
                        gantt_chart_update(gantt_chart,&chart_size,queue0[0]->name,1);
                        if(queue0[0]->burst_time==0){
                                dequeue(queue0,&s1);
                                }
                                current++;
                        
        }
        else if(s2>0){
                queue1[0]->remain_time--;
                queue1[0]->burst_time--;
                //printf(queue1[0].name);

                gantt_chart_update(gantt_chart,&chart_size,queue1[0]->name,1);
                if(queue1[0]->burst_time==0){
                        dequeue(queue1,&s2);
                        
                }
                current++;
                
        }
        else if(s3>0){
                queue2[0]->remain_time--;
                queue2[0]->burst_time--;
                gantt_chart_update(gantt_chart,&chart_size,queue2[0]->name,1);
                if(queue2[0]->burst_time==0)
                        dequeue(queue2,&s3);
                current++;
                }
                
                /*printf("\n After update:\n");
                printf("s1:%d s2:%d s3:%d\n",s1,s2,s3);
                printf("queue0:");
                for(int i=0;i<s1;i++){
                printf("%s ",queue0[i]->name);}
                for(int i=0;i<s1;i++){
                printf("%d ",queue0[i]->burst_time);}
                for(int i=0;i<s1;i++){
                printf("%d ",queue0[i]->remain_time);}
                printf("\nqueue1:");
                for(int i=0;i<s2;i++){
                printf("%s ",queue1[i]->name);}
                for(int i=0;i<s2;i++){
                printf("%d ",queue1[i]->burst_time);}
                for(int i=0;i<s2;i++){
                printf("%d ",queue1[i]->remain_time);}
                printf("\nqueue2:");
                for(int i=0;i<s3;i++){
                printf("%s ",queue2[i]->name);}
                printf("\n");
                for(int i=0;i<s3;i++){
                printf("%d ",queue2[i]->burst_time);}
                for(int i=0;i<s3;i++){
                printf("%d ",queue2[i]->remain_time);}
                printf("\n");*/

                

        
        }
    //printf("char_size:%d",chart_size);
    // At the end, display the final Gantt chart
    gantt_chart_print(gantt_chart, chart_size);
}
int main() {
    parse_input();
    print_parsed_values();
    mlfq();
    return 0;
}

