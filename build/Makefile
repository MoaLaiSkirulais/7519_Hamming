SOURCE=../source
BINARY=../binary

all: \
	$(BINARY)/tdc_Hamming_Controller.o \
	$(BINARY)/tdc_Hamming_Decoder.o \
	$(BINARY)/tdc_Hamming_Encoder.o \
	$(BINARY)/tdc_Hamming_File.o \
	$(BINARY)/tdc_Hamming_Helper.o \
	$(BINARY)/tdc_Hamming_Time.o \
	$(BINARY)/tap.o

$(BINARY)/tdc_Hamming_Controller.o: $(SOURCE)/tdc_Hamming_Controller.c $(SOURCE)/tdc_Hamming_Controller.h 
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

$(BINARY)/tdc_Hamming_Decoder.o: $(SOURCE)/tdc_Hamming_Decoder.c $(SOURCE)/tdc_Hamming_Decoder.h 
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

$(BINARY)/tdc_Hamming_Encoder.o: $(SOURCE)/tdc_Hamming_Encoder.c $(SOURCE)/tdc_Hamming_Encoder.h 
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

$(BINARY)/tdc_Hamming_File.o: $(SOURCE)/tdc_Hamming_File.c $(SOURCE)/tdc_Hamming_File.h 
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

$(BINARY)/tdc_Hamming_Helper.o: $(SOURCE)/tdc_Hamming_Helper.c $(SOURCE)/tdc_Hamming_Helper.h 
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

$(BINARY)/tdc_Hamming_Time.o: $(SOURCE)/tdc_Hamming_Time.c $(SOURCE)/tdc_Hamming_Time.h 
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

$(BINARY)/tap.o: $(SOURCE)/tap.c $(SOURCE)/tap.h 
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

all:
	@ar -cr $(BINARY)/tdc_Hamming.a \
		$(BINARY)/tdc_Hamming_Controller.o \
		$(BINARY)/tdc_Hamming_Decoder.o \
		$(BINARY)/tdc_Hamming_Encoder.o \
		$(BINARY)/tdc_Hamming_File.o 
