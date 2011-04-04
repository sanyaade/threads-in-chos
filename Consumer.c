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

	Source File : Consumer.c
	Student ID  : BIT10C1-XXX
	Main method : main()
*/

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#define SHMSZ sizeof(int)*3

main()
{
  int shmid, i=0;
  key_t key;
  key = 5678;
  int *shm, *s;
  
  if((shmid = shmget(key, SHMSZ, 0666)) < 0) {
      perror("shmget");
      exit(1);
  }

  if ((shm = shmat(shmid, NULL,0)) == (char *) -1) {
      perror("shmat");
      exit(1);
  }
  
  int numArray[]=0;

  for (s = shm; *s != NULL; s++) {
	numArray[i++] = *s;
  }
  
  int j, sum=0;
  for(j = 0;j < i;j++){
	printf("%d, ",numArray[j]);
	sum += numArray[i];
  }
  
  printf("\nSum : %d", sum);
  *shm = '*';
  exit(0);
}
