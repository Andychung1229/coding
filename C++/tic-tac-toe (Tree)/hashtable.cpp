#include "hashtable.h"
BoardOptimalMove BoardHashTable::getHashedMove(const unsigned long long id, const int depth){
    unsigned long long index= id%TABLE_SIZE;
    if(table[index]==nullptr){
        return BoardOptimalMove();
    }
    else{
        BoardHashNode* temp=table[index];
        for(;temp!=nullptr;temp=temp->next){
            if(temp->id==id&&temp->depth>=depth&&depth>=1){
                return temp->optimalMove;
            }
        }
    }
    return BoardOptimalMove();
}

void BoardHashTable::updateTable(const unsigned long long id, const int depth, const BoardOptimalMove &optimalMove){
    unsigned long long index=id%TABLE_SIZE;
    if(table[index]==nullptr){
        table[index]=new BoardHashNode(id,depth,optimalMove); 
        return; 
    }
    else{
        BoardHashNode* temp=table[index];
        for(;temp!=nullptr;temp=temp->next){
            if(temp->id==id){
                if(temp->depth<depth){
                    temp->depth=depth;
                    temp->optimalMove=optimalMove;
                    }
                else{
                    return;

                }
            }    
        }
        temp=new BoardHashNode(id,depth,optimalMove);
        return;
    }
}
void BoardHashTable::clearTable(){
    for( int i=0;i<TABLE_SIZE;i++){
        if(table[i]==nullptr){
            continue;
        }else{
            BoardHashNode* cur=table[i];
            while(cur!=nullptr){
                BoardHashNode* next=cur->next;
                delete cur;
                cur=next;
            }
            table[i]=nullptr;
        }
    }
}

