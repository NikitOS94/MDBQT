#ifndef _CREATE_QUERY_H_
#define _CREATE_QUERY_H_
#include <stdio.h>
#include <stdlib.h>

extern void yyerror(char *s);

extern void nSError(char *s);

extern _array *createNewArray(List *arrayList);

extern List *addArrayElement(leaf_value * value, List *arrayList);

extern operator *createNotOperator(operator *op);

extern operator *createModOperator(leaf_value *divisor, leaf_value *remainder);

extern operator *createArrayOperator(array_operator_type op, _array *ar);

extern operator *createValueOperator(value_operator_type op, leaf_value * value);

#endif