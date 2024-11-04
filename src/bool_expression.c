#include "gx/gx.h"

#define __BOOL_EXPRESSION_C__ 1
#include "bool_expression.h"
#include "bool_expression_token.h"
#undef __BOOL_EXPRESSION_C__

static int
_bool_expression_parse_internal(BoolExpression *self, const char *str);

#define _bool_expression_clear_expr(self)                                      \
  g_list_free_full(self->expr, (GDestroyNotify) bet_free)

#define _bool_expression_reset_vars(self) (self->n_vars = 0)

// Class methods

gboolean
bool_expression_is_var_idx_valid(gint idx)
{
  return ((0 <= idx) && (idx < BOOL_EXPRESSION_MAX_N_VARS));
}

// Constructors/Destructors

BoolExpression *
bool_expression_new(void)
{
  BoolExpression *self = g_malloc(sizeof(BoolExpression));
  if (!self) return NULL;
  self->str_expr = NULL;
  self->expr = NULL;
  self->vars[0][0] = '\0';
  self->n_vars = 0;
  return self;
}

BoolExpression *
bool_expression_new_from_string(const char *str)
{
  g_autoptr(BoolExpression) self = bool_expression_new();
  if (!self || _bool_expression_parse_internal(self, str)) return NULL;
  return g_steal_pointer(&self);
}

void
bool_expression_free(BoolExpression *self)
{
  if (!self) return;
  if (self->str_expr) g_free(self->str_expr);
  if (self->expr) _bool_expression_clear_expr(self);
  g_free(self);
}

// Getters/Setters
// note - static ones are private

static inline GList *
bool_expression_get_expr(BoolExpression *self)
{
  return (self ? self->expr : NULL);
}

/** @note The instance takes ownership of the data \a expr. */
static inline void
bool_expression_set_expr(BoolExpression *self, GList *expr)
{
  if (self) self->expr = expr;
}

static inline gchar *
bool_expression_get_str_expr(BoolExpression *self)
{
  return (self ? self->str_expr : NULL);
}

/** @note The data \a str_expr is owned by the caller. */
static inline void
bool_expression_set_str_expr(BoolExpression *self, const gchar *str_expr)
{
  if (!self) return;
  gchar *new_str_expr = (str_expr ? g_strdup(str_expr) : NULL);
  gx_free(self->str_expr);
  self->str_expr = new_str_expr;
}

/** @note No setters for this member. */
#define bool_expression_get_vars(self) ((self) ? (self->vars) : NULL)

/** @brief Gets self->var[idx] */
static inline const gchar *
bool_expression_get_var(BoolExpression *self, const int idx)
{
  return ((self && bool_expression_is_var_idx_valid(idx)) ? self->vars[idx]
                                                          : NULL);
}

/** @brief Used only within bool_expression_push_expr()
 *  @return -1 if failed, index otherwise. */
static inline int
_bool_expression_register_var(BoolExpression *self, const char *var)
{
  if (!self || !var) return -1;
  int var_index = gx_strfind_2d(var, self->n_vars,
                                BOOL_EXPRESSION_VAR_MAX_LENGTH, self->vars);
  if (var_index >= 0) return var_index;

  var_index = self->n_vars;
  if (var_index >= BOOL_EXPRESSION_MAX_N_VARS) return -1;

  self->n_vars += 1;
  // truncation never actually happens here
  GX_DIAGNOSTIC_BEGIN_MODIFY(ignored, "-Wstringop-truncation");
  strncpy(self->vars[var_index], var, BOOL_EXPRESSION_VAR_MAX_LENGTH);
  GX_DIAGNOSTIC_END_MODIFY();

  self->vars[var_index][BOOL_EXPRESSION_VAR_MAX_LENGTH] = '\0';
  return var_index;
}

static inline int
bool_expression_push_expr(BoolExpression *self,
                          const BoolExpressionTokenType type,
                          const BoolOperator opr,
                          const char *var)
{
  int var_id;
  if (!self) return 1;
  switch (type) {
  case BOOL_EXPRESSION_TOKEN_TRUE:
  case BOOL_EXPRESSION_TOKEN_FALSE:
  case BOOL_EXPRESSION_TOKEN_OPERATOR:
    self->expr = g_list_append(self->expr, bet_new(type, opr));
    return 0;
  case BOOL_EXPRESSION_TOKEN_VARIABLE:
    var_id = _bool_expression_register_var(self, var);
    if (var_id < 0) return 1;
    self->expr = g_list_append(self->expr, bet_new(type, var_id));
    return 0;
  default:
    return 1;
  }
}

int
bool_expression_get_n_vars(BoolExpression *self)
{
  return (self ? (int) self->n_vars : -1);
}

/* ---------- other methods ---------- */

