/*

Problem 0 
author-: Alejandro Aguilar 
Program makes process tree
*/


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include<unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>

#define NODE_NAME_SIZE  2


struct tree_node{
	unsigned 	nr_children;
	char		name[NODE_NAME_SIZE];
	struct tree_node *children;
};


static void _print_tree(struct tree_node *root, int level){
	int i;
	for(i=0; i < level; i++){
		printf("\t");
	}
	printf("%s \n",root->name);
	for(i = 0; i < root->nr_children; i++){
		_print_tree(root->children +i, level + i);	
	}

}

void print_tree(struct tree_node *root){
	_print_tree(root,0);
}

void Tree()
{	int status,status1,status2,status3;
	pid_t l,r;
	int a,b,c,d = 0;
	
	struct tree_node tree = {0};
	struct tree_node treeB= {0};
	struct tree_node treeC = {0};
	struct tree_node treeD = {0};
	
	tree.nr_children = 2;
	strcpy(tree.name,"A:");
	tree.children = &treeB;

	
	treeB.nr_children = 1;
	strcpy(treeB.name,"B:");
	treeB.children = &treeD;
	
	treeC.nr_children = 0;
	strcpy(treeC.name,"C:");
	treeC.children = NULL;
	
	treeD.nr_children = 0;
	strcpy(treeD.name,"D:");
	treeD.children = NULL;

	int p1[2];
    	pipe(p1);
        l = fork();
    	if (l == 0){
        	close(p1[0]);
		printf("Child Process start \n");
        	b = rand() % 15;
        	printf("Process %s with pid: %d and parent pid %d\n",treeB.name, getpid(), getppid());
        	write(p1[1], &b, sizeof(b));
        	close(p1[1]);
        	exit(0);
        
           	}else {
		printf("Wait for child process \n");
        	waitpid(l, &status, status);
        	close(p1[1]);
        	read(p1[0], &b, sizeof(b));
        	a = rand() % 20;
        	printf("Process %s with pid: %d and is the parent\n",tree.name, getpid());
        	close(p1[0]);
        
    		}
    
    	int p2[2];
    	pipe(p2);
    
    r = fork();
    if (r == 0)
    {
        close(p2[0]);

        d = rand() % 15;
	printf("Second child process start\n");
        printf("Process %s with pid: %d and parent pid %d\n",treeD.name,getpid(), getppid());
        write(p2[1], &d, sizeof(d));
        close(p2[1]);
        exit(0);
   
    }
    else {
	printf("Waiting for termination of second child process\n");
        waitpid(r, &status, status);
        close(p2[1]);
        read(p2[0], &d, sizeof(d));
        c = rand() % 20;
        printf("Process %s with pid: %d and parent pid %d\n", treeC.name, getpid(), getppid());
        close(p2[0]);
	}

	printf("Termination codes for processes:\n");
        printf("A = %d, B = %d, C = %d, D = %d\n", a,b,c,d);


}


int main(int argc, char const *argv[]){

printf("The following shows a process tree: \n");
    printf("The root is: %d\n", getpid());
    Tree();
	
	return 0;
}


