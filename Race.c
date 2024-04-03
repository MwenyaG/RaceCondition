#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>

void child();
void parent();
int *VARIABLE;

int main()
{
VARIABLE=mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1,0);

pid_t pid;
//pid is initialized to represent the process ids and initialized by the pid_t data-type
pid=fork();
if(pid == 0)
{

child();
printf("Execution 3: Child Process is done with execution, proceed \n");

}
else
{
printf("Ideally, Parent Process should allow Child process to execute first\n\n");
parent();
printf("Execution 6: Parent Process will now execute \n");
}
printf("VARIABLE is %d\n", *VARIABLE);
waitpid(pid, NULL,0);
return 0;
}

void child(){
printf("Execution 1: Child process will execute \n");
printf("Execution 2: Child is executing on the Variable \n");
for(int i=1;i<=1000000;i++){
*VARIABLE +=1;
}
}

void parent(){
printf("Execution 4: Parent Process allowed Child process to execute \n");
printf("Execution 5: Parent is executing on the Variable \n");
for(int i=1;i<=1000000;i++){
*VARIABLE +=1;
}
}

