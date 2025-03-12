/*
创建一个编号为1到10的链表。
给定m个数，每次将编号为x数的节点放在开头。
三个小孩玩游戏，玩m次，每次将数字为x的元素提升到队头。
要求创建队列，玩游戏，打印队列分别用函数实现。
示例：
  初始：1-2-3-4-5-6-7-8-9-10
  游戏1：2-1-3-4-5-6-7-8-9-10
  游戏2：3-2-1-4-5-6-7-8-9-10
  游戏3：1-3-2-4-5-6-7-8-9-10
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList {
  int data;
  struct LinkedList* next;
} LinkedList;

/* 打印链表 */
void PrintList(LinkedList* L) {
  LinkedList* tmp = L;
  while (tmp != NULL) {
    printf("%d ", tmp->data);  // 遍历并打印每个节点的值
    tmp = tmp->next;           // 移动指针到下一个节点
  }
  printf("\n");
}

/* 释放链表内存 */
void FreeList(LinkedList* L) {
  while (L != NULL) {
    LinkedList* tmp = L;  // 临时保存当前节点
    L = L->next;          // 指针先移动到下一个节点
    free(tmp);            // 释放当前节点内存
  }
}

/* 将指定节点移动到链表头部 */
LinkedList* liftToHead(LinkedList* cur, LinkedList* pre, LinkedList* L) {
  if (pre == NULL) return L;  // 已经是头节点，直接返回

  pre->next = cur->next;  // 前驱节点跳过当前节点
  cur->next = L;          // 当前节点指向原头节点
  return cur;             // 返回新头节点
}

/* 处理所有移动操作并更新链表 */
void changeList(LinkedList* L_ptr, int index[], int num) {
  for (int i = 0; i < num; i++) {
    LinkedList* current = L_ptr;
    LinkedList* pre = NULL;

    // 遍历查找目标节点
    while (current != NULL && current->data != index[i]) {
      pre = current;
      current = current->next;
    }

    if (current != NULL) {  // 找到目标节点时更新链表
      L_ptr = liftToHead(current, pre, L_ptr);
      PrintList(L_ptr);  // 打印每次移动后的链表状态
    }
  }
}

/* 创建包含n个节点的链表 */
LinkedList* CreateList(int n) {
  LinkedList* head = NULL;
  LinkedList* tail = NULL;

  for (int i = 1; i <= n; i++) {
    LinkedList* newNode = (LinkedList*)malloc(sizeof(LinkedList));
    newNode->data = i;     // 设置节点数据
    newNode->next = NULL;  // 新节点初始无后继

    if (head == NULL) {  // 处理第一个节点
      head = tail = newNode;
    } else {  // 后续节点追加到末尾
      tail->next = newNode;
      tail = newNode;
    }
  }
  return head;
}

int main() {
  int counter = 0;
  int* elements = NULL;

  // 初始化链表
  LinkedList* L = CreateList(10);
  PrintList(L);

  // 获取操作次数
  printf("Please input how many times you want to play: ");
  scanf("%d", &counter);

  // 分配并验证内存
  elements = (int*)malloc(counter * sizeof(int));
  if (elements == NULL) {
    printf("Memory allocation failed!");
    FreeList(L);
    return 1;
  }

  // 读取操作指令
  printf(
      "Now, input the numbers you want to lift to the list's front (1-10):\n");
  for (int i = 0; i < counter; i++) {
    scanf("%d", &elements[i]);
    if (elements[i] < 1 || elements[i] > 10) {  // 输入验证
      printf("Invalid input!");
      free(elements);
      FreeList(L);
      return 1;
    }
  }

  // 执行链表操作
  changeList(L, elements, counter);

  // 释放所有内存
  FreeList(L);
  free(elements);

  return 0;
}
