#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include "conf.h"
#include "settings.h"
#include "reader.h"
#include "styling.h"

struct StrArray
{
  char** strings;
  size_t size;
};

struct StrArray split (char* data)
{
  struct StrArray sa;
  sa.strings       = malloc(1 * sizeof(char*));
  sa.size          = 1;
  sa.strings[0]    = malloc(1 * sizeof(char));
  sa.strings[0][0] = 0;

  size_t csz = 1;

  for (register size_t i = 0; data[i]!=0; i++)
  {
    if (data[i] == '\n')
    {
      sa.size++;
      sa.strings = realloc(sa.strings, sa.size * sizeof(char*));
      sa.strings[sa.size-1] = malloc(1 * sizeof(char));
      sa.strings[sa.size-1][0] = 0;
      csz = 1;

      continue;
    }

    sa.strings[sa.size-1] = realloc(sa.strings[sa.size-1], ++csz * sizeof(char*));
    strncat(sa.strings[sa.size-1], &data[i], 1);
  }

  return sa;
}

int main (const int argc, const char** argv)
{
  // get settings
  struct Settings s = getSet(argc, argv);

  // read file
  char* data = reader(s);

  // style data
  char* out = style(data, s);
  free(data);

  // split into lines
  struct StrArray sa = split(out);
  free(out);

  if (s.flags & SETTINGS_FLAG_RAW)
  {
    for (size_t i = 0; i<sa.size; i++)
    {
      printf("%s\n", sa.strings[i]);
    }
  }
  else
  {
    // Less feature
  }

  // free lines
  for (sa.size--; sa.size; sa.size--)
  {
    free(sa.strings[sa.size]);
  }
  free(sa.strings[0]);
  free(sa.strings);

  // free input file name
  free(s.file);

  return 0;
}
