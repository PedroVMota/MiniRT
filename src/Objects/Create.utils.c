#include <center.h>


void *object_error_handler(Object *obj, void **ptr, char *msg) {

	delprops((char **) ptr);
	if (g_scene->error) {
		printf("Deleting content!\n");
		if (msg)
			printf("%s%s%s\n", RED, msg, RESET);
		free(obj);
		return NULL;
	}
	return (void *) obj;
}