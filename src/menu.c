#include "menu.h"
#include <string.h>
#include <stdlib.h>
#include "split.h"
#include <stdio.h>
#include <dirent.h>

char *strcasestr (const char *, const char *);

void addDir (char *, struct StrArray *);

void menu (char *path)
{
  struct StrArray files;
  files.size = 0;
  files.strings = NULL;

  addDir(path, &files);

  for (register size_t i = 0; i<files.size; i++)
  {
    printf("%s\n", files.strings[i]);
  }



  if (files.size)
  {
    free(files.strings[0]);

    for (--files.size; files.size; files.size--)
    {
      free(files.strings[files.size]);
    }
  }
  free(files.strings);

  path = realloc(path, sizeof("./README.md"));
  strcpy(path, "./README.md");

  free(path);
  exit(1);
}

void addDir (char *path, struct StrArray *files)
{
  struct dirent *pDirent;
  DIR *pDir;

  // open dir
  pDir = opendir(path);

  // leave if you can't open the dir
  if (pDir == NULL)
    return;

  char *hold = NULL;

  while ((pDirent = readdir(pDir)) != NULL)
  {
    if (pDirent->d_name[0] == '.')
      continue;

    if (pDirent->d_type == DT_DIR)
    {
      hold = realloc(hold, (strlen(path) + strlen(pDirent->d_name) + 2) * sizeof(char));
      strcpy(hold, path);
      strcat(hold, "/");
      strcat(hold, pDirent->d_name);

      addDir(hold, files);
    }
    else if (pDirent->d_type == DT_REG && strcasestr(pDirent->d_name, ".md"))
    {
      files->size++;
      files->strings = realloc(files->strings, files->size * sizeof(char*));
      files->strings[files->size-1] = malloc(strlen(path) + strlen(pDirent->d_name) + 2);

      strcpy(files->strings[files->size-1], path);
      strcat(files->strings[files->size-1], "/");
      strcat(files->strings[files->size-1], pDirent->d_name);
    }
  }

  free(hold);

  closedir(pDir);
}
