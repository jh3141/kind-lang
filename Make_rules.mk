.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.dep: %.cpp
	$(CXX) -MM $(CXXFLAGS) $< > $@
