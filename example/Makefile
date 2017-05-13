GCC = g++
FLAGS = -Wall -Wextra -pedantic -std=c++0x

DEPEND_LF = ../silk/leakageFunctions.cpp ../silk/leakageFunctions.hpp
DEPEND_LDF = ../silk/leakageDistributionFunctions.cpp ../silk/leakageDistributionFunctions.hpp
DEPEND_UT = ../silk/util_func.cpp ../silk/util_func.hpp
DEPEND_TR = ../silk/tracer.cpp ../silk/tracer.hpp
DEPEND_TG = ../silk/memoryUnit.hpp  ../silk/silk.hpp

DEPEND_SRC= $(DEPEND_TR) $(DEPEND_UT) $(DEPEND_LDF) $(DEPEND_LF)

DEPEND_O = util_func.o leakageFunctions.o leakageDistributionFunctions.o tracer.o

EXEC = aes test simParam aes_sbox

all: $(EXEC)

test: test.cpp #$(DEPEND_O)
	$(GCC) $(FLAGS) $< tracer.o ../silk/util_func.cpp ../silk/leakageFunctions.cpp ../silk/leakageDistributionFunctions.cpp -o $@

simParam: sim_parameters.cpp $(DEPEND_O)
	$(GCC) $(FLAGS) $< $(DEPEND_O) ../silk/leakageFunctions.cpp -o $@

aes_sbox: aes_sbox.cpp $(DEPEND_O)
	$(GCC) $(FLAGS) $< $(DEPEND_O) aes.o -o $@

# TEST AES
aes: aes_expl.cpp $(DEPEND_O) aes.o
	$(GCC) $(FLAGS) $< $(DEPEND_O) aes.o -o $@

aes.o: aes.cpp aes.hpp
	 $(GCC) $(FLAGS) $< -c


# common SILK files

util_func.o: $(DEPEND_UT)
	$(GCC) $(FLAGS) $< -c

leakageFunctions.o: $(DEPEND_LF)
	$(GCC) $(FLAGS) $< -c

leakageDistributionFunctions.o: $(DEPEND_LDF)
	$(GCC) $(FLAGS) $< -c
	
tracer.o: $(DEPEND_TR)
	$(GCC) $(FLAGS) $< -c

#%.o: %.cpp %.hpp
#	$(GCC) $(FLAGS) -c $< -o $@

clean :
	rm *.o

cleanall:
	rm *.o $(EXEC)
