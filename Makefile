.POSIX:
.SUFFIXES:
CC = gcc
CFLAGS = -Wall -Wpedantic -Wextra -O -D_XOPEN_SOURCE=700 -fpic
LDLIBS = -lm -llivesplit_core
LDFLAGS = -g -shared
PREFIX = /usr/local
LIBFOLDER = opensplit_core
OUTPUT = libopensplit_core.so

all: opensplit_core
opensplit_core: opensplit-core/deps/crypto-algorithms/base64.o opensplit-core/livesplit_hooks/livesplit.o opensplit-core/opensplit_core.o
	$(CC) $(LDFLAGS) opensplit_core.o livesplit.o base64.o -o $(OUTPUT) $(LDLIBS)
	
#b64
opensplit-core/deps/crypto-algorithms/base64.o: opensplit-core/deps/crypto-algorithms/base64.c opensplit-core/deps/crypto-algorithms/base64.h

#opensplit components
opensplit-core/livesplit_hooks/livesplit.o: opensplit-core/deps/crypto-algorithms/base64.o opensplit-core/livesplit_hooks/livesplit.c opensplit-core/livesplit_hooks/livesplit.h

opensplit-core/opensplit_core.o: opensplit-core/opensplit_core.h opensplit-core/opensplit_core.c opensplit-core/livesplit_hooks/livesplit.h opensplit-core/deps/crypto-algorithms/base64.o


clean:
	rm *.o

fullclean: clean
	rm *.so

install:
	mkdir $(PREFIX)/include/$(LIBFOLDER)
	cp opensplit-core/opensplit_core.h $(PREFIX)/include/$(LIBFOLDER)
	cp opensplit-core/livesplit_hooks/livesplit.h $(PREFIX)/include/$(LIBFOLDER)
	cp $(OUTPUT) $(PREFIX)/lib/
	ldconfig

uninstall:
	rm $(PREFIX)/include/$(LIBFOLDER)/opensplit_core.h
	rm $(PREFIX)/include/$(LIBFOLDER)/livesplit.h
	rmdir $(PREFIX)/include/$(LIBFOLDER)
	rm $(PREFIX)/lib/$(OUTPUT)
	ldconfig


.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) $(DEBUG) -c $<

