/**
 * 给定一个字符串，规定只含有字母和 *。如果出现其他字符则为非常字符串，输出
 * “error”。把该字符串除首尾的 * 号全部去除（只保留首尾 *
 * 和字母），例如：****A**B**C*****，输出 ****ABC*****
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100

// 检查输入字符串是否只包含字母和星号
int inputCheck(char* str, int* num) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (!((str[i] >= 'a' && str[i] <= 'z') ||
          (str[i] >= 'A' && str[i] <= 'Z') || (str[i] == '*'))) {
      return 0;  // 如果发现非法字符，返回0
    }
    // 右结合
    (*num)++;  // 正确递增num_char
  }
  return 1;  // 如果字符串有效，返回1
}

// 去除字符串中间部分的星号，保留首尾的星号
char* removeMidStar(char* str, int num) {
  char* str_alt = (char*)malloc(MAX_WORD_LENGTH * sizeof(char));
  int j = 0;
  int firstStar = 1;  // 标记是否遇到第一个星号
  int lastStar = 0;   // 标记是否遇到最后一个星号

  // 保留开头的星号
  // 从前往后
  for (int i = 0; i < num; i++) {
    if (str[i] == '*' && firstStar) {
      str_alt[j++] = str[i];
    } else if (str[i] != '*') {
      // 遇到字母后，不再保留中间的星号
      firstStar = 0;
      str_alt[j++] = str[i];
    }
  }

  // 保留结尾的星号
  // 从后往前
  for (int i = num - 1; i >= 0; i--) {
    if (str[i] == '*') {
      str_alt[j++] = str[i];
      lastStar = 1;
    } else {
      break;
    }
  }

  // 这个不能忘记
  str_alt[j] = '\0';  // 字符串结束符
  return str_alt;
}

int main() {
  char inputStr[MAX_WORD_LENGTH];
  int num_char = 0;

  printf("Please input the required string: ");
  fgets(inputStr, sizeof(inputStr), stdin);  // 使用fgets代替gets以确保安全

  // 移除可能的换行符
  inputStr[strcspn(inputStr, "\n")] = '\0';

  if (!inputCheck(inputStr, &num_char)) {
    printf("error!\n");
    return 1;
  } else {
    char* processedStr = removeMidStar(inputStr, num_char);
    printf("Processed string: %s\n", processedStr);
    free(processedStr);  // 释放动态分配的内存
  }

  return 0;
}
