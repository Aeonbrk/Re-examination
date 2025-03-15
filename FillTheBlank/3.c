#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 求两个数的最大公约数
int gcd(int a, int b) {
  /* 使用欧几里得算法求最大公约数 */
  while (b != 0) {
    int temp = a % b;
    a = b;
    b = temp;
  }
  return a;
}

// 求两个数的最小公倍数
int lcm(int a, int b) {
  /* 最小公倍数 = 两数之积 / 最大公约数 */
  return a / gcd(a, b) * b;  // 先除后乘防止溢出
}

// 求n个数的最大公约数
int findGCD(int arr[], int n) {
  /* 依次求每对数的最大公约数 */
  int result = arr[0];
  for (int i = 1; i < n; i++) {
    result = gcd(result, arr[i]);
  }
  return result;
}

// 求n个数的最小公倍数
int findLCM(int arr[], int n) {
  /* 依次求每对数的最小公倍数 */
  int result = arr[0];
  for (int i = 1; i < n; i++) {
    result = lcm(result, arr[i]);
  }
  return result;
}

// 将str2插入到str1的第m+1个位置
void insertString(char str1[], char str2[], int m) {
  /* 插入字符串，原字符后移 */
  int len1 = strlen(str1);
  int len2 = strlen(str2);

  // 将str1的字符向后移动len2个位置，为str2腾出空间
  for (int i = len1; i >= m; i--) {
    str1[i + len2] = str1[i];
  }

  // 将str2复制到str1中的m位置
  for (int i = 0; i < len2; i++) {
    str1[m + i] = str2[i];
  }
}

// 学生结构体定义
typedef struct {
  int num;     // 学号
  int age;     // 年龄
  int height;  // 身高
} Student;

// 比较两个学生
int compareStudents(const void* a, const void* b) {
  Student* s1 = (Student*)a;
  Student* s2 = (Student*)b;

  /* 先比较学号 */
  if (s1->num != s2->num) {
    return s1->num - s2->num;
  }

  /* 学号相同比较年龄 */
  if (s1->age != s2->age) {
    return s1->age - s2->age;
  }

  /* 学号和年龄都相同比较身高 */
  return s1->height - s2->height;
}

// 排序学生数组
void sortStudents(Student students[], int n) {
  /* 使用qsort函数排序 */
  qsort(students, n, sizeof(Student), compareStudents);
}

// 主函数调用所有功能
int main() {
  // 1. 求最大公约数和最小公倍数
  int numbers[] = {12, 18, 24, 36};
  int n = sizeof(numbers) / sizeof(numbers[0]);

  printf("Numbers: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", numbers[i]);
  }
  printf("\n");

  int greatestCommonDivisor = findGCD(numbers, n);
  int leastCommonMultiple = findLCM(numbers, n);

  printf("Greatest Common Divisor: %d\n", greatestCommonDivisor);
  printf("Least Common Multiple: %d\n", leastCommonMultiple);

  printf("\n");

  // 2. 字符串插入
  char str1[100] = "Hello World";
  char str2[] = "Beautiful ";
  int m = 6;  // 在World前插入

  printf("Original string 1: %s\n", str1);
  printf("String 2 to insert: %s\n", str2);
  printf("Insert position: %d\n", m);

  insertString(str1, str2, m);
  printf("Result after insertion: %s\n", str1);

  printf("\n");

  // 3. 学生排序
  Student students[] = {{101, 18, 175},
                        {102, 19, 180},
                        {101, 18, 178},
                        {103, 18, 172},
                        {101, 19, 175}};
  int numStudents = sizeof(students) / sizeof(students[0]);

  printf("Before sorting:\n");
  printf("Num\tAge\tHeight\n");
  for (int i = 0; i < numStudents; i++) {
    printf("%d\t%d\t%d\n", students[i].num, students[i].age,
           students[i].height);
  }

  sortStudents(students, numStudents);

  printf("\nAfter sorting:\n");
  printf("Num\tAge\tHeight\n");
  for (int i = 0; i < numStudents; i++) {
    printf("%d\t%d\t%d\n", students[i].num, students[i].age,
           students[i].height);
  }

  return 0;
}
