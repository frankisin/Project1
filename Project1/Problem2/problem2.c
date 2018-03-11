#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MaxInput 500
#define MaxProcesses 20

char* BuildProcessTree(char nodename[MaxInput],int branch[MaxProcesses], char* childname[MaxInput][MaxProcesses],int node_loc){
    char ProcessTree[MaxInput*MaxProcesses];
    char HoldPass[MaxInput*MaxProcesses];
    strcat(ProcessTree, nodename[0]);
    strcat(ProcessTree, "\n");
    //pipe values
	pid_t pid;
	int status;
	int fd[2];
	pipe(fd);

	if(branch[node_loc]>0){
        for(int i=0; i<branch[node_loc]; i++){

            strcat(ProcessTree, childname[node_loc]);
            pid = fork();
            if(pid==-1){
                //forking failed
                printf("fork failed - %d - %s\n", errno, strerror(errno));
                exit(-1);
            }
            else if(pid==0)
            {
                //child process
                dup2(fd[1],1);
                strcat(ProcessTree, BuildProcessTree(nodename, branch, childname, node_loc + branch - i));
                write(fd[1],ProcessTree,MaxProcesses*MaxInput);
                exit(0);
            }
            }
        }

    if(pid!=0){
        while ((pid = wait(&status)) != -1)
        {
            fprintf(stderr, "process %d exits with %d\n", pid, WEXITSTATUS(status));
        }
        dup2(fd[0],0);
        read(fd[0],HoldPass,MaxInput*MaxProcesses);
    }
    strcat(ProcessTree, nodename[node_loc]);
    strcat(ProcessTree, "\n");
	return ProcessTree;
}





int main()
{
    FILE *fp;
    printf("Enter the address of the input file:\n");
    gets(fileaddress);
    fp = fopen(fileaddress, "r");

    if (fp== NULL){
        printf("File address not found %s", fileaddress);
        return 1;
    }

    //Get all characters from file

    char *readtemp[MaxInput][MaxProcesses+2];
    char temp[MaxProcesses];
    int count = 0;

    while(fgets(&temp, MaxProcesses+2,fp)){
        strcpy(readtemp[count],temp);
        printf("%s", readtemp[count]);
        count=count+1;
        readtemp[count][MaxInput-1]='\0';
    }
    //extract information from c file
    char nodename[MaxInput];
    char *childname[MaxInput][MaxProcesses];
    int branch[MaxInput];
    char temp2[MaxProcesses];
    char temp3[2];

    for(int i=0; i<=count; i++){
        nodename[i]=readtemp[i][0];
        strncpy(temp2,readtemp[i],3);
        temp2[3]='\0';
        strncpy(temp3,temp2+2,1);
        temp3[1]='\0';
        branch[i]=atoi(temp3);
        printf("\n%d",branch[i]);
        //check if node has children
        strcpy(temp2,readtemp[i]);
        system("Pause");
        if(branch[i]>0){
            strncpy(childname[i],temp2+4,2*branch[i]-1);
            printf("\n%s",childname[i]);
        }
        else{
            strcpy(childname[i],"");
        }

    }
    char* ProcessTree;
    ProcessTree = BuildProcessTree(nodename,branch,childname,0);
    strcat(ProcessTree, "");
    system("Pause");
    return 0;
}
