#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "memwatch.h"
int main()
{
      char *a = NULL;
      if ((a = (char *) malloc(sizeof(char))) == NULL)
      {
          printf("malloc fail,%s.\n", strerror(errno));
          return -1;
     }
      return 0;
}      
