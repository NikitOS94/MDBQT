CREATE EXTENSION jsquery;

set escape_string_warning=off

# eq operator
select '{ "a" : 1 }'::jsonb <=> '{ a : 1 }';
select '{ "a" : 1 }'::jsonb <=> '{ a : 2 }';

# not eq operator
select '{ "a" : 1 }'::jsonb <=> '{ a : { $ne: 1 } }';
select '{ "a" : 1 }'::jsonb <=> '{ a : { $ne: 20 } }';

# eq operator two
select '{ "a" : 1 }'::jsonb <=> '{ a : { $eq: 1 } }';
select '{ "a" : 1 }'::jsonb <=> '{ a : { $eq: 20 } }';

# less operator
select '{ "a" : 1 }'::jsonb <=> '{ a : { $lt : 20 } }';
select '{ "a" : 1 }'::jsonb <=> '{ a : { $lt : 0 } }';

# greate operator
select '{ "a" : 1 }'::jsonb <=> '{ a : { $gt : 20 } }';
select '{ "a" : 1 }'::jsonb <=> '{ a : { $gt : 0 } }';

# less or eq operator
select '{ "a" : 1 }'::jsonb <=> '{ a : { $lte : 20 } }';
select '{ "a" : 1 }'::jsonb <=> '{ a : { $lte : 1 } }';
select '{ "a" : 1 }'::jsonb <=> '{ a : { $lte : 0 } }';

# greate or eq operator
select '{ "a" : 1 }'::jsonb <=> '{ a : { $gte : 20 } }';
select '{ "a" : 1 }'::jsonb <=> '{ a : { $gte : 1 } }';
select '{ "a" : 1 }'::jsonb <=> '{ a : { $gte : 0 } }';

# in array operator
select '{ "a" : 5 }'::jsonb <=> '{ a : { $in: [ 5, 15 ] } }';
select '{ "a" : 7 }'::jsonb <=> '{ a : { $in: [ 5, 15 ] } }';

# not in array operator
select '{ "a" : 5 }'::jsonb <=> '{ a : { $nin: [ 5, 15 ] } }';
select '{ "a" : 7 }'::jsonb <=> '{ a : { $nin: [ 5, 15 ] } }';

# size of array operator
select '{ "a" : [1, 2] }'::jsonb <=> '{ a: { $size: 2 } }';
select '{ "a" : [1, 2] }'::jsonb <=> '{ a: { $size: 1 } }';

# Logical query operators
# not operator
select '{ "a" : 2 }'::jsonb <=> '{ a: { $not: { $gt: 1.99 } } }';
select '{ "a" : 1 }'::jsonb <=> '{ a: { $not: { $gt: 1.99 } } }';

# and operator
select '{ "a" : 1 }'::jsonb <=> '{ $and: [ { a: { $ne: 1.99 } }, { a: { $exists: true } } ] }';

# or operator
select '{ "a" : 1 }'::jsonb <=> '{ $or: [ { a: { $ne: 1 } }, { a: { $exists: true } } ] }';
select '{ "a" : 1 }'::jsonb <=> '{ $or: [ { a: 1 }, { a: { $ne: 1 } }, { a: { $exists: true } } ] }';

# nor operator
select '{ "a" : 1 }'::jsonb <=> '{ $and: [ { a: { $ne: 1.99 } }, { a: { $exists: true } } ] }';

# Element query operators
# exists operator
select '{ "a" : 1 }'::jsonb <=> '{ a: { $exists: true } }';
select '{ "a" : 1 }'::jsonb <=> '{ a: { $exists: false } }';
select '{ "a" : 1 }'::jsonb <=> '{ b: { $exists: true } }';

# type operator
select '{ "a" : 1 }'::jsonb <=> '{ a: { $type: "int" } }';
select '{ "a" : "qwerty" }'::jsonb <=> '{ a: { $type: "string" } }';
select '{ "a" : [1, 2] }'::jsonb <=> '{ a: { $type: "array" } }';

# Array query operators
# All operator
select '{ "a" : [ "ssl","security"] }'::jsonb <=> '{ a: { $all: [ "ssl" , "security" ] } }';
select '{ "a" : [ security"] }'::jsonb <=> '{ a: { $all: [ "ssl" , "security" ] } }'; 
#
# Size operator
select '{ "a" : [ "ssl","security"] }'::jsonb <=> '{ a: { $size: 2 } }';
select '{ "a" : [ "ssl","security"] }'::jsonb <=> '{ a: { $size: 1 } }';

RESET enable_seqscan;