CC=g++
CFLAGS=-g

all: expectimax montecarlo

expectimax: expectimax.o

montecarlo: montecarlo.o

%.o: %.cc $(BUILDSTAMP)
	$(call run,$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c,COMPILE,$<)

clean= $(RM) *.o expectimax montecarlo
