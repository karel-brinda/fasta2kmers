CXX      ?= g++
CXXFLAGS  = -std=c++11 -Wall -Wextra -Wno-missing-field-initializers -g -O3
LIBS      = -lm -lz -lpthread

PREFIX    = $(DESTDIR)/usr/local
BINDIR    = $(PREFIX)/bin

ofiles    = src/fasta2kmers.cpp.o
hfiles    = $(wildcard src/*.h)

.PHONY: all clean install

all: fasta2kmers

install: fasta2kmers
	install  fasta2kmers $(BINDIR)/fasta2kmers
	install  $(MANPAGE) $(MANDIR)/$(MANPAGE)

fasta2kmers: $(ofiles)
	$(CXX) $(CXXFLAGS) $(DFLAGS) $(ofiles) -o $@ -L. $(LIBS) $(HTSLIB)

src/%.cpp.o: src/%.cpp $(hfiles)
	$(CXX) $(CXXFLAGS) $(DFLAGS) -c $< -o $@

clean:
	rm -f src/*.o
	rm -f fasta2kmers

