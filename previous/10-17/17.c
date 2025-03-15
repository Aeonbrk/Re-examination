#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 用指针实现将数组 b[10]中的元素按逆序存放
void reverseArray(int *arr, int size) {
  int *start = arr;           // 指向数组头部的指针
  int *end = arr + size - 1;  // 指向数组尾部的指针

  while (start < end) {
    // 交换头尾元素
    int temp = *start;
    *start = *end;
    *end = temp;

    // 移动指针
    start++;
    end--;
  }
}

// 用递归法将一个整数 n 转换成字符串
void intToStr(int n, char *str) {
  // 处理负数
  if (n < 0) {
    *str++ = '-';
    n = -n;
  }

  // 递归终止条件：数字小于10
  if (n < 10) {
    *str++ = n + '0';
    *str = '\0';
    return;
  }

  // 递归调用处理高位数字
  intToStr(n / 10, str);

  // 找到字符串末尾
  while (*str != '\0') {
    str++;
  }

  // 添加当前位的数字
  *str++ = n % 10 + '0';
  *str = '\0';
}

// 用递归方法求 5!
int factorial(int n) {
  if (n < 0) {
    printf("Wrong input.");
    return n;
  } else if (n == 0)
    return 1;  // 修正：0! = 1
  else if (n == 1)
    return 1;
  else {
    return n * factorial(n - 1);
  }
}

// 输入一行字符，统计其中有多少个单词，单词之间用空格分隔开
int countWords(char *str) {
  int count = 0;
  int inWord = 0;  // 标记是否在单词内

  while (*str) {
    if (*str == ' ' || *str == '\t' || *str == '\n') {
      inWord = 0;  // 遇到分隔符，标记不在单词内
    } else if (inWord == 0) {
      inWord = 1;  // 从分隔符进入单词，计数加1
      count++;
    }
    str++;
  }

  return count;
}

// 输入一个数 a，求 a+ aa + aaa + aaaa + aaaaa ...... （a个）
long long sumOfSeries(int a, int count) {
  long long sum = 0;
  long long term = 0;

  for (int i = 0; i < count; i++) {
    term = term * 10 + a;  // 构建当前项
    sum += term;
  }

  return sum;
}

// 给一个不多于 6 位的正整数，要求：
// ①求出它是几位数；②分别输出每一位数字；③按逆序输出各位数字
void analyzeNumber(int num) {
  // 备份原始数字
  int original = num;

  // 计算位数
  int digits = 0;
  while (num > 0) {
    digits++;
    num /= 10;
  }

  printf("Number of digits: %d\n", digits);

  // 恢复原始数字
  num = original;

  // 创建数组存储各位数字
  int digitArray[6];
  int i = 0;

  // 分解各位数字并存储
  while (num > 0) {
    digitArray[i++] = num % 10;
    num /= 10;
  }

  // 输出各位数字（从高位到低位）
  printf("Digits from left to right: ");
  for (int j = digits - 1; j >= 0; j--) {
    printf("%d ", digitArray[j]);
  }
  printf("\n");

  // 输出逆序结果
  printf("Reversed number: ");
  for (int j = 0; j < digits; j++) {
    printf("%d", digitArray[j]);
  }
  printf("\n");
}

int main() {
  int choice = 0;

  do {
    // 显示菜单
    printf("\n=== Program Menu ===\n");
    printf("1. Reverse array elements\n");
    printf("2. Convert integer to string recursively\n");
    printf("3. Calculate factorial\n");
    printf("4. Count words in a string\n");
    printf("5. Calculate sum of series\n");
    printf("6. Analyze a number\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1: {
        // 用指针实现将数组 b[10]中的元素按逆序存放
        int b[10];
        printf("Enter 10 integers for the array:\n");
        for (int i = 0; i < 10; i++) {
          scanf("%d", &b[i]);
        }

        printf("Original array: ");
        for (int i = 0; i < 10; i++) {
          printf("%d ", b[i]);
        }

        reverseArray(b, 10);

        printf("\nReversed array: ");
        for (int i = 0; i < 10; i++) {
          printf("%d ", b[i]);
        }
        printf("\n");
        break;
      }

      case 2: {
        // 用递归法将一个整数 n 转换成字符串
        int n;
        char str[20] = {0};
        printf("Enter an integer to convert to string: ");
        scanf("%d", &n);

        intToStr(n, str);
        printf("String representation: %s\n", str);
        break;
      }

      case 3: {
        // 用递归方法求阶乘
        int n;
        printf("Enter a number to calculate factorial: ");
        scanf("%d", &n);

        int result = factorial(n);
        printf("%d! = %d\n", n, result);
        break;
      }

      case 4: {
        // 输入一行字符，统计其中有多少个单词
        char line[200];
        getchar();  // 清除缓冲区中的换行符
        printf("Enter a line of text: ");
        fgets(line, sizeof(line), stdin);

        int wordCount = countWords(line);
        printf("Number of words: %d\n", wordCount);
        break;
      }

      case 5: {
        // 输入一个数 a，求 a+ aa + aaa + ...
        int a, count;
        printf("Enter a digit (0-9): ");
        scanf("%d", &a);
        printf("Enter the count: ");
        scanf("%d", &count);

        if (a >= 0 && a <= 9) {
          long long sum = sumOfSeries(a, count);
          printf("Sum of series: %lld\n", sum);
        } else {
          printf("Please enter a single digit (0-9)\n");
        }
        break;
      }

      case 6: {
        // 给一个不多于 6 位的正整数，分析它
        int num;
        printf("Enter a positive integer (up to 6 digits): ");
        scanf("%d", &num);

        if (num > 0 && num <= 999999) {
          analyzeNumber(num);
        } else {
          printf("Please enter a positive integer up to 6 digits\n");
        }
        break;
      }

      case 0:
        printf("Exiting program. Goodbye!\n");
        break;

      default:
        printf("Invalid choice. Please try again.\n");
    }

  } while (choice != 0);

  return 0;
}
