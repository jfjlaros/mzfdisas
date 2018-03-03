#include <stdio.h>
#include <stdlib.h>
#include "console.h"
#include "disas.h"

// Global variables.
extern FILE *IN;
extern word offset,
            fs,
            la,
            ea;

// Private function prototypes.
byte readbyte(void),
     readsbyte(void);
char translate(byte);
void disasCB(void),
     disasDDCB(void),
     disasDD(void),
     disasED(void),
     disasFDCB(void),
     disasFD(void);

// Private funcions.
byte readbyte(void) {
  byte ret = 0x0;

  if (!fread(&ret, 1, sizeof(byte), IN)) {
    printf("   ");
    return 0x0;
  }//if
  printf("%02x ", ret);
  offset++;
  return ret;
}//readbyte

byte readsbyte(void) {
  byte ret = 0x0;

  if (!fread(&ret, 1, sizeof(byte), IN)) {
    return 0x0;
  }//if
  offset++;
  return ret;
}//readsbyte

char translate(byte c) {
  if ((c > 0x1f) && (c < 0x5E))
    return c;
  switch (c) {
    case 0x7b:
      return 0xb0;
    case 0x80:
      return '}';
    case 0x8b:
      return '^';
    case 0x92:
      return 'e';
    case 0x93:
      return '`';
    case 0x94:
      return '~';
    case 0x96:
      return 't';
    case 0x97:
      return 'g';
    case 0x98:
      return 'h';
    case 0x9a:
      return 'b';
    case 0x9b:
      return 'x';
    case 0x9c:
      return 'd';
    case 0x9d:
      return 'r';
    case 0x9e:
      return 'p';
    case 0x9f:
      return 'c';
    case 0xa0:
      return 'q';
    case 0xa1:
      return 'a';
    case 0xa2:
      return 'z';
    case 0xa3:
      return 'w';
    case 0xa4:
      return 's';
    case 0xa5:
      return 'u';
    case 0xa6:
      return 'i';
    case 0xa8:
      return 0xd6;
    case 0xa9:
      return 'k';
    case 0xaa:
      return 'f';
    case 0xab:
      return 'v';
    case 0xad:
      return 0xfc;
    case 0xae:
      return 0xdf;
    case 0xaf:
      return 'j';
    case 0xb0:
      return 'n';
    case 0xb2:
      return 0xdc;
    case 0xb3:
      return 'm';
    case 0xb7:
      return 'o';
    case 0xb8:
      return 'l';
    case 0xb9:
      return 0xc4;
    case 0xba:
      return 0xd6;
    case 0xbb:
      return 0xe4;
    case 0xbd:
      return 'y';
    case 0xbe:
      return '{';
    case 0xcf:
      return '_';
    case 0xd7:
      return 0xaf;
    case 0xfc:
      return 0xa3;
    case 0xff:
      return 0x1c;
  }//switch
  return '.';
}//translate

void readheader(void) {
  byte i = 0x0;
  word b = 0x0;

  for (i = 0x0; i < 0x80; i++) {
    b = readsbyte();
    if (i == 0x12)
      fs = b;
    if (i == 0x13)
      fs |= b << 8;
    if (i == 0x14)
      la = b;
    if (i == 0x15)
      la |= b << 8;
    if (i == 0x16)
      ea = b;
    if (i == 0x17)
      ea |= b << 8;
  }//for
}//readheader

void dump(void) {
  char *readable = (char *)malloc(17 * sizeof(char));
  int i = 0;
  
  readable[16] = '\0';
  for (i = 0; i < 16; i++) 
    if (feof(IN)) {
      readable[i - 1] = '\0';
      printf("   ");
    }//if
    else
      readable[i] = translate(readbyte());
  printf("   %s", readable);
}//dump

void disasCB(void) {
  byte b = readbyte();

  switch (b) {
    case 0x00:
      printf("         rlc b");
      break;
    case 0x01:
      printf("         rlc c");
      break;
    case 0x02:
      printf("         rlc d");
      break;
    case 0x03:
      printf("         rlc e");
      break;
    case 0x04:
      printf("         rlc h");
      break;
    case 0x05:
      printf("         rlc l");
      break;
    case 0x06:
      printf("         rlc (hl)");
      break;
    case 0x07:
      printf("         rlc a");
      break;
    case 0x08:
      printf("         rrc b");
      break;
    case 0x09:
      printf("         rrc c");
      break;
    case 0x0A:
      printf("         rrc d");
      break;
    case 0x0B:
      printf("         rrc e");
      break;
    case 0x0C:
      printf("         rrc h");
      break;
    case 0x0D:
      printf("         rrc l");
      break;
    case 0x0E:
      printf("         rrc (hl)");
      break;
    case 0x0F:
      printf("         rrc a");
      break;
    case 0x10:
      printf("         rl b");
      break;
    case 0x11:
      printf("         rl c");
      break;
    case 0x12:
      printf("         rl d");
      break;
    case 0x13:
      printf("         rl e");
      break;
    case 0x14:
      printf("         rl h");
      break;
    case 0x15:
      printf("         rl l");
      break;
    case 0x16:
      printf("         rl (hl)");
      break;
    case 0x17:
      printf("         rl a");
      break;
    case 0x18:
      printf("         rr b");
      break;
    case 0x19:
      printf("         rr c");
      break;
    case 0x1A:
      printf("         rr d");
      break;
    case 0x1B:
      printf("         rr e");
      break;
    case 0x1C:
      printf("         rr h");
      break;
    case 0x1D:
      printf("         rr l");
      break;
    case 0x1E:
      printf("         rr (hl)");
      break;
    case 0x1F:
      printf("         rr a");
      break;
    case 0x20:
      printf("         sla b");
      break;
    case 0x21:
      printf("         sla c");
      break;
    case 0x22:
      printf("         sla d");
      break;
    case 0x23:
      printf("         sla e");
      break;
    case 0x24:
      printf("         sla h");
      break;
    case 0x25:
      printf("         sla l");
      break;
    case 0x26:
      printf("         sla (hl)");
      break;
    case 0x27:
      printf("         sla a");
      break;
    case 0x28:
      printf("         sra b");
      break;
    case 0x29:
      printf("         sra c");
      break;
    case 0x2A:
      printf("         sra d");
      break;
    case 0x2B:
      printf("         sra e");
      break;
    case 0x2C:
      printf("         sra h");
      break;
    case 0x2D:
      printf("         sra l");
      break;
    case 0x2E:
      printf("         sra (hl)");
      break;
    case 0x2F:
      printf("         sra a");
      break;
    case 0x30:
      printf("         sl1 b              ; undocumented");
      break;
    case 0x31:
      printf("         sl1 c              ; undocumented");
      break;
    case 0x32:
      printf("         sl1 c              ; undocumented");
      break;
    case 0x33:
      printf("         sl1 d              ; undocumented");
      break;
    case 0x34:
      printf("         sl1 h              ; undocumented");
      break;
    case 0x35:
      printf("         sl1 l              ; undocumented");
      break;
    case 0x36:
      printf("         sl1 (hl)           ; undocumented");
      break;
    case 0x37:
      printf("         sl1 a              ; undocumented");
      break;
    case 0x38:
      printf("         srl b");
      break;
    case 0x39:
      printf("         srl c");
      break;
    case 0x3A:
      printf("         srl d");
      break;
    case 0x3B:
      printf("         srl e");
      break;
    case 0x3C:
      printf("         srl h");
      break;
    case 0x3D:
      printf("         srl l");
      break;
    case 0x3E:
      printf("         srl (hl)");
      break;
    case 0x3F:
      printf("         srl a");
      break;
    case 0x40:
      printf("         bit 0,b");
      break;
    case 0x41:
      printf("         bit 0,c");
      break;
    case 0x42:
      printf("         bit 0,d");
      break;
    case 0x43:
      printf("         bit 0,e");
      break;
    case 0x44:
      printf("         bit 0,h");
      break;
    case 0x45:
      printf("         bit 0,l");
      break;
    case 0x46:
      printf("         bit 0,(hl)");
      break;
    case 0x47:
      printf("         bit 0,a");
      break;
    case 0x48:
      printf("         bit 1,b");
      break;
    case 0x49:
      printf("         bit 1,c");
      break;
    case 0x4A:
      printf("         bit 1,d");
      break;
    case 0x4B:
      printf("         bit 1,e");
      break;
    case 0x4C:
      printf("         bit 1,h");
      break;
    case 0x4D:
      printf("         bit 1,l");
      break;
    case 0x4E:
      printf("         bit 1,(hl)");
      break;
    case 0x4F:
      printf("         bit 1,a");
      break;
    case 0x50:
      printf("         bit 2,b");
      break;
    case 0x51:
      printf("         bit 2,c");
      break;
    case 0x52:
      printf("         bit 2,d");
      break;
    case 0x53:
      printf("         bit 2,e");
      break;
    case 0x54:
      printf("         bit 2,h");
      break;
    case 0x55:
      printf("         bit 2,l");
      break;
    case 0x56:
      printf("         bit 2,(hl)");
      break;
    case 0x57:
      printf("         bit 2,a");
      break;
    case 0x58:
      printf("         bit 3,b");
      break;
    case 0x59:
      printf("         bit 3,c");
      break;
    case 0x5A:
      printf("         bit 3,d");
      break;
    case 0x5B:
      printf("         bit 3,e");
      break;
    case 0x5C:
      printf("         bit 3,h");
      break;
    case 0x5D:
      printf("         bit 3,l");
      break;
    case 0x5E:
      printf("         bit 3,(hl)");
      break;
    case 0x5F:
      printf("         bit 3,a");
      break;
    case 0x60:
      printf("         bit 4,b");
      break;
    case 0x61:
      printf("         bit 4,c");
      break;
    case 0x62:
      printf("         bit 4,d");
      break;
    case 0x63:
      printf("         bit 4,e");
      break;
    case 0x64:
      printf("         bit 4,h");
      break;
    case 0x65:
      printf("         bit 4,l");
      break;
    case 0x66:
      printf("         bit 4,(hl)");
      break;
    case 0x67:
      printf("         bit 4,a");
      break;
    case 0x68:
      printf("         bit 5,b");
      break;
    case 0x69:
      printf("         bit 5,c");
      break;
    case 0x6A:
      printf("         bit 5,d");
      break;
    case 0x6B:
      printf("         bit 5,e");
      break;
    case 0x6C:
      printf("         bit 5,h");
      break;
    case 0x6D:
      printf("         bit 5,l");
      break;
    case 0x6E:
      printf("         bit 5,(hl)");
      break;
    case 0x6F:
      printf("         bit 5,a");
      break;
    case 0x70:
      printf("         bit 6,b");
      break;
    case 0x71:
      printf("         bit 6,c");
      break;
    case 0x72:
      printf("         bit 6,d");
      break;
    case 0x73:
      printf("         bit 6,e");
      break;
    case 0x74:
      printf("         bit 6,h");
      break;
    case 0x75:
      printf("         bit 6,l");
      break;
    case 0x76:
      printf("         bit 6,(hl)");
      break;
    case 0x77:
      printf("         bit 6,a");
      break;
    case 0x78:
      printf("         bit 7,b");
      break;
    case 0x79:
      printf("         bit 7,c");
      break;
    case 0x7A:
      printf("         bit 7,d");
      break;
    case 0x7B:
      printf("         bit 7,e");
      break;
    case 0x7C:
      printf("         bit 7,h");
      break;
    case 0x7D:
      printf("         bit 7,l");
      break;
    case 0x7E:
      printf("         bit 7,(hl)");
      break;
    case 0x7F:
      printf("         bit 7,a");
      break;
    case 0x80:
      printf("         res 0,b");
      break;
    case 0x81:
      printf("         res 0,c");
      break;
    case 0x82:
      printf("         res 0,d");
      break;
    case 0x83:
      printf("         res 0,e");
      break;
    case 0x84:
      printf("         res 0,h");
      break;
    case 0x85:
      printf("         res 0,l");
      break;
    case 0x86:
      printf("         res 0,(hl)");
      break;
    case 0x87:
      printf("         res 0,a");
      break;
    case 0x88:
      printf("         res 1,b");
      break;
    case 0x89:
      printf("         res 1,c");
      break;
    case 0x8A:
      printf("         res 1,d");
      break;
    case 0x8B:
      printf("         res 1,e");
      break;
    case 0x8C:
      printf("         res 1,h");
      break;
    case 0x8D:
      printf("         res 1,l");
      break;
    case 0x8E:
      printf("         res 1,(hl)");
      break;
    case 0x8F:
      printf("         res 1,a");
      break;
    case 0x90:
      printf("         res 2,b");
      break;
    case 0x91:
      printf("         res 2,c");
      break;
    case 0x92:
      printf("         res 2,d");
      break;
    case 0x93:
      printf("         res 2,e");
      break;
    case 0x94:
      printf("         res 2,h");
      break;
    case 0x95:
      printf("         res 2,l");
      break;
    case 0x96:
      printf("         res 2,(hl)");
      break;
    case 0x97:
      printf("         res 2,a");
      break;
    case 0x98:
      printf("         res 3,b");
      break;
    case 0x99:
      printf("         res 3,c");
      break;
    case 0x9A:
      printf("         res 3,d");
      break;
    case 0x9B:
      printf("         res 3,e");
      break;
    case 0x9C:
      printf("         res 3,h");
      break;
    case 0x9D:
      printf("         res 3,l");
      break;
    case 0x9E:
      printf("         res 3,(hl)");
      break;
    case 0x9F:
      printf("         res 3,a");
      break;
    case 0xA0:
      printf("         res 4,b");
      break;
    case 0xA1:
      printf("         res 4,c");
      break;
    case 0xA2:
      printf("         res 4,d");
      break;
    case 0xA3:
      printf("         res 4,e");
      break;
    case 0xA4:
      printf("         res 4,h");
      break;
    case 0xA5:
      printf("         res 4,l");
      break;
    case 0xA6:
      printf("         res 4,(hl)");
      break;
    case 0xA7:
      printf("         res 4,a");
      break;
    case 0xA8:
      printf("         res 5,b");
      break;
    case 0xA9:
      printf("         res 5,c");
      break;
    case 0xAA:
      printf("         res 5,d");
      break;
    case 0xAB:
      printf("         res 5,e");
      break;
    case 0xAC:
      printf("         res 5,h");
      break;
    case 0xAD:
      printf("         res 5,l");
      break;
    case 0xAE:
      printf("         res 5,(hl)");
      break;
    case 0xAF:
      printf("         res 5,a");
      break;
    case 0xB0:
      printf("         res 6,b");
      break;
    case 0xB1:
      printf("         res 6,c");
      break;
    case 0xB2:
      printf("         res 6,d");
      break;
    case 0xB3:
      printf("         res 6,e");
      break;
    case 0xB4:
      printf("         res 6,h");
      break;
    case 0xB5:
      printf("         res 6,l");
      break;
    case 0xB6:
      printf("         res 6,(hl)");
      break;
    case 0xB7:
      printf("         res 6,a");
      break;
    case 0xB8:
      printf("         res 7,b");
      break;
    case 0xB9:
      printf("         res 7,c");
      break;
    case 0xBA:
      printf("         res 7,d");
      break;
    case 0xBB:
      printf("         res 7,e");
      break;
    case 0xBC:
      printf("         res 7,h");
      break;
    case 0xBD:
      printf("         res 7,l");
      break;
    case 0xBE:
      printf("         res 7,(hl)");
      break;
    case 0xBF:
      printf("         res 7,a");
      break;
    case 0xC0:
      printf("         set 0,b");
      break;
    case 0xC1:
      printf("         set 0,c");
      break;
    case 0xC2:
      printf("         set 0,d");
      break;
    case 0xC3:
      printf("         set 0,e");
      break;
    case 0xC4:
      printf("         set 0,h");
      break;
    case 0xC5:
      printf("         set 0,l");
      break;
    case 0xC6:
      printf("         set 0,(hl)");
      break;
    case 0xC7:
      printf("         set 0,a");
      break;
    case 0xC8:
      printf("         set 1,b");
      break;
    case 0xC9:
      printf("         set 1,c");
      break;
    case 0xCA:
      printf("         set 1,d");
      break;
    case 0xCB:
      printf("         set 1, e");
      break;
    case 0xCC:
      printf("         set 1,h");
      break;
    case 0xCD:
      printf("         set 1,l");
      break;
    case 0xCE:
      printf("         set 1,(hl)");
      break;
    case 0xCF:
      printf("         set 1,a");
      break;
    case 0xD0:
      printf("         set 2,b");
      break;
    case 0xD1:
      printf("         set 2,c");
      break;
    case 0xD2:
      printf("         set 2,d");
      break;
    case 0xD3:
      printf("         set 2,e");
      break;
    case 0xD4:
      printf("         set 2,h");
      break;
    case 0xD5:
      printf("         set 2,l");
      break;
    case 0xD6:
      printf("         set 2,(hl)");
      break;
    case 0xD7:
      printf("         set 2,a");
      break;
    case 0xD8:
      printf("         set 3,b");
      break;
    case 0xD9:
      printf("         set 3,c");
      break;
    case 0xDA:
      printf("         set 3,d");
      break;
    case 0xDB:
      printf("         set 3,e");
      break;
    case 0xDC:
      printf("         set 3,h");
      break;
    case 0xDD:
      printf("         set 3,l");
      break;
    case 0xDE:
      printf("         set 3,(hl)");
      break;
    case 0xDF:
      printf("         set 3,a");
      break;
    case 0xE0:
      printf("         set 4,b");
      break;
    case 0xE1:
      printf("         set 4,c");
      break;
    case 0xE2:
      printf("         set 4,d");
      break;
    case 0xE3:
      printf("         set 4,e");
      break;
    case 0xE4:
      printf("         set 4,h");
      break;
    case 0xE5:
      printf("         set 4,l");
      break;
    case 0xE6:
      printf("         set 4,(hl)");
      break;
    case 0xE7:
      printf("         set 4,a");
      break;
    case 0xE8:
      printf("         set 5,b");
      break;
    case 0xE9:
      printf("         set 5,c");
      break;
    case 0xEA:
      printf("         set 5,d");
      break;
    case 0xEB:
      printf("         set 5,e");
      break;
    case 0xEC:
      printf("         set 5,h");
      break;
    case 0xED:
      printf("         set 5,l");
      break;
    case 0xEE:
      printf("         set 5,(hl)");
      break;
    case 0xEF:
      printf("         set 5,a");
      break;
    case 0xF0:
      printf("         set 6,b");
      break;
    case 0xF1:
      printf("         set 6,c");
      break;
    case 0xF2:
      printf("         set 6,d");
      break;
    case 0xF3:
      printf("         set 6,e");
      break;
    case 0xF4:
      printf("         set 6,h");
      break;
    case 0xF5:
      printf("         set 6,l");
      break;
    case 0xF6:
      printf("         set 6,(hl)");
      break;
    case 0xF7:
      printf("         set 6,a");
      break;
    case 0xF8:
      printf("         set 7,b");
      break;
    case 0xF9:
      printf("         set 7,c");
      break;
    case 0xFA:
      printf("         set 7,d");
      break;
    case 0xFB:
      printf("         set 7,e");
      break;
    case 0xFC:
      printf("         set 7,h");
      break;
    case 0xFD:
      printf("         set 7,l");
      break;
    case 0xFE:
      printf("         set 7,(hl)");
      break;
    case 0xFF:
      printf("         set 7,a");
      break;
    default:
      printf("         Invalid opcode");
      fseek(IN, -1, SEEK_CUR);
      offset--;
  }//switch
}//disasCB

