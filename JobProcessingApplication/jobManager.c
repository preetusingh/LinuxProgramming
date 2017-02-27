#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include "apue.h"
#define MSGSZ     10

int * msgqueue(const char* );


typedef struct msgbuf {				//Declare the message structure.
         long    mtype;
         char    mtext[MSGSZ];
         } message_buf;

main(int argc, char *argv[])
{
    
    char line[1024];
    int c;

    FILE* file;					
    FILE* file1;
      if (argc != 2)
        printf("Not enough argument. File name needs to be entered: ");

      file = fopen(argv[1],"r");
      printf("file opened successfully \n");
      if(file == NULL){
        perror("Error opening the text file");
        return -1;
      }
      
      int cur_line = 0;
     
      while(fscanf(file, "%1023s",line)==1){		//reading the commands one by one 
							 //from jobDefinition.txt
      printf("contents %s ",line);
      msgqueue(line);

	  cur_line++;
     }
 
	  fclose(file);
	  
   sleep(20);
   
   file1 = fopen("result.txt","r+");
   printf("file opened \n");
    while( fgets(line,sizeof line,file1)!= NULL){
      printf("%s",line);
      
    }
     fclose(file1);
     
     return(0);
    
}

int * msgqueue(const char* line)

{	
  int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    message_buf sbuf;
    size_t buf_length;
    key = 1234;
      
(void) fprintf(stderr, "\nmsgget: Calling msgget(%#lx,%#o)\n",key, msgflg);

    if ((msqid = msgget(key, msgflg )) < 0) {
        perror("msgget");
        exit(1);
    }
    sbuf.mtype = 1;
    (void) strcpy(sbuf.mtext, line);
    buf_length = strlen(sbuf.mtext) + 1 ;
 
     // Send a message.
     
    if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
       printf ("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
        perror("msgsnd");
        exit(1);
    }

   else 
      printf("\tMessage: \"%s Sent\n", sbuf.mtext);
   
      
    return (0);
}
