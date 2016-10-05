
void deleteConnection(nd* node1,nd* node2){
	adjNode* list1 = node1->adjHead;
	adjNode* list2 = node2->adjHead;
	int id1=node1->id;
	int id2=node2->id;

	if(list1!=NULL){//required
		adjNode* list1Next=list1->next;
		if(list1->id==id2){//first element
	    	node1->adjHead=list1Next;//    free(list1);
	    }
	    while(list1Next!=NULL){
	    	if(list1Next->id == id2){
		    	list1->next=list1Next->next; //remove the middle node.//    free(list1Next);
		    }
		    list1=list1->next;
		    list1Next=list1Next->next;
		}
	}
	if(list2!=NULL){//required
		adjNode* list2Next=list2->next;
		if(list2->id==id1){//first element
    		node2->adjHead=list2Next;//    free(list2);
    	}
    	while(list2Next!=NULL){
    		if(list2Next->id == id1){
	    	list2->next=list2Next->next; //remove the middle node.//    free(list2Next);
	    }
	    list2=list2->next;
	    list2Next=list2Next->next;
	}
}
}


void DFS_visit2(nd * curr_node,nd * nodeArray[]){
	curr_node->visit++; //makes gray
	give(curr_node->id);gives(" ");
	adjNode * head = curr_node->adjHead;//head points to current node's adj list
	//go thru the adjList of current node
	while(head!=NULL){
		nd * near_node = nodeArray[head->id-1];
		if(near_node->visit==0){//White
			deleteConnection(near_node,curr_node);
			DFS_visit2(near_node,nodeArray);
		}
		head=head->next;
	}
	//at this point all neighbours are explored.
	curr_node->visit++;
}
