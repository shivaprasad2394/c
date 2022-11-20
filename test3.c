/**
 * C program to find first occurrence of a word in file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1000

//pthread_t tid[2];
//pthread_mutex_t lock;
typedef struct arg_struct
{
    FILE *fptr;
    char word[50];
    int line;
    int col;
} args;

/* Function declarations */
void indexOf(FILE *fptr, const char *word, int *line, int *col);

void execute(const char *word){
    FILE *fp;   /* file pointer*/
    char fName[20];
 
    printf("Enter file name to create :");
    scanf("%s",fName);
 
    /*creating (open) a file, in “w”: write mode*/
    fp=fopen(fName,"w");
    /*check file created or not*/
    if(fp==NULL)
    {
        printf("File does not created!!!");
        exit(0); /*exit from program*/
    }
 
    printf("File created successfully.");
    printf("Enter contents to store in file : \n");
    //fgets(data, DATA_SIZE, stdin);

    /* Write data to file */
    //fputs(data, fp);

    /* Close file to save file data */
    fclose(fp);

    /* Success message */
    printf("File created and saved successfully. :) \n");
char *gcc_argv[] = {"gcc",
                    "-o",
                    "/abc/write.o",
                    "-c",
                    "/abc/write.c",
                    NULL};

execv("/usr/bin/gcc", gcc_argv);
}
void* func(void* arg)
{
    char str[BUFFER_SIZE];
    char *pos;

   
   //printf("Thread\n");
   printf("start -->%s\n", ((args *)arg)->word);
    ((args *)arg)->line = -1;
    ((args *)arg)->col  = -1;
   //printf("%d\n", ((args *)arg)->line);
   //printf("%d\n", ((args *)arg)->col);
 //  printf("%s\n", ((args *)arg)->fptr);
	// detach the current thread
	// from the calling thread
    while ((fgets(str, BUFFER_SIZE, ((args *)arg)->fptr)) != NULL)
    {
        ((args *)arg)->line += 1;
// Find first occurrence of word in str
        pos = strstr(str, ((args *)arg)->word);

        if (pos != NULL)
        {
            // First index of word in str is 
            // Memory address of pos - memory
            // address of str.
            ((args *)arg)->col = (pos - str);
            break;
        }
    }

    // If word is not found then set line to -1
    if (((args *)arg)->col == -1)
        ((args *)arg)->line = -1;

	if (((args *)arg)->line != -1)
        printf("'%s' found at line: %d, col: %d\n", ((args *)arg)->word, ((args *)arg)->line + 1, ((args *)arg)->col + 1);
    else
        printf("'%s' does not exists.", ((args *)arg)->word);
        
    while ((fgets(str, BUFFER_SIZE, ((args *)arg)->fptr)) != NULL)
    {
	printf("%s", str);
	sleep(3);
    if (strstr(str, "sTOp")) break;
    }


        
    // Close file
    fclose(((args *)arg)->fptr);

	//pthread_detach(pthread_self());??

	printf("exit thread\n");

	// exit the current thread
	pthread_exit(NULL);
	//return NULL;
}

void fun(FILE *fptr, const char *word, int *line, int *col)
{
	pthread_t ptid;
	args *Allen=NULL;
    if (NULL == (Allen = (args *)malloc(sizeof(args))))
    printf("nope");
    else{
    printf("ok ok ok");
    strcpy(Allen->word, word);
    Allen->line = *line;
    Allen->col = *col;
    Allen->fptr=fptr;
	}// Creating a new thread
	pthread_create(&ptid, NULL, &func, (void *)Allen);
	printf("This line may be printed"
		" before thread terminates\n");

	// The following line terminates
	// the thread manually
	// pthread_cancel(ptid);

	// Compare the two threads created
	if(pthread_equal(ptid, pthread_self()))
		printf("Threads are equal\n");
	else
		printf("Threads are not equal\n");


	// Waiting for the created thread to terminate
	pthread_join(ptid, NULL);

	printf("This line will be printed"
		" after thread ends\n");
    free(Allen);
	//pthread_exit(NULL);
}

