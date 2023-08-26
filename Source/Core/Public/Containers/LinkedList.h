#pragma once

/*
* 단순히 링크 및 언링크만 함
* => 해제는 하지 않음
*/

#ifdef LINKED_LIST_EXPORTS
#define LINKED_LIST_API __declspec(dllexport)
#else
#define LINKED_LIST_API __declspec(dllimport)
#endif
namespace yebuk
{
namespace core
{
namespace containers
{
struct LinkedListNode
{
    void* Element;
    struct LinkedListNode* Next;
    struct LinkedListNode* Prev;
};

extern "C" LINKED_LIST_API void AddHeadLinkedList(LinkedListNode * *pHead, LinkedListNode * *pTail, LinkedListNode * newNode);
extern "C" LINKED_LIST_API void AddTailLinkedList(LinkedListNode** pHead, LinkedListNode** pTail, LinkedListNode* newNode);
extern "C" LINKED_LIST_API void DeleteHeadLinkedList(LinkedListNode** pHead, LinkedListNode** pTail);
extern "C" LINKED_LIST_API void DeleteTailLinkedList(LinkedListNode** pHead, LinkedListNode** pTail);
extern "C" LINKED_LIST_API void InsertNodeLinkedList(LinkedListNode** pHead, LinkedListNode** pTail, LinkedListNode* prevNode, LinkedListNode* newNode);
extern "C" LINKED_LIST_API void DeleteNodeLinkedList(LinkedListNode** pHead, LinkedListNode** pTail, LinkedListNode* delNode);
}
}
}