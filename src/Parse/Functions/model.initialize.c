#include <center.h>

t_object *errhandler(t_object **obj);
bool		isallnum(char *str, int error);
void split_remove_element(char **arr, int index);

t_object    *camera_initilize(t_camera **obj, char **objd)
{
    if(!scene()->error && !objd[1])
		scene()->error = 6;
	else if(!scene()->error)
		(*obj)->vector = vector_generator(objd[1]);
	split_remove_element(objd, 1);
	if(!scene()->error &&!objd[1])
		scene()->error = 6;
	else if(!scene()->error)
		(*obj)->direction = vector_generator(objd[1]);
	split_remove_element(objd, 1);
	if(!scene()->error && !objd[1])
		scene()->error = 5;
	if (!isallnum(objd[1], 5))
		scene()->error = 3;
	else if(!scene()->error)
		(*obj)->fov = atof(objd[1]);
	(*obj)->phi = 0.0f;
	(*obj)->theta = 0.0f;
	(*obj)->qsi = 0.0f;
	return errhandler((t_object **)obj);
}
