#include <exec/exec.h>
#include <proto/exec.h>

#include "Parallel.h"

extern LONG LVORawIOInit;
extern LONG LVORawPutChar;
extern LONG LVORawMayGetChar;

// Putting SysBase in a6 is not necessary here, it is just to make vbcc
// produce simpler/better code.
void RawIO2Parallel(__reg("a6") struct ExecBase *SysBase) {
	SetFunction((void *) SysBase, &LVORawIOInit, (void *) &ParallelIOInit);
	SetFunction((void *) SysBase, &LVORawPutChar, (void *) &ParallelPutChar);
	SetFunction((void *) SysBase, &LVORawMayGetChar, (void *) GetParallelMayGetCharAddr());
}

