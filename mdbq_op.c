PG_FUNCTION_INFO_V1(json_mdbquery_exec);
Datum
json_mdbquery_exec(PG_FUNCTION_ARGS)
{
	Jsonb			*jb = PG_GETARG_JSONB(0);
	JsQuery			*jq = PG_GETARG_JSQUERY(1);
	bool			res;
	JsonbValue		jbv;
	JsQueryItem	jsq;

	jbv.type = jbvBinary;
	jbv.val.binary.data = &jb->root;
	jbv.val.binary.len = VARSIZE_ANY_EXHDR(jb);

	jsqInit(&jsq, jq);

	res = recursiveExecute(&jsq, &jbv, NULL);

	PG_FREE_IF_COPY(jb, 0);
	PG_FREE_IF_COPY(jq, 1);

	PG_RETURN_BOOL(res);
}


PG_FUNCTION_INFO_V1(mdbquery_json_exec);
Datum
mdbquery_json_exec(PG_FUNCTION_ARGS)
{
	JsQuery			*jq = PG_GETARG_JSQUERY(0);
	Jsonb			*jb = PG_GETARG_JSONB(1);
	bool			res;
	JsonbValue		jbv;
	JsQueryItem	jsq;

	jbv.type = jbvBinary;
	jbv.val.binary.data = &jb->root;
	jbv.val.binary.len = VARSIZE_ANY_EXHDR(jb);

	jsqInit(&jsq, jq);

	res = recursiveExecute(&jsq, &jbv, NULL);

	PG_FREE_IF_COPY(jq, 0);
	PG_FREE_IF_COPY(jb, 1);

	PG_RETURN_BOOL(res);
}