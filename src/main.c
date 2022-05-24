#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include "conf.h"
#include "settings.h"
#include "reader.h"

#define OVERRIDE  0b1
#define HEADER    0b10
#define LIST      0b100
#define TAB       0b1000
#define ALT       0b10000
#define LINK      0b100000
#define UNDERLINE 0b1000000
#define IDDONE    0b10000000
#define ITAL      0b100000000

void style (char* data)
{
  int flags = 0;
  unsigned int count = 0;

  printf("\x1b[0m" DEF_C);

  for (size_t i = 0; data[i]!=0; i++)
  {
    if (!(flags & OVERRIDE))
    {
      switch (data[i])
      {
        case '#':
          if (!(flags & IDDONE))
          {
            count++;
            flags |= HEADER;
          }

          continue;
        case '*':
          count++;
          flags |= ITAL;

          continue;
        case '-':
          if (!(flags & IDDONE))
          {
            printf(LIST_C);

            flags |= LIST;
          }

          break;
        case '>':
          if (!(flags & IDDONE))
          {
            printf(TAB_LIST_C);

            flags |= TAB;
          }

          break;
        case '[':
          flags |= ALT | OVERRIDE;

          printf(BRACKETS_C "[\x1b[0m");

          continue;
        case '(':
          if (!(flags & IDDONE))
          {
            flags |= LINK | OVERRIDE;

            printf(BRACKETS_C "(\x1b[0m");
          }

          continue;
        case '=':
          if (!(flags & IDDONE))
          {
            printf(UNDERLINE_C);

            flags |= UNDERLINE;
          }

          break;
        case '\n':
          goto newline;
        case ' ':
          break;
        case '\t':
          break;
        default:
          if (flags & HEADER)
          {
            flags |= OVERRIDE;

            if (count == 1)
            {
              printf(H1_C);
            }
            else if (count == 2)
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

          if (flags & ITAL)
          {
            if (count == 1)
            {
              printf(ITALIC_C);
            }
            else if (count == 2)
            {
              printf(BOLD_C);
            }
            else if (count == 3)
            {
              printf(BOLD_ITALIC_C);
            }

            flags |= OVERRIDE;
          }

          flags |= IDDONE;

          break;
      }
    }
    else
    {
      if (data[i] == ']')
      {
        printf(BRACKETS_C "]\x1b[0m");

        flags = 0;

        continue;
      }
      else if (data[i] == ')')
      {
        printf(BRACKETS_C ")\x1b[0m");

        flags = 0;

        continue;
      }
      else if (data[i] == '*')
      {
        count--;

        continue;
      }
      else if (count == 0 && flags & ITAL)
      {
        printf("\x1b[0m");

        flags = 0;
      }
      else if (flags & ALT)
      {
        printf(ALT_C);
      }
      else if (flags & LINK)
      {
        printf(LINK_C);
      }
      else if (data[i] == '\n')
      {
        newline:
        flags = 0;
        count = 0;
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
