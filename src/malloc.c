#include <stdlib.h>
#include <time.h>

extern void *__real_malloc(size_t size);

void  *__wrap_malloc(size_t size)
{
  srand(time(NULL));
  if (rand() % 5)
    return NULL;
  return __real_malloc(size);
}

/*
  Add this to the link flags and compile:
  -Wl,--wrap=malloc
*/