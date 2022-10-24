# RawIO2Parallel
This patch redirects the exec.library RawIO functions to the parallel port.

Created it to make it simpler and more powerful to use a [Parallel2Serial](https://github.com/patrikaxelsson/Parallel2Serial)
converter to capture debug output - nothing has to be modified or recompiled
(often not possible) to get debug output on the parallel port instead of the
serial port.

The exec.library RawIO functions are often used for serial debug output
when you develop software. Commonly by using functions like KPrintF(),
KPutStr() etc in debug.lib, which is included in the AmigaOS NDK.

Other notable examples of software using the exec.library RawIO functions
for serial output:
 - Enforcer and MuForce when the RAWIO argument is specified
 - SnoopDos when "Log Mode" is set to "Serial Port"


## Installation

Start RawIO2Parallel from User-Startup, WBStartup, somewhere else or use
LoadModule, BlizKick, RemApollo or similar software to load it as a
resident module.


## Testing

A simplistic RawIOEcho command is included, which outputs text via the
exec.library RawIO functions. RawIO2Parallel needs to be started for it to
output to the parallel port, else it will output to the serial port.

