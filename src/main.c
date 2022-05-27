#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "conf.h"
#include "settings.h"
#include "reader.h"
#include "styling.h"
#include "split.h"
#include "chars.h"

size_t intLen (int x)
{
  size_t i;
  for (i = 0; x; x/=10)
  {
    i++;
  }

  return i;
}

char keypress ()
{
	char c;

	struct termios old, new;

	tcgetattr(0, &old);
	new = old;
	new.c_lflag &= ~ICANON;
	new.c_lflag &= ~ECHO;
	tcsetattr(0, TCSANOW, &new);

	c = getc(stdin);

	tcsetattr(0, TCSANOW, &old);

	return c;
}

void sigintHandle (int)
{
  printf(END);

  exit(1);
}

int main (const int argc, const char** argv)
{
  // printf(SETUP REFRESH);
  //
  // char key1, key2, key3, key4;
  // key1 = keypress();
  // key2 = keypress();
  // key3 = keypress();
  // key4 = keypress();
  //
  // printf(END);
  //
  // printf("%x : %x : %x : %x\n", key1, key2, key3, key4);

  signal(SIGINT, sigintHandle);

  // get settings
  struct Settings s = getSet(argc, argv);

  // read file
  char* data = reader(s);

  // style data
  char* out = style(data, s);
  free(data);

  // split into lines
  struct StrArray sa = split(out);
  free(out);

  // get i size
  size_t iSize = intLen(sa.size+1);

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
