#pragma once

#include <gtk/gtk.h>
#include "gx/gx.h"

#include "bool_expression.h"

G_BEGIN_DECLS

#define TRUTH_TABLE_TYPE_APPLICATION (truth_table_application_get_type())

G_DECLARE_FINAL_TYPE(TruthTableApplication,
                     truth_table_application,
                     TRUTH_TABLE,
                     APPLICATION,
                     GtkApplication)

struct _TruthTableApplicationClass {
  GtkApplicationClass parent_class;
  // currently has no additional member
};

TruthTableApplication *
truth_table_application_new(void);

int
truth_table_application_run(TruthTableApplication *self, int argc, char **argv);

G_DEFINE_AUTOPTR_CLEANUP_FUNC(TruthTableApplication, g_object_unref)

G_END_DECLS
