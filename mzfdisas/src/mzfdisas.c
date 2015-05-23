/*
 * mzfdisas by: Jeroen F. J. Laros.
 *
 * Last change on: Sep 7 2003.
 * 
 * This program is freeware and may be used without paying any registration 
 * fees. It may be distributed freely provided it is done so using the 
 * original, unmodified version. Usage of parts of the source code is granted, 
 * provided the author is referenced. For private use only. Re-selling or any 
 * commercial use of this program or parts of it is strictly forbidden. The
 * author is not responsible for any damage or data loss as a result of using 
 * this program.
 */
#include <stdio.h>
#include <stdlib.h>
#include "console.h"
#include "disas.h"

// Global variables.
FILE *IN = NULL;
word offset = 0x0,
     fs = 0x0,
     la = 0x0,
     ea = 0x0;
void (*function)(void) = disassemble;

// Private funcion prototypes.
void quit(void); 

// Private funcions.
void quit(void) {
  fclose(IN);
  exit(0);
}//quit

int main(int argc, char **argv) {
  boolean ep = FALSE;
  int i = 0;

  if (argc < 2) {
    printf("Usage: %s filename\n", argv[0]);
    return 1;
  }//if

  IN = fopen(argv[1], "rb");
  if (!IN) {
    printf("Could not open file %s for reading.\n", argv[1]);
    return 2;
  }//if

  printf("Mzfdisas\n");
  for (i = 0; i < 8; i++) {
    printf("%04x: ", offset);
    dump();
    printf("\n");
  }//for
  
  fseek(IN, 0, SEEK_SET);
  readheader();
  printf("Header information:\n");
  printf("Filesize          : %04x\n", fs);
  printf("Load address      : %04x\n", la);
  printf("Execution address : %04x\n", ea);
        
  offset = la;
  while (1) {
    if (getcommand())
      break;
    for (i = 0; i < 22; i++) 
      if (!feof(IN)) {
        if (offset == ea)
          ep = TRUE;
        printf("%04x: ", offset);
        function();
        if (ep && (function == disassemble)) {
          printf("		--- Execution point ---");
          ep = FALSE;
        }//if
        printf("\n");
      }//if
  }//while

  quit();

  return 0;
}//main
