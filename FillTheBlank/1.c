#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* 问题1: 快速排序法求某个数组前 n 个元素第 k 小的数 */
// 分区函数，将数组按基准值分成两部分，返回基准值位置
int partition(int arr[], int low, int high) {
  int pivot = arr[low];  // 选择第一个元素作为基准值
  while (low < high) {
    // 从右向左找小于基准值的元素
    while (low < high && arr[high] >= pivot) {
      high--;
    }
    arr[low] = arr[high];  // 将小于基准值的元素放到左边

    // 从左向右找大于基准值的元素
    while (low < high && arr[low] <= pivot) {
      low++;
    }
    arr[high] = arr[low];  // 将大于基准值的元素放到右边
  }

  arr[low] = pivot;  // 将基准值放到最终位置
  return low;        // 返回基准值的位置
}

// 使用快速排序思想寻找第k小的元素
int quickSelect(int arr[], int low, int high, int k) {
  if (low <= high) {
    int pivotPos = partition(arr, low, high);

    if (pivotPos == k - 1) {  // 找到第k小的元素
      return arr[pivotPos];
    } else if (pivotPos > k - 1) {  // 第k小的元素在左半部分
      return quickSelect(arr, low, pivotPos - 1, k);
    } else {  // 第k小的元素在右半部分
      return quickSelect(arr, pivotPos + 1, high, k);
    }
  }
  return -1;  // 表示未找到
}

/* 问题2: 完美乘法，a*b=c,abc中只出现0~9的数字，且每个数字在这个等式中只出现一遍
 */
// 检查并标记数字，返回是否有重复数字
bool checkAndMark(int num, int used[]) {
  while (num > 0) {
    int digit = num % 10;
    if (used[digit]) return false;
    used[digit] = 1;
    num /= 10;
  }
  return true;
}

// 寻找完美乘法
void findPerfectMultiplications() {
  printf("Perfect Multiplications:\n");

  for (int a = 1; a <= 9876; a++) {
    for (int b = 1; b * a <= 98765 && b <= 9876; b++) {
      int c = a * b;
      int used[10] = {0};  // 标记数字0-9是否使用

      // 依次检查 a, b, c 是否符合条件
      if (!checkAndMark(a, used) || !checkAndMark(b, used) ||
          !checkAndMark(c, used)) {
        continue;
      }

      // 检查是否用完所有 0-9 的数字
      bool allUsed = true;
      for (int i = 0; i < 10; i++) {
        if (!used[i]) {
          allUsed = false;
          break;
        }
      }

      if (allUsed) {
        printf("%d * %d = %d\n", a, b, c);
      }
    }
  }
}

/* 问题3: 链表实现选择排序（带头结点） */
// 定义链表节点结构
typedef struct Node {
  int data;
  struct Node* next;
} Node;

// 创建带头结点的链表
Node* createList() {
  Node* head = (Node*)malloc(sizeof(Node));
  head->next = NULL;
  return head;
}

// 在链表尾部添加节点
void appendNode(Node* head, int value) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->data = value;
  newNode->next = NULL;

  Node* current = head;
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = newNode;
}

// 打印链表
void printList(Node* head) {
  Node* current = head->next;
  while (current != NULL) {
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");
}

// 链表选择排序
void selectionSort(Node* head) {
  Node *p, *q, *min;

  for (p = head->next; p != NULL && p->next != NULL; p = p->next) {
    min = p;  // 假设当前节点值最小

    // 查找p之后的最小节点
    for (q = p->next; q != NULL; q = q->next) {
      if (q->data < min->data) {
        min = q;
      }
    }

    // 如果找到更小的值，交换节点的值
    if (min != p) {
      int temp = p->data;
      p->data = min->data;
      min->data = temp;
    }
  }
}

// 释放链表内存
void freeList(Node* head) {
  Node* current = head;
  Node* next;

  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
}

/* 主函数 */
int main() {
  // 问题1：快速排序法求第k小元素
  printf("Problem 1: Quick Select\n");
  int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
  int n = sizeof(arr) / sizeof(arr[0]);
  int k = 4;  // 查找第4小的元素

  printf("Array: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  int kthSmallest = quickSelect(arr, 0, n - 1, k);
  printf("The %dth smallest element is: %d\n\n", k, kthSmallest);

  // 问题2：完美乘法
  printf("Problem 2: Perfect Multiplication\n");
  findPerfectMultiplications();
  printf("\n");

  // 问题3：链表实现选择排序
  printf("Problem 3: Selection Sort on Linked List\n");
  Node* head = createList();

  // 添加数据到链表
  int listData[] = {64, 25, 12, 22, 11};
  int listSize = sizeof(listData) / sizeof(listData[0]);

  for (int i = 0; i < listSize; i++) {
    appendNode(head, listData[i]);
  }

  printf("Before sorting: ");
  printList(head);

  selectionSort(head);

  printf("After sorting: ");
  printList(head);

  // 释放链表内存
  freeList(head);

  return 0;
}
