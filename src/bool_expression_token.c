/* Used only internally by bool_expression.c/h */

#define __BOOL_EXPRESSION_TOKEN_C__ 1
#include "bool_expression_token.h"
#undef __BOOL_EXPRESSION_TOKEN_C__

BoolExpressionToken *
bet_new(BoolExpressionTokenType type, int id)
{
  BoolExpressionToken *self = g_malloc(sizeof(BoolExpressionToken));
  if (!self) return NULL;
  self->type = type;
  self->id = id;
  return self;
}

void
bet_free(BoolExpressionToken *self)
{
  if (self) g_free(self);
}

static gboolean
bet_is_char_a_part_of_var(const char a);

/**
 * @brief Gets next token from the given string.
 * @param[in,out] str
 * A pointer to the string of tokens, gets updated to the next position of the
 *   read token.
 * @param[out] operator
 * Significant only when the token was an operator, gets updated to the operator
 *   type.\n
 * Not nullable.
 * @param[out] var_name
 * Significant only when the token was a variable, gets updated to the variable
 *   name.\n
 * Writes at most 16 characters including the trailing nul.\n
 * Not nullable.
 * @return
 * The type of token.\n
 * Returns #BOOL_EXPRESSION_TOKEN_NONE if reached the end.\n
 * Returns #BOOL_EXPRESSION_TOKEN_INVALID if encountered a syntax error.
 */
BoolExpressionTokenType
bet_get_next_token(const char **str,
                   BoolOperator *operator,
                   char * var_name,
                   const size_t var_length)
{
  if (!str) return BOOL_EXPRESSION_TOKEN_INVALID;

  // ignore whitespaces
  for (; (**str == ' ' || **str == '\n' || **str == '\t'); *str = *str + 1);

  if (**str == '\0') return BOOL_EXPRESSION_TOKEN_NONE;

  size_t i;
  char token_char = **str;
  *str = *str + 1;
  switch (token_char) {
  case 'a' ... 'z':
  case 'A' ... 'Z':
  case '_':
    var_name[0] = token_char;
    for (i = 1; bet_is_char_a_part_of_var(**str); i++, *str = *str + 1) {
      if (i >= var_length) {
        g_print("Error; variable token must be %ld characters or less.\n",
                var_length);
        return BOOL_EXPRESSION_TOKEN_INVALID;
      }
      var_name[i] = **str;
    }
    var_name[i] = '\0';
    return BOOL_EXPRESSION_TOKEN_VARIABLE;
  case '(':
  case '{':
  case '[':
    return BOOL_EXPRESSION_TOKEN_L_PARANTHESIS;
  case ')':
  case '}':
  case ']':
    return BOOL_EXPRESSION_TOKEN_R_PARANTHESIS;
  case '0':
    return BOOL_EXPRESSION_TOKEN_FALSE;
  case '1':
    return BOOL_EXPRESSION_TOKEN_TRUE;
  case '!':
  case '^':
    switch (**str) {
    case '\0':
      return BOOL_EXPRESSION_TOKEN_INVALID;
    case '&':
    case '*':
      *str = *str + 1;
      *operator= BO_NAND;
      return BOOL_EXPRESSION_TOKEN_OPERATOR;
      return BOOL_EXPRESSION_TOKEN_OPERATOR;
    case '|':
    case '+':
      *str = *str + 1;
      *operator= BO_NOR;
      return BOOL_EXPRESSION_TOKEN_OPERATOR;
    case '=':
      *str = *str + 1;
      *operator= BO_XOR;
      return BOOL_EXPRESSION_TOKEN_OPERATOR;
    default:
      *operator= BO_NOT;
      return BOOL_EXPRESSION_TOKEN_OPERATOR;
    }
  case '&':
    if (**str == '&') *str = *str + 1;
    G_GNUC_FALLTHROUGH;
  case '*':
    *operator= BO_AND;
    return BOOL_EXPRESSION_TOKEN_OPERATOR;
  case '|':
    if (**str == '|') *str = *str + 1;
    G_GNUC_FALLTHROUGH;
  case '+':
    *operator= BO_OR;
    return BOOL_EXPRESSION_TOKEN_OPERATOR;
  case '=':
    if (**str == '=') *str = *str + 1;
    *operator= BO_XNOR;
    return BOOL_EXPRESSION_TOKEN_OPERATOR;
  case '\\':
    g_print("Info; backslash \'\\\' is currently not supported.\n");
    return BOOL_EXPRESSION_TOKEN_INVALID;
  default:
    return BOOL_EXPRESSION_TOKEN_INVALID;
  }
}

static gboolean
bet_is_char_a_part_of_var(const char a)
{
  switch (a) {
  case '0' ... '9':
  case 'a' ... 'z':
  case 'A' ... 'Z':
  case '_':
    return TRUE;
  default:
    return FALSE;
  }
}
