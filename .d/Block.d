Block.o .d/Block.d : Block.cpp Block.hpp
Block.bin: Block.o Block.o
	$(CXX) $(CXXFLAGS) $(LIBARYFLAGS) -o $@ $^
