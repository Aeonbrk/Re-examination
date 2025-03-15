#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node* next;
} node;

// 输入整形数据，按输入的顺序建立单链表
node* createList() {
  node *head, *p, *q;
  int x;

  printf("Please enter integers (enter -1 to end):\n");
  scanf("%d", &x);

  // 创建头节点
  head = (node*)malloc(sizeof(node));
  head->next = NULL;
  p = head;

  while (x != -1) {
    q = (node*)malloc(sizeof(node));
    q->data = x;
    q->next = NULL;
    p->next = q;
    p = q;
    scanf("%d", &x);
  }

  return head;  // 返回头节点
}

// 打印链表函数
void printList(node* head) {
  node* p = head->next;
  printf("List content: ");
  while (p) {
    printf("%d ", p->data);
    p = p->next;
  }
  printf("\n");
}

// 链表逆序函数
void turn(struct node* head) {
  // 如果链表为空或只有一个节点，直接返回
  if (head->next == NULL || head->next->next == NULL) {
    return;
  }

  node* prev = NULL;           // 前一个节点
  node* current = head->next;  // 当前节点（从第一个实际数据节点开始）
  node* next = NULL;           // 下一个节点

  while (current != NULL) {
    next = current->next;  // 保存下一个节点
    current->next = prev;  // 当前节点指向前一个节点
    prev = current;        // 移动前一个节点指针
    current = next;        // 移动当前节点指针
  }

  head->next = prev;  // 头节点指向新的链表头（原来的尾节点）
}

// 链表逆序函数（不带头结点）
node* turnNoHead(node* head) {
  // 如果链表为空或只有一个节点，直接返回
  if (head == NULL || head->next == NULL) {
    return head;
  }

  node* prev = NULL;     // 前一个节点
  node* current = head;  // 当前节点（从第一个实际数据节点开始）
  node* next = NULL;     // 下一个节点

  while (current != NULL) {
    next = current->next;  // 保存下一个节点
    current->next = prev;  // 当前节点指向前一个节点
    prev = current;        // 移动前一个节点指针
    current = next;        // 移动当前节点指针
  }

  return prev;  // 返回新的头结点（原来的尾结点）
}

// 求两个链表L1和L2的交集，要求交集放到L1上，不允许申请内存，只能删除节点
void intersection(node* L1, node* L2) {
  // L1和L2都有头节点
  node* p1 = L1;
  node* cur1;
  node* L2_cur = L2->next;  // L2的当前节点
  int found;

  // 遍历L1的每个节点，检查是否在L2中存在
  while (p1->next != NULL) {
    found = 0;
    L2_cur = L2->next;  // 重置L2的遍历指针

    // 在L2中查找当前L1节点的值
    while (L2_cur != NULL) {
      if (p1->next->data == L2_cur->data) {
        found = 1;
        break;
      }
      L2_cur = L2_cur->next;
    }

    // 如果在L2中没找到，则从L1中删除该节点
    if (!found) {
      cur1 = p1->next;        // 保存要删除的节点
      p1->next = cur1->next;  // 绕过要删除的节点
      free(cur1);             // 释放节点内存
    } else {
      p1 = p1->next;  // 移动到下一个节点
    }
  }
}

// 求两个链表L1和L2的交集，要求交集放到L1上，不允许申请内存，只能删除节点
node* intersectionNoHead(node* L1, node* L2) {
  // 处理特殊情况
  if (L1 == NULL) {
    return NULL;
  }
  if (L2 == NULL) {
    // 如果L2为空，交集也为空，删除L1所有节点
    node* temp;
    while (L1) {
      temp = L1;
      L1 = L1->next;
      free(temp);
    }
    return NULL;
  }

  // 创建dummy节点便于处理第一个节点可能被删除的情况
  node dummy;
  dummy.next = L1;
  node* p1 = &dummy;
  node* cur1;
  node* L2_cur;
  int found;

  // 遍历L1的每个节点，检查是否在L2中存在
  while (p1->next != NULL) {
    found = 0;
    L2_cur = L2;  // 重置L2的遍历指针

    // 在L2中查找当前L1节点的值
    while (L2_cur != NULL) {
      // p1 一直多一个 dummy 节点
      if (p1->next->data == L2_cur->data) {
        found = 1;
        break;
      }
      L2_cur = L2_cur->next;
    }

    // 如果在L2中没找到，则从L1中删除该节点
    if (!found) {
      cur1 = p1->next;        // 保存要删除的节点
      p1->next = cur1->next;  // 绕过要删除的节点
      free(cur1);             // 释放节点内存
    } else {
      p1 = p1->next;  // 移动到下一个节点
    }
  }

  return dummy.next;  // 返回新的L1头结点
}

int main() {
  // 创建第一个链表
  printf("Creating first list:\n");
  node* L1 = createList();
  printf("First ");
  printList(L1);

  // 创建第二个链表
  printf("Creating second list:\n");
  node* L2 = createList();
  printf("Second ");
  printList(L2);

  // 求交集
  printf("Calculating intersection...\n");
  intersection(L1, L2);
  printf("Intersection ");
  printList(L1);

  // 反转链表
  printf("Reversing the intersection list...\n");
  turn(L1);
  printf("Reversed ");
  printList(L1);

  return 0;
}
