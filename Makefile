NAME := famine

SRC_DIR := src
INC_DIR := include
BUILD_DIR := .build

CC := cc
CFLAGS := -Wall -Wextra -Werror
CPPFLAGS := -I$(INC_DIR) -MMD -MP
LDLIBS := $(addprefix -l, c)

SRCS := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@ $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME) ./woody

re: fclean all

-include $(DEPS)
