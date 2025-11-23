CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O3 -I./include
SRCDIR = src
OBJDIR = obj
SOURCES = $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TARGET = eptp_solver

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: clean