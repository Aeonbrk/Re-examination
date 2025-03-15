#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 删除字符串从第n个位置起长度为len的子串
 * @param str 原字符串
 * @param n 起始位置（从0开始计数）
 * @param len 要删除的长度
 */
void deleteSubstring(char* str, int n, int len) {
  // 获取字符串长度
  int length = strlen(str);

  // 检查参数有效性
  if (n < 0 || n >= length || len <= 0) return;

  // 如果删除长度超出字符串范围，则调整为删到字符串末尾
  if (n + len > length) len = length - n;

  // 将后面的字符前移覆盖要删除的部分
  for (int i = n; i <= length - len; i++) {
    str[i] = str[i + len];
  }
}

/**
 * 链表节点结构
 */
typedef struct ListNode {
  int val;
  struct ListNode* next;
} ListNode;

/**
 * 创建新节点
 */
ListNode* createNode(int val) {
  ListNode* node = (ListNode*)malloc(sizeof(ListNode));
  node->val = val;
  node->next = NULL;
  return node;
}

/**
 * 反转从位置m到n的链表
 * @param head 链表头节点
 * @param m 起始位置（从1开始计数）
 * @param n 结束位置（从1开始计数）
 * @return 反转后的链表头节点
 */
ListNode* reverseBetween(ListNode* head, int m, int n) {
  // 特殊情况处理
  if (!head || m == n) return head;

  // 创建一个哑节点，避免处理头节点的特殊情况
  ListNode dummy;
  dummy.next = head;

  // 找到第m-1个节点
  ListNode* pre = &dummy;
  for (int i = 1; i < m; i++) {
    pre = pre->next;
  }

  // 当前节点是第m个节点
  ListNode* curr = pre->next;
  // 用于保存反转过程中的下一个节点
  ListNode* next;

  // 反转从m到n的节点
  for (int i = m; i < n; i++) {
    next = curr->next;
    curr->next = next->next;
    next->next = pre->next;
    pre->next = next;
  }

  return dummy.next;
}

/**
 * 计算数列和
 * @param n 输入数字
 * @return 计算结果
 */
double calculateSum(int n) {
  double sum = 0.0;

  if (n % 2 == 0) {  // 偶数情况：1/2 + 2/3 + 3/5 + ...
    // 设定初始分母
    int denominator = 2;
    for (int i = 1; i <= n / 2; i++) {
      sum += (double)i / denominator;
      denominator = (i == 1) ? 3 : denominator + 2;
    }
  } else {  // 奇数情况：1/1 + 1/3 + 1/5 + ...
    for (int i = 0; i < n; i++) {
      sum += 1.0 / (2 * i + 1);
    }
  }

  return sum;
}

/**
 * 打印链表
 */
void printList(ListNode* head) {
  ListNode* curr = head;
  while (curr) {
    printf("%d -> ", curr->val);
    curr = curr->next;
  }
  printf("NULL\n");
}

/**
 * 释放链表内存
 */
void freeList(ListNode* head) {
  ListNode* curr = head;
  ListNode* temp;

  while (curr) {
    temp = curr;
    curr = curr->next;
    free(temp);
  }
}

int main() {
  // 测试删除子字符串函数
  printf("-------- Testing deleteSubstring --------\n");
  char str[100] = "Hello World!";
  printf("Original string: %s\n", str);

  deleteSubstring(str, 6, 5);
  printf("After deleting 5 chars from position 6: %s\n", str);

  strcpy(str, "Programming is fun");
  printf("\nOriginal string: %s\n", str);
  deleteSubstring(str, 0, 7);
  printf("After deleting 7 chars from position 0: %s\n", str);

  // 测试链表反转函数
  printf("\n-------- Testing reverseBetween --------\n");
  ListNode* head = createNode(1);
  head->next = createNode(2);
  head->next->next = createNode(3);
  head->next->next->next = createNode(4);
  head->next->next->next->next = createNode(5);

  printf("Original list: ");
  printList(head);

  head = reverseBetween(head, 2, 4);
  printf("After reversing from position 2 to 4: ");
  printList(head);

  // 测试计算数列和函数
  printf("\n-------- Testing calculateSum --------\n");
  int testCases[] = {1, 2, 3, 4, 5};

  for (int i = 0; i < 5; i++) {
    int n = testCases[i];
    printf("For n = %d, sum = %.6f\n", n, calculateSum(n));
  }

  // 释放链表内存
  freeList(head);

  return 0;
}
