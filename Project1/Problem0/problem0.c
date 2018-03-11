/*

Problem 0 
author-: Alejandro Aguilar 
Program takes in an input file filled with numbers calculates the min,max and sum
and output results to a file

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

	printf("Enter character for option:\n A.(Single process)\n B.(Two processes)\n C.(Multiple processes)\n");
	char input;
	scanf("%s",&input);

	if(input == 'A' || input == 'a'){
		printf("A: PartA\n");
		programA();

		printf("\n");
		}else if(input == 'B' || input == 'b'){
			printf("B: PartB\n");
			programB();
			printf("\n");

		}else if(input == 'C' || input == 'c'){
			printf("C: PartC\n");
			programC();
		}else{
			printf("Invalid input!\n");
		}
	
}

void programA(){
	min,max,sum=0;
	clock_t start = clock();

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
    
    FILE *writeOut = fopen("PartA", "w");
    printf("\n");
    printf("Results are printed in file 'PartA.txt'\n");

    fprintf(writeOut, "Max = %d\n", max);  
    fprintf(writeOut, "Min = %d\n", min);
    fprintf(writeOut, "Sum = %d\n", sum);
    fprintf(writeOut, "Time Elapsed = %f\n", (((double)clock()-start) / CLOCKS_PER_SEC));
    fclose(writeOut);
    fclose (fp);
    
}

void programB(){
    min,max,sum=0;
    clock_t start = clock();
    int i;
     
    printf("Enter file name including, example 'file.txt' \n");
    char file;
    scanf("%s",&file);

    FILE *fp = fopen(&file, "r");
    FILE *writeOut = fopen("PartB", "w");
    
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
    
    printf("Results are printed in file 'PartB'\n");
    pid_t pid2 = fork();
    if(pid2 == 0){
        for(i = 0; i < size; i++){
            sum += arrNum[i];
        }
        fprintf(writeOut, "Hi I'm process 2: my pid is %d \nMy Parent is process 1: pid is %d\n",getpid(),getppid());  
        int status;
        waitpid(pid2, &status, 0);
    	fprintf(writeOut, "Sum = %d\n", sum);
        
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
 	fprintf(writeOut, "Hi I'm Process 1: my pid is %d\n",getpid());  
        int status;
        waitpid(pid2, &status, 0);
    	fprintf(writeOut, "max = %d\n", max);
    	fprintf(writeOut, "min = %d\n", min);
    	}
    fprintf(writeOut, "Time Elapsed = %f\n", (((double)clock()-start) / CLOCKS_PER_SEC));
    fclose(writeOut);
    fclose (fp);

}


void programC(){
    min, max, sum=0;
    clock_t start = clock();
    int i;
    
    printf("Enter file name including, example 'file.txt' \n");
	char file;
	scanf("%s",&file);

    FILE *fp = fopen(&file, "r");
    FILE *writeOut = fopen("PartC", "w");
    
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
    
    
    int fd1[2];
    pipe(fd1);
    printf("Results are printed in file 'PartC.txt'\n");
    pid_t pid2 = fork();
    if(pid2 == 0){
        close(fd1[0]);
        for(i = 0; i < size; i++){
            sum += arrNum[i];
        }
fprintf(writeOut, "Hi I'm process 2: my pid is %d \nMy Parent is process 1: pid is %d\n",getpid(),getppid()); 
        write(fd1[1], &sum, sizeof(sum));
        close(fd1[1]);
        exit(0);
    }
    else{
fprintf(writeOut, "Hi I'm process 1: my pid is %d and I am the parent\n",getpid()); 
        close(fd1[1]);
        read(fd1[0], &sum, sizeof(sum));
        int status;
        waitpid(pid2, &status, 0);
        close(fd1[0]);
    }

    
    pid_t pid3 = fork();
    if (pid3 == 0){
fprintf(writeOut, "Hi I'm process 3: my pid is %d \nMy Parent is process 2: pid is %d\n",getpid(),getppid()); 
        if(arrNum[0] > arrNum[1]){
            max = arrNum[0];
            min = arrNum[1];
        }else{
            max = arrNum[1];
            min = arrNum[0];
        }
        pid_t pid4 = fork();
        if(pid4 == 0){
fprintf(writeOut, "Hi I'm process 4: my pid is %d \nMy Parent is process 3: pid is %d\n",getpid(),getppid()); 
            for(i = 0; i < size; i++){
                
                if(max < arrNum[i]){
                    max = arrNum[i];
                }
            }
    	    fprintf(writeOut, "Max = %d\n", max);
            exit(0);
            
        }else{
            for(i = 0; i < size; i++){
                
                if(min > arrNum[i]){
                    min = arrNum[i];
                }
            }
            int status;
            waitpid(pid4, &status, 0);
    	    fprintf(writeOut, "Min = %d\n", min);
        }
        exit(0);
    }
    else {
        
        int status1;
        waitpid(pid3, &status1, 0);
    }
    fprintf(writeOut, "Sum = %d\n", sum);

    fprintf(writeOut, "Time Elapsed = %f\n", (((double)clock()-start) / CLOCKS_PER_SEC));
    fclose(writeOut);    
    fclose (fp);
    

}
