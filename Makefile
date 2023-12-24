CC = @cc
CFLAGS = -Wall -Wextra -Werror -g
SRC_DIR = src
HEADER_DIR = headers
OBJ_DIR = obj
LIB_DIR = lib
MLX_DIR = mlx

SRC_FILES = src/Parse/boolf/.utilsf.c src/Parse/errorf/errorf.c src/Parse/Memory/delete.c src/Parse/Memory/List.c \
			src/Parse/Functions/model.initialize.c src/Parse/Functions/Model.c src/Parse/Functions/Model.u.c src/Parse/Functions/Vector.c \
			src/Parse/FileParsing/utils.c src/Parse/FileParsing/init.c src/Parse/FileParsing/utils.f.c src/main.c 
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

TARGET = miniRT

YEL = \e[0;33m
GRN = \e[0;32m
RESET = \e[0m

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@make -C Libft/utils/ --no-print
	$(CC) -g  $(CFLAGS) -Iheaders/ -ILibft/  $^ -L Libft/utils/ -lft -L minilibx-linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -o $(TARGET)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@printf "$(YEL)$@$(RESET)\n"
	$(CC) $(CFLAGS) -Iheaders/ -ILibft/ -g  -Iminilibx-linux -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

r:
	./ShellScripts/launch.sh

l:
	valgrind --log-file=valgrind_logs/valgrind.log.out --leak-check=full --show-leak-kinds=all --log-file=valgrind.log.out ./miniRT scene.rt

watch:
	@printf "Watching files..\n"
	@while true; do $(MAKE) -q --no-print-directory || $(MAKE) --no-print-directory; sleep 0.1; done;



fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
