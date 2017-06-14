MODULE_big = mdbqs
OBJS = mdbqs_gram.o mdbqs_scan.o
INCLUDES = structures.h

EXTENSION = mdbqs        	# the extensions name
DATA = mdbqs--0.1.sql  		# script files to install
REGRESS = mdbqs_test     	# our test script file (without extension)
MODULES = mdbqs          	# our c module file to build
ENCODING = UTF8

#EXTRA_CLEAN = y.tab.c y.tab.h \
#				mdbqs_gram.c mdbqs_scan.c mdbqs_gram.h

# postgres build stuff
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

mdbqs_gram.c: BISONFLAGS += -dt

mdbqs_gram.o: mdbqs_scan.c

distprep: mdbqs_gram.c mdbqs_scan.c
