struct FreeObjects
{
	struct GGGGC_Header * freeObjHeader;
	struct FreeObjects *next;
}

struct MarkReferences {
	struct MarkReferences *next;

extern struct FreeObjects *freeList;
extern char *isFreeObject,*isNotFreeObject;
	
