// 随机输入若干整数和若干浮点数（顺序也是随机的，最多 100 个），要求编写完整的程
// 序，将整数按从大到小排列，浮点数按从小到大排列（浮点数排序可省略），并输出。如：
// 输入 10 12.3 12 5 52.1 3.65 88.6 输出：12 10 5 3.65 12.3 52.1 88.6

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void my_qsort(void *base, size_t num, size_t size,
              int (*compare)(const void *, const void *)) {
  if (num <= 1) return;  // 如果元素个数为 0 或 1，则无需排序

  // 定义左右指针
  char *left = (char *)base;
  char *right = (char *)base + (num - 1) * size;

  // 选择最右边的元素作为基准值
  char pivot[size];
  memcpy(pivot, right, size);

  // 分区过程
  char *i = left - size;
  char *j = right;
  while (1) {
    // 从左向右找到第一个大于等于 pivot 的元素
    do {
      i += size;
    } while (i < right && compare(i, pivot) < 0);

    // 从右向左找到第一个小于等于 pivot 的元素
    do {
      j -= size;
    } while (j > left && compare(j, pivot) > 0);

    // 如果指针相遇或交叉，则退出循环
    if (i >= j) break;

    // 交换 i 和 j 指向的元素
    char temp[size];
    memcpy(temp, i, size);
    memcpy(i, j, size);
    memcpy(j, temp, size);
  }

  // 将 pivot 放到正确的位置
  memcpy(right, i, size);
  memcpy(i, pivot, size);

  // 递归排序左右两部分
  size_t left_count = (i - left) / size;
  my_qsort(base, left_count, size, compare);                // 排序左半部分
  my_qsort(i + size, num - left_count - 1, size, compare);  // 排序右半部分
}

// 这个还是很实用的，但是要是遇到让你实现快排也得会
// 整数比较函数（降序）
int compare_int(const void *a, const void *b) {
  return (*(int *)b - *(int *)a);
}

// 浮点数比较函数（升序）
// 如果 fa > fb，则 (fa > fb) - (fa < fb) 的值为 1。
// 如果 fa < fb，则 (fa > fb) - (fa < fb) 的值为 -1。
// 如果 fa == fb，则 (fa > fb) - (fa < fb) 的值为 0。
int compare_float(const void *a, const void *b) {
  float fa = *(float *)a;
  float fb = *(float *)b;
  return (fa > fb) - (fa < fb);
}

int main() {
  int num_int[100], count_int = 0, count_float = 0;
  float num_float[100];
  char str[1000];

  printf("Please input and divide them with space: ");
  fgets(str, sizeof(str), stdin);

  // strtok 将字符串分割成多个子字符串
  //
  char *token = strtok(str, " ");
  while (token != NULL) {
    // 判断是否为浮点数
    // strchr 在字符串中查找某个字符首次出现的位置
    if (strchr(token, '.') != NULL) {
      // 将字符串转换为浮点数
      num_float[count_float++] = atof(token);
    } else {
      // 将字符串转换为整数
      num_int[count_int++] = atoi(token);
    }
    token = strtok(NULL, " ");
  }

  // 参考 2024(1)
  // 排序整数数组（降序）
  qsort(num_int, count_int, sizeof(int), compare_int);
  // 排序浮点数数组（升序）
  qsort(num_float, count_float, sizeof(float), compare_float);

  // 输出结果（整数在前，浮点数在后）
  int noSpace = 1;
  for (int i = 0; i < count_int; i++) {
    // 最开始不放空格，后面都放
    if (noSpace) {
      noSpace = 0;
    } else {
      printf(" ");
    }
    printf("%d", num_int[i]);
  }
  for (int i = 0; i < count_float; i++) {
    if (noSpace) {
      noSpace = 0;
    } else {
      printf(" ");
    }
    printf("%g", num_float[i]);
  }
  printf("\n");

  return 0;
}
