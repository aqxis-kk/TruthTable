#include "truth_table_application.h"

struct _TruthTableApplication {
  GtkApplication parent;
  // currently has no additional member
};

G_DEFINE_FINAL_TYPE(TruthTableApplication,
                    truth_table_application,
                    GTK_TYPE_APPLICATION)

TruthTableApplication *
truth_table_application_new(void)
{
  GtkApplication *parent = gtk_application_new("temp.app-id.truth-table",
                                               G_APPLICATION_DEFAULT_FLAGS);
}

int
truth_table_application_run(TruthTableApplication *self, int argc, char **argv);
