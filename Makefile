CC = @cc
CFLAGS = -g #-Wall -Wextra -Werror -g
SRC_DIR = src
HEADER_DIR = headers
OBJ_DIR = obj
LIB_DIR = lib
MLX_DIR = mlx

SRC_FILES = src/main.c src/FileParsing/init.c src/FileParsing/utils.c
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

TARGET = miniRT

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@make -C Libft/utils/ --no-print
	$(CC) -g  $(CFLAGS) -Iheaders/ -ILibft/  $^ -L Libft/utils/ -lft -L minilibx-linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -o $(TARGET)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -Iheaders/ -ILibft/ -g  -Iminilibx-linux -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

r:
	make  && valgrind --leak-check=full --show-leak-kinds=all ./miniRT scene.rt

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
