#include <StandarLibrarys.h>

void lights(Light *l, Light **lst)
{
    Light *head;

    head = *lst;
    if(!*lst) {
        *lst = l;
        return;
    }
    while(*lst && (*lst)->next)
        (*lst) = (*lst)->next;
    (*lst)->next = l;
    *lst = head;
}

void objects(Object *l, Object **lst)
{
	Object *head;

	head = *lst;
	if(!*lst) {
		*lst = l;
		return;
	}
	while((*lst)->next)
		(*lst) = (Object *)(*lst)->next;
	(*lst)->next = l;
	*lst = head;
}
void camera(Camera *l, Camera **lst)
{
	Camera *head;

	head = *lst;
	if(!*lst) {
		*lst = l;
		return;
	}
	while((*lst)->next)
		(*lst) = (Camera *)(*lst)->next;
	(*lst)->next = l;
	*lst = head;
}


void	objectadd(Object *nObj, void **list)
{
	printf("Adding object\n");
	printf("Object type: %d\n", nObj->type);
	if(nObj->type == POINT || nObj->type == AMBIENT)
		lights((Light *)nObj, (Light **)list);
	else if(nObj->type == CAMERA)
		camera((Camera *)nObj, (Camera **)list);
	else if(nObj->type == SPHERE || nObj->type == PLANE || \
	nObj->type == CYLINDER || nObj->type == PYRAMID)
		objects(nObj, (Object **)list);
}
