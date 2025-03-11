// 编写完整的程序，构造整数集合(其实就是一个整数链表)，并实现对该集合操作的若干功
// 能：加入一个新元素，判断某元素是否在集合内，输出两个集合并集，输出两个集合交集，
// 删除集合中某一元素。
// struct set{int numb; struct set *next;}
// 注意：链表里是没有重复数字的，因为题目中说了是集合，集合是不会有重复元素出现的。

#include <stdio.h>
#include <stdlib.h>

typedef struct Set {
  int numb;
  struct Set* next;
} Set;

// 创建一个空集合
Set* createSet() {
  // 创建头结点，头结点不存储数据
  Set* head = (Set*)malloc(sizeof(Set));
  if (head == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }
  head->next = NULL;
  return head;
}

// 判断元素是否在集合中
int isInSet(Set* head, int num) {
  Set* current = head->next;
  while (current != NULL) {
    if (current->numb == num) {
      return 1;  // 找到了该元素
    }
    current = current->next;
  }
  return 0;  // 没有找到该元素
}

// 向集合中添加元素（如果元素已存在则不添加）
void addToSet(Set* head, int num) {
  // 先检查元素是否已经存在于集合中
  if (isInSet(head, num)) {
    printf("%d is already in the set\n", num);
    return;
  }

  // 创建新节点
  Set* newNode = (Set*)malloc(sizeof(Set));
  if (newNode == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }
  newNode->numb = num;

  // 插入到链表头部（头插法）
  newNode->next = head->next;
  head->next = newNode;

  printf("%d added to the set\n", num);
}

// 从集合中删除元素
void removeFromSet(Set* head, int num) {
  Set* current = head;
  Set* temp;

  // 遍历链表查找要删除的元素
  while (current->next != NULL) {
    if (current->next->numb == num) {
      temp = current->next;
      current->next = current->next->next;
      free(temp);
      printf("%d removed from the set\n", num);
      return;
    }
    current = current->next;
  }

  printf("%d not found in the set\n", num);
}

// 打印集合中的所有元素
void printSet(Set* head) {
  if (head->next == NULL) {
    printf("Empty set\n");
    return;
  }

  Set* current = head->next;
  printf("Set elements: ");
  while (current != NULL) {
    printf("%d ", current->numb);
    current = current->next;
  }
  printf("\n");
}

// 计算两个集合的并集
Set* unionSets(Set* set1, Set* set2) {
  Set* result = createSet();
  Set* current;

  // 添加第一个集合的所有元素
  current = set1->next;
  while (current != NULL) {
    addToSet(result, current->numb);
    current = current->next;
  }

  // 添加第二个集合的所有元素（addToSet会自动去重）
  current = set2->next;
  while (current != NULL) {
    addToSet(result, current->numb);
    current = current->next;
  }

  return result;
}

// 计算两个集合的交集
Set* intersectSets(Set* set1, Set* set2) {
  Set* result = createSet();
  Set* current = set1->next;

  // 遍历第一个集合，检查每个元素是否在第二个集合中
  while (current != NULL) {
    if (isInSet(set2, current->numb)) {
      addToSet(result, current->numb);
    }
    current = current->next;
  }

  return result;
}

// 释放集合占用的内存
void freeSet(Set* head) {
  Set* current = head;
  Set* next;

  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
}

int main() {
  // 创建两个集合
  Set* set1 = createSet();
  Set* set2 = createSet();

  printf("Operations on Set 1:\n");
  addToSet(set1, 10);
  addToSet(set1, 20);
  addToSet(set1, 30);
  addToSet(set1, 10);  // 尝试添加重复元素
  printSet(set1);

  printf("\nOperations on Set 2:\n");
  addToSet(set2, 20);
  addToSet(set2, 40);
  addToSet(set2, 50);
  printSet(set2);

  // 测试元素是否存在
  printf("\nElement existence check:\n");
  printf("Is 20 in set1? %s\n", isInSet(set1, 20) ? "Yes" : "No");
  printf("Is 40 in set1? %s\n", isInSet(set1, 40) ? "Yes" : "No");

  // 计算并集
  printf("\nUnion of the sets:\n");
  Set* unionSet = unionSets(set1, set2);
  printSet(unionSet);

  // 计算交集
  printf("\nIntersection of the sets:\n");
  Set* intersectSet = intersectSets(set1, set2);
  printSet(intersectSet);

  // 删除元素
  printf("\nRemoving elements:\n");
  removeFromSet(set1, 20);
  printSet(set1);
  removeFromSet(set1, 100);  // 尝试删除不存在的元素

  // 释放内存
  freeSet(set1);
  freeSet(set2);
  freeSet(unionSet);
  freeSet(intersectSet);

  return 0;
}
