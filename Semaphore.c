//This C Code Solves the Race Condition of Multiple processes in synchronized manner
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/mman.h>

void child();//to call child function
void parent();//call parent function
int *VARIABLE;
int main()
{
//mmap is used for mapping between a process address space and either files
VARIABLE=mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1,0);
//sem_t is also used to perform semaphore operations
//sem_id returns a named process semaphore
//sem_open is used to open the named semaphore "OS"
sem_t *sem_id = sem_open("OS", O_CREAT,0644, 0);
//pid is initialized to represent the process ids and initialized by the pid_t data-type
pid_t pid;
pid=fork();
if(pid == 0)
{
//sem_t is also used to perform semaphore operations
//sem_id returns a named process semaphore
//sem_open is used to open the named semaphore "GEORGE"
sem_t *sem_id = sem_open("OS", 0);
child();
printf("Execution 3: Child Process is done with execution, proceed \n");
sem_post(sem_id);//sempost() is initialized to increment/unlocks the semaphore pointed to by sem_id
}
else
{
printf("Ideally, Parent Process should allow Child process to execute first\n\n");
sem_wait(sem_id);//sem_wait() is initialized to decrement/lock the semaphore pointed to by sem_id
parent();
sem_close(sem_id);//sem_close is initialized to close the named semaphore referred to by sem_id
printf("Execution 6: Parent Process will now execute \n");
}
printf("The Variable is %d\n", *VARIABLE);
waitpid(pid, NULL,0);
return 0;
}
void child(){
printf("Execution 1: Child process will execute \n");
printf("Execution 2: Child is executing on the Variable \n");
for(int i=1;i<=100000;i++)
{
*VARIABLE = *VARIABLE +1;
}
}void parent()
{
printf("Execution 4: Parent Process allowed Child process to execute \n");
printf("Execution 5: Parent is executing on the Variable \n");
for(int i=1;i<=1000000;i++){
*VARIABLE = *VARIABLE +1;
}
}
