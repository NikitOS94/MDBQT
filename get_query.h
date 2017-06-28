#ifndef _GET_QUERY_H_
#define _GET_QUERY_H_
#include <stdio.h>
#include <stdlib.h>

extern void nSError(char *s);

extern char* sconcat1(char *form, char *s1, int plus);

extern char* sconcat2(char *form, char *s1, char *s2, int plus);

extern char* sconcat3(char *form, char *s1, char *s2, char *s3, int plus);

extern char *get_jsquery(MDBQuery * qu);

extern char *get_expression(expression * ex);

extern char *get_clause(Clause *cl);

	// Expression tree clause functions
	extern char *get_expression_clause(expression_clause* exp_clause);

	extern char *get_expression_operator(expression_operator_type exp_op);

	// Text clause functions
	extern char *get_text_clause(text_clause* t_clause);

	// Leaf clause functions
	extern char *get_leaf_clause(leaf_clause *lc);

	extern char *get_leaf_clause_value(char* key, value *val);

		// Leaf value eq
		extern char *get_leaf_value_eq(char *key, leaf_value *lv);

		// Leaf value operators
		extern char *get_operator_object(char *key, operator_object *op_object);

		// Operators
		extern char *get_operator(char *key, operator *op);

			//Not operator
			extern char *get_not_operator(char *key, not_operator *op);

			//Arrray operator
			extern char *get_array_operator(char *key, array_operator *aop);

			extern char *get_array_operator_type(array_operator_type aop_type);

			extern char *get_array(_array * ar);

			extern char *get_leaf_value(leaf_value * value);

			// Value operator
			extern char *get_value_operator(char *key, value_operator *vop);

			extern char *get_value_operator_type(value_operator_type vop_type);

			extern char *get_value_type(char *value_type);

#endif