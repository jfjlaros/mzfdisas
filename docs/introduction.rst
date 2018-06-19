Introduction
============

When disassembling a file, alignment can be a problem. Take the following code
for example:

::

    0000: c3 04 00                jp 0004h   ; jump to address 0004
    0003: 06                                 ; just a byte with value 06
    0004: 00                      nop        ; no operation

The disassembled code will look like this:

::

    0000: c3 04 00                jp 0004h   ; jump to address 0004
    0003: 06 00                   ld b,00    ; put 00 in register b

This problem is caused by the disassembler itself since it can not distinguish
data from code. To disassemble the example correctly the user should restart
the disassembly procedure from address ``0004`` in order to retrieve the
``nop`` instruction.
