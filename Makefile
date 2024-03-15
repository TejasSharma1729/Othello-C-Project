all: othelloSmart

%: %.cpp
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@
	rm -rf *.dSYM

clean:
	rm -rf othelloSmart
