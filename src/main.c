#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include "conf.h"
#include "settings.h"
#include "reader.h"
#include "styling.h"
#include "split.h"

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

  if (!(s.flags & SETTINGS_FLAG_NO_DEC))
  {

  }

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
