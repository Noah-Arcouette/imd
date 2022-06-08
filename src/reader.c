#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "settings.h"
#include "reader.h"
#include "conf.h"
#include "menu.h"

char* reader (struct Settings *s)
{
  // test if file is a directory
  // if directory run menu then reset s.file
  struct stat path_stat;
  stat(s->file, &path_stat);
  if (!S_ISREG(path_stat.st_mode))
  {
    menu(s);
  }

  // open file
  register FILE *fp;
  if (s->flags & SETTINGS_FLAG_PIPE)
  {
    fp = stdin;
  }
  else
  {
    fp = fopen(s->file, "r");
  }

  // check if file opened
  if (fp == NULL)
  {
    printf(
      ERROR_C "Error"
      DEF_C ": Cannot open file `"
      HIGHLIGHT_C "%s"
      DEF_C "'.\x1b[0m\n",
      s->file
    );

    free(s->file);
    exit(1);
  }

  // line
  char* line = NULL;
  size_t len = 0;
  ssize_t size;

  // output data
  register char* data = malloc(1 * sizeof(char));
  data[0] = 0;
  register size_t datasz = 1;

  // read lines
  while ((size = getline(&line, &len, fp)) != -1) {
    datasz += size;
    data = realloc(data, datasz * sizeof(char));
    strcat(data, line);
  }

  // free file
  fclose(fp);

  // swap stdin to a tty is piped
  if (s->flags & SETTINGS_FLAG_PIPE)
  {
    freopen("/dev/tty", "r", stdin);
  }

  return data;
}
