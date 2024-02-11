# CC			= 	cc -fsanitize=leak -g
CC			= 	cc -O3 -g -fsanitize=address
CFLAGS		=  	#-Wall -Wextra -Werror
RM			= 	/bin/rm -f
NAME		= 	a
INCLUDES	= 	-I include/ -I Libft/
SRCS		=   src/ReflectionsAndLights/utils.1.c src/ReflectionsAndLights/init.c src/ReflectionsAndLights/utils.c src/mlx/utils.c \
src/mlxfunc/utils.1.c src/MathFunctions/utils.1.c src/normalcalc.c src/Show.c \
src/.utils.1.c src/main.c src/Objects/Camera/Camera.c src/Objects/Lights/Lights.c \
src/Objects/Body/cylinderColision3.c src/Objects/Body/cylinderColision2.c src/Objects/Body/Body.c src/Objects/Body/Colisions.c \
src/Objects/Body/cylinderColision.c src/Objects/List/ObjectAdd.c src/ParseFunctions/generate.c src/ParseFunctions/parse.c \
src/Vector/Operators.c src/Vector/Operators3.c src/Vector/Operators2.c src/TextureRender/utils.c \
src/GetFunctions/Vec3.c src/GetFunctions/Float.c src/GetFunctions/utils.c
				
OBJS		= 	$(SRCS:.c=.o)

UNAME := $(shell uname)

# Regular text colors
BLK = \e[0;30m
RED = \e[0;31m
GRN = \e[0;32m
YEL = \e[0;33m
PUR = \033[0;35m

# Reset color
RESET = \e[0m


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