/**
 * @file gx_malloc.h
 * @brief extensions related to memory allocation
 */
#pragma once

#if !__GX_INTERNAL__
#  error "include gx.h instead."
#endif

#include <glib.h>

/**
 * @brief g_free() variant that does nothing if \a data was NULL.
 */
void
gx_free(gpointer data);
