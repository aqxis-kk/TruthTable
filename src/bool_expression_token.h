/* Used only internally by bool_expression.c/h */

#include <glib-object.h>
#include "bool_operator.h"

#if !__BOOL_EXPRESSION_C__ && !__BOOL_EXPRESSION_TOKEN_C__
#  error "This header is only available within bool_expression.c"
#endif

G_BEGIN_DECLS

typedef enum _BoolExpressionTokenType {
  BOOL_EXPRESSION_TOKEN_INVALID = -1,
  BOOL_EXPRESSION_TOKEN_NONE = 0,
  BOOL_EXPRESSION_TOKEN_VARIABLE = 0X01,
  BOOL_EXPRESSION_TOKEN_TRUE,
  BOOL_EXPRESSION_TOKEN_FALSE,
  BOOL_EXPRESSION_TOKEN_OPERATOR = 0X10,
  BOOL_EXPRESSION_TOKEN_L_PARANTHESIS,
  BOOL_EXPRESSION_TOKEN_R_PARANTHESIS,
} BoolExpressionTokenType;

/** @brief Type cast (similar to G_OBJECT()). */
#define BET(pointer) ((BoolExpressionToken *) pointer)

/** @brief Private class of #BoolExpression. */
typedef struct _BoolExpressionToken {
  BoolExpressionTokenType type;
  /** @brief BoolOperatorType or variable ID, otherwise undefined. */
  int id;
} BoolExpressionToken;

BoolExpressionToken *
bet_new(BoolExpressionTokenType type, int id) G_GNUC_MALLOC;

void
bet_free(BoolExpressionToken *self);

BoolExpressionTokenType
bet_get_next_token(const char **str,
                   BoolOperator *operator,
                   char * var_name,
                   const size_t var_length) __attribute__((nonnull(2, 3)));

G_END_DECLS
