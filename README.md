# RawIO2Parallel
This patch redirects the exec.library RawIO functions to the parallel port.
Created it to make it simpler and more powerful to use a [Parallel2Serial](https://github.com/patrikaxelsson/Parallel2Serial)
converter to capture debug output - nothing has to be modified or recompiled
(often not possible) to get debug output on the parallel port instead of the
serial port.

Normally, what would be redirected is the debug output produced when you run
software which is linked with debug.lib from the AmigaOS NDK and uses its
output functions, but any software which uses the exec.library RawIO
functions to output text on the serial port will be redirected. For example
SnoopDos does this.


## Installation

Start RawIO2Parallel from User-Startup, WBStartup, somewhere else or use
LoadModule, BlizKick, RemApollo or similar software to load it as a
resident module.


## Testing

Included a simplistic RawEcho command, which outputs text via the
exec.library RawIO functions. RawIO2Parallel needs to be started for it to
output to the parallel port, else it will output to the serial port.

