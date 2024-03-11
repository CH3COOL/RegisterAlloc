SRCDIR += ./include
SRCDIR += ./src

OBJDIR := ./obj

INCS := $(foreach dir,${SRCDIR},-I${dir})
SRCS := $(foreach dir,$(SRCDIR),$(wildcard $(dir)/*.cc))
OBJS := $(patsubst %.cc,$(OBJDIR)/%.o,$(SRCS))

minialloc : ${OBJS}
	clang++ $(OBJS) -o bin/minialloc -O2 -std=c++17

$(OBJDIR)/%.o : %.cc
	mkdir -p $(dir $@)
	clang++ -c $(INCS) $< -o $@ -O2 -std=c++17

.PHONY : clean,run

run : bin/minialloc
	bin/minialloc

clean:
	rm -r ${OBJDIR}/*
	rm -r bin/*