Block.o .d/Block.d : Block.cpp
Block.bin: Block.o
	$(CXX) $(CXXFLAGS) $(LIBARYFLAGS) -o $@ $^
