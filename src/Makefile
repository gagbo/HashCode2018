CXX = g++

CXXFLAGS += -Wall -Wextra
CXXFLAGS += -std=gnu++11
CXXFLAGS += -O3
# CXXFLAGS += -fsanitize=address
# CXXFLAGS += -fsanitize=leak
# CXXFLAGS += -fno-omit-frame-pointer
# CXXFLAGS += -g

# LDFLAGS += -lasan

BINARY = oqr_scheduler
SOURCES = \
	  main.cpp \
	  Position.cpp \
	  Ride.cpp \
	  Vehicle.cpp

OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))

$(BINARY): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(BINARY) $(OBJECTS)

tests: test_a test_b test_c test_d test_e

test_a: $(BINARY)
	./$(BINARY) < ../input/a_example.in > ../input/a_example.out

test_b: $(BINARY)
	./$(BINARY) < ../input/b_should_be_easy.in > ../input/b_should_be_easy.out

test_c: $(BINARY)
	./$(BINARY) < ../input/c_no_hurry.in > ../input/c_no_hurry.out

test_d: $(BINARY)
	./$(BINARY) < ../input/d_metropolis.in > ../input/d_metropolis.out

test_e: $(BINARY)
	./$(BINARY) < ../input/e_high_bonus.in > ../input/e_high_bonus.out

.PHONY: clean tests test_a test_b test_c test_d test_e $(SOURCES)
