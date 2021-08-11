#ifndef __PARALLEL_H_
#define __PARALLEL_H_

extern void *ParallelIOInit(void);
extern char *ParallelPutChar(__reg("d0") c);
extern void *GetParallelMayGetCharAddr(void);

#endif
