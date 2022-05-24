#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include "conf.h"
#include "settings.h"
#include "reader.h"

#define OVERRIDE 0b1
#define HEADER   0b10
#define LIST     0b100
#define TAB      0b1000

void style (char* data)
{
  int flags = 0;
  unsigned int hcount = 0;

  printf("\x1b[0m" DEF_C);

  for (size_t i = 0; data[i]!=0; i++)
  {
    if (!(flags & OVERRIDE))
    {
      switch (data[i])
      {
        case '#':
          hcount++;
          flags |= HEADER;

          continue;
        case '-':
          printf(LIST_C);

          flags |= LIST;

        case '>':
          printf(TAB_LIST_C);

          flags |= TAB;

          break;
        case '\n':
          goto newline;
        default:
          if (flags & HEADER)
          {
            flags |= OVERRIDE;

            if (hcount == 1)
            {
              printf(H1_C);
            }
            else if (hcount == 2)
            {
              printf(H2_C);
            }
            else
            {
              printf(H3_C);
            }
          }
          else if (flags & LIST || flags & TAB)
          {
            printf("\x1b[0m" DEF_C);
          }

          break;
      }
    }
    else
    {
      newline:
        if (data[i] == '\n')
        {
          flags = 0;
          hcount = 0;
          printf("\x1b[0m" DEF_C);
        }
    }

    printf("%c", data[i]);
  }
}

int main (const int argc, const char** argv)
{
  // get settings
  struct Settings s = getSet(argc, argv);

  // read file
  char* data = reader(s);

  style(data);

  // free data
  free(data);
  free(s.file);

  return 0;
}
