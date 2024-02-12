#include <center.h>

bool	err(char *msg, int exit_code);

bool	distributeobject(int type, char **props)
{
	if(type == UNKNOWN)
	{
		delprops(props);
		return (err("Unknown object type", 1));
	}
	if(type == SPHERE)
		objectadd((Object *)newSphere(type, props), (void **)&g_scene->objects);
	if(type == PLANE)
		objectadd((Object *)newPlane(type, props), (void **)&g_scene->objects);
	if(type == CAMERA)
		objectadd((Object *)newCamera(type, props), (void **)&g_scene->camera);
	if(type == POINT)
		objectadd((Object *)newlight(type, props), (void **)&g_scene->lights);
	if(type == AMBIENT)
		objectadd((Object *)newlight(type, props), (void **)&g_scene->am);
	if(type == CYLINDER)
		objectadd((Object *)newCylinder(type, props), (void **)&g_scene->objects);
	return (true);
}