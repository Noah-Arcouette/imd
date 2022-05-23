#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include "conf.h"
#include "settings.h"
#include "reader.h"

int main (const int argc, const char** argv)
{
  // get settings
  struct Settings s = getSet(argc, argv);

  char* data = reader(s);

  printf("%s", data);

  free(data);

  getc(stdin);

  free(s.file);

  return 0;
}
