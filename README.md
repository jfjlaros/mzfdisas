# MZF Disassembler
This version of a Z80 disassembler works directly on a MZF-file (or M12, or
MZT; simple rename the file to MZF).

If you start the disassembler from the Windows-DOS prompt (The program will not
work under plain DOS!) by

    mzfdisas myprog.mzf

the contents of the header and the addresses in the header are displayed
automatically:

![Header display](doc/mzfdisass1.gif)

![Available commands](doc/mzfdisass2.gif)

There are several commands available.

The command "e" presets the disassembler to the execution address ("l" will use
the load address) and "d" toggles between the disassemble mode and the dump
mode. "u" performs the mode previously set.

![Dump mode output](doc/mzfdisass3.gif)

Dump mode

![Disassembler mode output](doc/mzfdisass4.gif)

Disassemble mode

A further "u" shows the next page.

Download the operation manual (PDF, 38kb, 4 pages).

Download this utility now (50kb, all Windows). The sourcecode is included.
Download this utility now (47kb, LINUX). The sourcecode is included.
