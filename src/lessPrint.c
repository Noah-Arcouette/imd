printf(DEF_C SETUP REFRESH);

char c = 0;
size_t offset = 0;

while (c != 'q')
{
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

  if (c == 'j' && offset > 0)
  {
    offset--;
  }

  if (c == 'k')
  {
    offset++;
  }
}

printf(END);
