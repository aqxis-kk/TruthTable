#pragma once

#if !__GX_INTERNAL__
#  error "include gx.h instead."
#endif

#include <gtk/gtk.h>

typedef unsigned long gxflag;

gboolean
gx_flag_is_set(gxflag flag, gint bit_number);

/**
 * @brief Sets ( \a bit_number )th bit of \a *flag to \a set_to.
 * @param[in] flag The flag, nonnull.
 * @param[in] bit_number The bit number to edit (&ge; 0).
 * @param[in] set_to TRUE to set, FALSE to unset
 * @return Same as flag.
 */
gxflag
gx_flag_set(gxflag *flag, gint bit_number, gboolean set_to)
    __attribute__((__nonnull__(1)));
