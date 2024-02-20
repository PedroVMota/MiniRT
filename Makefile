# CC			= 	cc -fsanitize=leak -g
CC			= 	cc  -g -O3 -O1 -O2 -march=native -ffast-math -funsafe-math-optimizations -ffinite-math-only  #-fsanitize=address
CFLAGS		=  	-pthread -Wall -Wextra -Werror 
RM			= 	/bin/rm -f
NAME		= 	miniRT
INCLUDES	= 	-I include/ -I Libft/
SRCS		=   src/Initializers/utils.1.c src/MathFunctions/Operators.c src/MathFunctions/Operators2.c src/MathFunctions/Operators3.c \
				src/MathFunctions/utils.1.c src/mlx/hooks.c src/mlx/utils.c src/.utils.1.c \
				src/GetFunctions/Float.c src/GetFunctions/Vec3.c src/GetFunctions/utils.c src/GetFunctions/Integer.c \
				src/Objects/Camera/Camera.c src/Objects/CreateObject.c src/Objects/Cylinder/Cylinder.c src/Objects/Cylinder/CylinderColision.c \
				src/Objects/Cylinder/cylinderUtils1.c src/Objects/Cylinder/cylinderUtils2.c src/Objects/Light/Lights.c src/Objects/Paraboloid/Paraboloid.c \
				src/Objects/Paraboloid/ParaboloidColision.c src/Objects/Paraboloid/paraboloidUtils.c src/Objects/Plane/Plane.c src/Objects/Plane/PlaneColision.c \
				src/Objects/Sphere/Sphere.c src/Objects/Sphere/SphereColision.c src/ParseFunctions/Parse.utils.c src/ParseFunctions/generate.c \
				src/ParseFunctions/parse.c src/Render/CameraRotation.c src/Render/ComputeLight.c src/Render/RayColor.c \
				src/Render/Render.c src/Render/theta.c src/Render/utils.1.c src/Render/utils.c \
				src/Selection/Select.c src/TextureRender/utils.c src/main.c src/normalcalc.c \
				src/rotation.c
OBJS		= 	$(SRCS:.c=.o)
# Regular text colors
PUR = \033[0;35m
RESET = \e[0m
MLX_LIB_DIR = mlx_linux/
MLX_INCLUDE = -Imlx_linux
MLX_FLAGS = -L$(MLX_LIB_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz




TOTAL_FILES := $(words $(SRCS)) * 10
COMPILED_FILES := 0


all: $(NAME)

$(NAME):  $(OBJS)
	@make -C ./Libft/utils/ --no-print
	@$(CC)  $(CFLAGS) $(^) ./Libft/utils/libft.a  ./mlx_linux/libmlx_Linux.a $(MLX_FLAGS) -o $(@)

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


re: fclean all