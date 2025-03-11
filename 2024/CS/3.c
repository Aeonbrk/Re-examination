/**
 * 写一个函数，把一个不带头结点的单链表使用冒泡排序（升序）
 */

#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
typedef struct LinkedList {
  int data;                 // 节点数据
  struct LinkedList* next;  // 指向下一个节点的指针
} LinkedList;

// 冒泡排序函数
void BubbleSort(LinkedList* L) {
  if (L == NULL || L->next == NULL) {
    return;  // 如果链表为空或只有一个节点，直接返回
  }

  LinkedList* move = L;           // 用于遍历链表的指针
  LinkedList* lastSorted = NULL;  // 指向已排序部分的最后一个节点
  int isSorted;                   // 标记是否已经排序完成

  // 至少走一遍看看是不是已经有序了
  // 所以使用 do-while
  do {
    isSorted = 1;  // 假设链表已经有序
    move = L;      // 从头节点开始遍历

    // 遍历链表，比较相邻节点的值并交换
    while (move->next != lastSorted) {
      if (move->data > move->next->data) {
        // 交换相邻节点的数据
        int tmp = move->data;
        move->data = move->next->data;
        move->next->data = tmp;
        isSorted = 0;  // 发生了交换，说明链表未完全有序
      }
      move = move->next;  // 移动到下一个节点
    }
    lastSorted = move;  // 更新已排序部分的最后一个节点
  } while (isSorted == 0);  // 如果链表未完全有序，继续排序
}

// 打印链表
void PrintList(LinkedList* L) {
  LinkedList* tmp = L;
  while (tmp != NULL) {
    printf("%d ", tmp->data);  // 打印当前节点的数据
    tmp = tmp->next;           // 移动到下一个节点
  }
  printf("\n");
}

// 创建新节点
LinkedList* CreateNode(int data) {
  LinkedList* newNode = (LinkedList*)malloc(sizeof(LinkedList));
  newNode->data = data;  // 设置节点数据
  newNode->next = NULL;  // 初始化下一个节点指针为NULL
  return newNode;
}

// 释放链表内存
void FreeList(LinkedList* L) {
  LinkedList* tmp;
  while (L != NULL) {
    tmp = L;      // 保存当前节点
    L = L->next;  // 移动到下一个节点
    free(tmp);    // 释放当前节点的内存
  }
}

int main() {
  // 创建链表
  LinkedList* list = CreateNode(5);
  list->next = CreateNode(3);
  list->next->next = CreateNode(8);
  list->next->next->next = CreateNode(1);
  list->next->next->next->next = CreateNode(6);

  printf("The original LinkedList without head is: ");
  PrintList(list);

  // 冒泡排序
  BubbleSort(list);

  printf("The sorted LinkedList is: ");
  PrintList(list);

  // 释放链表内存
  FreeList(list);

  return 0;
}
