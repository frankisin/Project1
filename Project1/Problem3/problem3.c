#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include <sys/types.h>

//Here we will be declaring the basic structure of a node...
struct node
{
	int data;
	struct node *left;
	struct node *right;
};

/* newNode() allocates a new node with the given data and NULL left and
right pointers. */
struct node* newNode(int data)
{
	// Allocate memory for new node 
	struct node* node = (struct node*)malloc(sizeof(struct node));

	// Assign data to this node
	node->data = data;

	// Initialize left and right children as NULL
	node->left = NULL;
	node->right = NULL;
	return(node);
}
//We are going to be invoking the spawnNodes function to create our tree...
void spawnNodes(int curLevel, int levelLimit, int childrenNumber, 
                int nodeNumber, int offset)
{
    if (curLevel == levelLimit)
        pause();

    curLevel++;
    printf("(%d, %d) Pid: %d with parent %d\n", curLevel, nodeNumber, 
            getpid(), getppid());

    for (int i = 0; i < childrenNumber; i++)
    {
        pid_t childPid = fork();
        if (childPid == -1)
        {
            perror("Couldn't create process");
            exit(1);
        }

        if (childPid == 0)
        {
            spawnNodes(curLevel, levelLimit, childrenNumber, offset + i, 
                       offset + i);
        }
        else
        {
            wait(NULL);
        }
    }
}
//The objective of this function is to fork recursively...(Not utilized).
void forker(int nprocesses)
{
    pid_t pid;

    if(nprocesses > 0)
    {
        if ((pid = fork()) < 0)
        {
            perror("fork");
        }
        else if (pid == 0)
        {
            //Child stuff here
            printf("Child %d end\n", nprocesses);
        }
        else if(pid > 0)
        {
            //parent
            forker(nprocesses - 1);
        }
    }
}
int main()
{
	/*This is an example of node creation...*/
	struct node *root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);
	root->left->left = newNode(4);
	/*The code above creates a root node and branches...*/
	
	int status; //This arbitrary integer will keep track of the process status...
    int pid;    //Here we are going to keep track of the pid...
    pid=fork(); //Fork the process...
    if(pid<0)   //In the Event that we get an error...
    {
        printf("\n Error ");
        exit(1);
    }
    else if(pid==0) // Child process...(The first child process will initiate the process tree)...
    {
        //The child process is going to be reponsible for executing its process...
        //From there, the creation of the tree is handled recursively. Once all of the
        //child processes are done, proceed to the parent process...
       
       //Invoke recursive spawnNodes here...()
       
        int depthLimit = 3; // This is going to be the depth limit...
        int children = 10;  // Define number of children...
        //scanf("%d %d", &depthLimit, &children);

    spawnNodes(0, depthLimit, children, 0, 0);
        exit(0);
    }
    else // This is the code that the parent process executes...
    {
        //The parent process needs to wait while its child processes execute their functions...
        wait(&status); // It accomplishes it with the 'wait' function...
        printf("Parent process has executed, program terminating.");
        exit(1);
    }
    
	getchar();
	return 0;
}
