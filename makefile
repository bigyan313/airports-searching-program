CXXFLAGS += --std=c++17
airport: airports.cpp
	$(CXX) $(CXXFLAGS) -o airports airports.cpp
clean:
	-rm -f a.out airports airports.o