// for convenience
#define TOKEN(type) BOOL_EXPRESSION_TOKEN_##type
#define BOOL_EXPRESSION_TOKEN_L_PAR BOOL_EXPRESSION_TOKEN_L_PARANTHESIS
#define BOOL_EXPRESSION_TOKEN_R_PAR BOOL_EXPRESSION_TOKEN_R_PARANTHESIS

const gchar *
bool_expression_to_string(BoolExpression *self)
{
  return self->str_expr;
}

int
bool_expression_parse(BoolExpression *self, const char *str)
{
  if (!self) return 1;
  // Initialize self and call ..._internal()
  bool_expression_set_str_expr(self, NULL);
  _bool_expression_reset_vars(self);
  if (bool_expression_get_expr(self)) _bool_expression_clear_expr(self);
  bool_expression_set_expr(self, NULL);

  return _bool_expression_parse_internal(self, str);
}

typedef GQueue stack;
#define stack_new() g_queue_new()
#define stack_push(_stack, data) g_queue_push_tail(_stack, data)
#define stack_pop(_stack) g_queue_pop_tail(_stack)
#define stack_peek(_stack) g_queue_peek_tail(_stack)
#define stack_is_empty(_stack) g_queue_is_empty(_stack)
#define stack_free(_stack) g_queue_free_full(_stack, (gpointer) bet_free)

/**
 * @return 0 if (cond) was false, 1 if __top became empty.
 */
#define _be_push_expr_from_stack_until(self, _stack, cond)                     \
  ({                                                                           \
    BoolExpressionToken *__top;                                                \
    gint __return_val = 0;                                                     \
    while (!__return_val) {                                                    \
      __top = stack_peek(_stack);                                              \
      if (!__top) {                                                            \
        __return_val = 1;                                                      \
        break;                                                                 \
      }                                                                        \
      if (!(cond)) break;                                                      \
      stack_pop(_stack);                                                       \
      __return_val =                                                           \
          bool_expression_push_expr(self, __top->type, __top->id, NULL);       \
    }                                                                          \
    __return_val;                                                              \
  })

/**
 * Expects self to be in initial state (i.e. no expression assigned).
 * @note Shunting yard algorythm, NOT operator is equal to (1 !=)
 */
static int
_bool_expression_parse_internal(BoolExpression *self, const char *str)
{
  const char *token_idx = str;
  BoolExpressionTokenType type;
  BoolOperator opr = -1;
  char var_name[16];
  stack *opr_stack = stack_new();

  while ((type = bet_get_next_token(&token_idx, &opr, var_name,
                                    BOOL_EXPRESSION_VAR_MAX_LENGTH)) !=
         TOKEN(NONE)) {
    switch (type) {
    case TOKEN(VARIABLE)... TOKEN(FALSE):
      if (bool_expression_push_expr(self, type, opr, var_name)) return 1;
      break;

    case TOKEN(OPERATOR):
      if (opr == BO_NOT) bool_expression_push_expr(self, TOKEN(TRUE), 0, NULL);

      _be_push_expr_from_stack_until(
          self, opr_stack,
          (__top->type == TOKEN(OPERATOR)) &&
              (bool_operator_get_priority(__top->id) <=
               bool_operator_get_priority(opr)));
      stack_push(opr_stack, bet_new(type, opr));
      break;

    case TOKEN(L_PAR):
      stack_push(opr_stack, bet_new(TOKEN(L_PAR), opr));
      break;

    case TOKEN(R_PAR):
      if (_be_push_expr_from_stack_until(self, opr_stack,
                                         (__top->type != TOKEN(L_PAR)))) {
        g_print("stack empty\n");
        return 1; // expr is invalid if stack is empty here
      }
      stack_pop(opr_stack); // remove L_PARANTHESIS
      break;

    case TOKEN(INVALID):
    default:
      g_print("token invalid\n");
      return 1;
    }
  }
  _be_push_expr_from_stack_until(self, opr_stack, TRUE);
  bool_expression_set_str_expr(self, str);
  return 0;
}

void
bool_expression_dump(BoolExpression *self)
{
  if (!self || !self->expr) return;

  printf("variables: ");
  guint i;
  for (i = 0; i < self->n_vars; i++) printf("%d:%s, ", i, self->vars[i]);

  printf("\nexpr:\n");
  BoolExpressionToken *token;
  for (i = 0; (token = g_list_nth_data(self->expr, i)); i++) {
    const char *desc;
    switch (token->type) {
    case TOKEN(VARIABLE):
      desc = self->vars[token->id];
      break;
    case TOKEN(TRUE):
      desc = "TRUE";
      break;
    case TOKEN(FALSE):
      desc = "FALSE";
      break;
    case TOKEN(OPERATOR):
      desc = bool_operator_to_string(token->id);
      break;
    default:
      desc = "UNEXPECTED TOKEN";
      break;
    }
    printf("  type: %02X, id: %02d - %s\n", token->type, token->id, desc);
  }
}

int
bool_expression_evaluate(BoolExpression *self, const gxflag variable_values)
{
  return 0;
}
