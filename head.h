struct FreeObjects
{
	struct FreeObjects *next;
}

struct MarkReferences {
	struct MarkReferences *next;

extern struct FreeObjects *freeList;
extern char *isFreeObject,*isNotFreeObject;
	
