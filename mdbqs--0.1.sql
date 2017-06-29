\echo Use "CREATE EXTENSION MDBQS" to load this file. \quit

CREATE TYPE mdbquery;

CREATE FUNCTION mdbquery_in(cstring) RETURNS mdbquery
AS '$libdir/mdbqs'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION mdbquery_out(mdbquery) RETURNS cstring
AS '$libdir/mdbqs'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION json_mdbquery_exec(jsonb, mdbquery) RETURNS bool
AS '$libdir/mdbqs'
LANGUAGE C STRICT IMMUTABLE;

CREATE FUNCTION mdbquery_json_exec(mdbquery, jsonb) RETURNS bool
AS '$libdir/mdbqs'
LANGUAGE C STRICT IMMUTABLE;

CREATE TYPE mdbquery (
	INTERNALLENGTH = -1,
	INPUT = mdbquery_in,
	OUTPUT = mdbquery_out,
	STORAGE = extended
);

CREATE OPERATOR <=> (
	LEFTARG = jsonb,
	RIGHTARG = mdbquery,
	PROCEDURE = json_mdbquery_exec,
	COMMUTATOR = '<=>',
	RESTRICT = contsel,
	JOIN = contjoinsel
);

CREATE OPERATOR <=> (
	LEFTARG = mdbquery,
	RIGHTARG = jsonb,
	PROCEDURE = mdbquery_json_exec,
	COMMUTATOR = '<=>',
	RESTRICT = contsel,
	JOIN = contjoinsel
);

