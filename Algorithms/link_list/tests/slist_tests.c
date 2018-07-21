#include "minunit.h"
#include "../src/slist.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static Slist* list = NULL;

char* testData1 = "test1 data";
char* testData2 = "test2 data";
char* testData3 = "test3 data";

int compareDataFunctionCallback(void* data1, void* data2) {
    return strcmp((char*)data1, (char*)data2) == 0 ? 1 : 0;
}

void releaseDataFunctionCallback(void* data) {
    (void*)data;
}

char* testCreateList() {
    list = slistCreateNewSlist();
    mu_assert(list != NULL, "Failed to create list.");

    return NULL;
}

char* testSlistAppendAtFirst() {
    /* case: append at empty list */
    slistAppendAtFirst(list, testData2);
    mu_assert(slistGetFirstDataNode(list) == testData2, "Wrong first value.");
    mu_assert(slistGetLastDataNode(list) == testData2, "Wrong last value.");
    /* case: append at non-empty list */
    slistAppendAtFirst(list, testData1);
    mu_assert(slistGetFirstDataNode(list) == testData1, "Wrong first value.");

    mu_assert(slistGetSize(list) == 2, "Wrong list size.");

    return NULL;
}

char* testSlistAppendAtLast() {
    /* case: append at non-empty list */
    slistAppendAtLast(list, testData3);
    mu_assert(slistGetLastDataNode(list) == testData3, "Wrong last value.");

    return NULL;
}

char* testPickFirstNode() {
    SlistNode* pickNode = NULL;
    /* case: pick from list includes more than one node */
    pickNode = slistPickFirstNode(list);
    mu_assert(slistGetFirstDataNode(list) == testData2, "Wrong first value.");
    mu_assert(pickNode->dataOfNode == testData1, "Wrong value on pick first node.");

    return NULL;
}
char* testPickLastNode() {
    SlistNode* pickNode = NULL;
    /* case: pick from list includes more than one node */
    pickNode = slistPickLastNode(list);
    mu_assert(slistGetLastDataNode(list) == testData2, "Wrong last value.");
    mu_assert(pickNode->dataOfNode == testData3, "Wrong value on pick last node.");

    return NULL;
}

char* testSlistPickFirstNode_2() {
    SlistNode* pickNode = NULL;
    /* case: pick form one node - list */
    pickNode = slistPickFirstNode(list);
    mu_assert(slistGetSize(list) == 0, "Wrong size list.");
    mu_assert(pickNode->dataOfNode == testData2, "Wrong value on pick first node.");

    mu_assert(slistGetFirstDataNode(list) == NULL, "Wrong first value.");
    mu_assert(slistGetLastDataNode(list) == NULL, "Wrong last value.");

    return NULL;
}

char* testSlistAppendAtLast_2() {
    /* case: append at empty list */
    slistAppendAtLast(list, testData1);
    mu_assert(slistGetLastDataNode(list) == testData1, "Wrong last value.");
    mu_assert(slistGetFirstDataNode(list) == testData1, "Wrong first value.");

    return NULL;
}

char* testSlistPickLastNode_2() {
    SlistNode* pickNode = NULL;
    /* case: pick from one node - list */
    pickNode = slistPickLastNode(list);
    mu_assert(slistGetSize(list) == 0, "Wrong size list.");
    mu_assert(pickNode->dataOfNode == testData1, "Wrong value on pick last node.");

    return NULL;
}

char* testSlistFindNode() {
    SlistNode* findNode = NULL;
    slistAppendAtLast(list, testData1);
    slistAppendAtLast(list, testData2);
    slistAppendAtLast(list, testData3);
    char* referenceData = "test2 data";
    findNode = slistFindNode(list, referenceData, compareDataFunctionCallback);
    mu_assert(findNode->dataOfNode == testData2, "Wrong value on find node.");

    char* referenceData_2 = "test not data";
    findNode = slistFindNode(list, referenceData_2, compareDataFunctionCallback);
    mu_assert(findNode == NULL, "Wrong value on fine node.");

    char* referenceData_3 = "test3 data";
    findNode = slistFindNode(list, referenceData_3, compareDataFunctionCallback);
    mu_assert(findNode->dataOfNode == testData3, "Wrong value on find node.");

    return NULL;
}

char* testSlistFindAndPickNode() {
    SlistNode* findNode = NULL;

    char* referenceData = "test1 data";
    findNode = slistFindAndPickNode(list, referenceData, compareDataFunctionCallback);
    mu_assert(findNode->dataOfNode == testData1, "Wrong value on find node.");
    mu_assert(slistGetFirstDataNode(list) == testData2, "Wrong first value.");
    mu_assert(slistGetLastDataNode(list) == testData3, "Wrong last value.");

    char* referenceData_2 = "test2 data";
    findNode = slistFindAndPickNode(list, referenceData_2, compareDataFunctionCallback);
    mu_assert(findNode->dataOfNode == testData2, "Wrong value on find node.");
    mu_assert(slistGetFirstDataNode(list) == testData3, "Wrong first value.");
    mu_assert(slistGetLastDataNode(list) == testData3, "Wrong last value.");

    char* referenceData_3 = "test3 data";
    findNode = slistFindAndPickNode(list, referenceData_3, compareDataFunctionCallback);
    mu_assert(findNode->dataOfNode == testData3, "Wrong value on find node.");
    mu_assert(slistGetFirstDataNode(list) == NULL, "Wrong first value.");
    mu_assert(slistGetLastDataNode(list) == NULL, "Wrong last value.");
    mu_assert(slistGetSize(list) == 0, "Wrong value of size.");

    return NULL;
}

char* testRemoveAllNode() {
    slistAppendAtLast(list, testData1);
    slistAppendAtLast(list, testData2);
    slistAppendAtLast(list, testData3);

    slistRemoveAllNode(list, releaseDataFunctionCallback);
    mu_assert(slistGetFirstDataNode(list) == NULL, "Wrong first value.");
    mu_assert(slistGetLastDataNode(list) == NULL, "Wrong last value.");
    mu_assert(slistGetSize(list) == 0, "Wrong value of size.");

    return NULL;
}

char* all_tests() {
    mu_suite_start();
    mu_run_test(testCreateList);
    mu_run_test(testSlistAppendAtFirst);
    mu_run_test(testSlistAppendAtLast);
    mu_run_test(testPickFirstNode);
    mu_run_test(testPickLastNode);
    mu_run_test(testSlistPickFirstNode_2);
    mu_run_test(testSlistAppendAtLast_2);
    mu_run_test(testSlistPickLastNode_2);
    mu_run_test(testSlistFindNode);
    mu_run_test(testSlistFindAndPickNode);
    mu_run_test(testRemoveAllNode);

    return NULL;
}

RUN_TESTS(all_tests)
