
SRCS = $(wildcard *.C)

PROGS = $(patsubst %.C,%,$(SRCS))

%: %.C 
	g++ $< -o $@

clean:
	rm -f $(PROGS)
