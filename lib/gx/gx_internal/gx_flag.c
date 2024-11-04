#include "gx.h"

gboolean
gx_flag_is_set(gxflag flag, gint bit_number)
{
  return ((flag >> bit_number) & 1);
}

gxflag
gx_flag_set(gxflag *flag, gint bit_number, gboolean set_to)
{
  return (set_to ? (*flag = (*flag | (1 << bit_number)))
                 : (*flag = (*flag & ~(1 << bit_number))));
}
