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
#define SYNTAX    0b1000000000
#define SYN_IN    0b10000000000

void style (char* data)
{
  int flags = 0;
  unsigned int count = 0;

  register char* out = malloc(sizeof("\x1b[0m" DEF_C));
  register size_t sz = sizeof("\x1b[0m" DEF_C);
  strcpy(out, "\x1b[0m" DEF_C);

  for (register size_t i = 0; data[i]!=0; i++)
  {
    if (!(flags & (OVERRIDE | SYN_IN)))
    {
      switch (data[i])
      {
        case '#':
          if (!(flags & IDDONE))
          {
            count++;
            flags |= HEADER;

            continue;
          }

          break;
        case '*':
          count++;
          flags |= ITAL;

          continue;
        case '-':
          if (!(flags & IDDONE))
          {
            sz += sizeof(LIST_C);
            out = realloc(out, sz);
            strcat(out, LIST_C);

            flags |= LIST;
          }

          break;
        case '>':
          if (!(flags & IDDONE))
          {
            sz += sizeof(TAB_LIST_C);
            out = realloc(out, sz);
            strcat(out, TAB_LIST_C);

            flags |= TAB;
          }

          break;
        case '[':
          flags |= ALT | OVERRIDE;

          sz += sizeof(BRACKETS_C "[\x1b[0m");
          out = realloc(out, sz);
          strcat(out, BRACKETS_C "[\x1b[0m");

          continue;
        case '(':
          if (!(flags & IDDONE))
          {
            flags |= LINK | OVERRIDE;

            sz += sizeof(BRACKETS_C "(\x1b[0m");
            out = realloc(out, sz);
            strcat(out, BRACKETS_C "(\x1b[0m");

            continue;
          }

          break;
        case '=':
          if (!(flags & IDDONE))
          {
            sz += sizeof(UNDERLINE_C);
            out = realloc(out, sz);
            strcat(out, UNDERLINE_C);

            flags |= UNDERLINE;
          }

          break;
        case '\n':
          goto newline;
        case ' ':
          break;
        case '\t':
          break;
        case '`':
          flags |= SYNTAX;
          count++;

          break;
        default:
          if (flags & SYNTAX)
          {
            goto syntax_label;
          }

          if (flags & HEADER)
          {
            flags |= OVERRIDE;

            if (count == 1)
            {
              sz += sizeof(H1_C);
              out = realloc(out, sz);
              strcat(out, H1_C);
            }
            else if (count == 2)
            {
              sz += sizeof(H2_C);
              out = realloc(out, sz);
              strcat(out, H2_C);
            }
            else
            {
              sz += sizeof(H3_C);
              out = realloc(out, sz);
              strcat(out, H3_C);
            }
          }
          else if (flags & LIST || flags & TAB)
          {
            sz += sizeof("\x1b[0m" DEF_C);
            out = realloc(out, sz);
            strcat(out, "\x1b[0m" DEF_C);
          }

          if (flags & ITAL)
          {
            if (count == 1)
            {
              sz += sizeof(ITALIC_C);
              out = realloc(out, sz);
              strcat(out, ITALIC_C);
            }
            else if (count == 2)
            {
              sz += sizeof(BOLD_C);
              out = realloc(out, sz);
              strcat(out, BOLD_C);
            }
            else if (count == 3)
            {
              sz += sizeof(BOLD_ITALIC_C);
              out = realloc(out, sz);
              strcat(out, BOLD_ITALIC_C);
            }

            flags |= OVERRIDE;
          }

          flags |= IDDONE;

          break;
      }
    }
    else if (flags & OVERRIDE)
    {
      if (data[i] == ']')
      {
        sz += sizeof(BRACKETS_C "]\x1b[0m");
        out = realloc(out, sz);
        strcat(out, BRACKETS_C "]\x1b[0m");

        flags = 0;

        continue;
      }
      else if (data[i] == ')')
      {
        sz += sizeof(BRACKETS_C ")\x1b[0m");
        out = realloc(out, sz);
        strcat(out, BRACKETS_C ")\x1b[0m");

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
        sz += sizeof("\x1b[0m");
        out = realloc(out, sz);
        strcat(out, "\x1b[0m");

        flags = 0;
      }
      else if (flags & ALT)
      {
        sz += sizeof(ALT_C);
        out = realloc(out, sz);
        strcat(out, ALT_C);
      }
      else if (flags & LINK)
      {
        sz += sizeof(LINK_C);
        out = realloc(out, sz);
        strcat(out, LINK_C);
      }
      else if (data[i] == '\n')
      {
        newline:

        if (flags & SYNTAX)
        {
            syntax_label:
            flags |= SYN_IN;
            i--;

            sz += sizeof(SYNTAX_C);
            out = realloc(out, sz);
            strcat(out, SYNTAX_C);

            continue;
        }

        flags = 0;
        count = 0;
        sz += sizeof("\x1b[0m" DEF_C);
        out = realloc(out, sz);
        strcat(out, "\x1b[0m" DEF_C);
      }
    }
    else
    {
      switch (data[i])
      {
          case '`':
            sz += sizeof(DEF_C);
            out = realloc(out, sz);
            strcat(out, DEF_C);

            count--;

            break;
          case '\n':
            sz += sizeof(SYNTAX_C);
            out = realloc(out, sz);
            strcat(out, SYNTAX_C);

            break;
      }

      if (!count)
      {
        flags = 0;
      }
    }

    out = realloc(out, ++sz);
    strncat(out, &data[i], 1);
  }

  printf("%s", out);

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
