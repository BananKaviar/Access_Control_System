# Use MSYS2/Git Bash shell
SHELL := /usr/bin/sh

# Compiler + flags
CC := gcc
CFLAGS := -Wall -Werror -g

# Program + folders
PROG := main.exe
OUTPUTDIR := obj

# Only include headers that actually exist
DEPS := adminMenu.h safeinput.h cards.h cards_storage.h

# Only list .c files that exist
SOURCES := main.c adminMenu.c safeinput.c cards.c cards_storage.c

# Object list in obj/
OBJS := $(addprefix $(OUTPUTDIR)/,$(SOURCES:.c=.o))

# Default target
all: $(OUTPUTDIR) $(PROG)

# Link step
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Compile step (pattern rule)
$(OUTPUTDIR)/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure obj folder exists
$(OUTPUTDIR):
	@mkdir -p "$(OUTPUTDIR)"

# Cross-shell clean (works in Git Bash)
clean:
	@rm -rf "$(OUTPUTDIR)"
	@rm -f "$(PROG)"

.PHONY: all clean
