SOURCE=../source
BINARY=../binary

all: \
	$(BINARY)/tdc_Hamming_Reader.o \
	$(BINARY)/tap.o

$(BINARY)/tdc_Hamming_Reader.o: $(SOURCE)/tdc_Hamming_Reader.c $(SOURCE)/tdc_Hamming_Reader.h 
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

$(BINARY)/tap.o: $(SOURCE)/tap.c $(SOURCE)/tap.h 
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

all:
	@ar -cr $(BINARY)/tdc_Hamming.a \
		$(BINARY)/tdc_Hamming_Reader.o
