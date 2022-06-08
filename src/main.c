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

// gets amount of digits in a number
size_t intLen (int x)
{
  register size_t i;
  for (i = 0; x; x/=10)
  {
    i++;
  }

  return i;
}

// gets and waits for keypress
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

// check if string is a number
int isNum (char* data)
{
  if (data[0] == 0 || data[0] == ' ')
    return 0;

  for (size_t i = 0; data[i]!=0 && data[i]!=' '; i++)
  {
    if (data[i] < '0' || data[i] > '9')
      return 0;
  }

  return 1;
}

// change string to number
int toNum (char* data)
{
  int out = 0;

  for (size_t i = 0; data[i]!=0 && data[i]!=' '; i++)
  {
      out *= 10;
      out += data[i] - '0';
  }

  return out;
}

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
