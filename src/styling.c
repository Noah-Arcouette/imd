#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conf.h"
#include "settings.h"
#include "styling.h"

char* style (char* data, struct Settings s)
{
  int flags = 0;
  unsigned int count = 0;

  register char* out = malloc(sizeof(DEF_C));
  register size_t sz = sizeof(DEF_C);
  strcpy(out, DEF_C);

  for (register size_t i = 0; data[i]!=0; i++)
  {
    if (!(flags & (OVERRIDE | SYN_IN)))
    {
      switch (data[i])
      {
        case '#':
          if (!(flags & (IDDONE | SYNTAX)))
          {
            count++;
            flags |= HEADER;

            continue;
          }

          if (flags & SYNTAX)
            goto syntax_label;

          break;
        case '*':
          if (!(flags & (HEADER | SYNTAX)))
          {
            count++;
            flags |= ITAL;

            continue;
          }

          if (flags & SYNTAX)
            goto syntax_label;

          goto defs;
        case '-':
          if (!(flags & (IDDONE | HEADER | SYNTAX)))
          {
            sz += sizeof(LIST_C);
            out = realloc(out, sz);
            strcat(out, LIST_C);

            flags |= LIST;
          }

          if (flags & HEADER)
            goto defs;

          else if (flags & SYNTAX)
            goto syntax_label;

          break;
        case '>':
          if (!(flags & (IDDONE | HEADER | SYNTAX)))
          {
            sz += sizeof(TAB_LIST_C);
            out = realloc(out, sz);
            strcat(out, TAB_LIST_C);

            flags |= TAB;
          }

          if (flags & HEADER)
            goto defs;

          else if (flags & SYNTAX)
            goto syntax_label;

          break;
        case '[':
          if (!(flags & (HEADER | SYNTAX)))
          {
            flags |= ALT | OVERRIDE;

            sz += sizeof(BRACKETS_C "[\x1b[0m");
            out = realloc(out, sz);
            strcat(out, BRACKETS_C "[\x1b[0m");

            continue;
          }

          if (flags & SYNTAX)
            goto syntax_label;

          goto defs;
        case '(':
          if (!(flags & (IDDONE | HEADER | SYNTAX)) && flags & LINK)
          {
            flags |= OVERRIDE;

            sz += sizeof(BRACKETS_C "(\x1b[0m");
            out = realloc(out, sz);
            strcat(out, BRACKETS_C "(\x1b[0m");

            continue;
          }

          if (flags & HEADER)
            goto defs;

          else if (flags & SYNTAX)
            goto syntax_label;

          break;
        case '=':
          if (!(flags & (IDDONE | HEADER | SYNTAX)))
          {
            sz += sizeof(UNDERLINE_C);
            out = realloc(out, sz);
            strcat(out, UNDERLINE_C);

            flags |= UNDERLINE;
          }

          if (flags & HEADER)
            goto defs;

          else if (flags & SYNTAX)
            goto syntax_label;

          break;
        case '\n':
          goto newline;
        case ' ':
          break;
        case '\t':
          break;
        case '`':
          if (!(flags & HEADER))
          {
            flags |= SYNTAX;
            count++;

            break;
          }

          goto defs;
        default:
          defs:

          if (flags & LINK)
            flags &= ~LINK;

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
            sz += sizeof(DEF_C);
            out = realloc(out, sz);
            strcat(out, DEF_C);
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
      if (flags & HEADER)
      {
        // do nothing
      }
      else if (data[i] == ']')
      {
        sz += sizeof(BRACKETS_C "]\x1b[0m");
        out = realloc(out, sz);
        strcat(out, BRACKETS_C "]\x1b[0m");

        flags = LINK;

        continue;
      }
      else if (data[i] == ')' && !(flags & ALT))
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

      if (data[i] == '\n')
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
        sz += sizeof(DEF_C);
        out = realloc(out, sz);
        strcat(out, DEF_C);
      }
    }
    else
    {
      if (!(s.flags & SETTINGS_FLAG_NO_SYNTAX))
      {
        // syntax
      }

      if (data[i-1] != '\\' && data[i] == '`')
      {
        sz += sizeof(DEF_C);
        out = realloc(out, sz);
        strcat(out, DEF_C);

        count--;
      }
      else if (data[i] == '\n')
      {
        sz += sizeof("\n" SYNTAX_C);
        out = realloc(out, sz);
        strcat(out, "\n" SYNTAX_C);

        continue;
      }

      if (!count)
      {
        flags = IDDONE;
      }
    }

    out = realloc(out, ++sz);
    strncat(out, &data[i], 1);
  }

  return out;
}
