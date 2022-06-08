#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#define SETTINGS_FLAG_PIPE      0b0001
#define SETTINGS_FLAG_RAW       0b0010
#define SETTINGS_FLAG_NO_DEC    0b0100
#define SETTINGS_FLAG_NO_SYNTAX 0b1000

#include "stddef.h"

struct Settings
{
  char* file;
  size_t win_rows;
  size_t win_cols;
  int flags:4;
};

struct Settings getSet (const int, const char**);

#endif
