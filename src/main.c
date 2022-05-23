#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include "conf.h"
#include "settings.h"

int main (const int argc, const char** argv)
{
  struct Settings s = getSet(argc, argv);

  printf("%s\n", s.file);

  free(s.file);

  return 0;
}
