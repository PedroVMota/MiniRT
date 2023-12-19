#ifndef CENTER_H
# define CENTER_H

# define WIDTH 1000
# define HEIGHT 1000

# include <3DMath.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define RED "\033[0;31m"
# define GRN "\033[0;32m"
# define YEL "\033[0;33m"
# define BLU "\033[0;34m"
# define MAG "\033[0;35m"
# define CYN "\033[0;36m"
# define WHT "\033[0;37m"
# define RESET "\033[0m"

# define info(msg) printf("%s[%s]%s\n", MAG, msg, RESET)
# define war(msg) printf("%s[%s]%s\n", YEL, msg, RESET)
# define ok(msg) printf("%s[%s]%s\n", GRN, msg, RESET)
# define err(msg) printf("%s[%s]%s\n", RED, msg, RESET)


extern t_light	light;
extern t_sphere	sphere;
extern t_vector	rayOrigin;
extern t_vector	rayDirection;
#endif