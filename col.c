struct ObjectsForMark
{
	struct ObjectsForMark *next;
	void **pointersFromObjects;
	ggc_size_t numPointers;
	}

static struct ObjectsForMark listForMarking;

#define MarkListBufferSize 1024
#define Mark(obj) do { \
    struct GGGGC_Header *hobj = (obj); \
    hobj->descriptor__ptr = (struct GGGGC_Descriptor *) \
        ((ggc_size_t) hobj->descriptor__ptr | 2); \
} while (0)

#define UnMark(obj) do { \
    struct GGGGC_Header *hobj = (obj); \
    hobj->descriptor__ptr = (struct GGGGC_Descriptor *) \
        ((ggc_size_t) hobj->descriptor__ptr & (ggc_size_t)~2); \
} while (0)

#define MarkListInit() do {\
\
	if(listForMarking->buf==NULL)\
	{\
		listForMarking->buf=(void **)malloc(MarkListBufferSize * sizeof(void *));\
		if(listForMarking->buf==NULL){\
			 perror("malloc"); \
            abort(); \
        } \
    } \
    markList = &listForMarking; \
    markList->numPointers = 0; \
}while (0)
	
//here we pass the pointers to the roots
#define AddToMarkList(ptr) do {\
\
	marklist->buf[markList->numPointers++]=ptr;\
}while (0)

#define MarklistPop(type,ptr) do{\
	ptr=(type)markList->buf[--markList->numPointers];\
	}while(0)
		
#define IsMarked(obj) ((ggc_size_t) obj->descriptor__ptr & (ggc_size_t) 2)


#define AddObjectPointers(obj,descriptor) do{\
	ggc_size_t size=descriptor->size;\
	if(!(descriptor->pointer[0] & 1))\
	{\
		break;\
	}\
	ggc_size_t pointerMap=descriptor->pointer[0];\
	void **objCopy=(void **)obj;\
	for(ggc_size_t i=0;i<size;i++)\
	{\
		if(pointerMap & 1)\
		{\
			AddToMarkList(&objCopy[i]);\
		}\
		pointerMap>>1;\
	}\
}
				
void ggggc_collect()
{
	struct GGGGC_PointerStack *pointer_Cur;
	int i,j;
	struct ObjectsForMark *markList;
	//Now all the roots are put on the stack
	for(pointerCur=ggggc_pointerStack;pointerCur!=NULL;pointerCur=pointerCur->next)
	{
		for(i=0;i<pointerCur->size;i++)
		{
			AddToMarkList(pointerCur->pointer[i]);
		}
	}
	//Now the Mark Phase begins
	struct GGGGC_Header *obj;
	while(markList->numPointers)
	{
		void **ptr;
		MarkListPop(void **,ptr);
		obj=(GGGGC_Header *)*ptr; //This has been done so that ob1 now points to the object itself
		
		if(obj==NULL) continue;
		//UnMark(obj); //	Incase it was left marked by mistake
		
		if(!IsMarked(obj))
		{
			//That is the object is not marked, then fist copy the reference to the descriptor so as to 			save the further pointers
			struct GGGC_Descriptor *correctDescriptorAddress=obj->descriptor_ptr;
			
			GGGGC_POOL_OF(obj)->survivors+=correctDescriptorAddress->size; //increment the number of survivros this collection 
			
			Mark(obj);
			//add the pointers to the list for marking;
			 AddObjectPointers(obj,correctDescriptorAddress);
		}
	}
	// now call the sweep code
	GGGGC_Pool *pool=ggggc_poolList,*sweep;
	struct GGGGC_Header *obj;
	struct FreeObjects *fobj1,*LastPointer;
	freeList=NULL;
	while(pool)
	{
		sweep=pool->start;
		while(sweep!=pool->end || sweep!=pool->free || sweep!=NULL)
		{
			obj=(struct GGGGC_Header *)sweep;
			if(IsMarked(obj))
			{
				Unmark(obj);
			}
			else
			{
				fobj1=(struct FreeObjects *)sweep;
				fobj1->next=NULL;
				if(freeList==NULL)
				{
					freeList=fobj1;
					LastPointer=fobj1;
				}
				else
				{
					LastPointer->next=fobj1; //appending to the freeList
				}
			}
			sweep+=sweep->size;
		}
		pool=pool->next;
	}
}
		
					
				
			
		
			
