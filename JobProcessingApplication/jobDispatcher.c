#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include "apue.h"
#define MSGSZ     128



typedef struct msgbuf {				//Declare the message structure.
         long    mtype;
         char    mtext[MSGSZ];
         } message_buf;
	 
void * sort_asc(void){
      FILE* file;
      FILE* file1;
      char line1[1024];
      char line2[1024];
      char temp[512];
      file = fopen("list.txt","r+");
      file1 = fopen("output_list.txt","w+");
      int cur_line = 0;
      long p_id;
      p_id = (long)getpid();
      printf("pid %ld\n",p_id);
      
      while(fscanf(file, "%1023s",line1)==1){
	
      if (cur_line == 0){
	strcpy(line2,line1);
      } 
     
     else if(strcmp(line2,line1)>0){
      strcpy(temp,line2);
      strcpy(line2,line1);
      strcpy(line1,temp);
      fputs(line2,file1);
      printf(" %s\n", line2);
      strcpy(line2,temp);
      
    }
    else 
    { fputs(line1,file1);
    printf(" line1 %s\n", line1);
    
    }
   cur_line++ ;
    }
    printf(" %s\n", line2);
    fputs(line2,file1);
    
    fclose(file);
    fclose(file1);
}	
    
void * sort_dsc(void){
     FILE* file;
     FILE* file1;
     char line1[1024];
     char line2[1024];
     char temp[512];
      long p_id;
      p_id = (long)getpid();
      printf("pid %ld\n",p_id);
     
     file = fopen("list1.txt","r+");
     file1 = fopen("output_list2.txt","w+");
     int cur_line = 0;
 
     while(fscanf(file, "%1023s",line1)==1){
	
      if (cur_line == 0){
	strcpy(line2,line1);
      } 
     
     else if(strcmp(line2,line1)>0){
      strcpy(temp,line1);
      strcpy(line1,line2);
      strcpy(line2,temp);
      fputs(line1,file1);
      printf(" %s\n", line1);
      strcpy(line1,temp);
      
    }
    else 
    { fputs(line1,file1);
    printf("%s\n", line1);
    
    }
   cur_line++ ;
    }
    printf(" %s\n", line2);
    fputs(line2,file1);
    
    fclose(file);
    fclose(file1);
}

void * avg(void){
     FILE* file;
     FILE* file1;
     char line1[1024];
     int num=0, sum=0, avg = 0;
      long p_id;
      p_id = (long)getpid();
      printf("pid %ld\n",p_id);
     
     file = fopen("raw.txt","r+");
     file1 = fopen("output_avg.txt","w+");
     int cur_line = 0;
 
     while(fscanf(file, "%1023s",line1)==1){
	num = atoi (line1);
	sum = sum + num;
      
   cur_line++ ;
    }
   
    avg=sum/cur_line;
    printf("Average = %d \n", avg);
    fprintf(file1,"%d ",avg);
    
    fclose(file);
    fclose(file1);
}

void * med(void){
	
	FILE* file;
	FILE* file1;
	int  medarray[8];
	char line1[1024];
	file = fopen("raw.txt","r+");
	file1 = fopen("output_med.txt","w+");
	int i=0, j=0 ,t=0, median=0;
	 long p_id;
      p_id = (long)getpid();
      printf("pid %ld\n",p_id);
      
	printf("array entered  :");
     while(fscanf(file, "%1023s",line1)==1){
	medarray[i] = atoi (line1);
	printf("%d ", medarray[i]);
	i++;
       }
   for(i = 0 ; i < 8 ; i++){
     for(j = i ; j > 0 ; j--){
      if( medarray[j]<medarray[j-1]){
	t = medarray[j];
	medarray[j] = medarray[j-1];
	medarray[j-1] = t;
     }
   }
   }
   printf("\n");
   printf("array sorted :");
   for(i = 0 ; i < 8 ; i++)
    printf(" %d ", medarray[i]);
    
   printf("\n");
   median = (medarray[3]+medarray[4])/2;
   printf("Median =%d \n",median);
   fprintf(file1,"%d ",median);
    
    fclose(file);
    fclose(file1);
}

void * std(void){
      char line1[1024];
      int res=0, std = 0, i=0, sum1=0, addition = 0;
     
      FILE* file;
      FILE* file1;
      int stdarray[8];
      int stdarrayd[8];
       long p_id;
      p_id = (long)getpid();
      printf("pid %ld\n",p_id);
      
      file = fopen("raw.txt","r+");
      file1 = fopen("output_std.txt","w+");
     while(fscanf(file, "%1023s",line1)==1){			
	stdarray[i]= atoi (line1);
	sum1=sum1 + stdarray[i];
      i++ ;
    }
    sum1 = sum1 /8; 						//Calculate mean
    printf("reading value from raw file :");
   for(i = 0 ; i < 8 ; i++)
    printf(" %d ", stdarray[i]);
   
   for(i = 0 ; i < 8 ; i++){					//Substract mean from observed value
      stdarrayd[i]= stdarray[i] - sum1;
   }
   
   for(i = 0 ; i < 8 ; i++){
      stdarrayd[i]= stdarrayd[i] * stdarrayd[i];		//Square of difference
   }
   
   for(i = 0 ; i < 8 ; i++){
      addition = stdarrayd[i] + addition;			//Adding the value
   }
   res =  (addition/7);					//Divide addition by n-1 
   std = sqrt(res);
   printf("\n");
   printf("Standard deviation=  %d \n", std);
   fprintf(file1,"%d ",std);
   
   fclose(file);
   fclose(file1);
}
main()
{
    int msqid;
    key_t key;
    message_buf  rbuf;

    key = 1234;
    char* line[1024];
    
    if ((msqid = msgget(key, 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

    if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }
    
   
    if (strncmp(rbuf.mtext,"SORT_ASC",8)==0){
      printf("1st message received = %s\n", rbuf.mtext);			//Calling sort_asc()
      sort_asc();
    }
    
   else if (strncmp(rbuf.mtext,"SORT_DSC",8)==0){
     printf("2nd message received = %s\n", rbuf.mtext);			//Calling sort_dsc()
      sort_dsc();
    }							
    
    else if (strncmp(rbuf.mtext,"AVG",3)==0){
      printf("3rd message received = %s\n", rbuf.mtext);			//Calling avg()
      avg();
    }							
    
   else if (strncmp(rbuf.mtext,"MED",3)==0){
     printf("4th message received =%s\n", rbuf.mtext);			//Calling med()
      med();
    }							
    
    else if (strncmp(rbuf.mtext,"STD",3)==0){
      printf("5th message received =%s\n", rbuf.mtext);			//Calling std()
      std();
    }							
    
  
     exit(0);
}
