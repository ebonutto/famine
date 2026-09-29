NAME := famine

SRC_DIR := src
INC_DIR := include
BUILD_DIR := .build

CC := cc
CFLAGS := -Wall -Wextra -Werror
CPPFLAGS := -I$(INC_DIR) -MMD -MP

SRCS := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

WOODY_DIR := woody-woodpacker
WOODY_REPO := https://github.com/ebonutto/woody_woodpacker.git
WOODY_BIN := $(WOODY_DIR)/woody_woodpacker

.PHONY: all woody clean fclean rclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

woody: $(NAME) $(WOODY_BIN)
	$(WOODY_BIN) $(NAME)

$(WOODY_BIN): $(WOODY_DIR)
	$(MAKE) -C $(WOODY_DIR) --no-print-directory

$(WOODY_DIR):
	git clone $(WOODY_REPO) $(WOODY_DIR)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME) ./woody

rclean:
	rm -rf $(WOODY_DIR)

re: fclean all

-include $(DEPS)
