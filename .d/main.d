main.o .d/main.d : main.cpp Block.hpp
main.bin: main.o Block.o
	$(CXX) $(CXXFLAGS) $(LIBARYFLAGS) -o $@ $^
