ggggc_poolList=NULL;
ggggc_curPool=NULL;
freeList=NULL;
void *ggggc_malloc(struct GGGGC_Descriptor *descriptor)
{
	GGGGC_Pool *pool;
	if(!ggggc_poolList)
	{
		pool=newPool(1);
		ggggc_poolList=gggggc_curPool=freePoolsHead=pool;
	}
	struct GGGGC_Header *obj_header=NULL;
	//First check if free space is avaialble in the pool
	if(pool->free - pool->end >= descriptor->size)
	{
		obj_header = (struct GGGGC_Header *) pool->free;
		pool->free = pool->free + descriptor->size;
	}
	else if(freeList)  //Implementing First Fit Criteria with splitting 
	{
		struct FreeObjects *start=freelist , *prev=free;
		while(start!=NULL)
		{
			if(start->size >= descriptor->size)
			{
				obj->header=(struct GGGGC_Header *) start
	GGGGC_Pool *currentPointer; 
	if(freePoolsHead->free + descriptor.size > freePoolsHead->end)
	{
		GGC_YIELD(); // do garbage collection
	}
	else
	{
		currentPointer=freePoolsHead->free; //allocating at the end of the available pool
		freePoolsHead->free+=descriptor.size;
	}
	return currentPointer;
}

		
	
	
