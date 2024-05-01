all: othelloSmart

othelloSmart: othelloSmart.cpp
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@
	rm -rf *.dSYM
	./othelloSmart

clean:
	rm -rf othelloSmart

.PHONY: all clean
