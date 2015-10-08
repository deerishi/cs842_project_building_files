struct ObjectsForMark
{
	struct ObjectsForMark *next;
	}


#define MARK(obj) do { \
    struct GGGGC_Header *hobj = (obj); \
    hobj->descriptor__ptr = (struct GGGGC_Descriptor *) \
        ((ggc_size_t) hobj->descriptor__ptr | 2); \
} while (0)
	
void ggggc_collect()
{
	struct GGGGC_PointerStack *pointer_Cur;
	int i,j;
	for(pointerCur=ggggc_pointerStack;pointerCur!=NULL;pointerCur=pointerCur->next)
	{
		
