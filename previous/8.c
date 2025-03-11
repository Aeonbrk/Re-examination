#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *next;
} node;

/**
 * 删除链表中的最小值节点
 * 思路: 遍历链表找到最小值节点和其前驱，然后删除该节点
 *
 * @param L 带头结点的链表
 */
void delmin(node *L) {
  if (L == NULL || L->next == NULL) {
    // 空链表或只有头结点，无需操作
    return;
  }

  node *p = L->next;  // 当前遍历节点
  node *pre = L;      // 当前节点的前驱
  node *min = p;      // 最小值节点
  node *minpre = L;   // 最小值节点的前驱

  while (p) {
    if (p->data < min->data) {
      min = p;       // 更新最小值节点
      minpre = pre;  // 更新最小值节点的前驱
    }
    pre = p;
    p = p->next;
  }

  // 删除最小值节点
  minpre->next = min->next;
  free(min);
}

/**
 * 合并两个递增有序链表为一个递减有序链表
 * 思路: 采用头插法，每次将较小的节点插入到结果链表的头部
 *
 * @param La 第一个递增有序链表（带头结点）
 * @param Lb 第二个递增有序链表（带头结点）
 * @return 合并后的递减有序链表
 */
node *Union(node *La, node *Lb) {
  if (La == NULL) return Lb;
  if (Lb == NULL) return La;

  node *p = La->next;  // La的数据节点
  node *q = Lb->next;  // Lb的数据节点
  node *temp;          // 临时节点指针

  La->next = NULL;  // 将La作为结果链表，初始化为空

  // 同时处理两个链表中的节点
  while (p && q) {
    if (p->data <= q->data) {
      // 取出p节点
      temp = p->next;
      // 头插法插入p
      p->next = La->next;
      La->next = p;
      // 继续处理p链表的下一个节点
      p = temp;
    } else {
      // 取出q节点
      temp = q->next;
      // 头插法插入q
      q->next = La->next;
      La->next = q;
      // 继续处理q链表的下一个节点
      q = temp;
    }
  }

  // 处理剩余节点
  if (q) p = q;  // 如果q还有剩余节点，将p指向q
  while (p) {
    temp = p->next;
    // 头插法插入剩余节点
    p->next = La->next;
    La->next = p;
    p = temp;
  }

  free(Lb);  // 释放Lb的头结点
  return La;
}

/**
 * 创建一个新的节点
 *
 * @param data 节点数据
 * @return 新创建的节点指针
 */
node *createNode(int data) {
  node *newNode = (node *)malloc(sizeof(node));
  if (newNode == NULL) {
    printf("Memory allocation failed!\n");
    exit(1);
  }
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

/**
 * 创建带头结点的链表
 *
 * @return 头结点指针
 */
node *createList() {
  node *head = createNode(0);  // 头结点data通常为0或不使用
  return head;
}

/**
 * 打印链表内容
 *
 * @param L 带头结点的链表
 */
void printList(node *L) {
  if (L == NULL) {
    printf("List is NULL!\n");
    return;
  }

  node *p = L->next;
  printf("List: ");
  while (p) {
    printf("%d ", p->data);
    p = p->next;
  }
  printf("\n");
}

/**
 * 释放整个链表内存
 *
 * @param L 带头结点的链表
 */
void freeList(node *L) {
  node *p = L;
  node *temp;

  while (p) {
    temp = p->next;
    free(p);
    p = temp;
  }
}
