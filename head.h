struct FreeObjects
{
	ggc_size_t size;
	struct FreeObjects *next;
}
extern struct FreeObjects *freeList;
	
