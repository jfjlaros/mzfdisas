#include <stdio.h>
#include <stdlib.h>
#include "console.h"
#include "disas.h"

// External variables.
extern FILE *IN;
extern word offset,
            fs,
            la,
            ea;
extern void (*function)(void);

// Private function prototypes.
byte atoh(char);

// Convert an ascii character to hex.
byte atoh(char c) {
  byte ret = (byte)c - 48;

  switch (ret) {
    case 0x11:
      return 0xa;
    case 0x12:
      return 0xb;
    case 0x13:
      return 0xc;
    case 0x14:
      return 0xd;
    case 0x15:
      return 0xe;
    case 0x16:
      return 0xf;
    case 0x31:
      return 0xa;
    case 0x32:
      return 0xb;
    case 0x33:
      return 0xc;
    case 0x34:
      return 0xd;
    case 0x35:
      return 0xe;
    case 0x36:
      return 0xf;
  }//switch
  return ret;
}//atoh

// Get a command from stdin and execute it if possible.
int getcommand(void) {
  char *command = (char *)malloc(80);
  word jumpaddr = 0x0;
  int i = 0;
  

  while (1) {
    for (i = 0; i < 79; i++)
      command[i] = 0x0a;
    printf("> ");
    fflush(stdout);
    command = fgets(command, 79, stdin);
    switch (command[0]) {
      case 'j':
        if ((command[4] != 0x0a) && (command[5] == 0x0a)) {
          jumpaddr = (word)atoh(command[1]) << 12;
          jumpaddr |= (word)atoh(command[2]) << 8;
          jumpaddr |= (word)atoh(command[3]) << 4;
          jumpaddr |= (word)atoh(command[4]);
          if ((jumpaddr >= la) && (jumpaddr <= (la + fs))) {
            fseek(IN, jumpaddr - offset, SEEK_CUR);
            offset = jumpaddr;
            printf("Address set to: %04x\n", offset);
          }
          else 
            printf("Value out of range: %04x (%04x, %04x)\n", 
                   jumpaddr, la, la + fs);
        }//if
        else
          printf("Illegal address: %s", &command[1]);
        break;
      case 'e':
        fseek(IN, 0x80 + (ea - la), SEEK_SET);
        offset = ea;
        printf("Address set to exec addr: %04x\n", offset);
        break;
      case 'l':
        fseek(IN, 0x80, SEEK_SET);
        offset = la;
        printf("Address set to load addr: %04x\n", offset);
        break;
      case 'u':
        free(command);
        return 0;
      case 'q':
        free(command);
        return 1;
      case 'h':
        printf("Recognized options:\n"
               "jxxxx : Set address to xxxx.\n"
               "e     : Go to the execution point.\n"
               "l     : Go to the load address.\n"
               "d     : Toggle dump/disassemble mode.\n"
               "u     : Disassemble or dump.\n"
               "h     : This message.\n"
               "q     : Quit.\n");
        break;
      case 'd':
        if (function == dump) {
          function = disassemble;
          printf("Disassemble mode.\n");
          break;
        }//if
        function = dump;
        printf("Dump mode.\n");
        break;
      case 0x0a:
        break;
      default:
        printf("Unrecognized command: %c\n", command[0]);
    }//switch
  }//while
  return 0;
}//getcommand
