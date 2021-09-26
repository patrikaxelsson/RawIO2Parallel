#ifndef __PARALLEL_H_
#define __PARALLEL_H_

void *ParallelIOInit(void);
char *ParallelPutChar(__reg("d0") c);
void *GetParallelMayGetCharAddr(void);

#endif
