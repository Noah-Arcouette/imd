#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include "conf.h"
#include "settings.h"
#include "reader.h"

#define STYLED_HEADER 0b01
#define STYLED_SPACE  0b10

void style (char* data)
{
  register char* out = malloc(1);
  register size_t out_sz = 1;
  out[0] = 0;

  int hcount = 0;
  int flags = 0;

  char* color = NULL;

  for (register size_t i = 0; data[i]!=0; i++)
  {
    switch (data[i])
    {
      case '#':
        hcount++;

        flags |= STYLED_HEADER | STYLED_SPACE;

        if (hcount == 1)
        {
          color = realloc(color, sizeof(H1_C));
          strcpy(color, H1_C);
        }
        else if (hcount == 2)
        {
          color = realloc(color, sizeof(H2_C));
          strcpy(color, H2_C);
        }
        else
        {
          color = realloc(color, sizeof(H3_C));
          strcpy(color, H3_C);
        }

        break;
      case ' ':
        if (flags & STYLED_HEADER)
        {
          out_sz += strlen(color);
          out = realloc(out, out_sz);
          strcat(out, color);
        }

        if (!(flags & STYLED_SPACE))
          goto dump;

        flags &= ~STYLED_SPACE;

        break;
      case '\n':
        // clear all flags
        hcount = 0;

        // clear color
        out_sz += sizeof(DEF_C);
        out = realloc(out, out_sz);
        strcat(out, DEF_C);

        color = realloc(color, 1);
        color[0] = 0;

        goto dump;
      default:
        dump:
          out_sz++;
          out = realloc(out, out_sz);
          strncat(out, &data[i], 1);
        break;
    }
  }

  printf("%s", out);

  free(color);
  free(out);
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
