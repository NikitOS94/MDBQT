#ifndef _CREATE_QUERY_H_
#define _CREATE_QUERY_H_
#include <stdio.h>
#include <stdlib.h>

extern _array *createNewArray(List *arrayList);

extern List *addArrayElement(LeafValue * value, List *arrayList);

extern operator *createNotOperator(operator *op);

extern operator *createModOperator(LeafValue *divisor, LeafValue *remainder);

extern operator *createArrayOperator(array_operator_type op, _array *ar);

extern operator *createValueOperator(value_operator_type op, LeafValue *value);

extern LeafValue *createStringValue(char *str);

extern LeafValue *createDoubleValue(char* d);

extern LeafValue *createIntegerValue(char* i);

extern LeafValue *createArrayValue(_array *ar);

extern LeafValue *createBooleanValue(_bool b);

extern List *addOperator(operator *op, List *operatorList);

extern operator_object *createOperatorObject(List *operatorList);

extern MDBValue *createOperatorObjectValue(operator_object *oob);

extern MDBValue *createLeafValueValue(LeafValue *lv);

extern Clause *createLeafClause(char* key, MDBValue *vl);

extern Clause *createCommentClause(char *op, char *str);

extern WhereClauseValue *stringToWhereClauseValue(char *str);

extern Clause *createWhereClause(char *op, WhereClauseValue *wcv);

extern List *addClause(Clause *clause, List *clauseList);

extern Expression *createExpression(List *clauseList);

extern List *addExpression(Expression *exp, List *expressionList);

extern Clause *createExpressionTreeClause(expression_operator_type op, List *expressionList);

extern Clause *createTextClause(char* search_str, _bool lang_op, char* lang_str, _bool case_sense, _bool diacr_sense);

extern MDBQuery *createQuery(Expression *exp);

#endif