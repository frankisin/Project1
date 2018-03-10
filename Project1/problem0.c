/*

Problem 0 
author-: Alejandro Aguilar 
Program takes in an input take file filled with numbers

*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include<unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#define BUF 1000


void programA();
void programB();
void programC();

int max,min,sum;

void main(int argc, char *argv[]){

	printf("Enter character for option:\n A.(single process)\n B.(DFS)\n C.(multiple processes)\n");
	char input;
	scanf("%s",&input);

	if(input == 'A' || input == 'a'){
		printf("A:\n");
		programA();

		printf("\n");
		}else if(input == 'B' || input == 'b'){
			printf("B:\n");
			programB();
			printf("\n");

		}else if(input == 'C' || input == 'c'){
			printf("C:\n");
			programC();
		}else{
			printf("Invalid input!\n");
		}
	
}

void programA(){
     min,max,sum=0;

	printf("Enter file name including, example 'file.txt' \n");
	char file;
	scanf("%s",&file);

    FILE *fp = fopen(&file, "r");
    int i;
    int size = 1;
    int ch = 0;
    
    if(fp == NULL){
        perror("Error! File not opened");
        exit(1);
    	}

    while(!feof(fp)){
        
        ch = fgetc(fp);
        if(ch == '\n'){
            size++;
        }
    }
    int arrNum[size];
    rewind(fp);
    
    for (i = 0; i < size; i++)
    {
        fscanf(fp, "%d", &arrNum[i]);
    }
    
    if(arrNum[0] > arrNum[1]){
        max = arrNum[0];
        min = arrNum[1];
    }else{
        max = arrNum[1];
        min = arrNum[0];
    }
    
    for(i = 0; i < size; i++){
        sum += arrNum[i];
        
        if(max < arrNum[i]){
            max = arrNum[i];
        }
        
        if(min > arrNum[i]){
            min = arrNum[i];
        }
    }
    
    printf("\n");
    printf("max=%d\n", max);
    printf("min=%d\n", min);
    printf("sum=%d\n", sum);
    fclose (fp);
    
}

void programB(){
    min,max,sum=0;
    int i;
     
    printf("Enter file name including, example 'file.txt' \n");
    char file;
    scanf("%s",&file);

    FILE *fp = fopen(&file, "r");
    
    int size = 1;
    int ch = 0;
    
    if(fp == NULL){
        perror("Error! File not opened");
        exit(1);
    	}

    
    while(!feof(fp)){
        
        ch = fgetc(fp);
        if(ch == '\n'){
            size++;
        }
    }
    int arrNum[size];
    
    rewind(fp);
    
    for (i = 0; i < size; i++)
    {
        fscanf(fp, "%d", &arrNum[i]);
    }
    
    if(size == 1){
        printf("Max = %d\n", arrNum[0]);
        printf("Min = %d\n", arrNum[0]);
        printf("Sum = %d\n", arrNum[0]);
    }
    
    pid_t pid2 = fork();
    if(pid2 == 0){
        for(i = 0; i < size; i++){
            sum += arrNum[i];
        }
        printf("Process 2: pid is %d \nParent: pid is %d\n",getpid(),getppid());
        int status;
        waitpid(pid2, &status, 0);
        printf("sum=%d\n", sum);
        
    }
    else if (pid2 > 0){
        if(arrNum[0] > arrNum[1]){
            max = arrNum[0];
            min = arrNum[1];
        }else{
            max = arrNum[1];
            min = arrNum[0];
        }
        
        for(i = 0; i < size; i++){
            
            if(max < arrNum[i]){
                max = arrNum[i];
            }
            
            else if(min > arrNum[i]){
                min = arrNum[i];
            }
        }
        printf("Process 1(parent): pid is %d\n",getpid());
        int status;
        waitpid(pid2, &status, 0);
        printf("max=%d\n", max);
        printf("min=%d\n", min);
    }
    
    fclose (fp);

}


void programC(){
    min, max, sum=0;
    int i;
    
    printf("Enter file name including, example 'file.txt' \n");
	char file;
	scanf("%s",&file);

    FILE *fp = fopen(&file, "r");
    
    int size = 1;
    int ch = 0;
    
    if(fp == NULL){
        perror("Error! File not opened");
        exit(1);
    	}

    
    while(!feof(fp)){
        
        ch = fgetc(fp);
        if(ch == '\n'){
            size++;
        }
    }
    int arrNum[size];
    
    rewind(fp);
    
    for (i = 0; i < size; i++)
    {
        fscanf(fp, "%d", &arrNum[i]);
    }
    
    if(size == 1){
        printf("Max = %d\n", arrNum[0]);
        printf("Min = %d\n", arrNum[0]);
        printf("Sum = %d\n", arrNum[0]);

    }
    
    int fd1[2];
    pipe(fd1);
    
    pid_t pid2 = fork();
    if(pid2 == 0){
        close(fd1[0]);

        for(i = 0; i < size; i++){
            sum += arrNum[i];
        }
        printf("Hi I am Process 2 and my pid is %d. My Parent's pid is %d\n",getpid(),getppid());
        //printf("sum=%d\n", sum);
        write(fd1[1], &sum, sizeof(sum));
        close(fd1[1]);
        exit(0);
    }
    else{
        close(fd1[1]);
        read(fd1[0], &sum, sizeof(sum));
        int status;
        waitpid(pid2, &status, 0);
        close(fd1[0]);
    }
  //  printf("Hi I am Process 1 and my pid is %d. I am the Parent.\n", getpid());
    
    pid_t pid3 = fork();
    if (pid3 == 0){
        if(arrNum[0] > arrNum[1]){
            max = arrNum[0];
            min = arrNum[1];
        }else{
            max = arrNum[1];
            min = arrNum[0];
        }
        printf("Hi I am Process 3 and my pid is %d. My Parent's pid is %d\n", getpid(), getppid());
        
        pid_t pid4 = fork();
        if(pid4 == 0){
            printf("Hi I am Process 4 and my pid is %d. My Parent's pid is %d\n", getpid(), getppid());
            for(i = 0; i < size; i++){
                
                if(max < arrNum[i]){
                    max = arrNum[i];
                }
            }
            printf("Max=%d\n", max);
            exit(0);
            
        }else{
            for(i = 0; i < size; i++){
                
                if(min > arrNum[i]){
                    min = arrNum[i];
                }
            }
            int status;
            waitpid(pid4, &status, 0);
            printf("Min=%d\n", min);
        }
        exit(0);
    }
    else {
        
        int status1;
        waitpid(pid3, &status1, 0);
    }
    printf("Sum=%d\n", sum);
    
    fclose (fp);
    

}
