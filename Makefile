CC = gcc
CFLAGS = -g #-Wall -Wextra -Werror -g
SRC_DIR = src
HEADER_DIR = headers
OBJ_DIR = obj
LIB_DIR = lib
MLX_DIR = mlx

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

TARGET = miniRT

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) -g -fsanitize=address $(CFLAGS) -Iheaders/ -ILibft/ $^ minilibx-linux/libmlx_Linux.a -L$(MLX_LIB_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -Iheaders/ -ILibft/ -g -fsanitize=address -Iminilibx-linux -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
