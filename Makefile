PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man/man6

CFLAGS += -lncurses

all: cgol

cgol:
	$(CC) cgol.c -o cgol $(CFLAGS) 

install: cgol
	mkdir -p $(PREFIX)/bin
	cp cgol $(PREFIX)/bin/
	mkdir -p $(MANPREFIX)
	cp cgol.6 $(MANPREFIX)/

uninstall:
	rm -f $(PREFIX)/bin/cgol $(MANPREFIX)/cgol.6

clean:
	rm -f cgol
