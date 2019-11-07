main.o .d/main.d : main.cpp Block.cpp
main.bin: main.o Block.o
	$(CXX) $(CXXFLAGS) $(LIBARYFLAGS) -o $@ $^
