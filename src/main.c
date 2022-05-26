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
#include "chars.h"

size_t intLen (int x)
{
  size_t i;
  for (i = 0; x; x/=10)
  {
    i++;
  }

  return i;
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

  // get i size
  size_t iSize = intLen(sa.size+1);

  // print data raw
  if (s.flags & SETTINGS_FLAG_RAW)
  {
    if (!(s.flags & SETTINGS_FLAG_NO_DEC))
    {
      // print file name
      printf(BOX_TEXT_C "%s\n", s.file);

      // print top of box
      printf(BOX_C);

      for (size_t i = 0; i<s.win_cols; i++)
      {
        if (i == (iSize+1))
        {
          printf(TBAR_TOP);

          continue;
        }

        printf(HBAR);
      }

      printf("\n");
    }

    // print lines
    for (size_t i = 0; i<sa.size; i++)
    {
      if (!(s.flags & SETTINGS_FLAG_NO_DEC))
      {
        // print box and padding
        printf(BOX_TEXT_C "%lu ", i+1);

        for (size_t j = 0; j<(iSize-intLen(i+1)); j++)
        {
          printf(" ");
        }

        printf(BOX_C VBAR " \x1b[0m");
      }

      // print line
      printf("%s\n", sa.strings[i]);
    }

    // print bottom of the box
    if (!(s.flags & SETTINGS_FLAG_NO_DEC))
    {
      printf(BOX_C);

      for (size_t i = 0; i<(iSize+1); i++)
      {
        printf(HBAR);
      }

      printf(BR_CORNER "\n");
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
