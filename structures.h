#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_
 
#include <stdio.h>
#include <stdlib.h>


    typedef enum bool { false, true } bool;

    typedef enum type_of_leaf_value { S, I, A, D, B } type_of_leaf_value;

    typedef enum type_of_operator { NOP, MOP, AOP, VOP } type_of_operator;

    typedef enum type_of_clause { LEAF, COMMENT, TEXT, WHERE, EXPRESSION } type_of_clause;

    typedef enum type_of_value { LF_VALUE, OP_OBJECT } type_of_value;

    /* structures of array */
    typedef struct _array{
        struct array_element *first_ae;
    } _array;

    typedef struct leaf_value{

        type_of_leaf_value type;

        char * str;
        int i;
        _array * ar;
        bool b;
        float d;

    } leaf_value;

     typedef struct array_element{
        leaf_value * value;
        struct array_element *next_ae;
    } array_element;

    /* Operators */
    typedef struct value_operator{
        char * value_op;
        leaf_value * value;
    } value_operator;

    typedef struct not_operator{
        struct operator * op;
    } not_operator;

    typedef struct array_operator{
        char * array_op;
        _array *ar;
    } array_operator;

    typedef struct mod_operator{
        leaf_value *divisor;
        leaf_value *remainder;
    } mod_operator;

    typedef struct operator{

        type_of_operator type;

        value_operator vop;
        not_operator nop;
        array_operator aop;
        mod_operator mop;

    } operator;



    typedef struct operator_list{
        operator op;
        struct operator_list* next_op;
    } operator_list;

    typedef struct operator_object{
        operator_list ol;
    } operator_object;

    typedef struct value{
        type_of_value type;
        leaf_value *lv;
        operator_object oob;
    } value;

    typedef struct leaf_clause{
        char * key;
        struct value vl;
    } leaf_clause;

    typedef struct comment_clause{
        char *op;
        char *str;
    } comment_clause;

    typedef struct clause{
        type_of_clause type;
        leaf_clause lc;
        comment_clause comm_clause;
    } clause;

    typedef struct clause_list{
        clause cl;
        struct clause_list *next_cll;
    } clause_list;

    typedef struct expression{
        clause_list *cll;
    } expression;

    typedef struct query{
        expression *exp;
    } query;

#endif