#include <stdlib.h>
#include <string.h>
#include "split.h"

struct StrArray split (char* data)
{
  register struct StrArray sa;
  sa.strings       = (char**)malloc(1 * sizeof(char*));
  sa.size          = 1;
  sa.strings[0]    = (char*)malloc(1 * sizeof(char));
  sa.strings[0][0] = (char)0;

  size_t csz = 1;

  for (register size_t i = 0; data[i]!=(char)0; i++)
  {
    if (data[i] == '\n')
    {
      sa.size++;
      sa.strings = (char**)realloc(sa.strings, sa.size * sizeof(char*));
      sa.strings[sa.size-1] = (char*)malloc(1 * sizeof(char));
      sa.strings[sa.size-1][0] = (char)0;
      csz = 1;

      continue;
    }

    sa.strings[sa.size-1] = (char*)realloc(
      sa.strings[sa.size-1],
      ++csz * sizeof(char)
    );
    strncat(sa.strings[sa.size-1], &data[i], 1);
  }

  return sa;
}