int main()
{
    FILE *fptr;
    char path[100];
    pid_t p;
    char word[50];
    int line, col;


    /* Input file path */
    printf("Enter file path: ");
    scanf("%s", path);
	
    
   int value,choice=0;
   int quit = 0; 
	while(!quit){
	
		printf("enter the choice\n1)c\n2)c++\n3)Linux system programmming\n4)Wifi\n5)Gps\n6)programsforinterview\n7)Execute\n8)exit\nEnter your choice:-");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: printf("1)Intro\n2)Compilation\n3)**Macros**\n4)**Inline\n5)storage classes\n6)**const\n7)**Typedef\n8)Enum\n9)**volatile keyword\n10)**pointers\n11)pointer**increment\n12)pointer**to**an**Array\n13)char**pointers\n14)**malloc\n15)**Function pointer\n16)Structures**\n17)bits**op\n18)string**ops\n");

    		printf("Enter the Topic to Learn in file: ");
			scanf("%s", word);
/* Try to open file */
    fptr = fopen(path, "r");

/* Exit if file not opened successfully */
    if (fptr == NULL)
    {
        printf("Unable to open file.\n");
        printf("Please check you have read/write previleges.\n");
        exit(EXIT_FAILURE);
    }		
		  p = fork();
		  if (p < 0){
			   fprintf(stderr, "fork Failed" );
			   return 1;
		  }
		  // Parent process
		  else if (p > 0)
		  {
		    sleep(4);
			wait(NULL);
			break;
		    }
		  // child process
		  else
		  {
			indexOf(fptr, word, &line, &col);
   			exit(0);
		  }
			//break;
			case 2: printf("To-Do\n");
				//scanf("%d",&value); 
				//create_after(value);// code to be executed if n = 2;
				//print_list();        
				break;
			case 3: printf("1)Shared**memory\n2)SHAREDMEMORY-WRITER\n3)SHAREDMEMORY-READER\n4)Message-Queues\n5)MESSAGEQUEUE-WRITER\n6)MESSAGEQUEUE-READERPROCESS\n7)**fork\n8)FIFO/Named-Pipes\n9)Pthread**");
    		printf("Enter the Topic to Learn in file: ");
			scanf("%s", word);
/* Try to open file */
		    fptr = fopen(path, "r");
/* Exit if file not opened successfully */
    if (fptr == NULL)
    {
        printf("Unable to open file.\n");
        printf("Please check you have read/write previleges.\n");
        exit(EXIT_FAILURE);
    }        
    printf("calling FUN: ");
    			fun(fptr, word, &line, &col);
				break;
			/*case 4: print_list();// code to be executed if n = 4
				break;
			case 5:
				printf("enter the value and position\n");
				scanf("%d",&value);
				delete(value);// code to be executed if n = 5
				print_list();
				break;*/
			case 6: // code to be executed if n = 6
		printf("enter the choice\n1)WAP-min/max\n2)reverse-string\n3)sort-asending\n4)sort-desending\n5)Remove-an-element-in-array\n6)fun-linked-list\n7)Binary-search-tree\n8)duplicate-array-element\n9)frequency-of-each-element\n10)strstr_implemenatation\nPaste your choice here:-");
			printf("Enter the Topic to Learn in file: ");
			scanf("%s", word);
/* Try to open file */
		    fptr = fopen(path, "r");
/* Exit if file not opened successfully */
    if (fptr == NULL)
    {
        printf("Unable to open file.\n");
        printf("Please check you have read/write previleges.\n");
        exit(EXIT_FAILURE);
    }        
    			fun(fptr, word, &line, &col);
				break;
			case 7:
			printf("To-Do: ");
			//scanf("%s", word);
			//execute(word);
			break;
			case 8: //exit_fun();// code to be executed if n is 7
				quit=1;
				break;
			default: printf("kindly enter a valid option\n"); 
		}

	}

    return 0;
}



/**
 * Finds, first index of a word in given file. First index is represented
 * using line and column.
 */
void indexOf(FILE *fptr, const char *word, int *line, int *col)
{
    char str[BUFFER_SIZE];
    char *pos;
    *line = -1;
    *col  = -1;


    while ((fgets(str, BUFFER_SIZE, fptr)) != NULL)
    {
        *line += 1;
// Find first occurrence of word in str
        pos = strstr(str, word);

        if (pos != NULL)
        {
            // First index of word in str is 
            // Memory address of pos - memory
            // address of str.
            *col = (pos - str);
            break;
        }
    }

    while ((fgets(str, BUFFER_SIZE, fptr)) != NULL)
    {
	printf("%s", str);
	sleep(2);
    if (strstr(str, "sTOp")) break;
    }

    // If word is not found then set line to -1
    if (*col == -1)
        *line = -1;

	if (*line != -1)
        printf("'%s' found at line: %d, col: %d\n", word, *line + 1, *col + 1);
    else
        printf("'%s' does not exists.", word);
        
    // Close file
    fclose(fptr);  
}
