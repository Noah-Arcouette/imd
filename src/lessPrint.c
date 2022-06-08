printf(DEF_C SETUP);

char c = 0;
size_t offset = 0;

s.win_rows-=2;

if (!(s.flags & SETTINGS_FLAG_NO_DEC))
{
  s.win_rows -= 1;
}

char* buff = (char*)malloc(s.win_cols * sizeof(char));

for (size_t i = 0; i<s.win_cols; i++)
{
  buff[i] = ' ';
}
buff[s.win_cols-1] = 0;

size_t j = 0;

while (c != 'q')
{
  printf(REFRESH);

  // draw top bar
  if (!(s.flags & SETTINGS_FLAG_NO_DEC))
  {
    // print file name
    if (s.flags & SETTINGS_FLAG_PIPE)
    {
      printf(BOX_TEXT_C "<PIPED>");
    }
    else
    {
      printf(BOX_TEXT_C "%s", s.file);
    }

    printf(" %ld%%\n" BOX_C, ((offset+1)*100) / sa.size);

    // print top of box
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
  else
  {
    printf(BOX_TEXT_C " %ld%%\n", ((offset+1)*100) / sa.size);
  }

  // draw text
  for (size_t i = 0; i<s.win_rows; i++)
  {
    if ((i+offset)<sa.size)
    {
      if (!(s.flags & SETTINGS_FLAG_NO_DEC))
      {
        // print box and padding
        printf(BOX_TEXT_C "%lu ", i+1+offset);

        for (size_t j = 0; j<(iSize-intLen(i+1+offset)); j++)
        {
          printf(" ");
        }

        printf(BOX_C VBAR " \x1b[0m");
      }

      printf("%s\n", sa.strings[i+offset]);

      continue;
    }

    if (!(s.flags & SETTINGS_FLAG_NO_DEC))
    {
      // print padding
      for (size_t j = 0; j<(iSize+1); j++)
      {
        printf(" ");
      }

      printf(BOX_C VBAR " \x1b[0m");
    }

    printf("\n");
  }

  c = keypress();

  if (c == ':')
  {
    // get input
    while (1)
    {
      MOVE_P((size_t)0, s.win_cols);
      printf(BOX_TEXT_C ":%s", buff);

      c = keypress();

      if (c == 0x7f)
      {
        if (j > 0)
        {
          buff[--j] = ' ';

          continue;
        }

        break;
      }

      if (c == '\n' || j > s.win_cols-3)
      {
        break;
      }

      buff[j++] = c;
    }

    if (isNum(buff))
    {
      offset = toNum(buff)-1;
    }

    // reset
    for (; j; )
    {
      buff[j--] = ' ';
    }
    buff[0] = ' ';
  }
  else if (c == 'G')
  {
    if (sa.size > s.win_rows)
    {
      offset = sa.size-s.win_rows;

      continue;
    }

    offset = 0;
  }
  else if (c == 'g')
  {
    offset = 0;
  }
  else if ((c == 'j' || c == 'w') && offset)
  {
    offset--;
  }
  else if ((c == 'k' || c == 's'))
  {
    offset++;
  }
  // special characters
  else if (c == 0x1b)
  {
    c = keypress();

    if (c == 0x5b)
    {
      c = keypress();

      // up arrow
      if (c == 0x41 && offset)
      {
        offset--;
      }
      // down arrow
      else if (c == 0x42)
      {
        offset++;
      }
      else if (c == 0x35)
      {
        if (offset >= s.win_rows)
        {
          offset -= s.win_rows;
        }
        else
        {
          offset = 0;
        }
      }
      else if (c == 0x36)
      {
        offset += s.win_rows;
      }
    }
    // mouse
    else if (c == 0x4f)
    {
      c = keypress();

      // mouse down
      if (c == 0x42)
      {
        offset++;
      }
      // mouse up
      else if (c == 0x41 && offset)
      {
        offset--;
      }
    }
  }
}

free(buff);

printf(END DEF_C "Thank you for using " HIGHLIGHT_C "IMD\x1b[0m\n");
