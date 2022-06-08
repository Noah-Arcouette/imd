#include <termios.h>
#include <stdio.h>
#include <unistd.h>

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
