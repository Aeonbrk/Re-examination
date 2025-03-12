#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 问题一：约瑟夫环问题
 * 有n个人围成一圈，顺序排号。从第一个人开始报数（从1到3报数），
 * 凡报到3的人退出圈子，问最后留下来的是原来第几号的那位。
 * 使用指针知识实现
 */
typedef struct Person {
  int number;           // 人的编号
  struct Person *next;  // 指向下一个人的指针
} Person;

// 创建环形链表函数
Person *createCircle(int n) {
  Person *head = NULL, *current = NULL, *prev = NULL;
  int i;

  // 创建n个节点的链表
  for (i = 1; i <= n; i++) {
    current = (Person *)malloc(sizeof(Person));
    if (current == NULL) {
      printf("Memory allocation failed\n");
      exit(1);
    }

    current->number = i;
    current->next = NULL;

    if (head == NULL) {
      head = current;
    } else {
      prev->next = current;
    }

    prev = current;
  }

  // 构成环
  if (current != NULL) {
    current->next = head;
  }

  return head;
}

// 约瑟夫环问题求解函数
int josephus(int n, int k) {
  if (n <= 0 || k <= 0) return -1;
  if (n == 1) return 1;

  Person *head = createCircle(n);
  Person *current = head;
  Person *prev = NULL;

  // 查找尾节点，使其指向头节点
  while (current->next != head) {
    current = current->next;
  }
  prev = current;
  current = head;

  // 模拟报数过程
  while (current->next != current) {  // 当环中只剩一个节点时停止
    // 报数k-1次，找到第k个人
    for (int i = 1; i < k; i++) {
      prev = current;
      current = current->next;
    }

    // 删除第k个人
    prev->next = current->next;
    Person *temp = current;
    current = current->next;
    free(temp);
  }

  // 记录最后一个人的编号
  int result = current->number;
  free(current);  // 释放最后一个节点

  return result;
}

/* 问题二：密码翻译
 * 有一行电文，已按规律译成密码：
 * A→Z, a→z, B→Y, b→y, C→X, c→x等
 * 即第i个字母变成第(26-i+1)个字母，非字母符号不变
 * 编程序将密码译回原文
 */
void decodeCipher(char *cipher, char *original) {
  int j = 0;

  // 解密过程
  while (cipher[j] != '\0') {
    if (cipher[j] >= 'A' && cipher[j] <= 'Z')
      original[j] = 'A' + 'Z' - cipher[j];  // 155 - cipher[j] 的简化形式
    else if (cipher[j] >= 'a' && cipher[j] <= 'z')
      original[j] = 'a' + 'z' - cipher[j];  // 219 - cipher[j] 的简化形式
    else
      original[j] = cipher[j];  // 非字母字符保持不变
    j++;
  }

  original[j] = '\0';  // 添加字符串结束符
}

int main() {
  int choice;

  printf("Select problem (1 or 2): ");
  scanf("%d", &choice);
  getchar();  // 消除换行符

  if (choice == 1) {
    // 问题一: 约瑟夫环
    int n;
    printf("Enter number of people: ");
    scanf("%d", &n);

    if (n <= 0) {
      printf("Invalid input, number must be positive\n");
      return 1;
    }

    int result = josephus(n, 3);  // 从1到3报数，凡报到3的人退出
    printf("The last person remaining is number %d\n", result);
  } else if (choice == 2) {
    // 问题二: 密码解密
    char cipher[80], original[80];

    printf("Input cipher code: ");
    fgets(cipher, sizeof(cipher), stdin);
    if (cipher[strlen(cipher) - 1] == '\n')
      cipher[strlen(cipher) - 1] = '\0';  // 移除换行符

    printf("\nCipher code: %s", cipher);

    decodeCipher(cipher, original);

    printf("\nOriginal text: %s\n", original);
  } else {
    printf("Invalid choice\n");
  }

  return 0;
}
