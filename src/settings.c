#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include "conf.h"
#include "settings.h"

struct Settings getSet (const int argc, const char** argv)
{
  register struct Settings s;
  s.flags = 0;

  s.file = malloc(sizeof("./README.md"));
  strcpy(s.file, "./README.md");

  // get window size
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  s.win_rows = w.ws_row;
  s.win_cols = w.ws_col;

  // check for stdin pipe
  if (!isatty(STDIN_FILENO))
  {
    s.flags |= SETTINGS_FLAG_PIPE;
  }

  // parse args
  for (int i = 1; i<argc; i++)
  {
    if (argv[i][0] == '-' && argv[i][1] == '-')
    {
      if (!strcmp(argv[i], "--raw"))
      {
        s.flags |= SETTINGS_FLAG_RAW;
      }
      else if (!strcmp(argv[i], "--no-decoration"))
      {
        s.flags |= SETTINGS_FLAG_NO_DEC;
      }
      else if (!strcmp(argv[i], "--no-syntax"))
      {
        s.flags |= SETTINGS_FLAG_NO_SYNTAX;
      }
      else if (!strcmp(argv[i], "--help"))
      {
        s.file = realloc(s.file, sizeof("/etc/imd/man.md"));
        strcpy(s.file, "/etc/imd/man.md");
      }
      else
      {
        goto error;
      }
    }
    else if (argv[i][0] == '-')
    {
      for (int j = 1; argv[i][j]!='\0'; j++)
      {
        switch (argv[i][j])
        {
          case 'r':
            s.flags |= SETTINGS_FLAG_RAW;

            break;
          case 'd':
            s.flags |= SETTINGS_FLAG_NO_DEC;

            break;
          case 's':
            s.flags |= SETTINGS_FLAG_NO_SYNTAX;

            break;
          case 'h':
            s.file = realloc(s.file, sizeof("/etc/imd/man.md"));
            strcpy(s.file, "/etc/imd/man.md");

            break;
          default:
            goto error;
        }
      }
    }
    else
    {
      s.file = realloc(s.file,
        (strlen(argv[i])+1)*
        sizeof(char)
      );
      strcpy(s.file, argv[i]);
    }

    continue;

    error:
      printf(\
        ERROR_C "Error"\
        DEF_C ": Unknown option `"\
        HIGHLIGHT_C "%s"\
        DEF_C "'.\n\x1b[0m",
        argv[i]);

      free(s.file);
      exit(1);

      continue;
  }

  return s;
}
