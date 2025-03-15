// 编写一个函数，从字符串中寻找整个连续的数字字符，将其转化成整数并保存在 arr
// 整型数组里，溢出以-1 作为标志。字符串以'#'结束（如"uestc2015jsj123#"）

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 1000
#define MAX_NUMBER_LEN 1000

// 将连续数字字符串转换为整数，处理溢出情况
int str2int(char str[], int start, int end) {
  long long num = 0;  // 使用long long防止中间计算溢出

  for (int i = start; i < end; i++) {
    // 检查是否溢出
    // 这里的溢出检查学习下
    if (num > INT_MAX / 10 ||
        (num == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10)) {
      return -1;  // 溢出标记
    }
    num = num * 10 + (str[i] - '0');
  }

  // 强制类型转换
  return (int)num;
}

// 从字符串中寻找连续数字并转换为整数存入数组
void intFind(char str[], int arr[], int* count) {
  int len = strlen(str);
  int start = -1;  // 数字开始位置
  *count = 0;      // 初始化计数器

  // 关键是记录，纸上模拟一下就明白了
  for (int i = 0; i <= len; i++) {
    // 如果当前字符是数字且之前没有开始记录数字
    if (i < len && str[i] >= '0' && str[i] <= '9') {
      if (start == -1) {
        start = i;  // 标记数字开始位置
      }
    }
    // 如果当前不是数字但之前有数字序列，或到达字符串末尾
    else if (start != -1) {
      // 将连续数字转换为整数
      arr[*count] = str2int(str, start, i);
      (*count)++;
      start = -1;  // 重置数字开始标记
    }
  }

  // 如果没有找到任何数字
  if (*count == 0) {
    printf("The string does not contain any number!");
    exit(1);
  }
}

int main() {
  char inputStr[MAX_STRING_LEN];
  int arr[MAX_NUMBER_LEN];
  int counter = 0;

  printf("Please input the string with # as the end: ");
  fgets(inputStr, sizeof(inputStr), stdin);

  // 将#及之后的内容截断
  inputStr[strcspn(inputStr, "#")] = '\0';
  // 去除可能存在的换行符
  inputStr[strcspn(inputStr, "\n")] = '\0';

  // 查找并转换数字
  intFind(inputStr, arr, &counter);

  // 输出结果
  printf("The numbers in string are: ");
  for (int i = 0; i < counter; i++) {
    if (i > 0) {
      printf(" ");
    }
    printf("%d", arr[i]);
  }

  return 0;
}
