#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_
 
#include <stdio.h>
#include <stdlib.h>

#include "postgres.h"

    typedef enum _bool 
    { 
        _false, 
        _true 
    } _bool;

    typedef enum type_of_leaf_value 
    { 
        S, 
        I, 
        A, 
        D, 
        B 
    } type_of_leaf_value;

    typedef enum type_of_operator 
    { 
        NOP, 
        MOP, 
        AOP, 
        VOP 
    } type_of_operator;

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

    typedef enum type_of_where_clause_value 
    { 
        STR 
    } type_of_where_clause_value;

    typedef struct _array
    {
    	List 	*arrayList;
    } _array;

    typedef struct leaf_value
    {
        type_of_leaf_value type;
        union
        {
            char    *str;
            char    *i;
            _array  *ar;
            _bool    b;
            char    *d;
        };
    } leaf_value;

    /* Operators */
    typedef struct value_operator
    {
        type_of_operator     type;

        value_operator_type  value_op;
        leaf_value           *value;
    } value_operator;

    typedef struct not_operator
    {
        type_of_operator type;

        struct operator * op;
    } not_operator;

    typedef struct array_operator
    {
        type_of_operator type;

        array_operator_type array_op;
        _array *ar;
    } array_operator;

    typedef struct mod_operator
    {
        type_of_operator type;

        leaf_value *divisor;
        leaf_value *remainder;
    } mod_operator;

    typedef struct operator
    {
        type_of_operator type;
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

    typedef struct value
    {
        type_of_value type;
        union{
            leaf_value *lv;
            operator_object *oob;
        };
    } value;

    typedef struct leaf_clause
    {
        type_of_clause              type;

        char * key;
        struct value *vl;
    } leaf_clause;

    typedef struct comment_clause
    {
        type_of_clause              type;

        char *op;
        char *str;
    } comment_clause;

    typedef struct where_clause_value
    {
        type_of_clause              type;

        type_of_where_clause_value  val_type;
        char *                      str;
    } where_clause_value;

    typedef struct where_clause
    {
        type_of_clause            type;

        char *op;
        where_clause_value *wcv;
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

    typedef struct expression
    {
        List  				*clauseList;
    } expression;

    typedef struct expression_clause
    {
        type_of_clause               type;

        expression_operator_type     op;
        List             			*expressionList;
    } expression_clause;

    typedef struct MDBQuery
    {
        expression *exp;
    } MDBQuery;

#endif