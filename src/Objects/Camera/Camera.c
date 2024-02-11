#include <StandarLibrarys.h>

Object *newObject(size_t targetsize, tValues (*colision)(struct Object *, Ray));
void *object_error_handler(Object *obj, void **ptr, char *msg);
/*
	To calculate the:

	aspect = width / height -> just divide the width by the height
	height = tan(fov / 2 * M_PI / 180) -> fov is the field of view, it's the angle of the camera
	width = aspect * height -> the width is the aspect times the height to keep the aspect ratio
*/
Camera *newCamera(int type, char **props)
{
	Camera *c;

	c = (Camera *)newObject(sizeof(Camera), NULL);
	c->type = CAMERA;
	c->o = getVec4(props[1], true, INT16_MAX, -INT16_MAX);
	c->d = getVec4(props[2], true, 1, -1);
	c->theta = getVec4("0,0,0", true, 1, -1);
	c->fov = getFloat(props[3], true, (float []){180, 0}, 1);
	c->aspect = (double)g_scene->width / (double)g_scene->height;
	c->height = tan(c->fov / 2 * M_PI / 180);
	c->width = c->aspect * c->height;
	c->next = NULL;
	return (Camera *)object_error_handler((Object *)c, (void **)props, "-> Invalid Camera");
}
