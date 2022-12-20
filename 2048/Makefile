CC=g++
CFLAGS=-g

all: expectimax montecarlo

expectimax: expectimax.o game.o expectimax_policy.o policy.o

montecarlo: montecarlo.o game.o montecarlo_policy.o policy.o

%.o: %.cc $(BUILDSTAMP)
	$(call run,$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c,COMPILE,$<)

clean:
	$(RM) *.o expectimax montecarlo
