#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "conf.h"
#include "settings.h"
#include "reader.h"
#include "styling.h"
#include "split.h"
#include "chars.h"
#include "useful.h"

// handle sigint ( Doesn't free memory )
void sigintHandle (int sig)
{
  printf(END);

  printf(ERROR_C "!!!CRASHED!!!\n\x1b[0m");

  exit(1);
}

int main (const int argc, const char** argv)
{
  signal(SIGINT, sigintHandle);

  // get settings
  struct Settings s = getSet(argc, argv);

  // read file
  char* data = reader(&s);

  // style data
  register char* out = style(data, s);
  free(data);

  // split into lines
  struct StrArray sa = split(out);
  free(out);

  // get i size
  const size_t iSize = intLen(sa.size+1);

  // print data raw
  if (s.flags & SETTINGS_FLAG_RAW)
  {
    #include "rawPrint.c"
  }
  else
  {
    #include "lessPrint.c"
  }

  // free lines
  for (sa.size--; sa.size; sa.size--)
  {
    free(sa.strings[sa.size]);
  }
  free(sa.strings[0]);
  free(sa.strings);

  // free input file name
  free(s.file);

  return 0;
}
