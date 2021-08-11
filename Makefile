all: RawIO2Parallel RawEcho 

RawIO2Parallel: RawIO2Parallel.c Parallel.asm Parallel.h EndFunction.c EndFunction.h Makefile
	vc +aos68k -D__NOLIBBASE__ -nostdlib -c99 -O1 -sc -lamiga -lddebug -o $@ $< Parallel.asm EndFunction.c

RawEcho: RawEcho.c Makefile
	vc +aos68k -D__NOLIBBASE__ -nostdlib -c99 -O1 -sc -lamiga -ldebug -o $@ $<

clean:
	$(RM) RawIO2Parallel RawEcho

