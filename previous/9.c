#include <stdio.h>
#include <stdlib.h>

// 编写一个函数，把整数序列分成两个部分，使得左边部分都不大于右边部分，
// 不需要排序。
int partion(int arr[], int n) {
  int pos = 0;  // 选择第一个元素作为基准
  int i = 0, j = n - 1;
  int temp;
  while (i != j) {
    while (arr[j] >= arr[pos] && i < j) j--;  // 从右向左找小于基准的元素
    while (arr[i] <= arr[pos] && i < j) i++;  // 从左向右找大于基准的元素
    if (i < j) {                              // 交换两个元素
      temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
    }
  }
  // 将基准元素放到最终位置
  temp = arr[i];
  arr[i] = arr[pos];
  arr[pos] = temp;
  return i;  // 返回基准元素的位置
}

// 定义链表节点结构
typedef struct node {
  int data;
  struct node *next;
} node;

// 编写完整程序，一个链表，找出其中数据项最大的结点，然后将其移动到链表尾部
// 结点由整型data和节点指针next构成，不允许申请新的结点
// 方法一：不断链（交换数据）
void movemax(node *L) {
  if (L == NULL || L->next == NULL) return;  // 处理空链表或只有一个节点的情况

  node *p = L->next, *pre = L;
  node *max = L->next, *preMax = L;  // 记录最大值节点及其前驱

  // 遍历找出最大值节点
  while (p) {
    if (p->data > max->data) {
      max = p;
      preMax = pre;
    }
    pre = p;
    p = p->next;
  }

  // 如果最大值已经在尾部，则不需要操作
  if (max->next == NULL) return;

  // 交换最大值节点的数据和尾节点的数据
  p = L;
  while (p->next != NULL) p = p->next;  // 找到尾节点

  int temp = p->data;
  p->data = max->data;
  max->data = temp;
}

// 方法二：断链（移动节点）
void maxInsert(node *L) {
  if (L == NULL || L->next == NULL) return;  // 处理空链表或只有一个节点的情况

  node *p = L;
  node *max = L->next, *preMax = L;  // 记录最大值节点及其前驱

  // 遍历找出最大值节点及其前驱
  while (p->next != NULL) {
    if (p->next->data > max->data) {
      max = p->next;
      preMax = p;
    }
    p = p->next;
  }

  // 如果最大值已经在尾部，则不需要操作
  if (max->next == NULL) return;

  // 断链并将最大值节点移到尾部
  preMax->next = max->next;  // 从原位置删除最大值节点
  p->next = max;             // 将最大值节点连接到尾部
  max->next = NULL;          // 更新尾部节点的next为NULL
}

// 输入整形数据，按输入的顺序建立单链表
node *createList() {
  node *head, *p, *q;
  int x;

  // 创建头节点
  head = (node *)malloc(sizeof(node));
  head->next = NULL;
  p = head;

  printf("Please enter integers (enter -1 to end):\n");
  scanf("%d", &x);

  while (x != -1) {
    q = (node *)malloc(sizeof(node));
    q->data = x;
    q->next = NULL;
    p->next = q;
    p = q;
    scanf("%d", &x);
  }

  return head;
}

// 打印链表函数
void printList(node *head) {
  node *p = head->next;
  printf("List content: ");
  while (p) {
    printf("%d ", p->data);
    p = p->next;
  }
  printf("\n");
}

// 主函数示例
int main() {
  int choice;
  node *head;

  // 创建链表
  head = createList();
  printList(head);

  printf("Choose method (1: Exchange data, 2: Move node): ");
  scanf("%d", &choice);

  if (choice == 1) {
    movemax(head);
    printf("After moving max node (method 1):\n");
  } else {
    maxInsert(head);
    printf("After moving max node (method 2):\n");
  }

  printList(head);

  return 0;
}
