#include "menu.h"
#include <string.h>
#include <stdlib.h>

void menu (char *path)
{
  path = realloc(path, sizeof("./README.md"));
  strcpy(path, "./README.md");
}
