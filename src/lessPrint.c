printf(DEF_C SETUP);

char c = 0;
size_t offset = 0;

while (c != 'q')
{
  printf(REFRESH);

  for (size_t i = 0; i<(s.win_rows-1); i++)
  {
    if ((i+offset)<sa.size)
    {
      printf("%s\n", sa.strings[i+offset]);

      continue;
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
  // special character
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
    }
    // mouse ?
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
