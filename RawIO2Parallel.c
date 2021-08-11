#include <exec/exec.h>
#include <dos/dos.h>
#include <dos/dosextens.h>
#include <workbench/startup.h>

#include <proto/exec.h>
#include <proto/dos.h>

#include <stdbool.h>

#include "Parallel.h"
#include "EndFunction.h"


static void RawIO2Parallel(struct ExecBase *SysBase);

const struct Resident ROMTag = {
	.rt_MatchWord = RTC_MATCHWORD,
	.rt_MatchTag  = (struct Resident *) &ROMTag,
	.rt_EndSkip   = (void *) &EndFunction,
	.rt_Flags     = RTF_COLDSTART,
	.rt_Version   = 1,
	.rt_Type      = 0, // Nothing, we just want to run rt_init
	.rt_Pri       = 0, // Need to be initialized later than exec obviously
	.rt_Name      = "RawIO2Parallel",
	.rt_IdString  = "RawIO2Parallel 1.0 (10.8.2021) by Patrik Axelsson",
	.rt_Init      = (void *) &RawIO2Parallel
};

LONG Startup(void) {
	struct ExecBase *SysBase = *(struct ExecBase **) 4;

	struct WBStartup *wbStartupMsg = NULL;
	struct Process *thisProcess = (struct Process *) FindTask(NULL);
	struct CommandLineInterface *cli = (void *) BADDR(thisProcess->pr_CLI);
	if (NULL == cli) {
		// If started from Workbench, get the startup message
		WaitPort(&thisProcess->pr_MsgPort);
		wbStartupMsg = (void *) GetMsg(&thisProcess->pr_MsgPort);
		// Make our seglist stay in memory after exit, so patch code can
		// continue to execute
		wbStartupMsg->sm_Segment = NULL;
	}
	else {
		// Make our seglist stay in memory after exit, so patch code can
		// continue to execute
		cli->cli_Module = NULL;
	}
	
	RawIO2Parallel(SysBase);

	if(NULL != wbStartupMsg) {
		Forbid();
		// If started from Workbench, reply to the startup message
		ReplyMsg((struct Message *) wbStartupMsg);
	}

	return RETURN_OK;
}

extern LONG LVORawIOInit;
extern LONG LVORawPutChar;
extern LONG LVORawMayGetChar;

static void RawIO2Parallel(__reg("a6") struct ExecBase *SysBase) {
	SetFunction((void *) SysBase, &LVORawIOInit, (void *) &ParallelIOInit);
	SetFunction((void *) SysBase, &LVORawPutChar, (void *) &ParallelPutChar);
	SetFunction((void *) SysBase, &LVORawMayGetChar, (void *) GetParallelMayGetCharAddr());
}

