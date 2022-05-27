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
