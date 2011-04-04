/**
SLIIT GNU Public License
Copyright (c) 2011 Harsha Siriwardena
www.harshdura.com

Permission is hereby granted, free of charge, to any person obtaining 
a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation 
the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
sell copies of the Software, and to permit persons to whom the Software is furnished 
to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included 
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE 
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

	Source File : Producer.c
	Student ID  : BIT10C1-XXX
	Main method : main()
*/

/**
 * Necessary Header files and Libraries
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#define SHMSZ sizeof(int)*3

void *getInp( void *ptr );
void *copyArr;
int *ptrArr; 
int arraySize;

void *getInp(void *ptr){

    printf("Enter Size Arr : ");
    scanf ("%d", &arraySize);
    int i;
        
    pthread_mutex_t chain; 
    pthread_mutex_lock(&chain);

    for(i = 0; i < arraySize; i++) {  
      scanf("%d",ptrArr++);
    }

    pthread_mutex_unlock(&chain); 
    printf("Show Array List : ");

    for(i = 0; i < arraySize; i++) {  
      printf("%d, ",ptrArr[i]);
    }
}


void *copyArr(void *ptr) {

    if(ptrArr == NULL){
	printf("Error!\n");
	exit(1);
    } 
    
    else{
	  int shmid, i;
	  key_t key;
	  int *shm, *s;
	  key = 5678;
  
	  if((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
	      perror("shmget"); 
	      exit(1);
	  }

	  if((shm = shmat(shmid, NULL,0)) == (char *) -1) {
	      perror("shmat");
	      exit(1);
	  }

	  pthread_mutex_lock(&chain); 
	  
	  s = shm;
	  for (i = 0; i < arraySize; i++) {
	      s++ = ptrArr[i];
	  }

	  pthread_mutex_unlock(&chain); 

	  *s = NULL;
	  while (*shm != 999) {
	    sleep(1);
	    shmctl(shmid, IPC_RMID, NULL);
	    exit(0);
	  }
      }
} 

main() {
  
     pthread_t thr1,thr2;
     int  rt1, rt2;
     
     rt1 = pthread_create(&thr1, NULL, getInp, (void*)NULL);
     rt2 = pthread_create(&thr2, NULL, copyArr, (void*)NULL); 
     
     exit(0); 
}