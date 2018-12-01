#
# This makefile scans the SOURCEDIR for .C files, and builds them in 
# the local directory.  It also has a rule for copying out the input
# files, assumed to have .txt suffixes.  This Makefile thus belongs in
# the parent of the source directory.  It's in among the sources as
# a clumsy way of including it in version control.

SOURCEDIR = aoc2018

SRCS = $(wildcard $(SOURCEDIR)/*.C)

PROGS = $(patsubst $(SOURCEDIR)/%.C,%,$(SRCS))

%.txt : $(SOURCEDIR)/%.txt
	cp $< $@

%: $(SOURCEDIR)/%.C 
	g++ $< -o $@

clean:
	rm -f $(PROGS)
	rm -f *.txt
