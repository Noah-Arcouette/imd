printf(DEF_C SETUP);

char c = 0;
size_t offset = 0;

s.win_rows--;

if (!(s.flags & SETTINGS_FLAG_NO_DEC))
{
  s.win_rows -= 2;
}

while (c != 'q')
{
  printf(REFRESH);

  // draw top bar
  if (!(s.flags & SETTINGS_FLAG_NO_DEC))
  {
    // print file name
    if (s.flags & SETTINGS_FLAG_PIPE)
    {
      printf(BOX_TEXT_C "<PIPED>\n" BOX_C);
    }
    else
    {
      printf(BOX_TEXT_C "%s\n" BOX_C, s.file);
    }

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

  if ((c == 'j' || c == 'w') && offset > 0)
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
      if (c == 0x41 && offset > 0)
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
      else if (c == 0x41 && offset > 0)
      {
        offset--;
      }
    }
  }
}

printf(END);
