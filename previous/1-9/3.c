// 输⼊若⼲个整数（以 0 结束）如何逆序构建双向链表

// 头插法 --> 逆序

#include <stdio.h>
#include <stdlib.h>

typedef struct DoubleLinkedList {
  int data;
  struct DoubleLinkedList* prev;
  struct DoubleLinkedList* next;
} DoubleLinkedList;

int main() {
  DoubleLinkedList* head = NULL;  // 链表头指针初始化
  int num;

  // 输入数字直到遇到0
  printf("Please input any integer (use 0 to end):\n");
  while (1) {
    scanf("%d", &num);
    if (num == 0) break;

    // 创建新节点
    DoubleLinkedList* newNode =
        (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
    newNode->data = num;
    newNode->prev = NULL;
    newNode->next = head;  // 新节点指向原头节点

    // 如果链表非空则设置原头节点的前驱
    if (head != NULL) {
      head->prev = newNode;
    }

    head = newNode;  // 更新头指针为新节点
  }

  // 遍历验证结果（正向输出）
  printf("Reverse result: ");
  DoubleLinkedList* current = head;
  while (current != NULL) {
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");

  // 释放内存（逆向释放更方便）
  current = head;
  while (current != NULL) {
    DoubleLinkedList* temp = current;
    current = current->next;
    free(temp);
  }

  return 0;
}
