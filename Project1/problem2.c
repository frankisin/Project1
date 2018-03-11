#include <stdio.h>
#include <stdlib.h>
#define MaxInput 500
#define MaxProcesses 20
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
    char *line[MaxInput];
    char *nodename[MaxInput][3];
    char *childname[MaxInput][MaxProcesses];
    char i[3];
    char s[MaxProcesses];
    char temp[MaxProcesses];
    int count = 0;
    int branch[MaxInput];
    int b_no;
    while(fgets(&temp, MaxProcesses+2,fp)){
        printf("%s\n",temp);
        
        printf("%s\n",)
        system("Pause");
    }

    int c=0;
    system("Pause");
    return 0;
}
