#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include "conf.h"
#include "settings.h"
#include "reader.h"
#include "styling.h"

int main (const int argc, const char** argv)
{
  // get settings
  struct Settings s = getSet(argc, argv);

  // read file
  char* data = reader(s);

  char* out = style(data, s);

  printf("%s", out);

  free(out);

  // free data
  free(data);
  free(s.file);

  return 0;
}
