
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slist.h"
#include "dbg.h"


void *slistAppendAtLast(Slist *list, void *data)
{
    check_mem(list);
    SlistNode* newSlistNode = (SlistNode*) calloc(1, sizeof(SlistNode));
    check_mem(newSlistNode);
    newSlistNode->dataOfNode = data;
    newSlistNode->nextNode = NULL;

    if(list->firstNode == NULL && list->lastNode == NULL) {
        list->firstNode = list->lastNode = newSlistNode;
        list->numOfSlistNode = 1;
    }
    else {
        list->lastNode->nextNode = newSlistNode;
        list->lastNode = newSlistNode;
        list->numOfSlistNode++;
    }

error:
    return NULL;
}

void *slistAppendAtFirst(Slist *list, void *data)
{
    check_mem(list);
    SlistNode* newSlistNode = (SlistNode*) calloc(1, sizeof(SlistNode));
    check_mem(newSlistNode);
    newSlistNode->dataOfNode = data;
    if(list->firstNode == NULL && list->lastNode == NULL) {
        list->firstNode = list->lastNode = newSlistNode;
        list->numOfSlistNode = 1;
    }
    else {
        newSlistNode->nextNode = list->firstNode;
        list->firstNode = newSlistNode;
        list->numOfSlistNode++;
    }

error:
    return NULL;
}

void *slistRemoveAllNode(Slist *list, releaseDataFunction releaseDataCallback)
{
    check_mem(list);
    check(releaseDataCallback != NULL, "Callback function should not be NULL.");
    SlistNode* currentNode;
    currentNode = list->firstNode;
    SlistNode* nodeToRemove = NULL;
    while(currentNode != NULL) {
        nodeToRemove = currentNode;
        currentNode = currentNode->nextNode;
        releaseDataCallback(nodeToRemove->dataOfNode);
        free(nodeToRemove);
        list->numOfSlistNode--;
    }
    list->firstNode = list->lastNode = NULL;

error:
    return NULL;
}

void *slistConcat(Slist *list, Slist *addList)
{
    check_mem(list);
    check_mem(addList);

    list->lastNode->nextNode = addList->firstNode;
    list->numOfSlistNode += addList->numOfSlistNode;

error:
    return NULL;
}

void *slistInsertAfterNode(Slist *list, void *insertData, void *referenceData, compareDataFunction compareDataCallback)
{
    check_mem(list);
    check(compareDataCallback != NULL, "Callback function should not be NULL.");
    SlistNode* currentNode;
    currentNode = list->firstNode;
    SlistNode* nodeInsertAfterIt = NULL;
    while(currentNode != NULL) {
        if(compareDataCallback(referenceData, nodeInsertAfterIt->dataOfNode)) {
            nodeInsertAfterIt = currentNode;
            break;
        }
    }
    check(nodeInsertAfterIt != NULL, "Could not find data.");
    SlistNode* nodeToInsert = (SlistNode*) calloc(1, sizeof(SlistNode));
    check_mem(nodeToInsert);
    nodeToInsert->dataOfNode = insertData;
    if(nodeInsertAfterIt == list->lastNode) {
        nodeToInsert->nextNode = NULL;
        list->lastNode->nextNode = nodeToInsert;
        list->lastNode = nodeToInsert;
    }
    else {
        nodeToInsert->nextNode = nodeInsertAfterIt->nextNode->nextNode;
        nodeInsertAfterIt->nextNode = nodeToInsert;
    }
    list->numOfSlistNode++;

error:
    return NULL;
}

SlistNode *slistFindNode(Slist *list, void *referenceData, compareDataFunction compareDataCallback)
{
   check_mem(list);
   check(compareDataCallback != NULL, "Callback function should not be NULL.");
   SlistNode* currentNode;
   currentNode = list->firstNode;
   SlistNode* foundNode = NULL;
   while(currentNode != NULL) {
       if(compareDataCallback(referenceData, currentNode->dataOfNode)) {
           foundNode = currentNode;
           return foundNode;
       }
       currentNode = currentNode->nextNode;
   }
   check(foundNode != NULL, "Could not find data.");
error:
   return NULL;
}

