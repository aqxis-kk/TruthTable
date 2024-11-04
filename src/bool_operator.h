#pragma once

#include <glib.h>

typedef enum _BoolOperator {
  /** @brief NOT(Q) = !Q */
  BO_NOT = 0,

  /** @brief CONT(P, Q) = 0 */
  BO_CONT,
  /** @brief TAUT(P, Q) = 1 */
  BO_TAUT,

  /** @brief PROPOSITION_P(P, Q) = P */
  BO_PRPP,
  /** @brief INVERSION_P(P, Q) = !P */
  BO_INVP,
  /** @brief PROPOSITION_Q(P, Q) = Q */
  BO_PRPQ,
  /** @brief INVERSIONQ(P, Q) = !Q */
  BO_INVQ,

  /** @brief OR(P, Q) = P | Q */
  BO_OR,
  /** @brief NOR(P, Q) = !(P | Q) */
  BO_NOR,
  /** @brief AND(P, Q) = P & Q */
  BO_AND,
  /** @brief NAND(P, Q) = !(P & Q) */
  BO_NAND,

  /** @brief IMPLICATION(P, Q) = P -> Q */
  BO_IMPL,
  /** @brief INVERT_IMPLICATION(P, Q) = !(P -> Q) */
  BO_IIMP,
  /** @brief REVERSE_IMPLICATION(P, Q) = Q -> P */
  BO_RIMP,
  /** @brief INVERT_REVERSE_IMPLICATION(P, Q) = !(Q -> P) */
  BO_IRIM,

  /** @brief XOR(P, Q) = P != Q */
  BO_XOR,
  /** @brief XNOR(P, Q) = P == Q */
  BO_XNOR,
} BoolOperator;

/**
 * @attention #BO_NOT is the same as XOR. Use (1, BO_NOT, var).
 * @brief returns (P \a opr Q).
 */
gboolean
bool_operator_evaluate(const gboolean P,
                       const BoolOperator opr,
                       const gboolean Q) __THROW G_GNUC_CONST;

/**
 * @brief Smaller value means higher priority (&ge; 0)
 */
int
bool_operator_get_priority(const BoolOperator opr) __THROW G_GNUC_CONST;

/**
 * @brief Stringifies #BoolOperator.
 * @note The returned string is owned by the instance.
 */
const gchar *
bool_operator_to_string(const BoolOperator opr);
