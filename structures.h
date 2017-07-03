#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_
 
#include <stdio.h>
#include <stdlib.h>

#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"

    typedef enum _bool 
    { 
        _false, 
        _true 
    } _bool;

    typedef enum TypeOfLeafValue 
    { 
        S, 
        I, 
        A, 
        D, 
        B 
    } TypeOfLeafValue;

    typedef enum typeOfOperator 
    { 
        NOP, 
        MOP, 
        AOP, 
        VOP 
    } typeOfOperator;

    typedef enum array_operator_type 
    { 
        _IN, 
        _NIN, 
        _ALL
    } array_operator_type;

    typedef enum expression_operator_type 
    { 
        _OR, 
        _NOR, 
        _AND 
    } expression_operator_type;

    typedef enum value_operator_type
    { 
        _LESS, 
        _EQ,
        _NOTEQ,
        _LESSEQ,
        _GREAT,
        _GREATEQ,
        _TYPE,
        _SIZE,
        _EXISTS  
    } value_operator_type;


    typedef enum type_of_clause 
    { 
        LEAF, 
        COMMENT, 
        TEXT, 
        WHERE, 
        EXPRESSION 
    } type_of_clause;

    typedef enum type_of_value 
    { 
        LF_VALUE, 
        OP_OBJECT 
    } type_of_value;

    typedef enum type_of_WhereClauseValue 
    { 
        STR 
    } type_of_WhereClauseValue;

    typedef struct _array
    {
    	List 	*arrayList;
    } _array;

    typedef struct LeafValue
    {
        TypeOfLeafValue type;
        union
        {
            char    *str;
            char    *i;
            _array  *ar;
            _bool    b;
            char    *d;
        };
    } LeafValue;

    /* Operators */
    typedef struct ValueOperator
    {
        typeOfOperator     type;

        value_operator_type  value_op;
        LeafValue           *value;
    } ValueOperator;

    typedef struct not_operator
    {
        typeOfOperator type;

        struct operator * op;
    } not_operator;

    typedef struct array_operator
    {
        typeOfOperator type;

        array_operator_type array_op;
        _array *ar;
    } array_operator;

    typedef struct mod_operator
    {
        typeOfOperator type;

        LeafValue *divisor;
        LeafValue *remainder;
    } mod_operator;

    typedef struct operator
    {
        typeOfOperator type;
    } operator;

    typedef struct operator_list
    {
        operator                *op;
        struct operator_list    *next_op;
    } operator_list;

    typedef struct operator_object
    {
        List *operatorList;
    } operator_object;

    typedef struct MDBValue
    {
        type_of_value type;
        union{
            LeafValue *lv;
            operator_object *oob;
        };
    } MDBValue;

    typedef struct leaf_clause
    {
        type_of_clause   type;

        char            *key;
        MDBValue           *vl;
    } leaf_clause;

    typedef struct comment_clause
    {
        type_of_clause              type;

        char *op;
        char *str;
    } comment_clause;

    typedef struct WhereClauseValue
    {
        type_of_clause              type;

        type_of_WhereClauseValue  val_type;
        char *                      str;
    } WhereClauseValue;

    typedef struct where_clause
    {
        type_of_clause            type;

        char *op;
        WhereClauseValue *wcv;
    } where_clause;

    typedef struct text_clause
    {
        type_of_clause            type;

        char* search_str;
        _bool lang_op;
        char* lang_str;
        _bool case_sense;
        _bool diacr_sense;
    } text_clause;

    typedef struct Clause
    {
        type_of_clause            type;
    } Clause;

    typedef struct Expression
    {
        List  				*clauseList;
    } Expression;

    typedef struct expression_clause
    {
        type_of_clause               type;

        expression_operator_type     op;
        List             			*expressionList;
    } expression_clause;

    typedef struct MDBQuery
    {
        Expression *exp;
    } MDBQuery;

#endif