void* slistTraceDataList(Slist *list, void *referenceData, traceFunction traceDataCallback)
{
    check_mem(list);
    check(traceDataCallback != NULL, "Callback function should not be NULL.");
    int i = 0;
    SlistNode* currentNode;
    currentNode = list->firstNode;
    while(i < list->numOfSlistNode) {
        traceDataCallback(i, referenceData, currentNode->dataOfNode);
        i--;
    }
error:
    return NULL;
}

void *slistRemoveNode(Slist *list, SlistNode *nodeToRemove, releaseDataFunction releaseDataCallback)
{
    check_mem(list);
    check(releaseDataCallback != NULL, "Callback function should not be NULL.");
    check(nodeToRemove != NULL, "Node to remove should not be NULL.");
    SlistNode* currentNode;
    currentNode = list->firstNode;
    SlistNode* previousCurrentNode = NULL;
    while(currentNode != NULL) {
        if(currentNode == nodeToRemove) {
            if(nodeToRemove == list->firstNode){
                list->firstNode = nodeToRemove->nextNode;
            }
            else if (nodeToRemove == list->lastNode) {
                previousCurrentNode->nextNode = NULL;
                list->lastNode = previousCurrentNode;
            }
            else {
                previousCurrentNode->nextNode = nodeToRemove->nextNode;
            }
            releaseDataCallback(nodeToRemove->dataOfNode);
            free(nodeToRemove);
            list->numOfSlistNode--;
            if(list->numOfSlistNode == 0) {
                list->firstNode = list->lastNode = NULL;
            }
            break;
        }
        previousCurrentNode = currentNode;
        currentNode = currentNode->nextNode;
    }

error:
    return NULL;
}

SlistNode *slistFindAndPickNode(Slist *list, void *referenceData, compareDataFunction compareDataCallback)
{
    check_mem(list);
    check(compareDataCallback != NULL, "Callback function should not be NULL.");
    SlistNode* currentNode;
    currentNode = list->firstNode;
    SlistNode* previousCurrentNode = NULL;
    SlistNode* nodeToPick = NULL;
    while(currentNode != NULL) {
        if(compareDataCallback(referenceData, currentNode->dataOfNode)) {
            nodeToPick = currentNode;
            if(nodeToPick == list->firstNode) {
                list->firstNode = nodeToPick->nextNode;
            }
            else if(nodeToPick == list->lastNode) {
                previousCurrentNode->nextNode = NULL;
                list->lastNode = previousCurrentNode;
            }
            else {
                previousCurrentNode->nextNode = currentNode->nextNode;
            }
            list->numOfSlistNode--;
            if(list->numOfSlistNode == 0) {
                list->firstNode = list->lastNode = NULL;
            }
            return nodeToPick;
        }
    }
error:
    return NULL;
}


SlistNode *slistPickNodeByIndex(Slist *list, int index)
{
    check_mem(list);
    check(index < slistGetSize(list), "Index exceeds size of list.");
    int i = 0;
    SlistNode* currentNode;
    currentNode = list->firstNode;
    SlistNode* previousCurrentNode = NULL;
    SlistNode* nodeToPick = NULL;
    while(i <= index) {
        if(i == index) {
            nodeToPick = currentNode;
            if(i == 0) {
                list->firstNode = nodeToPick->nextNode;
            }
            else if(i == slistGetSize(list)-1) {
                previousCurrentNode->nextNode = NULL;
                list->lastNode = previousCurrentNode;
            }
            else {
                previousCurrentNode->nextNode = nodeToPick->nextNode;
            }
            list->numOfSlistNode--;
            if(list->numOfSlistNode == 0) {
                list->firstNode = list->lastNode = NULL;
            }
            return nodeToPick;
        }
        i++;
        previousCurrentNode = currentNode;
        currentNode = currentNode->nextNode;
    }
error:
    return NULL;
}

Slist *slistCreateNewSlist()
{
    return (Slist*) calloc(1, sizeof(Slist));
}

void *slistDeleteSlist(Slist *list, releaseDataFunction releaseDataCallback)
{
    check_mem(list);
    slistRemoveAllNode(list, releaseDataCallback);
    free(list);

 error:
    return NULL;
}
