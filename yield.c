int ggggc_yield()
{
    /* FILLME */
  	/*We'll will check how much space is available in curent pool, if its filled more than 3/4 , we'll call the Garbage Collector and 
  	  
  	*/
	ggc_size_t freeSpace,totalSpace;
	
	struct GGGGC_Pool  *pool=ggggc_curPool;
    if (pool==NULL) return;

    /* first figure out how much space was used */
    freeSpace = 0;
    freeSpace += pool->end - pool->start;
	
	totalSpace=pool->end-pool->start[0];
	totalSpace=GGGGC_WORDS_PER_POOL;
	ggc_size_t space=0, survivors=0, numPools=0;
    /* now decide if it's too much */
    if (freeSpace < ((3*totalSpace)/4))
    {
    	ggggc_collect();
    	

		pool=ggggc_poolList;

		/* first figure out how much space was used */
		
		while (pool!=NULL) 
		{
		    space += pool->end - pool->start;
		    survivors += pool->survivors;
		    pool->survivors = 0;
		    numPools++;
		    if(pool->next==NULL) break;
		    pool = pool->next;
		}
		
    	for(ggc_size_t i=0;i<2*numPools;i++)
    	{
    		pool->next=newPool(1);
    		pool->next->next=NULL;
    	}	
    		
   	}
	
    return 0;
}
