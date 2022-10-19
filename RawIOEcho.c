#include <exec/exec.h>
#include <dos/dos.h>

#include <proto/exec.h>
#include <proto/dos.h>
// Redefining inline to pass string pointer in adress register to make vbcc
// emit pc-relative code, thus avoiding relocations
struct RDArgs * __pcrel_ReadArgs(__reg("a6") void *, __reg("a0") CONST_STRPTR arg_template, __reg("d2") LONG * array, __reg("d3") struct RDArgs * args)="\tmove.l\ta0,d1\n\tjsr\t-798(a6)";
#undef ReadArgs
#define ReadArgs(arg_template, array, args) __pcrel_ReadArgs(DOSBase, (arg_template), (array), (args))

#include <stdbool.h>

#include "MinimalDebug.h"

const char Version[] = "$VER: RawIOEcho 1.1 (19.10.2022) by Patrik Axelsson";

LONG RawIOEcho(void) {
	struct ExecBase *SysBase = *(struct ExecBase **) 4;
	// Variables requiring cleanup at end
	struct DosLibrary *DOSBase = NULL;
	struct RDArgs *argsResult = NULL;
	
	LONG retVal = RETURN_FAIL;
	
	DOSBase = (void *) OpenLibrary("dos.library", 36);
	if (NULL == DOSBase) {
		goto cleanup;
	}

	struct {
		const char **strings;
		const void *noLine;
	} args = { 0 };

	argsResult = ReadArgs("/M,NOLINE/S", (void *) &args, NULL);
	if (NULL == argsResult) {
		PrintFault(IoErr(), NULL);
		goto cleanup;
	}

	if (NULL != args.strings) {
		const char **strings = args.strings;
		const char *string = *strings++;
		if (NULL != string) {
			while (true) {
				KPutStr(string);
				string = *strings++;
				if (NULL == string) {
					break;
				}
				KPutChar(' ');
			}
			if (!args.noLine) {
				KPutChar('\n');
			}
		}
	}

	retVal = RETURN_OK;

cleanup:
	if (NULL != argsResult) {
		FreeArgs(argsResult);
	}
	CloseLibrary((void *) DOSBase);

	return retVal;
}

