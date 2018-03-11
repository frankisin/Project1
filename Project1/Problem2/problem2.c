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

char* BuildProcessTree(char nodename[MaxInput],int branch[MaxProcesses], char* childname[MaxInput][MaxProcesses], int depth){
    char ProcessTree[MaxInput*MaxProcesses];
	pid_t pids[MaxProcesses];
	for(int i=0; i<branch; i++){
        pids[i] = fork();

        if(pids[i]==-1){
            //forking failed
            printf("fork failed - %d - %s\n", errno, strerror(errno));
            exit(-1);
        }
        else if(pids[i]==0)
        {
            //child process
            BuildProcessTree(nodename, branch, childname, depth + 1);
            exit(0);
        }
        else{
            //parent process
            
            wait();
        }
	}
	return ProcessTree;
}



int main()
{
    FILE *fp;
    char fileaddress[100] = "D:\\Alex\\Projects\\Project1Q2\\input.txt";
    printf("Enter the address of the input file:\n");
    //gets(fileaddress);
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
