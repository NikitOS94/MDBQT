#ifndef _CREATE_QUERY_H_
#define _CREATE_QUERY_H_
#include <stdio.h>
#include <stdlib.h>

extern _array *createNewArray(List *arrayList);

extern List *addArrayElement(leaf_value * value, List *arrayList);

extern operator *createNotOperator(operator *op);

extern operator *createModOperator(leaf_value *divisor, leaf_value *remainder);

extern operator *createArrayOperator(array_operator_type op, _array *ar);

extern operator *createValueOperator(value_operator_type op, leaf_value * value);

extern leaf_value *createStringValue(char *str);

extern leaf_value *createDoubleValue(char* d);

extern leaf_value *createIntegerValue(char* i);

extern leaf_value *createArrayValue(_array *ar);

extern leaf_value *createBooleanValue(_bool b);

extern List *addOperator(operator *op, List *operatorList);

extern operator_object *createOperatorObject(List *operatorList);

extern value *createOperatorObjectValue(operator_object *oob);

extern value *createLeafValueValue(leaf_value *lv);

extern Clause *createLeafClause(char* key, value *vl);

extern Clause *createCommentClause(char *op, char *str);

extern where_clause_value *stringToWhereClauseValue(char *str);

extern Clause *createWhereClause(char *op, where_clause_value *wcv);

extern List *addClause(Clause *clause, List *clauseList);

extern expression *createExpression(List *clauseList);

extern List *addExpression(expression *exp, List *expressionList);

extern Clause *createExpressionTreeClause(expression_operator_type op, List *expressionList);

extern Clause *createTextClause(char* search_str, _bool lang_op, char* lang_str, _bool case_sense, _bool diacr_sense);

extern MDBQuery *createQuery(expression *exp);



#endif