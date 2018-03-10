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

void genTreeExample()
{	int status,status1,status2,status3;
	pid_t l,r,s,q;
	
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
	
	//print_tree(&tree);

	//printf("A:\n");
	int counter = 1;
	l = fork();

	if(l == 0){
		 q = fork();
			if(q == 0){
				sleep(1);
				kill(getpid(),SIGINT);
			}else{
				waitpid(q,&status1,0);
				sleep(1);
				printf("%s status = %d\n",treeB.name,status1);
				s = fork();
				if(s==0){
				sleep(1);
				kill(getpid(),SIGALRM);
				}else{
					waitpid(s,&status3,0);
					sleep(1);
					printf("%s status = %d\n",treeD.name,status3);
				}

				kill(getpid(),SIGPIPE);
			}
	}else{
		waitpid(l,&status,0);
		printf("%s status = %d\n",tree.name,status);
		pid_t r = fork();
		if(r==0){
			sleep(1);
			kill(getpid(),SIGALRM);
		}

		//waitpid(l,&status,0);
		//printf("B: status = %d\n",status1);
		waitpid(r,&status2,0);
		printf("%s status = %d\n",treeC.name,status2);
	}
}

void genTree(int counter)
{
	int status,status1,status2;
	pid_t l;
	if(counter<0)
	{
	kill(getpid(),SIGPIPE);
	}
	l = fork();

	if(l == 0)
		{			
			sleep(1);	
			genTree(counter-=2);
			kill(getpid(),SIGINT);
		}
	else
	{
		
				pid_t r = fork();
				if(r==0)
				{
					sleep(1);
					genTree(counter-=2);
					kill(getpid(),SIGKILL);
				}
					waitpid(r,&status2,0);
		printf("%d->%d: status = %d\n",getpid(),r,WTERMSIG(status2));

		waitpid(l,&status,0);
		printf("%d->%d: status = %d\n",getpid(),l,status);
	}
}

int main(int argc, char const *argv[]){

printf("The following shows a tree: \n");

	if((argv[1])!=NULL){
		genTree(atoi(argv[1]));
	}else{
		genTreeExample();
	}
	return 0;
}


