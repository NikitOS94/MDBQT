#ifndef _GET_QUERY_H_
#define _GET_QUERY_H_
#include <stdio.h>
#include <stdlib.h>

extern char *getJsquery(MDBQuery * qu);

extern char *getExpression(Expression * ex);

extern char *get_clause(Clause *cl);

	// Expression tree clause functions
	extern char *getExpression_clause(expression_clause* exp_clause);

	extern char *getExpression_operator(expression_operator_type exp_op);

	// Text clause functions
	extern char *get_text_clause(text_clause* t_clause);

	// Leaf clause functions
	extern char *get_leaf_clause(leaf_clause *lc);

	extern char *get_leaf_clause_value(char* key, MDBValue *val);

		// Leaf value eq
		extern char *getLeafValue_eq(char *key, LeafValue *lv);

		// Leaf value operators
		extern char *get_operator_object(char *key, operator_object *op_object);

		// Operators
		extern char *get_operator(char *key, operator *op);

			//Not operator
			extern char *get_not_operator(char *key, not_operator *op);

			//Arrray operator
			extern char *getArrayOperator(char *key, array_operator *aop);

			extern char *getArraySequence(_array *ar);

			extern char *getLeafValue(LeafValue *value);

			// Value operator
			extern char *get_value_operator(char *key, ValueOperator *vop);

			extern char *get_value_operator_type(value_operator_type vop_type);

			extern char *get_value_type(char *value_type);

#endif