#ifndef __IMD_SPLIT_H__
#define __IMD_SPLIT_H__

#include <stddef.h>

struct StrArray
{
  char** strings;
  size_t size;
};

struct StrArray split (char*);

#endif
