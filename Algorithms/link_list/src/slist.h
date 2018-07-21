/*
 * slist.h
 *
 *  Created on: 25-06-2017
 *      Author: shymaxtic
 */

#ifndef SLIST_H_
#define SLIST_H_

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief	Data structure for single link list
 */

typedef struct SlistNode{
        void * dataOfNode;                        /**< the pointer to data */
        struct SlistNode * nextNode;            /**< the pointer to next element of list */
}SlistNode;

typedef struct Slist {
    SlistNode* firstNode;
    SlistNode* lastNode;
    int numOfSlistNode;
}Slist;

#define slistGetSize(A)   ((A)->numOfSlistNode)
#define slistGetFirstDataNode(A)   ((A)->firstNode != NULL ? (A)->firstNode->dataOfNode : NULL)
#define slistGetLastDataNode(A)    ((A)->lastNode != NULL ? (A)->lastNode->dataOfNode : NULL)
#define slistPickLastNode(A)        (slistPickNodeByIndex((A), slistGetSize((A)) - 1))
#define slistPickFirstNode(A)       (slistPickNodeByIndex((A), 0))

typedef void (*releaseDataFunction)(void* data);
typedef int (*compareDataFunction)(void* data1, void* data2);
typedef void (*traceFunction)(int index, void* referenceData, void* data);

extern Slist * slistCreateNewSlist();

extern void * slistDeleteSlist(Slist* list, releaseDataFunction releaseDataCallback);

extern void * slistAppendAtLast(Slist* list, void * data);

extern void * slistAppendAtFirst(Slist* list, void* data);

extern void * slistRemoveNode(Slist* list, SlistNode* nodeToRemove, releaseDataFunction releaseDataCallback);

extern void * slistRemoveAllNode(Slist * list, releaseDataFunction releaseDataCallback);

extern void * slistConcat(Slist * list, Slist * addList);

extern void * slistInsertAfterNode(Slist * list,void * insertData,void * referenceData, compareDataFunction compareDataCallback);

extern SlistNode * slistFindNode(Slist * list, void * referenceData, compareDataFunction compareDataCallback);

extern SlistNode* slistFindAndPickNode(Slist* list, void* referenceData, compareDataFunction compareDataCallback);

extern void* slistTraceDataList(Slist *list, void * referenceData, traceFunction traceDataCallback);

extern SlistNode* slistPickNodeByIndex(Slist* list, int index);


#ifdef __cplusplus
}//extern "C" {
#endif


#endif /* SLIST_H_ */
