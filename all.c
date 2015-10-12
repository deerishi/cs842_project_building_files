ggggc_poolList=NULL;
ggggc_curPool=NULL;
freeList=NULL;freeList->next=NULL;
isFreeObject="Free",*isNotFreeObject="Not Free";
//  I am nullyfying the freepoolshead pointer
void *ggggc_malloc(struct GGGGC_Descriptor *descriptor)
{
	//Change this for incrementing the pool list 
	struct FreeObjects *start=freelist , *prev=start,*temp;
	
	struct GGGGC_Pool  *pool;
    if(ggggc_poolList==NULL) // ALLOCATE 10 NEW POOLS IF NO POOL IS ALLOCATED YET
    {
    	pool=ggggc_poolList;
    	for(int i=0;i<10;i++)
    	{
    		pool=newPool(1);
    		pool->next=NULL;
    		pool->survivors = 0;
    		if(ggggc_poolList==NULL)
    		{
				ggggc_poolList=gggggc_curPool=pool;
			}
			pool=pool->next;
		}
	}
	
	struct GGGGC_Header *obj_header=NULL;
	//First check if free space is avaialble in the pool
method_1_ForAllocation:	
	//For the first method of allocation we will traverse all the pools to see if any space is available or not.
	pool=ggggc_curPool;
	while(pool!=NULL) 
	{
		if(pool->end - pool->free >= descriptor->size)
		{
			obj_header = (struct GGGGC_Header *) pool->free;
			pool->free = pool->free + descriptor->size;
			obj_header->descriptor__ptr=descriptor;
			//obj_header->descriptor__ptr->user__ptr=isNotFreeObject;
			return obj_header;
		}
		pool=pool->next;
	}
	else if(freeList)  //Implementing First Fit Criteria with splitting. Free objects also have an object header
	{
		
		while(start!=NULL)
		{
			if(start->descriptor__ptr->size >= descriptor->size)
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
	if(start==NULL) // i.e. the free list got traversed fully, and all pools were traversed , and still no appropiate object was found , we will allocate a new pool.
	{
		pool=newPool(1);
		pool->next=NULL;
		pool->survivors = 0;
		ggggc_curPool=pool;
		
		goto method_1_ForAllocation:	;
	}		
	return obj;
}

		
	
	
