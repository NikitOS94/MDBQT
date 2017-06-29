#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "utils/pg_crc.h"
#include "miscadmin.h"

#include "structures.h"
#include "create_query.h"

_array *
createNewArray(List *arrayList) 
{
    _array *new_ar = (_array *) palloc(sizeof(_array));
    new_ar->arrayList = arrayList;
    return new_ar;
}

List *
addArrayElement(LeafValue *value, List *arrayList) 
{
    return lappend(arrayList, value);
}

operator *
createNotOperator(operator *op) 
{
    not_operator *new_op = (not_operator *) palloc(sizeof(operator));
    new_op->type = NOP;
    new_op->op = op;
    return (operator*) new_op;
}

operator *
createModOperator(LeafValue *divisor, LeafValue *remainder) 
{
    mod_operator *new_op = (mod_operator *) palloc(sizeof(mod_operator));
    new_op->type = MOP;
    new_op->divisor = divisor;
    new_op->remainder = remainder;
    return (operator*) new_op;
}

operator *
createArrayOperator(array_operator_type op, _array *ar) 
{
    array_operator *new_op = (array_operator *) palloc(sizeof(array_operator));
    new_op->type = AOP;
    new_op->array_op = op;
    new_op->ar = ar;
    return (operator*) new_op;
}

operator *
createValueOperator(value_operator_type op, LeafValue * value) 
{
    ValueOperator *new_op = (ValueOperator *) palloc(sizeof(ValueOperator));
    new_op->type = VOP;  
    new_op->value_op = op;
    new_op->value = value;
    return (operator*) new_op;
}

LeafValue *
createStringValue(char *str)
{
    LeafValue *lv = (LeafValue *) palloc(sizeof(LeafValue));
    lv->type = S;
    lv->str = str;
    return lv;
}

LeafValue *
createDoubleValue(char* d)
{
    LeafValue *lv = (LeafValue *) palloc(sizeof(LeafValue));
    lv->type = D;
    lv->d = d;
    return lv;
}

LeafValue *
createIntegerValue(char* i)
{
    LeafValue *lv = (LeafValue *) palloc(sizeof(LeafValue));
    lv->type = I;
    lv->i = i;
    return lv;
}

LeafValue *
createArrayValue(_array *ar)
{
  LeafValue *lv = (LeafValue *) palloc(sizeof(LeafValue));
  lv->type = A;
  lv->ar = ar;
  return lv;
}

LeafValue *
createBooleanValue(_bool b)
{
  LeafValue *lv = (LeafValue *) palloc(sizeof(LeafValue));
  lv->type = B;
  lv->b = b;
  return lv;
}

List *
addOperator(operator *op, List *operatorList) 
{  
    return lcons(op, operatorList);
}

operator_object *
createOperatorObject(List *operatorList) 
{
    operator_object *new_oob = (operator_object *) palloc(sizeof(operator_object));
    new_oob->operatorList = operatorList;
    return new_oob;
}

MDBValue *
createOperatorObjectValue(operator_object *oob) 
{
    MDBValue *vl = (MDBValue *) palloc(sizeof(MDBValue));
    vl->type = OP_OBJECT;
    vl->oob = oob;
    return vl;
}

MDBValue *
createLeafValueValue(LeafValue *lv) 
{
    MDBValue *vl = (MDBValue *) palloc(sizeof(MDBValue));
    vl->type = LF_VALUE;
    vl->lv = lv;
    return vl;
}

Clause *
createLeafClause(char* key, MDBValue *vl) 
{
    leaf_clause *new_lc = (leaf_clause *) palloc(sizeof(leaf_clause));
    new_lc->type = LEAF;
    new_lc->key = key;
    new_lc->vl = vl;
    return ( Clause* ) new_lc;
}

Clause *
createCommentClause(char *op, char *str) 
{
    comment_clause *new_com_cl = (comment_clause *) palloc(sizeof(comment_clause));
    new_com_cl->type = COMMENT;
    new_com_cl->op = op;
    new_com_cl->str = str;
    return ( Clause* ) new_com_cl;
}

WhereClauseValue *
stringToWhereClauseValue(char *str)
{
    WhereClauseValue *wcv = (WhereClauseValue *) palloc(sizeof(WhereClauseValue));
    wcv->str = str;   
    return wcv;
}

Clause *
createWhereClause(char *op, WhereClauseValue *wcv)
{
    where_clause *wc = (where_clause *) palloc(sizeof(where_clause));
    wc->type = WHERE;
    wc->op = op;
    wc->wcv = wcv;
    return (Clause *) wc;
}

List *
addClause(Clause *clause, List *clauseList)
{
    return lappend(clauseList, clause);
}

Expression *
createExpression(List *clauseList)
{
    Expression *exp = (Expression *) palloc(sizeof(Expression));
    exp->clauseList = clauseList;
    return exp;
}

List *
addExpression(Expression *exp, List *expressionList)
{
    return lcons(exp, expressionList);
}

Clause *
createExpressionTreeClause(expression_operator_type op, List *expressionList)
{
    expression_clause *exp_cl = (expression_clause *) palloc(sizeof(expression_clause));
    exp_cl->type = EXPRESSION;
    exp_cl->op = op;
    exp_cl->expressionList = expressionList;
    return (Clause *) exp_cl;
}

Clause *
createTextClause(char* search_str, _bool lang_op, char* lang_str, _bool case_sense, _bool diacr_sense)
{
    text_clause *text_cl = (text_clause *) palloc(sizeof(text_clause));
    text_cl->type = TEXT;
    text_cl->search_str = search_str;
    text_cl->lang_op = lang_op;
    text_cl->lang_str = lang_str;
    text_cl->case_sense = case_sense;
    text_cl->diacr_sense = diacr_sense;
    return (Clause *) text_cl;
}

MDBQuery *
createQuery(Expression *exp)
{
    MDBQuery *qu = (MDBQuery *) palloc(sizeof(MDBQuery));
    qu->exp = exp;
    return qu;
}