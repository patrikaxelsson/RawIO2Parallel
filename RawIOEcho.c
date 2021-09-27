#include <exec/exec.h>
#include <dos/dos.h>
#include <dos/dosextens.h>

#include <proto/exec.h>
#include <proto/dos.h>

#include <clib/debug_protos.h>

#include <stdbool.h>


const char Version[] = "$VER: RawIOEcho 1.1 (27.9.2021) by Patrik Axelsson";

LONG RawIOEcho(void) {
	struct ExecBase *SysBase = *(struct ExecBase **) 4;
	// Variables possibly requiring cleanup at end
	struct DosLibrary *DOSBase = NULL;
	struct RDArgs *argsResult = NULL;
	
	LONG retVal = RETURN_FAIL;
	
	DOSBase = (void *) OpenLibrary("dos.library", 36);
	if (NULL == DOSBase) {
		goto cleanup;
	}

	void *argsValues[2] = {0};
	argsResult = ReadArgs("OUTPUTSTRING/M,NOLINE/S", (void *) argsValues, NULL);
	if(NULL == argsResult) {
		PrintFault(IoErr(), NULL);
		goto cleanup;
	}
	const char **outputStringArray = argsValues[0];
	const bool noLine = NULL != argsValues[1];
	
	bool firstOutput = true;
	const char *outputString;
	while (NULL != (outputString = *outputStringArray++)) {
		if (!firstOutput) {
			KPutChar(' ');
		}
		KPutStr(outputString);
		firstOutput = false;
	}
	if (!noLine) {
		KPutChar('\n');
	}

	retVal = RETURN_OK;

cleanup:
	if (NULL != argsResult) {
		FreeArgs(argsResult);
	}
	CloseLibrary((void *) DOSBase);

	return retVal;
}

