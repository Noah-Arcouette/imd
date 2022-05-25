#ifndef __IMD_STYLING_H__
#define __IMD_STYLING_H__
#include "settings.h"

#define OVERRIDE  0b1
#define HEADER    0b10
#define LIST      0b100
#define TAB       0b1000
#define ALT       0b10000
#define LINK      0b100000
#define UNDERLINE 0b1000000
#define IDDONE    0b10000000
#define ITAL      0b100000000
#define SYNTAX    0b1000000000
#define SYN_IN    0b10000000000

char* style (char*, struct Settings);

#endif
