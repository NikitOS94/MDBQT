\echo Use "CREATE EXTENSION MDBQS" to load this file. \quit

CREATE FUNCTION start_parse2(cstring) RETURNS text
AS '$libdir/mdbqs'
LANGUAGE C IMMUTABLE STRICT;