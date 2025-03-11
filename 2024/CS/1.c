/**
 * 给定一个数，将数位中的奇数取出，并按与位权值大小从小到大排序。
 * 比如输入 1325789，输出 97531
 */

#include <stdio.h>
#include <stdlib.h>

// 比较函数，用于从大到小排序
int compare(const void *a, const void *b) {
  /**
   * *(int *)a 和 *(int *)b 是将 void * 类型的指针转换为 int *
   * 类型，并解引用得到实际的整数值
   */
  return (*(int *)b - *(int *)a);
}

int main() {
  int num;
  printf("Please input a integer: ");
  scanf("%d", &num);

  int digits[20];  // 假设最多有20位数字
  int count = 0;

  // 提取奇数位数字
  while (num > 0) {
    int digit = num % 10;
    if (digit % 2 != 0) {
      digits[count++] = digit;
    }
    num /= 10;
  }

  /**
   * 对奇数位数字从大到小排序
   * void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void
   * *, const void *));
   * base：指向要排序的数组的第一个元素的指针。
   * nmemb：数组中元素的个数。
   * size：每个元素的大小（以字节为单位）。
   * compar：指向比较函数的指针
   */
  qsort(digits, count, sizeof(int), compare);

  // 组合成新的整数
  int result = 0;
  for (int i = 0; i < count; i++) {
    result = result * 10 + digits[i];
  }

  printf("The result is: %d\n", result);

  return 0;
}
