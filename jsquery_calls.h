#ifndef _JSQUERY_CALLS_H_
#define _JSQUERY_CALLS_H_
 
#include <stdio.h>
#include <stdlib.h>

#include "postgres.h"

extern Datum callJsquery_in(char *query);

extern Datum callJsquery_out(Datum *jsquery_query);

extern Datum callJsquery_jsonb_exec(Datum *jsonb_data, Datum *jsquery_query);

#endif