void disasDDCB(void) {
  byte arg1 = readbyte(),
  b = readbyte();

  switch (b) {
    case 0x00:
      printf("   rlc b,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x01:
      printf("   rlc c,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x02:
      printf("   rlc d,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x03:
      printf("   rlc e,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x04:
      printf("   rlc h,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x05:
      printf("   rlc l,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x06:
      printf("   rlc (ix+%02xh)", arg1);
      break;
    case 0x07:
      printf("   rlc a,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x08:
      printf("   rrc b,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x09:
      printf("   rrc c,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x0A:
      printf("   rrc d,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x0B:
      printf("   rrc e,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x0C:
      printf("   rrc h,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x0D:
      printf("   rrc l,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x0E:
      printf("   rrc (ix+%02xh)", arg1);
      break;
    case 0x0F:
      printf("   rrc a,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x10:
      printf("   rl b,(ix+%02xh)      ; undocumented", arg1);
      break;
    case 0x11:
      printf("   rl c,(ix+%02xh)      ; undocumented", arg1);
      break;
    case 0x12:
      printf("   rl d,(ix+%02xh)      ; undocumented", arg1);
      break;
    case 0x13:
      printf("   rl e,(ix+%02xh)      ; undocumented", arg1);
      break;
    case 0x14:
      printf("   rl h,(ix+%02xh)      ; undocumented", arg1);
      break;
    case 0x15:
      printf("   rl l,(ix+%02xh)      ; undocumented", arg1);
      break;
    case 0x16:
      printf("   rl (ix+%02xh)", arg1);
      break;
    case 0x17:
      printf("   rl a,(ix+%02xh)      ; undocumented", arg1);
      break;
    case 0x18:
      printf("   rr b,(ix+%02xh)      ; undocumented", arg1);
      break;
    case 0x19:
      printf("   rr c,(ix+%02xh)      ; undocumented", arg1);
      break;
    case 0x1A:
      printf("   rr d,(ix+%02xh)      ; undocumented", arg1);
      break;
    case 0x1B:
      printf("   rr e,(ix+%02xh)      ; undocumented", arg1);
      break;
    case 0x1C:
      printf("   rr h,(ix+%02xh)      ; undocumented", arg1);
      break;
    case 0x1D:
      printf("   rr l,(ix+%02xh)      ; undocumented", arg1);
      break;
    case 0x1E:
      printf("   rr (ix+%02xh)", arg1);
      break;
    case 0x1F:
      printf("   rr a,(ix+%02xh)      ; undocumented", arg1);
      break;
    case 0x20:
      printf("   sla b,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x21:
      printf("   sla c,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x22:
      printf("   sla d,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x23:
      printf("   sla e,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x24:
      printf("   sla h,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x25:
      printf("   sla l,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x26:
      printf("   sla (ix+%02xh)", arg1);
      break;
    case 0x27:
      printf("   sla a,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x28:
      printf("   sra b,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x29:
      printf("   sra c,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x2A:
      printf("   sra d,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x2B:
      printf("   sra e,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x2C:
      printf("   sra h,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x2D:
      printf("   sra l,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x2E:
      printf("   sra (ix+%02xh)", arg1);
      break;
    case 0x2F:
      printf("   sra a,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x30:
      printf("   sl1 b,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x31:
      printf("   sl1 c,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x32:
      printf("   sl1 d,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x33:
      printf("   sl1 e,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x34:
      printf("   sl1 h,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x35:
      printf("   sl1 l,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x36:
      printf("   sl1 (ix+%02xh)       ; undocumented", arg1);
      break;
    case 0x37:
      printf("   sl1 a,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x38:
      printf("   srl b,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x39:
      printf("   srl c,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x3A:
      printf("   srl d,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x3B:
      printf("   srl e,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x3C:
      printf("   srl h,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x3D:
      printf("   srl l,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x3E:
      printf("   srl (ix+%02xh)", arg1);
      break;
    case 0x3F:
      printf("   srl a,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x47:
      printf("   bit 0,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x46:
      printf("   bit 0,(ix+%02xh)", arg1);
      break;
    case 0x48:
    case 0x49:
    case 0x4A:
    case 0x4B:
    case 0x4C:
    case 0x4D:
    case 0x4F:
      printf("   bit 1,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x4E:
      printf("   bit 1,(ix+%02xh)", arg1);
      break;
    case 0x50:
    case 0x51:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x57:
      printf("   bit 2,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x56:
      printf("   bit 2,(ix+%02xh)", arg1);
      break;
    case 0x58:
    case 0x59:
    case 0x5A:
    case 0x5B:
    case 0x5C:
    case 0x5D:
    case 0x5F:
      printf("   bit 3,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x5E:
      printf("   bit 3,(ix+%02xh)", arg1);
      break;
    case 0x60:
    case 0x61:
    case 0x62:
    case 0x63:
    case 0x64:
    case 0x65:
    case 0x67:
      printf("   bit 4,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x66:
      printf("   bit 4,(ix+%02xh)", arg1);
      break;
    case 0x68:
    case 0x69:
    case 0x6A:
    case 0x6B:
    case 0x6C:
    case 0x6D:
    case 0x6F:
      printf("   bit 5,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x6E:
      printf("   bit 5,(ix+%02xh)", arg1);
      break;
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x73:
    case 0x74:
    case 0x75:
    case 0x77:
      printf("   bit 6,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x76:
      printf("   bit 6,(ix+%02xh)", arg1);
      break;
    case 0x78:
    case 0x79:
    case 0x7A:
    case 0x7B:
    case 0x7C:
    case 0x7D:
    case 0x7F:
      printf("   bit 7,(ix+%02xh)     ; undocumented", arg1);
      break;
    case 0x7E:
      printf("   bit 7,(ix+%02xh)", arg1);
      break;
    case 0x80:
      printf("   res b,0,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x81:
      printf("   res c,0,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x82:
      printf("   res d,0,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x83:
      printf("   res e,0,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x84:
      printf("   res h,0,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x85:
      printf("   res l,0,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x86:
      printf("   res 0,(ix+%02xh)", arg1);
      break;
    case 0x87:
      printf("   res a,0,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x88:
      printf("   res b,1,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x89:
      printf("   res c,1,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x8A:
      printf("   res d,1,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x8B:
      printf("   res e,1,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x8C:
      printf("   res h,1,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x8D:
      printf("   res l,1,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x8E:
      printf("   res 1,(ix+%02xh)", arg1);
      break;
    case 0x8F:
      printf("   res a,1,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x90:
      printf("   res b,2,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x91:
      printf("   res c,2,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x92:
      printf("   res d,2,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x93:
      printf("   res e,2,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x94:
      printf("   res h,2,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x95:
      printf("   res l,2,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x96:
      printf("   res 2,(ix+%02xh)", arg1);
      break;
    case 0x97:
      printf("   res a,2,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x98:
      printf("   res b,3,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x99:
      printf("   res c,3,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x9A:
      printf("   res d,3,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x9B:
      printf("   res e,3,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x9C:
      printf("   res h,3,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x9D:
      printf("   res l,3,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0x9E:
      printf("   res 3,(ix+%02xh)", arg1);
      break;
    case 0x9F:
      printf("   res a,3,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xA0:
      printf("   res b,4,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xA1:
      printf("   res c,4,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xA2:
      printf("   res d,4,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xA3:
      printf("   res e,4,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xA4:
      printf("   res h,4,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xA5:
      printf("   res l,4,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xA6:
      printf("   res 4,(ix+%02xh)", arg1);
      break;
    case 0xA7:
      printf("   res a,4,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xA8:
      printf("   res b,5,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xA9:
      printf("   res c,5,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xAA:
      printf("   res d,5,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xAB:
      printf("   res e,5,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xAC:
      printf("   res h,5,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xAD:
      printf("   res l,5,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xAE:
      printf("   res 5,(ix+%02xh)", arg1);
      break;
    case 0xAF:
      printf("   res a,5,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xB0:
      printf("   res b,6,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xB1:
      printf("   res c,6,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xB2:
      printf("   res d,6,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xB3:
      printf("   res e,6,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xB4:
      printf("   res h,6,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xB5:
      printf("   res l,6,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xB6:
      printf("   res 6,(ix+%02xh)", arg1);
      break;
    case 0xB7:
      printf("   res a,6,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xB8:
      printf("   res b,7,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xB9:
      printf("   res c,7,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xBA:
      printf("   res d,7,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xBB:
      printf("   res e,7,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xBC:
      printf("   res h,7,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xBD:
      printf("   res l,7,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xBE:
      printf("   res 7,(ix+%02xh)", arg1);
      break;
    case 0xBF:
      printf("   res a,7,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xC0:
      printf("   set b,0,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xC1:
      printf("   set c,0,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xC2:
      printf("   set d,0,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xC3:
      printf("   set e,0,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xC4:
      printf("   set h,0,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xC5:
      printf("   set l,0,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xC6:
      printf("   set 0,(ix+%02xh)", arg1);
      break;
    case 0xC7:
      printf("   set a,0,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xC8:
      printf("   set b,1,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xC9:
      printf("   set c,1,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xCA:
      printf("   set d,1,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xCB:
      printf("   set e,1,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xCC:
      printf("   set h,1,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xCD:
      printf("   set l,1,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xCE:
      printf("   set 1,(ix+%02xh)", arg1);
      break;
    case 0xCF:
      printf("   set a,1,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xD0:
      printf("   set b,2,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xD1:
      printf("   set c,2,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xD2:
      printf("   set d,2,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xD3:
      printf("   set e,2,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xD4:
      printf("   set h,2,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xD5:
      printf("   set l,2,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xD6:
      printf("   set 2,(ix+%02xh)", arg1);
      break;
    case 0xD7:
      printf("   set a,2,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xD8:
      printf("   set b,3,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xD9:
      printf("   set c,3,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xDA:
      printf("   set d,3,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xDB:
      printf("   set e,3,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xDC:
      printf("   set h,3,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xDD:
      printf("   set l,3,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xDE:
      printf("   set 3,(ix+%02xh)", arg1);
      break;
    case 0xDF:
      printf("   set a,3,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xE0:
      printf("   set b,4,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xE1:
      printf("   set c,4,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xE2:
      printf("   set d,4,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xE3:
      printf("   set e,4,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xE4:
      printf("   set h,4,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xE5:
      printf("   set l,4,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xE6:
      printf("   set 4,(ix+%02xh)", arg1);
      break;
    case 0xE7:
      printf("   set a,4,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xE8:
      printf("   set b,5,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xE9:
      printf("   set c,5,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xEA:
      printf("   set d,5,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xEB:
      printf("   set e,5,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xEC:
      printf("   set h,5,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xED:
      printf("   set l,5,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xEE:
      printf("   set 5,(ix+%02xh)", arg1);
      break;
    case 0xEF:
      printf("   set a,5,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xF0:
      printf("   set b,6,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xF1:
      printf("   set c,6,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xF2:
      printf("   set d,6,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xF3:
      printf("   set e,6,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xF4:
      printf("   set h,6,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xF5:
      printf("   set l,6,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xF6:
      printf("   set 6,(ix+%02xh)", arg1);
      break;
    case 0xF7:
      printf("   set a,6,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xF8:
      printf("   set b,7,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xF9:
      printf("   set c,7,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xFA:
      printf("   set d,7,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xFB:
      printf("   set e,7,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xFC:
      printf("   set h,7,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xFD:
      printf("   set l,7,(ix+%02xh)   ; undocumented", arg1);
      break;
    case 0xFE:
      printf("   set 7,(ix+%02xh)", arg1);
      break;
    case 0xFF:
      printf("   set a,7,(ix+%02xh)   ; undocumented", arg1);
      break;
    default:
      printf("   Invalid opcode");
      fseek(IN, -1, SEEK_CUR);
      offset--;
  }//switch
}//disasDDCB

void disasDD(void) {
  byte arg1 = 0x0,
       arg2 = 0x0,
       b = readbyte();

  switch (b) {
    case 0x00:
      if (!feof(IN))
        printf("         nop                ; undocumented (dup)");
      break;
    case 0x01:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld bc,%02x%02xh        ; undocumented (dup)", arg2, arg1);
      break;
    case 0x02:
      printf("         ld (bc),a          ; undocumented (dup)");
      break;
    case 0x03:
      printf("         inc bc             ; undocumented (dup)");
      break;
    case 0x04:
      printf("         inc b              ; undocumented (dup)");
      break;
    case 0x05:
      printf("         dec b              ; undocumented (dup)");
      break;
    case 0x06:
      arg1 = readbyte();
      printf("      ld b,%02xh           ; undocumented (dup)", arg1);
      break;
    case 0x07:
      printf("         rlca               ; undocumented (dup)");
      break;
    case 0x08:
      printf("         ex af,af'          ; undocumented (dup)");
      break;
    case 0x09:
      printf("         add ix,bc");
      break;
    case 0x0A:
      printf("         ld a,(bc)          ; undocumented (dup)");
      break;
    case 0x0B:
      printf("         dec bc             ; undocumented (dup)");
      break;
    case 0x0C:
      printf("         inc c              ; undocumented (dup)");
      break;
    case 0x0D:
      printf("         dec c              ; undocumented (dup)");
      break;
    case 0x0E:
      arg1 = readbyte();
      printf("      ld c,%02xh           ; undocumented (dup)", arg1);
      break;
    case 0x0F:
      printf("         rrca               ; undocumented (dup)");
      break;
    case 0x10:
      arg1 = readbyte();
      printf("      djnz %02xh           ; undocumented (dup)", arg1);
      break;
    case 0x11:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld de,%02x%02xh        ; undocumented (dup)", arg2, arg1);
      break;
    case 0x12:
      printf("         ld (de),a          ; undocumented (dup)");
      break;
    case 0x13:
      printf("         inc de             ; undocumented (dup)");
      break;
    case 0x14:
      printf("         inc d              ; undocumented (dup)");
      break;
    case 0x15:
      printf("         dec d              ; undocumented (dup)");
      break;
    case 0x16:
      arg1 = readbyte();
      printf("      ld d,%02xh           ; undocumented (dup)", arg1);
      break;
    case 0x17:
      printf("         rla                ; undocumented (dup)");
      break;
    case 0x18:
      arg1 = readbyte();
      printf("      jr %02xh             ; undocumented (dup)", arg1);
      break;
    case 0x19:
      printf("         add ix,de");
      break;
    case 0x1A:
      printf("         ld a,(de)          ; undocumented (dup)");
      break;
    case 0x1B:
      printf("         dec de             ; undocumented (dup)");
      break;
    case 0x1C:
      printf("         inc e              ; undocumented (dup)");
      break;
    case 0x1D:
      printf("         dec e              ; undocumented (dup)");
      break;
    case 0x1E:
      arg1 = readbyte();
      printf("      ld e,%02xh           ; undocumented (dup)", arg1);
      break;
    case 0x1F:
      printf("         rra                ; undocumented (dup)");
      break;
    case 0x20:
      arg1 = readbyte();
      printf("      jr nz,%02xh          ; undocumented (dup)", arg1);
      break;
    case 0x21:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld ix,%02x%02xh", arg2, arg1);
      break;
    case 0x22:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld (%02x%02xh),ix", arg2, arg1);
      break;
    case 0x23:
      printf("         inc ix");
      break;
    case 0x24:
      printf("         inc hx             ; undocumented");
      break;
    case 0x25:
      printf("         dec hx             ; undocumented");
      break; 
    case 0x26:
      arg1 = readbyte();
      printf("      ld hx,%02xh          ; undocumented", arg1);
      break;
    case 0x27:
      printf("         daa                ; undocumented (dup)");
      break;
    case 0x28:
      arg1 = readbyte();
      printf("      jr z,%02xh           ; undocumented (dup)", arg1);
      break;
    case 0x29:
      printf("         add ix,ix");
      break;
    case 0x2A:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld ix,(%02x%02xh)", arg2, arg1);
      break;
    case 0x2B:
      printf("         dec ix");
      break;
    case 0x2C:
      printf("         inc lx             ; undocumented");
      break;
    case 0x2D:
      printf("         dec lx             ; undocumented");
      break;
    case 0x2E:
      arg1 = readbyte();
      printf("      ld lx,%02xh          ; undocumented", arg1);
      break;
    case 0x2F:
      printf("         cpl                ; undocumented (dup)");
      break;
    case 0x30:
      arg1 = readbyte();
      printf("      jr nc,%02xh          ; undocumented (dup)", arg1);
      break;
    case 0x31:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld sp,%02x%02xh        ; undocumented (dup)", arg2, arg1);
      break;
    case 0x32:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld (%02x%02xh),a       ; undocumented (dup)", arg2, arg1);
      break;
    case 0x33:
      printf("         inc sp             ; undocumented (dup)");
      break;
    case 0x34:
      arg1 = readbyte();
      printf("      inc (ix+%02xh)", arg1);
      break;
    case 0x35:
      arg1 = readbyte();
      printf("      dec (ix+%02xh)", arg1);
      break;
    case 0x36:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld (ix+%02xh),%02xh", arg1, arg2);
      break;
    case 0x37:
      printf("         scf                ; undocumented (dup)");
      break;
    case 0x38:
      arg1 = readbyte();
      printf("      jr c,%02xh           ; undocumented (dup)", arg1);
      break;
    case 0x39:
      printf("         add hl,sp");
      break;
    case 0x3A:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld a,(%02x%02xh)       ; undocumented (dup)", arg2, arg1);
      break;
    case 0x3B:
      printf("         dec sp             ; undocumented (dup)");
      break;
    case 0x3C:
      printf("         inc a              ; undocumented (dup)");
      break;
    case 0x3D:
      printf("         dec a              ; undocumented (dup)");
      break;
    case 0x3E:
      arg1 = readbyte();
      printf("      ld a,%02xh           ; undocumented (dup)", arg1);
      break;
    case 0x3F:
      printf("         ccf                ; undocumented (dup)");
      break;
    case 0x40:
      printf("         ld b,b             ; undocumented (dup)");
      break;
    case 0x41:
      printf("         ld b,c             ; undocumented (dup)");
      break;
    case 0x42:
      printf("         ld b,d             ; undocumented (dup)");
      break;
    case 0x43:
      printf("         ld b,e             ; undocumented (dup)");
      break;
    case 0x44:
      printf("         ld b,hx            ; undocumented");
      break;
    case 0x45:
      printf("         ld b,lx            ; undocumented");
      break;
    case 0x46:
      arg1 = readbyte();
      printf("      ld b,(ix+%02xh)", arg1);
      break;
    case 0x47:
      printf("         ld b,a             ; undocumented (dup)");
      break;
    case 0x48:
      printf("         ld c,b             ; undocumented (dup)");
      break;
    case 0x49:
      printf("         ld c,c             ; undocumented (dup)");
      break;
    case 0x4A:
      printf("         ld c,d             ; undocumented (dup)");
      break;
    case 0x4B:
      printf("         ld c,e             ; undocumented (dup)");
      break;
    case 0x4C:
      printf("         ld c,hx            ; undocumented");
      break;
    case 0x4D:
      printf("         ld c,lx            ; undocumented");
      break;
    case 0x4E:
      arg1 = readbyte();
      printf("      ld c,(ix+%02xh)", arg1);
      break;
    case 0x4F:
      printf("         ld c,a             ; undocumented (dup)");
      break;
    case 0x50:
      printf("         ld d,b             ; undocumented (dup)");
      break;
    case 0x51:
      printf("         ld d,c             ; undocumented (dup)");
      break;
    case 0x52:
      printf("         ld d,d             ; undocumented (dup)");
      break;
    case 0x53:
      printf("         ld d,e             ; undocumented (dup)");
      break;
    case 0x54:
      printf("         ld d,hx            ; undocumented");
      break;
    case 0x55:
      printf("         ld d,lx            ; undocumented");
      break;
    case 0x56:
      arg1 = readbyte();
      printf("      ld d,(ix+%02xh)", arg1);
      break;
    case 0x57:
      printf("         ld d,a             ; undocumented (dup)");
      break;
    case 0x58:
      printf("         ld e,b             ; undocumented (dup)");
      break;
    case 0x59:
      printf("         ld e,c             ; undocumented (dup)");
      break;
    case 0x5A:
      printf("         ld e,d             ; undocumented (dup)");
      break;
    case 0x5B:
      printf("         ld e,e             ; undocumented (dup)");
      break;
    case 0x5C:
      printf("         ld e,hx            ; undocumented");
      break;
    case 0x5D:
      printf("         ld e,lx            ; undocumented");
      break;
    case 0x5E:
      arg1 = readbyte();
      printf("      ld e,(ix+%02xh)", arg1);
      break;
    case 0x5F:
      printf("         ld e,a             ; undocumented (dup)");
      break;
    case 0x60:
      printf("         ld hx,b            ; undocumented");
      break;
    case 0x61:
      printf("         ld hx,c            ; undocumented");
      break;
    case 0x62:
      printf("         ld hx,d            ; undocumented");
      break;
    case 0x63:
      printf("         ld hx,e            ; undocumented");
      break;
    case 0x64:
      printf("         ld hx,hx           ; undocumented");
      break;
    case 0x65:
      printf("         ld hx,lx           ; undocumented");
      break;
    case 0x66:
      arg1 = readbyte();
      printf("      ld h,(ix+%02xh)", arg1);
      break;
    case 0x67:
      printf("         ld hx,a            ; undocumented");
      break;
    case 0x68:
      printf("         ld lx,b            ; undocumented");
      break;
    case 0x69:
      printf("         ld lx,c            ; undocumented");
      break;
    case 0x6A:
      printf("         ld lx,d            ; undocumented");
      break;
    case 0x6B:
      printf("         ld lx,e            ; undocumented");
      break;
    case 0x6C:
      printf("         ld lx,hx           ; undocumented");
      break;
    case 0x6D:
      printf("         ld lx,lx           ; undocumented");
      break;
    case 0x6E:
      arg1 = readbyte();
      printf("      ld l,(ix+%02xh)", arg1);
      break;
    case 0x6F:
      printf("         ld lx,a            ; undocumented");
      break;
    case 0x70:
      arg1 = readbyte();
      printf("      ld (ix+%02xh),b", arg1);
      break;
    case 0x71:
      arg1 = readbyte();
      printf("      ld (ix+%02xh),c", arg1);
      break;
    case 0x72:
      arg1 = readbyte();
      printf("      ld (ix+%02xh),d", arg1);
      break;
    case 0x73:
      arg1 = readbyte();
      printf("      ld (ix+%02xh),e", arg1);
      break;
    case 0x74:
      arg1 = readbyte();
      printf("      ld (ix+%02xh),h", arg1);
      break;
    case 0x75:
      arg1 = readbyte();
      printf("      ld (ix+%02xh),l", arg1);
      break;
    case 0x76:
      printf("         halt               ; undocumented (dup)");
      break;
    case 0x77:
      arg1 = readbyte();
      printf("      ld (ix+%02xh),a", arg1);
      break;
    case 0x78:
      printf("         ld a,b             ; undocumented (dup)");
      break;
    case 0x79:
      printf("         ld a,c             ; undocumented (dup)");
      break;
    case 0x7A:
      printf("         ld a,d             ; undocumented (dup)");
      break;
    case 0x7B:
      printf("         ld a,e             ; undocumented (dup)");
      break;
    case 0x7C:
      printf("         ld a,hx            ; undocumented");
      break;
    case 0x7D:
      printf("         ld a,lx            ; undocumented");
      break;
    case 0x7E:
      arg1 = readbyte();
      printf("      ld a,(ix+%02xh)", arg1);
      break;
    case 0x7F:
      printf("         ld a,a             ; undocumented (dup)");
      break;
    case 0x80:
      printf("         add a,b            ; undocumented (dup)");
      break;
    case 0x81:
      printf("         add a,c            ; undocumented (dup)");
      break;
    case 0x82:
      printf("         add a,d            ; undocumented (dup)");
      break;
    case 0x83:
      printf("         add a,e            ; undocumented (dup)");
      break;
    case 0x84:
      printf("         add a,hx           ; undocumented");
      break;
    case 0x85:
      printf("         add a,lx           ; undocumented");
      break;
    case 0x86:
      arg1 = readbyte();
      printf("      add a,(ix+%02xh)", arg1);
      break;
    case 0x87:
      printf("         add a,a            ; undocumented (dup)");
      break;
    case 0x88:
      printf("         adc a,b            ; undocumented (dup)");
      break;
    case 0x89:
      printf("         adc a,c            ; undocumented (dup)");
      break;
    case 0x8A:
      printf("         adc a,d            ; undocumented (dup)");
      break;
    case 0x8B:
      printf("         adc a,e            ; undocumented (dup)");
      break;
    case 0x8C:
      printf("         adc a,hx           ; undocumented");
      break;
    case 0x8D:
      printf("         adc a,lx           ; undocumented");
      break;
    case 0x8E:
      arg1 = readbyte();
      printf("      adc a,(ix+%02xh)", arg1);
      break;
    case 0x8F:
      printf("         adc a,a            ; undocumented (dup)");
      break;
    case 0x90:
      printf("         sub b              ; undocumented (dup)");
      break;
    case 0x91:
      printf("         sub c              ; undocumented (dup)");
      break;
    case 0x92:
      printf("         sub d              ; undocumented (dup)");
      break;
    case 0x93:
      printf("         sub e              ; undocumented (dup)");
      break;
    case 0x94:
      printf("         sub hx             ; undocumented");
      break;
    case 0x95:
      printf("         sub lx             ; undocumented");
      break;
    case 0x96:
      arg1 = readbyte();
      printf("      sub (ix+%02xh)", arg1);
      break;
    case 0x97:
      printf("         sub a              ; undocumented (dup)");
      break;
    case 0x98:
      printf("         sbc a,b            ; undocumented (dup)");
      break;
    case 0x99:
      printf("         sbc a,c            ; undocumented (dup)");
      break;
    case 0x9A:
      printf("         sbc a,d            ; undocumented (dup)");
      break;
    case 0x9B:
      printf("         sbc a,e            ; undocumented (dup)");
      break;
    case 0x9C:
      printf("         sbc a,hx           ; undocumented");
      break;
    case 0x9D:
      printf("         sbc a,lx           ; undocumented");
      break;
    case 0x9E:
      arg1 = readbyte();
      printf("      sbc a,(ix+%02xh)", arg1);
      break;
    case 0x9F:
      printf("         sbc a,a            ; undocumented (dup)");
      break;
    case 0xA0:
      printf("         and b              ; undocumented (dup)");
      break;
    case 0xA1:
      printf("         and c              ; undocumented (dup)");
      break;
    case 0xA2:
      printf("         and d              ; undocumented (dup)");
      break;
    case 0xA3:
      printf("         and e              ; undocumented (dup)");
      break;
    case 0xA4:
      printf("         and hx             ; undocumented");
      break;
    case 0xA5:
      printf("         and lx             ; undocumented");
      break;
    case 0xA6:
      arg1 = readbyte();
      printf("      and (ix+%02xh)", arg1);
      break;
    case 0xA7:
      printf("         and a              ; undocumented (dup)");
      break;
    case 0xA8:
      printf("         xor b              ; undocumented (dup)");
      break;
    case 0xA9:
      printf("         xor c              ; undocumented (dup)");
      break;
    case 0xAA:
      printf("         xor d              ; undocumented (dup)");
      break;
    case 0xAB:
      printf("         xor e              ; undocumented (dup)");
      break;
    case 0xAC:
      printf("         xor hx             ; undocumented");
      break;
    case 0xAD:
      printf("         xor lx             ; undocumented");
      break;
    case 0xAE:
      arg1 = readbyte();
      printf("      xor (ix+%02xh)", arg1);
      break;
    case 0xAF:
      printf("         xor a              ; undocumented (dup)");
      break;
    case 0xB0:
      printf("         or b               ; undocumented (dup)");
      break;
    case 0xB1:
      printf("         or c               ; undocumented (dup)");
      break;
    case 0xB2:
      printf("         or d               ; undocumented (dup)");
      break;
    case 0xB3:
      printf("         or e               ; undocumented (dup)");
      break;
    case 0xB4:
      printf("         or hx              ; undocumented");
      break;
    case 0xB5:
      printf("         or lx              ; undocumented");
      break;
    case 0xB6:
      arg1 = readbyte();
      printf("      or (ix+%02xh)", arg1);
      break;
    case 0xB7:
      printf("         or a               ; undocumented (dup)");
      break;
    case 0xB8:
      printf("         cp b               ; undocumented (dup)");
      break;
    case 0xB9:
      printf("         cp c               ; undocumented (dup)");
      break;
    case 0xBA:
      printf("         cp d               ; undocumented (dup)");
      break;
    case 0xBB:
      printf("         cp e               ; undocumented (dup)");
      break;
    case 0xBC:
      printf("         cp hx              ; undocumented");
      break;
    case 0xBD:
      printf("         cp lx              ; undocumented");
      break;
    case 0xBE:
      arg1 = readbyte();
      printf("      cp (ix+%02xh)", arg1);
      break;
    case 0xBF:
      printf("         cp a               ; undocumented (dup)");
      break;
    case 0xC0:
      printf("         ret nz             ; undocumented (dup)");
      break;
    case 0xC1:
      printf("         pop bc             ; undocumented (dup)");
      break;
    case 0xC2:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   jp nz,%02x%02xh        ; undocumented (dup)", arg2, arg1);
      break;
    case 0xC3:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   jp %02x%02xh           ; undocumented (dup)", arg2, arg1);
      break;
    case 0xC4:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   call nz,%02x%02xh      ; undocumented (dup)", arg2, arg1);
      break;
    case 0xC5:
      printf("         push bc            ; undocumented (dup)");
      break;
    case 0xC6:
      arg1 = readbyte();
      printf("   add a,%02xh             ; undocumented (dup)", arg1);
      break;
    case 0xC7:
      printf("         rst 00H            ; undocumented (dup)");
      break;
    case 0xC8:
      printf("         ret z              ; undocumented (dup)");
      break;
    case 0xC9:
      printf("         ret                ; undocumented (dup)");
      break;
    case 0xCA:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   jp z,%02x%02xh         ; undocumented (dup)", arg2, arg1);
      break;
    case 0xCB:
      disasDDCB();
      break;
    case 0xCC:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   call z,%02x%02xh       ; undocumented (dup)", arg2, arg1);
      break;
    case 0xCD:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   call %02x%02xh         ; undocumented (dup)", arg2, arg1);
      break;
    case 0xCE:
      arg1 = readbyte();
      printf("   adc a,%02xh             ; undocumented (dup)", arg1);
      break;
    case 0xCF:
      printf("         rst 08H            ; undocumented (dup)");
      break;
    case 0xD0:
      printf("         ret nc             ; undocumented (dup)");
      break;
    case 0xD1:
      printf("         pop de             ; undocumented (dup)");
      break;
    case 0xD2:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   jp nc,%02x%02xh        ; undocumented (dup)", arg2, arg1);
      break;
    case 0xD3:
      arg1 = readbyte();
      printf("      out (%02xh),a        ; undocumented (dup)", arg1);
      break;
    case 0xD4:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   call nc,%02x%02xh      ; undocumented (dup)", arg2, arg1);
      break;
    case 0xD5:
      printf("         push de            ; undocumented (dup)");
      break;
    case 0xD6:
      arg1 = readbyte();
      printf("      sub %02xh            ; undocumented (dup)", arg1);
      break;
    case 0xD7:
      printf("         rst 10H            ; undocumented (dup)");
      break;
    case 0xD8:
      printf("         ret c              ; undocumented (dup)");
      break;
    case 0xD9:
      printf("         exx                ; undocumented (dup)");
      break;
    case 0xDA:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   jp c,%02x%02xh         ; undocumented (dup)", arg2, arg1);
      break;
    case 0xDB:
      arg1 = readbyte();
      printf("      in a,(%02xh)         ; undocumented (dup)", arg1);
      break;
    case 0xDC:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   call c,%02x%02xh       ; undocumented (dup)", arg2, arg1);
      break;
    case 0xDD:
      printf("         nop                ; undocumented (dup)");
      fseek(IN, -1, SEEK_CUR);
      offset--;
      break;
    case 0xDE:
      arg1 = readbyte();
      printf("      sbc a,%02xh          ; undocumented (dup)", arg1);
      break;
    case 0xDF:
      printf("         rst 18H            ; undocumented (dup)");
      break;
    case 0xE0:
      printf("         ret po             ; undocumented (dup)");
      break;
    case 0xE1:
      printf("         pop ix");
      break;
    case 0xE2:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   jp po,%02x%02xh        ; undocumented (dup)", arg2, arg1);
      break;
    case 0xE3:
      printf("         ex (sp),ix");
      break;
    case 0xE4:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   call po,%02x%02xh      ; undocumented (dup)", arg2, arg1);
      break;
    case 0xE5:
      printf("         push ix");
      break;
    case 0xE6:
      arg1 = readbyte();
      printf("      and %02xh            ; undocumented (dup)", arg1);
      break;
    case 0xE7:
      printf("         rst 20H            ; undocumented (dup)");
      break;
    case 0xE8:
      printf("         ret pe             ; undocumented (dup)");
      break;
    case 0xE9:
      printf("         jp (ix)");
      break;
    case 0xEA:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   jp pe,%02x%02xh        ; undocumented (dup)", arg2, arg1);
      break;
    case 0xEB:
      printf("         ex de,hl           ; undocumented (dup)");
      break;
    case 0xEC:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   call pe,%02x%02xh      ; undocumented (dup)", arg2, arg1);
      break;
    case 0xED:
      printf("         nop                ; undocumented (dup)");
      fseek(IN, -1, SEEK_CUR);
      offset--;
      break;
    case 0xEE:
      arg1 = readbyte();
      printf("      xor %02xh            ; undocumented (dup)", arg1);
      break;
    case 0xEF:
      printf("         rst 28H            ; undocumented (dup)");
      break;
    case 0xF0:
      printf("         ret p              ; undocumented (dup)");
      break;
    case 0xF1:
      printf("         pop af             ; undocumented (dup)");
      break;
    case 0xF2:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   jp p,%02x%02xh         ; undocumented (dup)", arg2, arg1);
      break;
    case 0xF3:
      printf("         di                 ; undocumented (dup)");
      break;
    case 0xF4:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   call p,%02x%02xh       ; undocumented (dup)", arg2, arg1);
      break;
    case 0xF5:
      printf("         push af            ; undocumented (dup)");
      break;
    case 0xF6:
      arg1 = readbyte();
      printf("      or %02xh             ; undocumented (dup)", arg1);
      break;
    case 0xF7:
      printf("         rst 30H            ; undocumented (dup)");
      break;
    case 0xF8:
      printf("         ret m              ; undocumented (dup)");
      break;
    case 0xF9:
      printf("         ld sp,ix");
      break;
    case 0xFA:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   jp m,%02x%02xh         ; undocumented (dup)", arg2, arg1);
      break;
    case 0xFB:
      printf("         ei                 ; undocumented (dup)");
      break;
    case 0xFC:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   call m,%02x%02xh       ; undocumented (dup)", arg2, arg1);
      break;
    case 0xFD:
      printf("         nop                ; undocumented (dup)");
      fseek(IN, -1, SEEK_CUR);
      offset--;
      break;
    case 0xFE:
      arg1 = readbyte();
      printf("      cp %02xh             ; undocumented (dup)", arg1);
      break;
    case 0xFF:
      printf("         rst 38H            ; undocumented (dup)");
      break;
    default:
      printf("         Invalid opcode");
      fseek(IN, -1, SEEK_CUR);
      offset--;
  }//switch
}//disasDD

void disasED(void) {
  byte arg1 = 0x0,
       arg2 = 0x0,
       b = readbyte();

  switch (b) {
    case 0x00:
    case 0x01:
    case 0x02:
    case 0x03:
    case 0x04:
    case 0x05:
    case 0x06:
    case 0x07:
    case 0x08:
    case 0x09:
    case 0x0A:
    case 0x0B:
    case 0x0C:
    case 0x0D:
    case 0x0E:
    case 0x0F:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1A:
    case 0x1B:
    case 0x1C:
    case 0x1D:
    case 0x1E:
    case 0x1F:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2A:
    case 0x2B:
    case 0x2C:
    case 0x2D:
    case 0x2E:
    case 0x2F:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x38:
    case 0x39:
    case 0x3A:
    case 0x3B:
    case 0x3C:
    case 0x3D:
    case 0x3E:
    case 0x3F:
      printf("         nop                ; undocumented (dup)");
      break;
    case 0x40:
      printf("         in b,(c)");
      break;
    case 0x41:
      printf("         out (c),b");
      break;
    case 0x42:
      printf("         sbc hl,bc");
      break;
    case 0x43:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld (%02x%02xh),bc", arg2, arg1);
      break;
    case 0x44:
      printf("         neg");
      break;
    case 0x45:
      printf("         retn");
      break;
    case 0x46:
      printf("         im 0");
      break;
    case 0x47:
      printf("         ld i,a");
      break;
    case 0x48:
      printf("         in c,(c)");
      break;
    case 0x49:
      printf("         out (c),c");
      break;
    case 0x4A:
      printf("         adc hl,bc");
      break;
    case 0x4B:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld bc,(%02x%02xh)", arg2, arg1);
      break;
    case 0x4C:
      printf("         neg                ; undocumented (dup)");
      break;
    case 0x4D:
      printf("         reti");
      break;
    case 0x4E:
      printf("         im 0               ; undocumented (dup)");
      break;
    case 0x4F:
      printf("         ld r,a");
      break;
    case 0x50:
      printf("         in d,(c)");
      break;
    case 0x51:
      printf("         out (c),d");
      break;
    case 0x52:
      printf("         sbc hl,de");
      break;
    case 0x53:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld (%02x%02xh),de", arg2, arg1);
      break;
    case 0x54:
      printf("         neg                ; undocumented (dup)");
      break;
    case 0x55:
      printf("         retn               ; undocumented (dup)");
      break;
    case 0x56:
      printf("         im 1");
      break;
    case 0x57:
      printf("         ld a,i");
      break;
    case 0x58:
      printf("         in e,(c)");
      break;
    case 0x59:
      printf("         out (c),e");
      break;
    case 0x5A:
      printf("         adc hl,de");
      break;
    case 0x5B:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld de,(%02x%02xh)", arg2, arg1);
      break;
    case 0x5C:
      printf("         neg                ; undocumented (dup)");
      break;
    case 0x5D:
      printf("         reti               ; undocumented (dup)");
      break;
    case 0x5E:
      printf("         im 2");
      break;
    case 0x5F:
      printf("         ld a,r");
      break;
    case 0x60:
      printf("         in h,(c)");
      break;
    case 0x61:
      printf("         out (c),h");
      break;
    case 0x62:
      printf("         sbc hl,hl");
      break;
    case 0x63:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld (%02x%02xh),hl      ; undocumented (dup)", arg2, arg1);
      break;
    case 0x64:
      printf("         neg                ; undocumented (dup)");
      break;
    case 0x65:
      printf("         retn               ; undocumented (dup)");
      break;
    case 0x66:
      printf("         im 0               ; undocumented (dup)");
      break;
    case 0x67:
      printf("         rrd");
      break;
    case 0x68:
      printf("         in l,(c)");
      break;
    case 0x69:
      printf("         out (c),l");
      break;
    case 0x6A:
      printf("         adc hl,hl");
      break;
    case 0x6B:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld hl,(%02x%02xh)      ; undocumented (dup)", arg2, arg1);
      break;
    case 0x6C:
      printf("         neg                ; undocumented (dup)");
      break;
    case 0x6D:
      printf("         reti               ; undocumented (dup)");
      break;
    case 0x6E:
      printf("         im 0               ; undocumented (dup)");
      break;
    case 0x6F:
      printf("         rld");
      break;
    case 0x70:
      printf("         in (c)             ; undocumented");
      break;
    case 0x71:
      printf("         out (c),0          ; undocumented");
      break;
    case 0x72:
      printf("         sbc hl,sp");
      break;
    case 0x73:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld (%02x%02xh),sp", arg2, arg1);
      break;
    case 0x74:
      printf("         neg                ; undocumented (dup)");
      break;
    case 0x75:
      printf("         retn               ; undocumented (dup)");
      break;
    case 0x76:
      printf("         im 1               ; undocumented (dup)");
      break;
    case 0x77:
      printf("         ld i,i             ; undocumented");
      break;
    case 0x78:
      printf("         in a,(c)");
      break;
    case 0x79:
      printf("         out (c),a");
      break;
    case 0x7A:
      printf("         adc hl,sp");
      break;
    case 0x7B:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld sp,(%02x%02xh)", arg2, arg1);
      break;
    case 0x7C:
      printf("         neg                ; undocumented (dup)");
      break;
    case 0x7D:
      printf("         reti               ; undocumented (dup)");
      break;
    case 0x7E:
      printf("         im 2               ; undocumented (dup)");
      break;
    case 0x7F:
      printf("         ld r,r             ; undocumented");
      break;
    case 0x80:
    case 0x81:
    case 0x82:
    case 0x83:
    case 0x84:
    case 0x85:
    case 0x86:
    case 0x87:
    case 0x88:
    case 0x89:
    case 0x8A:
    case 0x8B:
    case 0x8C:
    case 0x8D:
    case 0x8E:
    case 0x8F:
    case 0x90:
    case 0x91:
    case 0x92:
    case 0x93:
    case 0x94:
    case 0x95:
    case 0x96:
    case 0x97:
    case 0x98:
    case 0x99:
    case 0x9A:
    case 0x9B:
    case 0x9C:
    case 0x9D:
    case 0x9E:
    case 0x9F:
      printf("         nop                ; undocumented (dup)");
      break;
    case 0xA0:
      printf("         ldi");
      break;
    case 0xA1:
      printf("         cpi");
      break;
    case 0xA2:
      printf("         ini");
      break;
    case 0xA3:
      printf("         outi");
      break;
    case 0xA4:
    case 0xA5:
    case 0xA6:
    case 0xA7:
      printf("         nop                ; undocumented (dup)");
      break;
    case 0xA8:
      printf("         ldd");
      break;
    case 0xA9:
      printf("         cpd");
      break;
    case 0xAA:
      printf("         ind");
      break;
    case 0xAB:
      printf("         outd");
      break;
    case 0xAC:
    case 0xAD:
    case 0xAE:
    case 0xAF:
      printf("         nop                ; undocumented (dup)");
      break;
    case 0xB0:
      printf("         ldir");
      break;
    case 0xB1:
      printf("         cpir");
      break;
    case 0xB2:
      printf("         inir");
      break;
    case 0xB3:
      printf("         otir");
      break;
    case 0xB4:
    case 0xB5:
    case 0xB6:
    case 0xB7:
      printf("         nop                ; undocumented (dup)");
      break;
    case 0xB8:
      printf("         lddr");
      break;
    case 0xB9:
      printf("         cpdr");
      break;
    case 0xBA:
      printf("         indr");
      break;
    case 0xBB:
      printf("         otdr");
      break;
    case 0xBC:
    case 0xBD:
    case 0xBE:
    case 0xBF:
      printf("         nop                ; undocumented (dup)");
      break;
    case 0xC0:
    case 0xC1:
    case 0xC2:
    case 0xC3:
    case 0xC4:
    case 0xC5:
    case 0xC6:
    case 0xC7:
    case 0xC8:
    case 0xC9:
    case 0xCA:
    case 0xCB:
    case 0xCC:
    case 0xCD:
    case 0xCE:
    case 0xCF:
    case 0xD0:
    case 0xD1:
    case 0xD2:
    case 0xD3:
    case 0xD4:
    case 0xD5:
    case 0xD6:
    case 0xD7:
    case 0xD8:
    case 0xD9:
    case 0xDA:
    case 0xDB:
    case 0xDC:
    case 0xDD:
    case 0xDE:
    case 0xDF:
    case 0xE0:
    case 0xE1:
    case 0xE2:
    case 0xE3:
    case 0xE4:
    case 0xE5:
    case 0xE6:
    case 0xE7:
    case 0xE8:
    case 0xE9:
    case 0xEA:
    case 0xEB:
    case 0xEC:
    case 0xED:
    case 0xEE:
    case 0xEF:
    case 0xF0:
    case 0xF1:
    case 0xF2:
    case 0xF3:
    case 0xF4:
    case 0xF5:
    case 0xF6:
    case 0xF7:
    case 0xF8:
    case 0xF9:
    case 0xFA:
    case 0xFB:
    case 0xFC:
    case 0xFD:
    case 0xFE:
    case 0xFF:
      printf("         nop                ; undocumented (dup)");
      break;
    default:
      printf("         Invalid opcode");
      fseek(IN, -1, SEEK_CUR);
      offset--;
  }//switch
}//disasED

void disasFDCB(void) {
  byte arg1 = readbyte(),
  b = readbyte();

  switch (b) {
    case 0x00:
      printf("   rlc b,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x01:
      printf("   rlc c,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x02:
      printf("   rlc d,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x03:
      printf("   rlc e,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x04:
      printf("   rlc h,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x05:
      printf("   rlc l,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x06:
      printf("   rlc (iy+%02xh)", arg1);
      break;
    case 0x07:
      printf("   rlc a,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x08:
      printf("   rrc b,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x09:
      printf("   rrc c,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x0A:
      printf("   rrc d,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x0B:
      printf("   rrc e,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x0C:
      printf("   rrc h,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x0D:
      printf("   rrc l,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x0E:
      printf("   rrc (iy+%02xh)", arg1);
      break;
    case 0x0F:
      printf("   rrc a,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x10:
      printf("   rl b,(iy+%02xh)      ; undocumented", arg1);
      break;
    case 0x11:
      printf("   rl c,(iy+%02xh)      ; undocumented", arg1);
      break;
    case 0x12:
      printf("   rl d,(iy+%02xh)      ; undocumented", arg1);
      break;
    case 0x13:
      printf("   rl e,(iy+%02xh)      ; undocumented", arg1);
      break;
    case 0x14:
      printf("   rl h,(iy+%02xh)      ; undocumented", arg1);
      break;
    case 0x15:
      printf("   rl l,(iy+%02xh)      ; undocumented", arg1);
      break;
    case 0x16:
      printf("   rl (iy+%02xh)", arg1);
      break;
    case 0x17:
      printf("   rl a,(iy+%02xh)      ; undocumented", arg1);
      break;
    case 0x18:
      printf("   rr b,(iy+%02xh)      ; undocumented", arg1);
      break;
    case 0x19:
      printf("   rr c,(iy+%02xh)      ; undocumented", arg1);
      break;
    case 0x1A:
      printf("   rr d,(iy+%02xh)      ; undocumented", arg1);
      break;
    case 0x1B:
      printf("   rr e,(iy+%02xh)      ; undocumented", arg1);
      break;
    case 0x1C:
      printf("   rr h,(iy+%02xh)      ; undocumented", arg1);
      break;
    case 0x1D:
      printf("   rr l,(iy+%02xh)      ; undocumented", arg1);
      break;
    case 0x1E:
      printf("   rr (iy+%02xh)", arg1);
      break;
    case 0x1F:
      printf("   rr a,(iy+%02xh)      ; undocumented", arg1);
      break;
    case 0x20:
      printf("   sla b,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x21:
      printf("   sla c,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x22:
      printf("   sla d,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x23:
      printf("   sla e,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x24:
      printf("   sla h,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x25:
      printf("   sla l,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x26:
      printf("   sla (iy+%02xh)", arg1);
      break;
    case 0x27:
      printf("   sla a,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x28:
      printf("   sra b,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x29:
      printf("   sra c,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x2A:
      printf("   sra d,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x2B:
      printf("   sra e,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x2C:
      printf("   sra h,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x2D:
      printf("   sra l,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x2E:
      printf("   sra (iy+%02xh)", arg1);
      break;
    case 0x2F:
      printf("   sra a,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x30:
      printf("   sl1 b,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x31:
      printf("   sl1 c,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x32:
      printf("   sl1 d,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x33:
      printf("   sl1 e,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x34:
      printf("   sl1 h,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x35:
      printf("   sl1 l,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x36:
      printf("   sl1 (iy+%02xh)       ; undocumented", arg1);
      break;
    case 0x37:
      printf("   sl1 a,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x38:
      printf("   srl b,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x39:
      printf("   srl c,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x3A:
      printf("   srl d,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x3B:
      printf("   srl e,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x3C:
      printf("   srl h,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x3D:
      printf("   srl l,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x3E:
      printf("   srl (iy+%02xh)", arg1);
      break;
    case 0x3F:
      printf("   srl a,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x47:
      printf("   bit 0,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x46:
      printf("   bit 0,(iy+%02xh)", arg1);
      break;
    case 0x48:
    case 0x49:
    case 0x4A:
    case 0x4B:
    case 0x4C:
    case 0x4D:
    case 0x4F:
      printf("   bit 1,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x4E:
      printf("   bit 1,(iy+%02xh)", arg1);
      break;
    case 0x50:
    case 0x51:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x57:
      printf("   bit 2,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x56:
      printf("   bit 2,(iy+%02xh)", arg1);
      break;
    case 0x58:
    case 0x59:
    case 0x5A:
    case 0x5B:
    case 0x5C:
    case 0x5D:
    case 0x5F:
      printf("   bit 3,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x5E:
      printf("   bit 3,(iy+%02xh)", arg1);
      break;
    case 0x60:
    case 0x61:
    case 0x62:
    case 0x63:
    case 0x64:
    case 0x65:
    case 0x67:
      printf("   bit 4,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x66:
      printf("   bit 4,(iy+%02xh)", arg1);
      break;
    case 0x68:
    case 0x69:
    case 0x6A:
    case 0x6B:
    case 0x6C:
    case 0x6D:
    case 0x6F:
      printf("   bit 5,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x6E:
      printf("   bit 5,(iy+%02xh)", arg1);
      break;
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x73:
    case 0x74:
    case 0x75:
    case 0x77:
      printf("   bit 6,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x76:
      printf("   bit 6,(iy+%02xh)", arg1);
      break;
    case 0x78:
    case 0x79:
    case 0x7A:
    case 0x7B:
    case 0x7C:
    case 0x7D:
    case 0x7F:
      printf("   bit 7,(iy+%02xh)     ; undocumented", arg1);
      break;
    case 0x7E:
      printf("   bit 7,(iy+%02xh)", arg1);
      break;
    case 0x80:
      printf("   res b,0,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x81:
      printf("   res c,0,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x82:
      printf("   res d,0,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x83:
      printf("   res e,0,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x84:
      printf("   res h,0,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x85:
      printf("   res l,0,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x86:
      printf("   res 0,(iy+%02xh)", arg1);
      break;
    case 0x87:
      printf("   res a,0,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x88:
      printf("   res b,1,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x89:
      printf("   res c,1,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x8A:
      printf("   res d,1,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x8B:
      printf("   res e,1,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x8C:
      printf("   res h,1,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x8D:
      printf("   res l,1,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x8E:
      printf("   res 1,(iy+%02xh)", arg1);
      break;
    case 0x8F:
      printf("   res a,1,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x90:
      printf("   res b,2,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x91:
      printf("   res c,2,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x92:
      printf("   res d,2,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x93:
      printf("   res e,2,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x94:
      printf("   res h,2,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x95:
      printf("   res l,2,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x96:
      printf("   res 2,(iy+%02xh)", arg1);
      break;
    case 0x97:
      printf("   res a,2,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x98:
      printf("   res b,3,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x99:
      printf("   res c,3,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x9A:
      printf("   res d,3,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x9B:
      printf("   res e,3,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x9C:
      printf("   res h,3,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x9D:
      printf("   res l,3,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0x9E:
      printf("   res 3,(iy+%02xh)", arg1);
      break;
    case 0x9F:
      printf("   res a,3,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xA0:
      printf("   res b,4,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xA1:
      printf("   res c,4,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xA2:
      printf("   res d,4,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xA3:
      printf("   res e,4,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xA4:
      printf("   res h,4,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xA5:
      printf("   res l,4,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xA6:
      printf("   res 4,(iy+%02xh)", arg1);
      break;
    case 0xA7:
      printf("   res a,4,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xA8:
      printf("   res b,5,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xA9:
      printf("   res c,5,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xAA:
      printf("   res d,5,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xAB:
      printf("   res e,5,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xAC:
      printf("   res h,5,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xAD:
      printf("   res l,5,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xAE:
      printf("   res 5,(iy+%02xh)", arg1);
      break;
    case 0xAF:
      printf("   res a,5,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xB0:
      printf("   res b,6,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xB1:
      printf("   res c,6,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xB2:
      printf("   res d,6,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xB3:
      printf("   res e,6,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xB4:
      printf("   res h,6,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xB5:
      printf("   res l,6,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xB6:
      printf("   res 6,(iy+%02xh)", arg1);
      break;
    case 0xB7:
      printf("   res a,6,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xB8:
      printf("   res b,7,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xB9:
      printf("   res c,7,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xBA:
      printf("   res d,7,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xBB:
      printf("   res e,7,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xBC:
      printf("   res h,7,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xBD:
      printf("   res l,7,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xBE:
      printf("   res 7,(iy+%02xh)", arg1);
      break;
    case 0xBF:
      printf("   res a,7,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xC0:
      printf("   set b,0,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xC1:
      printf("   set c,0,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xC2:
      printf("   set d,0,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xC3:
      printf("   set e,0,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xC4:
      printf("   set h,0,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xC5:
      printf("   set l,0,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xC6:
      printf("   set 0,(iy+%02xh)", arg1);
      break;
    case 0xC7:
      printf("   set a,0,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xC8:
      printf("   set b,1,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xC9:
      printf("   set c,1,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xCA:
      printf("   set d,1,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xCB:
      printf("   set e,1,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xCC:
      printf("   set h,1,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xCD:
      printf("   set l,1,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xCE:
      printf("   set 1,(iy+%02xh)", arg1);
      break;
    case 0xCF:
      printf("   set a,1,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xD0:
      printf("   set b,2,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xD1:
      printf("   set c,2,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xD2:
      printf("   set d,2,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xD3:
      printf("   set e,2,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xD4:
      printf("   set h,2,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xD5:
      printf("   set l,2,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xD6:
      printf("   set 2,(iy+%02xh)", arg1);
      break;
    case 0xD7:
      printf("   set a,2,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xD8:
      printf("   set b,3,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xD9:
      printf("   set c,3,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xDA:
      printf("   set d,3,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xDB:
      printf("   set e,3,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xDC:
      printf("   set h,3,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xDD:
      printf("   set l,3,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xDE:
      printf("   set 3,(iy+%02xh)", arg1);
      break;
    case 0xDF:
      printf("   set a,3,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xE0:
      printf("   set b,4,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xE1:
      printf("   set c,4,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xE2:
      printf("   set d,4,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xE3:
      printf("   set e,4,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xE4:
      printf("   set h,4,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xE5:
      printf("   set l,4,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xE6:
      printf("   set 4,(iy+%02xh)", arg1);
      break;
    case 0xE7:
      printf("   set a,4,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xE8:
      printf("   set b,5,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xE9:
      printf("   set c,5,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xEA:
      printf("   set d,5,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xEB:
      printf("   set e,5,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xEC:
      printf("   set h,5,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xED:
      printf("   set l,5,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xEE:
      printf("   set 5,(iy+%02xh)", arg1);
      break;
    case 0xEF:
      printf("   set a,5,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xF0:
      printf("   set b,6,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xF1:
      printf("   set c,6,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xF2:
      printf("   set d,6,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xF3:
      printf("   set e,6,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xF4:
      printf("   set h,6,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xF5:
      printf("   set l,6,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xF6:
      printf("   set 6,(iy+%02xh)", arg1);
      break;
    case 0xF7:
      printf("   set a,6,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xF8:
      printf("   set b,7,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xF9:
      printf("   set c,7,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xFA:
      printf("   set d,7,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xFB:
      printf("   set e,7,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xFC:
      printf("   set h,7,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xFD:
      printf("   set l,7,(iy+%02xh)   ; undocumented", arg1);
      break;
    case 0xFE:
      printf("   set 7,(iy+%02xh)", arg1);
      break;
    case 0xFF:
      printf("   set a,7,(iy+%02xh)   ; undocumented", arg1);
      break;
    default:
      printf("   Invalid opcode");
      fseek(IN, -1, SEEK_CUR);
      offset--;
  }//switch
}//disasFDCB

void disasFD(void) {
  byte arg1 = 0x0,
       arg2 = 0x0,
       b = readbyte();

  switch (b) {
    case 0x00:
      if (!feof(IN))
        printf("         nop                ; undocumented (dup)");
      break;
    case 0x01:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld bc,%02x%02xh        ; undocumented (dup)", arg2, arg1);
      break;
    case 0x02:
      printf("         ld (bc),a          ; undocumented (dup)");
      break;
    case 0x03:
      printf("         inc bc             ; undocumented (dup)");
      break;
    case 0x04:
      printf("         inc b              ; undocumented (dup)");
      break;
    case 0x05:
      printf("         dec b              ; undocumented (dup)");
      break;
    case 0x06:
      arg1 = readbyte();
      printf("      ld b,%02xh           ; undocumented (dup)", arg1);
      break;
    case 0x07:
      printf("         rlca               ; undocumented (dup)");
      break;
    case 0x08:
      printf("         ex af,af'          ; undocumented (dup)");
      break;
    case 0x09:
      printf("         add iy,bc");
      break;
    case 0x0A:
      printf("         ld a,(bc)          ; undocumented (dup)");
      break;
    case 0x0B:
      printf("         dec bc             ; undocumented (dup)");
      break;
    case 0x0C:
      printf("         inc c              ; undocumented (dup)");
      break;
    case 0x0D:
      printf("         dec c              ; undocumented (dup)");
      break;
    case 0x0E:
      arg1 = readbyte();
      printf("      ld c,%02xh           ; undocumented (dup)", arg1);
      break;
    case 0x0F:
      printf("         rrca               ; undocumented (dup)");
      break;
    case 0x10:
      arg1 = readbyte();
      printf("      djnz %02xh           ; undocumented (dup)", arg1);
      break;
    case 0x11:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld de,%02x%02xh        ; undocumented (dup)", arg2, arg1);
      break;
    case 0x12:
      printf("         ld (de),a          ; undocumented (dup)");
      break;
    case 0x13:
      printf("         inc de             ; undocumented (dup)");
      break;
    case 0x14:
      printf("         inc d              ; undocumented (dup)");
      break;
    case 0x15:
      printf("         dec d              ; undocumented (dup)");
      break;
    case 0x16:
      arg1 = readbyte();
      printf("      ld d,%02xh           ; undocumented (dup)", arg1);
      break;
    case 0x17:
      printf("         rla                ; undocumented (dup)");
      break;
    case 0x18:
      arg1 = readbyte();
      printf("      jr %02xh             ; undocumented (dup)", arg1);
      break;
    case 0x19:
      printf("         add iy,de");
      break;
    case 0x1A:
      printf("         ld a,(de)          ; undocumented (dup)");
      break;
    case 0x1B:
      printf("         dec de             ; undocumented (dup)");
      break;
    case 0x1C:
      printf("         inc e              ; undocumented (dup)");
      break;
    case 0x1D:
      printf("         dec e              ; undocumented (dup)");
      break;
    case 0x1E:
      arg1 = readbyte();
      printf("      ld e,%02xh           ; undocumented (dup)", arg1);
      break;
    case 0x1F:
      printf("         rra                ; undocumented (dup)");
      break;
    case 0x20:
      arg1 = readbyte();
      printf("      jr nz,%02xh          ; undocumented (dup)", arg1);
      break;
    case 0x21:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld iy,%02x%02xh", arg2, arg1);
      break;
    case 0x22:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld (%02x%02xh),iy", arg2, arg1);
      break;
    case 0x23:
      printf("         inc iy");
      break;
    case 0x24:
      printf("         inc hy             ; undocumented");
      break;
    case 0x25:
      printf("         dec hy             ; undocumented");
      break; 
    case 0x26:
      arg1 = readbyte();
      printf("      ld hy,%02xh          ; undocumented", arg1);
      break;
    case 0x27:
      printf("         daa                ; undocumented (dup)");
      break;
    case 0x28:
      arg1 = readbyte();
      printf("      jr z,%02xh           ; undocumented (dup)", arg1);
      break;
    case 0x29:
      printf("         add iy,iy");
      break;
    case 0x2A:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld iy,(%02x%02xh)", arg2, arg1);
      break;
    case 0x2B:
      printf("         dec iy");
      break;
    case 0x2C:
      printf("         inc ly             ; undocumented");
      break;
    case 0x2D:
      printf("         dec ly             ; undocumented");
      break;
    case 0x2E:
      arg1 = readbyte();
      printf("      ld ly,%02xh          ; undocumented", arg1);
      break;
    case 0x2F:
      printf("         cpl                ; undocumented (dup)");
      break;
    case 0x30:
      arg1 = readbyte();
      printf("      jr nc,%02xh          ; undocumented (dup)", arg1);
      break;
    case 0x31:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld sp,%02x%02xh        ; undocumented (dup)", arg2, arg1);
      break;
    case 0x32:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld (%02x%02xh),a       ; undocumented (dup)", arg2, arg1);
      break;
    case 0x33:
      printf("         inc sp             ; undocumented (dup)");
      break;
    case 0x34:
      arg1 = readbyte();
      printf("      inc (iy+%02xh)", arg1);
      break;
    case 0x35:
      arg1 = readbyte();
      printf("      dec (iy+%02xh)", arg1);
      break;
    case 0x36:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld (iy+%02xh),%02xh", arg1, arg2);
      break;
    case 0x37:
      printf("         scf                ; undocumented (dup)");
      break;
    case 0x38:
      arg1 = readbyte();
      printf("      jr c,%02xh           ; undocumented (dup)", arg1);
      break;
    case 0x39:
      printf("         add iy,sp");
      break;
    case 0x3A:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   ld a,(%02x%02xh)       ; undocumented (dup)", arg2, arg1);
      break;
    case 0x3B:
      printf("         dec sp             ; undocumented (dup)");
      break;
    case 0x3C:
      printf("         inc a              ; undocumented (dup)");
      break;
    case 0x3D:
      printf("         dec a              ; undocumented (dup)");
      break;
    case 0x3E:
      arg1 = readbyte();
      printf("      ld a,%02xh           ; undocumented (dup)", arg1);
      break;
    case 0x3F:
      printf("         ccf                ; undocumented (dup)");
      break;
    case 0x40:
      printf("         ld b,b             ; undocumented (dup)");
      break;
    case 0x41:
      printf("         ld b,c             ; undocumented (dup)");
      break;
    case 0x42:
      printf("         ld b,d             ; undocumented (dup)");
      break;
    case 0x43:
      printf("         ld b,e             ; undocumented (dup)");
      break;
    case 0x44:
      printf("         ld b,hy            ; undocumented");
      break;
    case 0x45:
      printf("         ld b,ly            ; undocumented");
      break;
    case 0x46:
      arg1 = readbyte();
      printf("      ld b,(iy+%02xh)", arg1);
      break;
    case 0x47:
      printf("         ld b,a             ; undocumented (dup)");
      break;
    case 0x48:
      printf("         ld c,b             ; undocumented (dup)");
      break;
    case 0x49:
      printf("         ld c,c             ; undocumented (dup)");
      break;
    case 0x4A:
      printf("         ld c,d             ; undocumented (dup)");
      break;
    case 0x4B:
      printf("         ld c,e             ; undocumented (dup)");
      break;
    case 0x4C:
      printf("         ld c,hy            ; undocumented");
      break;
    case 0x4D:
      printf("         ld c,ly            ; undocumented");
      break;
    case 0x4E:
      arg1 = readbyte();
      printf("      ld c,(iy+%02xh)", arg1);
      break;
    case 0x4F:
      printf("         ld c,a             ; undocumented (dup)");
      break;
    case 0x50:
      printf("         ld d,b             ; undocumented (dup)");
      break;
    case 0x51:
      printf("         ld d,c             ; undocumented (dup)");
      break;
    case 0x52:
      printf("         ld d,d             ; undocumented (dup)");
      break;
    case 0x53:
      printf("         ld d,e             ; undocumented (dup)");
      break;
    case 0x54:
      printf("         ld d,hy            ; undocumented");
      break;
    case 0x55:
      printf("         ld d,ly            ; undocumented");
      break;
    case 0x56:
      arg1 = readbyte();
      printf("      ld d,(iy+%02xh)", arg1);
      break;
    case 0x57:
      printf("         ld d,a             ; undocumented (dup)");
      break;
    case 0x58:
      printf("         ld e,b             ; undocumented (dup)");
      break;
    case 0x59:
      printf("         ld e,c             ; undocumented (dup)");
      break;
    case 0x5A:
      printf("         ld e,d             ; undocumented (dup)");
      break;
    case 0x5B:
      printf("         ld e,e             ; undocumented (dup)");
      break;
    case 0x5C:
      printf("         ld e,hy            ; undocumented");
      break;
    case 0x5D:
      printf("         ld e,ly            ; undocumented");
      break;
    case 0x5E:
      arg1 = readbyte();
      printf("      ld e,(iy+%02xh)", arg1);
      break;
    case 0x5F:
      printf("         ld e,a             ; undocumented (dup)");
      break;
    case 0x60:
      printf("         ld hy,b            ; undocumented");
      break;
    case 0x61:
      printf("         ld hy,c            ; undocumented");
      break;
    case 0x62:
      printf("         ld hy,d            ; undocumented");
      break;
    case 0x63:
      printf("         ld hy,e            ; undocumented");
      break;
    case 0x64:
      printf("         ld hy,hy           ; undocumented");
      break;
    case 0x65:
      printf("         ld hy,ly           ; undocumented");
      break;
    case 0x66:
      arg1 = readbyte();
      printf("      ld h,(iy+%02xh)", arg1);
      break;
    case 0x67:
      printf("         ld hy,a            ; undocumented");
      break;
    case 0x68:
      printf("         ld ly,b            ; undocumented");
      break;
    case 0x69:
      printf("         ld ly,c            ; undocumented");
      break;
    case 0x6A:
      printf("         ld ly,d            ; undocumented");
      break;
    case 0x6B:
      printf("         ld ly,e            ; undocumented");
      break;
    case 0x6C:
      printf("         ld ly,hy           ; undocumented");
      break;
    case 0x6D:
      printf("         ld ly,ly           ; undocumented");
      break;
    case 0x6E:
      arg1 = readbyte();
      printf("      ld l,(iy+%02xh)", arg1);
      break;
    case 0x6F:
      printf("         ld ly,a            ; undocumented");
      break;
    case 0x70:
      arg1 = readbyte();
      printf("      ld (iy+%02xh),b", arg1);
      break;
    case 0x71:
      arg1 = readbyte();
      printf("      ld (iy+%02xh),c", arg1);
      break;
    case 0x72:
      arg1 = readbyte();
      printf("      ld (iy+%02xh),d", arg1);
      break;
    case 0x73:
      arg1 = readbyte();
      printf("      ld (iy+%02xh),e", arg1);
      break;
    case 0x74:
      arg1 = readbyte();
      printf("      ld (iy+%02xh),h", arg1);
      break;
    case 0x75:
      arg1 = readbyte();
      printf("      ld (iy+%02xh),l", arg1);
      break;
    case 0x76:
      printf("         halt               ; undocumented (dup)");
      break;
    case 0x77:
      arg1 = readbyte();
      printf("      ld (iy+%02xh),a", arg1);
      break;
    case 0x78:
      printf("         ld a,b             ; undocumented (dup)");
      break;
    case 0x79:
      printf("         ld a,c             ; undocumented (dup)");
      break;
    case 0x7A:
      printf("         ld a,d             ; undocumented (dup)");
      break;
    case 0x7B:
      printf("         ld a,e             ; undocumented (dup)");
      break;
    case 0x7C:
      printf("         ld a,hy            ; undocumented");
      break;
    case 0x7D:
      printf("         ld a,ly            ; undocumented");
      break;
    case 0x7E:
      arg1 = readbyte();
      printf("      ld a,(iy+%02xh)", arg1);
      break;
    case 0x7F:
      printf("         ld a,a             ; undocumented (dup)");
      break;
    case 0x80:
      printf("         add a,b            ; undocumented (dup)");
      break;
    case 0x81:
      printf("         add a,c            ; undocumented (dup)");
      break;
    case 0x82:
      printf("         add a,d            ; undocumented (dup)");
      break;
    case 0x83:
      printf("         add a,e            ; undocumented (dup)");
      break;
    case 0x84:
      printf("         add a,hy           ; undocumented");
      break;
    case 0x85:
      printf("         add a,ly           ; undocumented");
      break;
    case 0x86:
      arg1 = readbyte();
      printf("      add a,(iy+%02xh)", arg1);
      break;
    case 0x87:
      printf("         add a,a            ; undocumented (dup)");
      break;
    case 0x88:
      printf("         adc a,b            ; undocumented (dup)");
      break;
    case 0x89:
      printf("         adc a,c            ; undocumented (dup)");
      break;
    case 0x8A:
      printf("         adc a,d            ; undocumented (dup)");
      break;
    case 0x8B:
      printf("         adc a,e            ; undocumented (dup)");
      break;
    case 0x8C:
      printf("         adc a,hy           ; undocumented");
      break;
    case 0x8D:
      printf("         adc a,ly           ; undocumented");
      break;
    case 0x8E:
      arg1 = readbyte();
      printf("      adc a,(iy+%02xh)", arg1);
      break;
    case 0x8F:
      printf("         adc a,a            ; undocumented (dup)");
      break;
    case 0x90:
      printf("         sub b              ; undocumented (dup)");
      break;
    case 0x91:
      printf("         sub c              ; undocumented (dup)");
      break;
    case 0x92:
      printf("         sub d              ; undocumented (dup)");
      break;
    case 0x93:
      printf("         sub e              ; undocumented (dup)");
      break;
    case 0x94:
      printf("         sub hy             ; undocumented");
      break;
    case 0x95:
      printf("         sub ly             ; undocumented");
      break;
    case 0x96:
      arg1 = readbyte();
      printf("      sub (iy+%02xh)", arg1);
      break;
    case 0x97:
      printf("         sub a              ; undocumented (dup)");
      break;
    case 0x98:
      printf("         sbc a,b            ; undocumented (dup)");
      break;
    case 0x99:
      printf("         sbc a,c            ; undocumented (dup)");
      break;
    case 0x9A:
      printf("         sbc a,d            ; undocumented (dup)");
      break;
    case 0x9B:
      printf("         sbc a,e            ; undocumented (dup)");
      break;
    case 0x9C:
      printf("         sbc a,hy           ; undocumented");
      break;
    case 0x9D:
      printf("         sbc a,ly           ; undocumented");
      break;
    case 0x9E:
      arg1 = readbyte();
      printf("      sbc a,(iy+%02xh)", arg1);
      break;
    case 0x9F:
      printf("         sbc a,a            ; undocumented (dup)");
      break;
    case 0xA0:
      printf("         and b              ; undocumented (dup)");
      break;
    case 0xA1:
      printf("         and c              ; undocumented (dup)");
      break;
    case 0xA2:
      printf("         and d              ; undocumented (dup)");
      break;
    case 0xA3:
      printf("         and e              ; undocumented (dup)");
      break;
    case 0xA4:
      printf("         and hy             ; undocumented");
      break;
    case 0xA5:
      printf("         and ly             ; undocumented");
      break;
    case 0xA6:
      arg1 = readbyte();
      printf("      and (iy+%02xh)", arg1);
      break;
    case 0xA7:
      printf("         and a              ; undocumented (dup)");
      break;
    case 0xA8:
      printf("         xor b              ; undocumented (dup)");
      break;
    case 0xA9:
      printf("         xor c              ; undocumented (dup)");
      break;
    case 0xAA:
      printf("         xor d              ; undocumented (dup)");
      break;
    case 0xAB:
      printf("         xor e              ; undocumented (dup)");
      break;
    case 0xAC:
      printf("         xor hy             ; undocumented");
      break;
    case 0xAD:
      printf("         xor ly             ; undocumented");
      break;
    case 0xAE:
      arg1 = readbyte();
      printf("      xor (iy+%02xh)", arg1);
      break;
    case 0xAF:
      printf("         xor a              ; undocumented (dup)");
      break;
    case 0xB0:
      printf("         or b               ; undocumented (dup)");
      break;
    case 0xB1:
      printf("         or c               ; undocumented (dup)");
      break;
    case 0xB2:
      printf("         or d               ; undocumented (dup)");
      break;
    case 0xB3:
      printf("         or e               ; undocumented (dup)");
      break;
    case 0xB4:
      printf("         or hy              ; undocumented");
      break;
    case 0xB5:
      printf("         or ly              ; undocumented");
      break;
    case 0xB6:
      arg1 = readbyte();
      printf("      or (iy+%02xh)", arg1);
      break;
    case 0xB7:
      printf("         or a               ; undocumented (dup)");
      break;
    case 0xB8:
      printf("         cp b               ; undocumented (dup)");
      break;
    case 0xB9:
      printf("         cp c               ; undocumented (dup)");
      break;
    case 0xBA:
      printf("         cp d               ; undocumented (dup)");
      break;
    case 0xBB:
      printf("         cp e               ; undocumented (dup)");
      break;
    case 0xBC:
      printf("         cp hy              ; undocumented");
      break;
    case 0xBD:
      printf("         cp ly              ; undocumented");
      break;
    case 0xBE:
      arg1 = readbyte();
      printf("      cp (iy+%02xh)", arg1);
      break;
    case 0xBF:
      printf("         cp a               ; undocumented (dup)");
      break;
    case 0xC0:
      printf("         ret nz             ; undocumented (dup)");
      break;
    case 0xC1:
      printf("         pop bc             ; undocumented (dup)");
      break;
    case 0xC2:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   jp nz,%02x%02xh        ; undocumented (dup)", arg2, arg1);
      break;
    case 0xC3:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   jp %02x%02xh           ; undocumented (dup)", arg2, arg1);
      break;
    case 0xC4:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   call nz,%02x%02xh      ; undocumented (dup)", arg2, arg1);
      break;
    case 0xC5:
      printf("         push bc            ; undocumented (dup)");
      break;
    case 0xC6:
      arg1 = readbyte();
      printf("      add a,%02xh          ; undocumented (dup)", arg1);
      break;
    case 0xC7:
      printf("         rst 00H            ; undocumented (dup)");
      break;
    case 0xC8:
      printf("         ret z              ; undocumented (dup)");
      break;
    case 0xC9:
      printf("         ret                ; undocumented (dup)");
      break;
    case 0xCA:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   jp z,%02x%02xh         ; undocumented (dup)", arg2, arg1);
      break;
    case 0xCB:
      disasFDCB();
      break;
    case 0xCC:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   call z,%02x%02xh       ; undocumented (dup)", arg2, arg1);
      break;
    case 0xCD:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   call %02x%02xh         ; undocumented (dup)", arg2, arg1);
      break;
    case 0xCE:
      arg1 = readbyte();
      printf("      adc a,%02xh          ; undocumented (dup)", arg1);
      break;
    case 0xCF:
      printf("         rst 08H            ; undocumented (dup)");
      break;
    case 0xD0:
      printf("         ret nc             ; undocumented (dup)");
      break;
    case 0xD1:
      printf("         pop de             ; undocumented (dup)");
      break;
    case 0xD2:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   jp nc,%02x%02xh        ; undocumented (dup)", arg2, arg1);
      break;
    case 0xD3:
      arg1 = readbyte();
      printf("      out (%02xh),a        ; undocumented (dup)", arg1);
      break;
    case 0xD4:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   call nc,%02x%02xh      ; undocumented (dup)", arg2, arg1);
      break;
    case 0xD5:
      printf("         push de            ; undocumented (dup)");
      break;
    case 0xD6:
      arg1 = readbyte();
      printf("      sub %02xh            ; undocumented (dup)", arg1);
      break;
    case 0xD7:
      printf("         rst 10H            ; undocumented (dup)");
      break;
    case 0xD8:
      printf("         ret c              ; undocumented (dup)");
      break;
    case 0xD9:
      printf("         exx                ; undocumented (dup)");
      break;
    case 0xDA:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   jp c,%02x%02xh         ; undocumented (dup)", arg2, arg1);
      break;
    case 0xDB:
      arg1 = readbyte();
      printf("      in a,(%02xh)         ; undocumented (dup)", arg1);
      break;
    case 0xDC:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   call c,%02x%02xh       ; undocumented (dup)", arg2, arg1);
      break;
    case 0xDD:
      printf("         nop                ; undocumented (dup)");
      fseek(IN, -1, SEEK_CUR);
      offset--;
      break;
    case 0xDE:
      arg1 = readbyte();
      printf("      sbc a,%02xh          ; undocumented (dup)", arg1);
      break;
    case 0xDF:
      printf("         rst 18H            ; undocumented (dup)");
      break;
    case 0xE0:
      printf("         ret po             ; undocumented (dup)");
      break;
    case 0xE1:
      printf("         pop iy");
      break;
    case 0xE2:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   jp po,%02x%02xh        ; undocumented (dup)", arg2, arg1);
      break;
    case 0xE3:
      printf("         ex (sp),iy");
      break;
    case 0xE4:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   call po,%02x%02xh      ; undocumented (dup)", arg2, arg1);
      break;
    case 0xE5:
      printf("         push iy");
      break;
    case 0xE6:
      arg1 = readbyte();
      printf("      and %02xh            ; undocumented (dup)", arg1);
      break;
    case 0xE7:
      printf("         rst 20H            ; undocumented (dup)");
      break;
    case 0xE8:
      printf("         ret pe             ; undocumented (dup)");
      break;
    case 0xE9:
      printf("         jp (iy)");
      break;
    case 0xEA:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   jp pe,%02x%02xh        ; undocumented (dup)", arg2, arg1);
      break;
    case 0xEB:
      printf("         ex de,hl           ; undocumented (dup)");
      break;
    case 0xEC:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   call pe,%02x%02xh      ; undocumented (dup)", arg2, arg1);
      break;
    case 0xED:
      printf("         nop                ; undocumented (dup)");
      fseek(IN, -1, SEEK_CUR);
      offset--;
      break;
    case 0xEE:
      arg1 = readbyte();
      printf("      xor %02xh            ; undocumented (dup)", arg1);
      break;
    case 0xEF:
      printf("         rst 28H            ; undocumented (dup)");
      break;
    case 0xF0:
      printf("         ret p              ; undocumented (dup)");
      break;
    case 0xF1:
      printf("         pop af             ; undocumented (dup)");
      break;
    case 0xF2:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   jp p,%02x%02xh         ; undocumented (dup)", arg2, arg1);
      break;
    case 0xF3:
      printf("         di                 ; undocumented (dup)");
      break;
    case 0xF4:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   call p,%02x%02xh       ; undocumented (dup)", arg2, arg1);
      break;
    case 0xF5:
      printf("         push af            ; undocumented (dup)");
      break;
    case 0xF6:
      arg1 = readbyte();
      printf("      or %02xh             ; undocumented (dup)", arg1);
      break;
    case 0xF7:
      printf("         rst 30H            ; undocumented (dup)");
      break;
    case 0xF8:
      printf("         ret m              ; undocumented (dup)");
      break;
    case 0xF9:
      printf("         ld sp,iy");
      break;
    case 0xFA:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   jp m,%02x%02xh         ; undocumented (dup)", arg2, arg1);
      break;
    case 0xFB:
      printf("         ei                 ; undocumented (dup)");
      break;
    case 0xFC:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("   call m,%02x%02xh       ; undocumented (dup)", arg2, arg1);
      break;
    case 0xFD:
      printf("         nop                ; undocumented (dup)");
      fseek(IN, -1, SEEK_CUR);
      offset--;
      break;
    case 0xFE:
      arg1 = readbyte();
      printf("      cp %02xh             ; undocumented (dup)", arg1);
      break;
    case 0xFF:
      printf("         rst 38H            ; undocumented (dup)");
      break;
    default:
      printf("         Invalid opcode");
      fseek(IN, -1, SEEK_CUR);
      offset--;
  }//switch
}//disasFD

void disassemble(void) {
  byte arg1 = 0x0,
       arg2 = 0x0,
       b = readbyte();

  switch (b) {
    case 0x00:
      if (!feof(IN))
        printf("            nop");
      break;
    case 0x01:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      ld bc,%02x%02xh", arg2, arg1);
      break;
    case 0x02:
      printf("            ld (bc),a");
      break;
    case 0x03:
      printf("            inc bc");
      break;
    case 0x04:
      printf("            inc b");
      break;
    case 0x05:
      printf("            dec b");
      break;
    case 0x06:
      arg1 = readbyte();
      printf("         ld b,%02xh", arg1);
      break;
    case 0x07:
      printf("            rlca");
      break;
    case 0x08:
      printf("            ex af,af'");
      break;
    case 0x09:
      printf("            add hl,bc");
      break;
    case 0x0A:
      printf("            ld a,(bc)");
      break;
    case 0x0B:
      printf("            dec bc");
      break;
    case 0x0C:
      printf("            inc c");
      break;
    case 0x0D:
      printf("            dec c");
      break;
    case 0x0E:
      arg1 = readbyte();
      printf("         ld c,%02xh", arg1);
      break;
    case 0x0F:
      printf("            rrca");
      break;
    case 0x10:
      arg1 = readbyte();
      printf("         djnz %02xh", arg1);
      break;
    case 0x11:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      ld de,%02x%02xh", arg2, arg1);
      break;
    case 0x12:
      printf("            ld (de),a");
      break;
    case 0x13:
      printf("            inc de");
      break;
    case 0x14:
      printf("            inc d");
      break;
    case 0x15:
      printf("            dec d");
      break;
    case 0x16:
      arg1 = readbyte();
      printf("         ld d,%02xh", arg1);
      break;
    case 0x17:
      printf("            rla");
      break;
    case 0x18:
      arg1 = readbyte();
      printf("         jr %02xh", arg1);
      break;
    case 0x19:
      printf("            add hl,de");
      break;
    case 0x1A:
      printf("            ld a,(de)");
      break;
    case 0x1B:
      printf("            dec de");
      break;
    case 0x1C:
      printf("            inc e");
      break;
    case 0x1D:
      printf("            dec e");
      break;
    case 0x1E:
      arg1 = readbyte();
      printf("         ld e,%02xh", arg1);
      break;
    case 0x1F:
      printf("            rra");
      break;
    case 0x20:
      arg1 = readbyte();
      printf("         jr nz,%02xh", arg1);
      break;
    case 0x21:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      ld hl,%02x%02xh", arg2, arg1);
      break;
    case 0x22:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      ld (%02x%02xh),hl", arg2, arg1);
      break;
    case 0x23:
      printf("            inc hl");
      break;
    case 0x24:
      printf("            inc h");
      break;
    case 0x25:
      printf("            dec h");
      break;
    case 0x26:
      arg1 = readbyte();
      printf("         ld h,%02xh", arg1);
      break;
    case 0x27:
      printf("            daa");
      break;
    case 0x28:
      arg1 = readbyte();
      printf("         jr z,%02xh", arg1);
      break;
    case 0x29:
      printf("            add hl,hl");
      break;
    case 0x2A:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      ld hl,(%02x%02xh)", arg2, arg1);
      break;
    case 0x2B:
      printf("            dec hl");
      break;
    case 0x2C:
      printf("            inc l");
      break;
    case 0x2D:
      printf("            dec l");
      break;
    case 0x2E:
      arg1 = readbyte();
      printf("         ld l,%02xh", arg1);
      break;
    case 0x2F:
      printf("            cpl");
      break;
    case 0x30:
      arg1 = readbyte();
      printf("         jr nc,%02xh", arg1);
      break;
    case 0x31:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      ld sp,%02x%02xh", arg2, arg1);
      break;
    case 0x32:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      ld (%02x%02xh),a", arg2, arg1);
      break;
    case 0x33:
      printf("            inc sp");
      break;
    case 0x34:
      printf("            inc (hl)");
      break;
    case 0x35:
      printf("            dec (hl)");
      break;
    case 0x36:
      arg1 = readbyte();
      printf("         ld (hl),%02xh", arg1);
      break;
    case 0x37:
      printf("            scf");
      break;
    case 0x38:
      arg1 = readbyte();
      printf("         jr c,%02xh", arg1);
      break;
    case 0x39:
      printf("            add hl,sp");
      break;
    case 0x3A:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      ld a,(%02x%02xh)", arg2, arg1);
      break;
    case 0x3B:
      printf("            dec sp");
      break;
    case 0x3C:
      printf("            inc a");
      break;
    case 0x3D:
      printf("            dec a");
      break;
    case 0x3E:
      arg1 = readbyte();
      printf("         ld a,%02xh", arg1);
      break;
    case 0x3F:
      printf("            ccf");
      break;
    case 0x40:
      printf("            ld b,b");
      break;
    case 0x41:
      printf("            ld b,c");
      break;
    case 0x42:
      printf("            ld b,d");
      break;
    case 0x43:
      printf("            ld b,e");
      break;
    case 0x44:
      printf("            ld b,h");
      break;
    case 0x45:
      printf("            ld b,l");
      break;
    case 0x46:
      printf("            ld b,(hl)");
      break;
    case 0x47:
      printf("            ld b,a");
      break;
    case 0x48:
      printf("            ld c,b");
      break;
    case 0x49:
      printf("            ld c,c");
      break;
    case 0x4A:
      printf("            ld c,d");
      break;
    case 0x4B:
      printf("            ld c,e");
      break;
    case 0x4C:
      printf("            ld c,h");
      break;
    case 0x4D:
      printf("            ld c,l");
      break;
    case 0x4E:
      printf("            ld c,(hl)");
      break;
    case 0x4F:
      printf("            ld c,a");
      break;
    case 0x50:
      printf("            ld d,b");
      break;
    case 0x51:
      printf("            ld d,c");
      break;
    case 0x52:
      printf("            ld d,d");
      break;
    case 0x53:
      printf("            ld d,e");
      break;
    case 0x54:
      printf("            ld d,h");
      break;
    case 0x55:
      printf("            ld d,l");
      break;
    case 0x56:
      printf("            ld d,(hl)");
      break;
    case 0x57:
      printf("            ld d,a");
      break;
    case 0x58:
      printf("            ld e,b");
      break;
    case 0x59:
      printf("            ld e,c");
      break;
    case 0x5A:
      printf("            ld e,d");
      break;
    case 0x5B:
      printf("            ld e,e");
      break;
    case 0x5C:
      printf("            ld e,h");
      break;
    case 0x5D:
      printf("            ld e,l");
      break;
    case 0x5E:
      printf("            ld e,(hl)");
      break;
    case 0x5F:
      printf("            ld e,a");
      break;
    case 0x60:
      printf("            ld h,b");
      break;
    case 0x61:
      printf("            ld h,c");
      break;
    case 0x62:
      printf("            ld h,d");
      break;
    case 0x63:
      printf("            ld h,e");
      break;
    case 0x64:
      printf("            ld h,h");
      break;
    case 0x65:
      printf("            ld h,l");
      break;
    case 0x66:
      printf("            ld h,(hl)");
      break;
    case 0x67:
      printf("            ld h,a");
      break;
    case 0x68:
      printf("            ld l,b");
      break;
    case 0x69:
      printf("            ld l,c");
      break;
    case 0x6A:
      printf("            ld l,d");
      break;
    case 0x6B:
      printf("            ld l,e");
      break;
    case 0x6C:
      printf("            ld l,h");
      break;
    case 0x6D:
      printf("            ld l,l");
      break;
    case 0x6E:
      printf("            ld l,(hl)");
      break;
    case 0x6F:
      printf("            ld l,a");
      break;
    case 0x70:
      printf("            ld (hl),b");
      break;
    case 0x71:
      printf("            ld (hl),c");
      break;
    case 0x72:
      printf("            ld (hl),d");
      break;
    case 0x73:
      printf("            ld (hl),e");
      break;
    case 0x74:
      printf("            ld (hl),h");
      break;
    case 0x75:
      printf("            ld (hl),l");
      break;
    case 0x76:
      printf("            halt");
      break;
    case 0x77:
      printf("            ld (hl),a");
      break;
    case 0x78:
      printf("            ld a,b");
      break;
    case 0x79:
      printf("            ld a,c");
      break;
    case 0x7A:
      printf("            ld a,d");
      break;
    case 0x7B:
      printf("            ld a,e");
      break;
    case 0x7C:
      printf("            ld a,h");
      break;
    case 0x7D:
      printf("            ld a,l");
      break;
    case 0x7E:
      printf("            ld a,(hl)");
      break;
    case 0x7F:
      printf("            ld a,a");
      break;
    case 0x80:
      printf("            add a,b");
      break;
    case 0x81:
      printf("            add a,c");
      break;
    case 0x82:
      printf("            add a,d");
      break;
    case 0x83:
      printf("            add a,e");
      break;
    case 0x84:
      printf("            add a,h");
      break;
    case 0x85:
      printf("            add a,l");
      break;
    case 0x86:
      printf("            add a,(hl)");
      break;
    case 0x87:
      printf("            add a,a");
      break;
    case 0x88:
      printf("            adc a,b");
      break;
    case 0x89:
      printf("            adc a,c");
      break;
    case 0x8A:
      printf("            adc a,d");
      break;
    case 0x8B:
      printf("            adc a,e");
      break;
    case 0x8C:
      printf("            adc a,h");
      break;
    case 0x8D:
      printf("            adc a,l");
      break;
    case 0x8E:
      printf("            adc a,(hl)");
      break;
    case 0x8F:
      printf("            adc a,a");
      break;
    case 0x90:
      printf("            sub b");
      break;
    case 0x91:
      printf("            sub c");
      break;
    case 0x92:
      printf("            sub d");
      break;
    case 0x93:
      printf("            sub e");
      break;
    case 0x94:
      printf("            sub h");
      break;
    case 0x95:
      printf("            sub l");
      break;
    case 0x96:
      printf("            sub (hl)");
      break;
    case 0x97:
      printf("            sub a");
      break;
    case 0x98:
      printf("            sbc a,b");
      break;
    case 0x99:
      printf("            sbc a,c");
      break;
    case 0x9A:
      printf("            sbc a,d");
      break;
    case 0x9B:
      printf("            sbc a,e");
      break;
    case 0x9C:
      printf("            sbc a,h");
      break;
    case 0x9D:
      printf("            sbc a,l");
      break;
    case 0x9E:
      printf("            sbc a,(hl)");
      break;
    case 0x9F:
      printf("            sbc a,a");
      break;
    case 0xA0:
      printf("            and b");
      break;
    case 0xA1:
      printf("            and c");
      break;
    case 0xA2:
      printf("            and d");
      break;
    case 0xA3:
      printf("            and e");
      break;
    case 0xA4:
      printf("            and h");
      break;
    case 0xA5:
      printf("            and l");
      break;
    case 0xA6:
      printf("            and (hl)");
      break;
    case 0xA7:
      printf("            and a");
      break;
    case 0xA8:
      printf("            xor b");
      break;
    case 0xA9:
      printf("            xor c");
      break;
    case 0xAA:
      printf("            xor d");
      break;
    case 0xAB:
      printf("            xor e");
      break;
    case 0xAC:
      printf("            xor h");
      break;
    case 0xAD:
      printf("            xor l");
      break;
    case 0xAE:
      printf("            xor (hl)");
      break;
    case 0xAF:
      printf("            xor a");
      break;
    case 0xB0:
      printf("            or b");
      break;
    case 0xB1:
      printf("            or c");
      break;
    case 0xB2:
      printf("            or d");
      break;
    case 0xB3:
      printf("            or e");
      break;
    case 0xB4:
      printf("            or h");
      break;
    case 0xB5:
      printf("            or l");
      break;
    case 0xB6:
      printf("            or (hl)");
      break;
    case 0xB7:
      printf("            or a");
      break;
    case 0xB8:
      printf("            cp b");
      break;
    case 0xB9:
      printf("            cp c");
      break;
    case 0xBA:
      printf("            cp d");
      break;
    case 0xBB:
      printf("            cp e");
      break;
    case 0xBC:
      printf("            cp h");
      break;
    case 0xBD:
      printf("            cp l");
      break;
    case 0xBE:
      printf("            cp (hl)");
      break;
    case 0xBF:
      printf("            cp a");
      break;
    case 0xC0:
      printf("            ret nz");
      break;
    case 0xC1:
      printf("            pop bc");
      break;
    case 0xC2:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      jp nz,%02x%02xh", arg2, arg1);
      break;
    case 0xC3:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      jp %02x%02xh", arg2, arg1);
      break;
    case 0xC4:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      call nz,%02x%02xh", arg2, arg1);
      break;
    case 0xC5:
      printf("            push bc");
      break;
    case 0xC6:
      arg1 = readbyte();
      printf("         add a,%02xh", arg1);
      break;
    case 0xC7:
      printf("            rst 00H");
      break;
    case 0xC8:
      printf("            ret z");
      break;
    case 0xC9:
      printf("            ret");
      break;
    case 0xCA:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      jp z,%02x%02xh", arg2, arg1);
      break;
    case 0xCB:
      disasCB();
      break;
    case 0xCC:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      call z,%02x%02xh", arg2, arg1);
      break;
    case 0xCD:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      call %02x%02xh", arg2, arg1);
      break;
    case 0xCE:
      arg1 = readbyte();
      printf("         adc a,%02xh", arg1);
      break;
    case 0xCF:
      printf("            rst 08H");
      break;
    case 0xD0:
      printf("            ret nc");
      break;
    case 0xD1:
      printf("            pop de");
      break;
    case 0xD2:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      jp nc,%02x%02xh", arg2, arg1);
      break;
    case 0xD3:
      arg1 = readbyte();
      printf("         out (%02xh),a", arg1);
      break;
    case 0xD4:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      call nc,%02x%02xh", arg2, arg1);
      break;
    case 0xD5:
      printf("            push de");
      break;
    case 0xD6:
      arg1 = readbyte();
      printf("         sub %02xh", arg1);
      break;
    case 0xD7:
      printf("            rst 10H");
      break;
    case 0xD8:
      printf("            ret c");
      break;
    case 0xD9:
      printf("            exx");
      break;
    case 0xDA:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      jp c,%02x%02xh", arg2, arg1);
      break;
    case 0xDB:
      arg1 = readbyte();
      printf("         in a,(%02xh)", arg1);
      break;
    case 0xDC:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      call c,%02x%02xh", arg2, arg1);
      break;
    case 0xDD:
      disasDD();
      break;
    case 0xDE:
      arg1 = readbyte();
      printf("         sbc a,%02xh", arg1);
      break;
    case 0xDF:
      printf("            rst 18H");
      break;
    case 0xE0:
      printf("            ret po");
      break;
    case 0xE1:
      printf("            pop hl");
      break;
    case 0xE2:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      jp po,%02x%02xh", arg2, arg1);
      break;
    case 0xE3:
      printf("            ex (sp),hl");
      break;
    case 0xE4:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      call po,%02x%02xh", arg2, arg1);
      break;
    case 0xE5:
      printf("            push hl");
      break;
    case 0xE6:
      arg1 = readbyte();
      printf("         and %02xh", arg1);
      break;
    case 0xE7:
      printf("            rst 20H");
      break;
    case 0xE8:
      printf("            ret pe");
      break;
    case 0xE9:
      printf("            jp (hl)");
      break;
    case 0xEA:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      jp pe,%02x%02xh", arg2, arg1);
      break;
    case 0xEB:
      printf("            ex de,hl");
      break;
    case 0xEC:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      call pe,%02x%02xh", arg2, arg1);
      break;
    case 0xED:
      disasED();
      break;
    case 0xEE:
      arg1 = readbyte();
      printf("         xor %02xh", arg1);
      break;
    case 0xEF:
      printf("            rst 28H");
      break;
    case 0xF0:
      printf("            ret p");
      break;
    case 0xF1:
      printf("            pop af");
      break;
    case 0xF2:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      jp p,%02x%02xh", arg2, arg1);
      break;
    case 0xF3:
      printf("            di");
      break;
    case 0xF4:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      call p,%02x%02xh", arg2, arg1);
      break;
    case 0xF5:
      printf("            push af");
      break;
    case 0xF6:
      arg1 = readbyte();
      printf("         or %02xh", arg1);
      break;
    case 0xF7:
      printf("            rst 30H");
      break;
    case 0xF8:
      printf("            ret m");
      break;
    case 0xF9:
      printf("            ld sp,hl");
      break;
    case 0xFA:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      jp m,%02x%02xh", arg2, arg1);
      break;
    case 0xFB:
      printf("            ei");
      break;
    case 0xFC:
      arg1 = readbyte();
      arg2 = readbyte();
      printf("      call m,%02x%02xh", arg2, arg1);
      break;
    case 0xFD:
      disasFD();
      break;
    case 0xFE:
      arg1 = readbyte();
      printf("         cp %02xh", arg1);
      break;
    case 0xFF:
      printf("            rst 38H");
      break;
    default:
      printf("            Invalid opcode");
  }//switch
}//disassemble
