/**
 * @brief Defines class #BoolExpression.
 *
 * The class is currently NOT a GObject, though it does kinda look like one.
 */

#include <glib-object.h>
#include "bool_operator.h"

G_BEGIN_DECLS

/** Not public; undefined at the end of the file. */
#define BOOL_EXPRESSION_MAX_N_VARS 8
/** Not public; undefined at the end of the file. */
#define BOOL_EXPRESSION_VAR_MAX_LENGTH 15

/* ---------- class method ---------- */

/**
 * @brief Returns TRUE if idx (for vars[idx]) is valid.
 * @note Not the second index (vars[first][second]).
 * @return TRUE or FALSE.
 */
gboolean
bool_expression_is_var_idx_valid(gint idx);

/* ---------- constructor ---------- */

/**
 * @brief The type of class BoolExpression
 * @note The members are not to be directly accessed.
 */
typedef struct _BoolExpression {
  /** @brief The expression in string. */
  gchar *str_expr;
  /** @brief A list of #BoolExpressionToken instances. */
  GList *expr;
  /** @brief An array of variables. */
  gchar vars[BOOL_EXPRESSION_MAX_N_VARS][BOOL_EXPRESSION_VAR_MAX_LENGTH + 1];
  /** @brief The number of variables */
  guint n_vars;
} BoolExpression;

BoolExpression *
bool_expression_new(void) G_GNUC_MALLOC;

/**
 * @brief Constructor of class #BoolExpression
 * @param[in] str
 * A string containing a boolean expression.\n
 * Accepted syntax is documented in \ref token_syntaxes.\n
 * The caller of this function owns the data.
 * @note
 * The caller of this function takes ownership of the data and is responsible
 *   for freeing it.
 * @return
 * The created instance, NULL if parameter \a str was NULL or failed otherwise.
 */
BoolExpression *
bool_expression_new_from_string(const char *str);

/* ---------- destructor ---------- */

void
bool_expression_free(BoolExpression *self);

G_DEFINE_AUTOPTR_CLEANUP_FUNC(BoolExpression, bool_expression_free);

/* ---------- getters/setters ---------- */

/**
 * @brief Gets number of variables in the expression.
 * @param[in] self A #BoolExpression instance.
 * @return The number of variables in the expression, -1 if \a self was NULL.
 */
int
bool_expression_get_n_vars(BoolExpression *self) G_GNUC_PURE;

/* ---------- other methods ---------- */

/**
 * @brief Stringifies the expression.
 * @note The data is owned by the instance.
 * @param[in] self A #BoolExpression instance.
 * @return The stringified expression.
 */
const gchar *
bool_expression_to_string(BoolExpression *self);

/**
 * @brief Parses string into #BoolExpression
 *
 * The function overwrites the expression in (self).\n
 *
 * @param[in] self A #BoolExpression instance.
 * @param[in] str
 * A string containing a boolean expression.\n
 * Accepted syntax is documented in \ref token_syntaxes.\n
 * The caller of this function owns the data.
 * @return
 * 0 if successfully parsed, 1 otherwise.\n
 * Mainly fails when either of the input was NULL or syntax error was detected.
 */
int
bool_expression_parse(BoolExpression *self, const char *str);

/**
 * @brief Evaluates \a self.
 * @param[in] self A #BoolExpression instance.
 * @param[in] variable_values
 * A flag, n-th bit representing the value of the n-th variable.
 */
int
bool_expression_evaluate(BoolExpression *self, const gxflag variable_values);

void
bool_expression_dump(BoolExpression *self);

G_END_DECLS

#if !__BOOL_EXPRESSION_C__
#  undef BOOL_EXPRESSION_MAX_N_VARS
#  undef BOOL_EXPRESSION_VAR_MAX_LENGTH
#endif
