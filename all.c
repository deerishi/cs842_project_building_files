ggggc_poolList=NULL;
ggggc_curPool=NULL;
freeList=NULL;freeList->next=NULL;
isFreeObject="Free",*isNotFreeObject="Not Free";
//  I am nullyfying the freepoolshead pointer
void *ggggc_malloc(struct GGGGC_Descriptor *descriptor)
{
	GGGGC_Pool *pool=ggggc_curPool;
	struct FreeObjects *start=freelist , *prev=start,*temp;
	if(!ggggc_poolList)
	{
		pool=newPool(1);
		ggggc_poolList=gggggc_curPool=pool;
		pool->next=gggggc_curPool->next=NULL;
	}

	struct GGGGC_Header *obj_header=NULL;
	//First check if free space is avaialble in the pool
method_1_ForAllocation:	

	if(pool->end - pool->free >= descriptor->size)
	{
		obj_header = (struct GGGGC_Header *) pool->free;
		pool->free = pool->free + descriptor->size;
		obj_header->descriptor__ptr=descriptor;
		obj_header->descriptor__ptr->user__ptr=isNotFreeObject;
	}
	else if(freeList)  //Implementing First Fit Criteria with splitting. Free objects also have an object header
	{
		
		while(start!=NULL)
		{
			if(start->freeObjHeader->descriptor__ptr->size >= descriptor->size)
			{
				obj->header=(struct GGGGC_Header *) start;
				obj_header->descriptor__ptr=descriptor;
				obj_header->descriptor__ptr->user__ptr=isNotFreeObject;
				temp=prev->next;
				prev->next=start+descriptor->size;
				prev->next->size=start->size-descriptor->size;
				prev->next->next=temp;
				break;
			}
			
			prev=start;
			start=start->next;
		}
	}
	if(start==NULL) // i.e. the free list got traversed fully and still no appropiate object was found , we will allocate a new pool.
	{
		pool=ggggc_curPool->next=newPool(1);
		if(!pool) GGC_YIELD();
		
		goto method_1_ForAllocation:	;
	}		
	return obj;
}

		
	
	
