CC = g++
CFLAGS = -Wall -Wextra -pedantic -std=c++11
LDFLAGS = -lncurses

SRCDIR = .
OBJDIR = obj
HPPDIR = hpp-files

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
TARGET = game
TARGET2 = Salvataggio.txt

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $< -I$(HPPDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET) $(TARGET2)

.PHONY: all clean


