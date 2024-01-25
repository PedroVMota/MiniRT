# CC			= 	cc -fsanitize=leak -g
CC			= 	cc -g -fsanitize=address
CFLAGS		=  	-Wall -Wextra -Werror 
RM			= 	/bin/rm -f
NAME		= 	MiniRT
INCLUDES	= 	-I include/ -I Libft/
SRCS		=   $(shell find src -name '*.c')
OBJS		= 	$(SRCS:.c=.o)

UNAME := $(shell uname)

# Regular text colors
BLK = \e[0;30m
RED = \e[0;31m
GRN = \e[0;32m
YEL = \e[0;33m
PUR = \033[0;35m

BLU = \e[0;34m
MAG = \e[0;35m
CYN = \e[0;36m
WHT = \e[0;37m

# Bold text colors
BBLK = \e[1;30m
BRED = \e[1;31m
BGRN = \e[1;32m
BYEL = \e[1;33m
BBLU = \e[1;34m
BMAG = \e[1;35m
BCYN = \e[1;36m
BWHT = \e[1;37m

# Underline text colors
UBLK = \e[4;30m
URED = \e[4;31m
UGRN = \e[4;32m
UYEL = \e[4;33m
UBLU = \e[4;34m
UMAG = \e[4;35m
UCYN = \e[4;36m
UWHT = \e[4;37m

# Regular background colors
BLKB = \e[40m
REDB = \e[41m
GRNB = \e[42m
YELB = \e[43m
BLUB = \e[44m
MAGB = \e[45m
CYNB = \e[46m
WHTB = \e[47m

# High intensity background colors
BLKHB = \e[0;100m
REDHB = \e[0;101m
GRNHB = \e[0;102m
YELHB = \e[0;103m
BLUHB = \e[0;104m
MAGHB = \e[0;105m
CYNHB = \e[0;106m
WHTHB = \e[0;107m

# High intensity text colors
HBLK = \e[0;90m
HRED = \e[0;91m
HGRN = \e[0;92m
HYEL = \e[0;93m
HBLU = \e[0;94m
HMAG = \e[0;95m
HCYN = \e[0;96m
HWHT = \e[0;97m

# Bold high intensity text colors
BHBLK = \e[1;90m
BHRED = \e[1;91m
BHGRN = \e[1;92m
BHYEL = \e[1;93m
BHBLU = \e[1;94m
BHMAG = \e[1;95m
BHCYN = \e[1;96m
BHWHT = \e[1;97m

# Reset color
RESET = \e[0m
CRESET = \e[0m
COLOR_RESET = \e[0m


ifeq ($(UNAME), Darwin)
	MLX_LIB_DIR = minilbx_opengl/
	MLX_INCLUDE = -Iminilbx_opengl
	MLX_FLAGS = -L$(MLX_LIB_DIR) -lmlx -framework OpenGL -framework AppKit
else
	MLX_LIB_DIR = mlx_linux/
	MLX_INCLUDE = -Imlx_linux
	MLX_FLAGS = -L$(MLX_LIB_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
endif


TOTAL_FILES := $(words $(SRCS)) * 10
COMPILED_FILES := 0


all: $(NAME)

$(NAME):  $(OBJS)
	@make -C ./Libft/utils/ --no-print
	@$(CC) $(CFLAGS) $(^) ./Libft/utils/libft.a  minilbx_opengl/libmlx.a $(MLX_FLAGS) -o $(@)

%.o: %.c
	clear
	@printf "[$(PUR)$(NAME)$(RESET)] Compiling... $@\n"
	@$(CC) $(CFLAGS) $(INCLUDES) $(MLX_INCLUDE) -c $(^) -o $(@)

bonus: all

clean:
	@$(RM) $(OBJS)

fclean: clean
	@printf "[$(PUR)$(NAME)$(RESET)] Removing Everything\n"
	@$(RM) $(NAME)
	@make fclean -C ./Libft/utils --no-print

upload: $(msg)
	@read -p "Enter commit message: " msg; \
	git add .; \
	git commit -m "$$msg"; \
	git push --force;

re: fclean all