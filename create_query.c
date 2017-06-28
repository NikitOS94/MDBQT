#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "utils/pg_crc.h"
#include "miscadmin.h"
#include "utils/jsonb.h"

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
addArrayElement(leaf_value * value, List *arrayList) 
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
createModOperator(leaf_value *divisor, leaf_value *remainder) 
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
createValueOperator(value_operator_type op, leaf_value * value) 
{
    value_operator *new_op = (value_operator *) palloc(sizeof(value_operator));
    new_op->type = VOP;  
    new_op->value_op = op;
    new_op->value = value;
    return (operator*) new_op;
}

leaf_value *
createStringValue(char *str)
{
    leaf_value *lv = (leaf_value *) palloc(sizeof(leaf_value));
    lv->type = S;
    lv->str = str;
    return lv;
}

leaf_value *
createDoubleValue(char* d)
{
    leaf_value *lv = (leaf_value *) palloc(sizeof(leaf_value));
    lv->type = D;
    lv->d = d;
    return lv;
}

leaf_value *
createIntegerValue(char* i)
{
    leaf_value *lv = (leaf_value *) palloc(sizeof(leaf_value));
    lv->type = I;
    lv->i = i;
    return lv;
}

leaf_value *
createArrayValue(_array *ar)
{
  leaf_value *lv = (leaf_value *) palloc(sizeof(leaf_value));
  lv->type = A;
  lv->ar = ar;
  return lv;
}

leaf_value *
createBooleanValue(_bool b)
{
  leaf_value *lv = (leaf_value *) palloc(sizeof(leaf_value));
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

value *
createOperatorObjectValue(operator_object *oob) 
{
    value *vl = (value *) palloc(sizeof(value));
    vl->type = OP_OBJECT;
    vl->oob = oob;
    return vl;
}

value *
createLeafValueValue(leaf_value *lv) 
{
    value *vl = (value *) palloc(sizeof(value));
    vl->type = LF_VALUE;
    vl->lv = lv;
    return vl;
}

Clause *
createLeafClause(char* key, value *vl) 
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

where_clause_value *
stringToWhereClauseValue(char *str)
{
    where_clause_value *wcv = (where_clause_value *) palloc(sizeof(where_clause_value));
    wcv->str = str;   
    return wcv;
}

Clause *
createWhereClause(char *op, where_clause_value *wcv)
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

expression *
createExpression(List *clauseList)
{
    expression *exp = (expression *) palloc(sizeof(expression));
    exp->clauseList = clauseList;
    return exp;
}

List *
addExpression(expression *exp, List *expressionList)
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
createQuery(expression *exp)
{
    MDBQuery *qu = (MDBQuery *) palloc(sizeof(MDBQuery));
    qu->exp = exp;
    return qu;
}