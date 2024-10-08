# Directories
SRC_DIR        := src
INC_DIR        := include
LIBFT_DIR      := libft
LIBFT_INC_DIR  := $(LIBFT_DIR)/include

# Source files
SRC_FILES      := main.c push_swap_ops.c rotate_ops.c reverse_rotate_ops.c \
                  sort_stacks.c process_input.c debug.c

# Header files
INC_FILES      := push_swap.h debug.h

# Sources list
SRCS           := $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# Includes list
INCS           := $(addprefix $(INC_DIR)/, $(INC_FILES))

# Objects and dependencies
OBJS           := $(SRCS:.c=.o)
DEPS           := $(OBJS:.o=.d)

# Library targets
LIBFT          := $(LIBFT_DIR)/libft.a

# Build configuration
NAME           := push_swap
CC             := cc
CFLAGS         := -Wall -Wextra
CFLAGS         += -MMD -g3 -fsanitize=address,undefined
CFLAGS         += -I$(INC_DIR) -I$(LIBFT_INC_DIR)
LDFLAGS        := -L$(LIBFT_DIR)
LDLIBS         := -lft

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

norm:
	-norminette $(SRCS) $(INCS)

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all norm clean fclean re
