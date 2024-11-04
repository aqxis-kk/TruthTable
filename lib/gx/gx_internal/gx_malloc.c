#include "gx.h"

void
gx_free(gpointer data)
{
  if (data) g_free(data);
}
