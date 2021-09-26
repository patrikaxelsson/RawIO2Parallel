#include <exec/execbase.h>

#include "RawIO2Parallel.h"


void *ResidentInit(__reg("d0") zero, __reg("a0") segList, __reg("a6") struct ExecBase *SysBase) {
	RawIO2Parallel(SysBase);

	// Returning NULL is technically an indication of error, but we have no need
	// to allocate anything for this patch, we have nothing allocated to return.
	// Also, for resident modules of type 0 (not a regular library, device
	// or resource), this value doesn't appear to be checked.
	return NULL;
}
