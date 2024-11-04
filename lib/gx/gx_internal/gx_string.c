#include "../gx.h"

#include <string.h>

int
gx_strfind(const char *__restrict target,
           const char **__restrict test,
           const size_t n)
{
  size_t i;
  for (i = 0; i < n; i++)
    if (test[i] && !strcmp(target, test[i])) return i;
  return -1;
}

int
gx_strlfind(const char *__restrict target,
            const size_t l,
            const char **__restrict test,
            const size_t n)
{
  size_t i;
  for (i = 0; i < n; i++)
    if (test[i] && !strncmp(target, test[i], l)) return i;
  return -1;
}

int
gx_strfind_2d(const char *__restrict target,
              const size_t x,
              const size_t y,
              const char test[x][y])
{
  size_t i;
  for (i = 0; i < x; i++)
    if (!strcmp(target, test[i])) return i;
  return -1;
}

int
gx_strlfind_2d(const char *__restrict target,
               const size_t l,
               const size_t x,
               const size_t y,
               const char test[x][y])
{
  size_t i;
  for (i = 0; i < x; i++)
    if (!strncmp(target, test[i], l)) return i;
  return -1;
}
