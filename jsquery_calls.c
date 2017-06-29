#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "utils/pg_crc.h"
#include "miscadmin.h"
#include "utils/jsonb.h"

#include "access/htup_details.h"
#include "access/sysattr.h"
#include "access/xact.h"
#include "catalog/dependency.h"
#include "catalog/indexing.h"
#include "catalog/namespace.h"
#include "catalog/objectaccess.h"
#include "catalog/pg_collation.h"
#include "catalog/pg_depend.h"
#include "catalog/pg_extension.h"
#include "catalog/pg_namespace.h"
#include "catalog/pg_type.h"
#include "commands/alter.h"
#include "commands/comment.h"
#include "commands/defrem.h"
#include "commands/extension.h"
#include "commands/schemacmds.h"
#include "funcapi.h"
#include "mb/pg_wchar.h"
#include "miscadmin.h"
#include "nodes/makefuncs.h"
#include "storage/fd.h"
#include "tcop/utility.h"
#include "utils/acl.h"
#include "utils/builtins.h"
#include "utils/fmgroids.h"
#include "utils/lsyscache.h"
#include "utils/memutils.h"
#include "utils/rel.h"
#include "utils/snapmgr.h"
#include "utils/tqual.h"

#include "structures.h"
#include "get_query.h"
#include "create_query.h"

static Oid
get_extension_schema(Oid ext_oid)
{
    Oid         result;
    Relation    rel;
    SysScanDesc scandesc;
    HeapTuple   tuple;
    ScanKeyData entry[1];

    rel = heap_open(ExtensionRelationId, AccessShareLock);

    ScanKeyInit(&entry[0],
                ObjectIdAttributeNumber,
                BTEqualStrategyNumber, F_OIDEQ,
                ObjectIdGetDatum(ext_oid));

    scandesc = systable_beginscan(rel, ExtensionOidIndexId, true,
                                  NULL, 1, entry);

    tuple = systable_getnext(scandesc);

    if (HeapTupleIsValid(tuple))
        result = ((Form_pg_extension) GETSTRUCT(tuple))->extnamespace;
    else
        result = InvalidOid;

    systable_endscan(scandesc);

    heap_close(rel, AccessShareLock);

    return result;
}

Datum
callJsquery_in(char *query)
{
    const char *EXTENSION_NAME = "jsquery";
    const char *FUNCTION_NAME = "jsquery_in";
    const char *JSQUERY_QUERY = query;

    Oid extensionOid;
    Oid shemaOid;
    Oid functionOid;
    Oid jsqueryOid;
    List *funcname;
    FmgrInfo *procedure = palloc0(sizeof(FmgrInfo));
    Oid funcargtypes[1];

    funcargtypes[0] = CSTRINGOID;

 //   jsqueryOid = LookupTypeNameOid(NULL, EXTENSION_NAME, true);
    extensionOid = get_extension_oid(EXTENSION_NAME, false);
    shemaOid = get_extension_schema(extensionOid);

    funcname = list_make2(makeString(get_namespace_name(shemaOid)), makeString(FUNCTION_NAME));
    functionOid = LookupFuncName(funcname, 1, funcargtypes, false);

    if (OidIsValid(functionOid))
    {
        fmgr_info(functionOid, procedure); 
        return FunctionCall1(procedure, JSQUERY_QUERY);
    }

    return NULL;
}

Datum
callJsquery_out(Datum *jsquery_query)
{
    const char *EXTENSION_NAME = "jsquery";
    const char *FUNCTION_NAME = "jsquery_out";

    Oid extensionOid;
    Oid shemaOid;
    Oid functionOid;
    Oid jsqueryOid;
    List *funcname;
    FmgrInfo *procedure = palloc0(sizeof(FmgrInfo));
    Oid funcargtypes[1];

    funcargtypes[0] = CSTRINGOID;

 //   jsqueryOid = LookupTypeNameOid(NULL, EXTENSION_NAME, true);
    extensionOid = get_extension_oid(EXTENSION_NAME, false);
    shemaOid = get_extension_schema(extensionOid);

    funcname = list_make2(makeString(get_namespace_name(shemaOid)), makeString(FUNCTION_NAME));
    functionOid = LookupFuncName(funcname, 1, funcargtypes, false);

    if (OidIsValid(functionOid))
    {
        fmgr_info(functionOid, procedure); 
        return FunctionCall1(procedure, jsquery_query);
    }

    return NULL;
}

Datum
callJsquery_jsonb_exec(Datum *jsonb_data, Datum *jsquery_query)
{
    const char *EXTENSION_NAME = "jsquery";
    const char *FUNCTION_NAME = "json_jsquery_exec";

    Oid extensionOid;
    Oid shemaOid;
    Oid functionOid;
    Oid jsqueryOid;
    List *funcname;
    FmgrInfo *procedure = palloc0(sizeof(FmgrInfo));
    Oid funcargtypes[2];

    funcargtypes[0] = JSONBOID;
    funcargtypes[1] = TypenameGetTypid("jsquery");

    extensionOid = get_extension_oid(EXTENSION_NAME, false);
    shemaOid = get_extension_schema(extensionOid);

    funcname = list_make2(makeString(get_namespace_name(shemaOid)), makeString(FUNCTION_NAME));
    functionOid = LookupFuncName(funcname, 2, funcargtypes, false);

    if (OidIsValid(functionOid))
    {
        fmgr_info(functionOid, procedure); 
        return FunctionCall2(procedure, jsonb_data, jsquery_query);
    }
}