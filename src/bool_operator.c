#include <glib.h>
#include "bool_operator.h"

gboolean
bool_operator_evaluate(const gboolean P,
                       const BoolOperator opr,
                       const gboolean Q)
{
  switch (opr) {
  case BO_NOT:
    // note: not is the SAME AS XOR, except priority.
    return (P ? !Q : Q);
  case BO_CONT:
    return FALSE;
  case BO_TAUT:
    return TRUE;
  case BO_PRPP:
    return P;
  case BO_INVP:
    return !P;
  case BO_PRPQ:
    return Q;
  case BO_INVQ:
    return !Q;
  case BO_OR:
    return (P || Q);
  case BO_NOR:
    return !(P || Q);
  case BO_AND:
    return (P && Q);
  case BO_NAND:
    return !(P && Q);
  case BO_IMPL:
    return (!P || Q);
  case BO_IIMP:
    return (P && !Q);
  case BO_RIMP:
    return (P || !Q);
  case BO_IRIM:
    return (!P && Q);
  case BO_XOR:
    // note that P can be 2 or any int value, i.e. P != Q is not valid.
    return (P ? !Q : Q);
  case BO_XNOR:
    return (P ? Q : !Q);
  }
  return FALSE;
}

int
bool_operator_get_priority(const BoolOperator opr)
{
  switch (opr) {
  case BO_NOT:
    return 0;
  case BO_AND:
  case BO_NAND:
    return 1;
  default:
    return 2;
  }
}

const gchar *
bool_operator_to_string(const BoolOperator opr)
{
  switch (opr) {
  case BO_NOT:
    return "NOT";
  case BO_CONT:
    return "CONT";
  case BO_TAUT:
    return "TAUT";
  case BO_PRPP:
    return "PRPP";
  case BO_INVP:
    return "INVP";
  case BO_PRPQ:
    return "PRPQ";
  case BO_INVQ:
    return "INVQ";
  case BO_OR:
    return "OR";
  case BO_NOR:
    return "NOR";
  case BO_AND:
    return "AND";
  case BO_NAND:
    return "NAND";
  case BO_IMPL:
    return "IMPL";
  case BO_IIMP:
    return "IIMP";
  case BO_RIMP:
    return "RIMP";
  case BO_IRIM:
    return "IRIM";
  case BO_XOR:
    return "XOR";
  case BO_XNOR:
    return "XNOR";
  default:
    return "";
  }
}
