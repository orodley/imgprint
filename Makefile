CC     = gcc
LD     = $(CC)
CFLAGS = -std=c99 -Wall -Wextra -Werror
OBJS   = $(patsubst %.c, %.o, $(wildcard src/*.c))
NAME   = imgprint

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(LD) $^ -o $@

.PHONY: clean
clean:
	rm -f src/*.o
	rm -f $(NAME)
