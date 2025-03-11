/**
 * 给定两个字符串，第二个串只有两个字符。判断第一个串中有几个第二个串。
 * 字符串A: ababaaabbb，字符串B: ab，求字符串A中有多少个字符串B
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 100  // 定义输入字符串的最大长度

/**
 * 统计主字符串中模式字符串的出现次数（标准暴力匹配法）
 * @param str 主字符串指针，要求非空且以'\0'结尾
 * @param pattern 模式字符串指针，要求非空且以'\0'结尾
 * @return 模式字符串在主字符串中的出现次数
 */
int CountPattern(const char* str, const char* pattern) {
  // 参数有效性检查
  if (str == NULL || pattern == NULL) {
    fprintf(stderr, "Error: Input strings cannot be NULL.\n");
    exit(EXIT_FAILURE);
  }

  int str_len = strlen(str);          // 主字符串长度
  int pattern_len = strlen(pattern);  // 模式字符串长度
  int count = 0;                      // 匹配计数器

  // 边界条件处理：模式为空或主串长度不足时直接返回0
  if (pattern_len == 0 || str_len < pattern_len) {
    return 0;
  }

  /* 核心匹配逻辑：
   * 遍历主字符串所有可能的起始位置（0 <= i <= str_len - pattern_len）
   * 对每个起始位置检查后续pattern_len个字符是否完全匹配
   */
  for (int i = 0; i <= str_len - pattern_len; i++) {
    int is_match = 1;  // 当前起始位置的匹配状态

    // 检查从i开始的连续pattern_len个字符
    for (int j = 0; j < pattern_len; j++) {
      if (str[i + j] != pattern[j]) {
        is_match = 0;  // 发现不匹配字符，结束内层循环
        break;
      }
    }

    // 完全匹配时增加计数器
    if (is_match) {
      count++;
    }
  }

  return count;
}

int main() {
  char str[MAX_STRING_LENGTH];      // 存储主字符串
  char pattern[MAX_STRING_LENGTH];  // 存储模式字符串

  // 用户输入处理
  printf("Enter string A: ");
  if (fgets(str, sizeof(str), stdin) == NULL) {
    fprintf(stderr, "Error: Failed to read input.\n");
    return EXIT_FAILURE;
  }
  printf("Enter string B: ");
  if (fgets(pattern, sizeof(pattern), stdin) == NULL) {
    fprintf(stderr, "Error: Failed to read input.\n");
    return EXIT_FAILURE;
  }

  // 去除换行符（fgets会保留输入中的换行符）
  str[strcspn(str, "\n")] = '\0';
  pattern[strcspn(pattern, "\n")] = '\0';

  // 检查模式字符串长度是否为2（根据题目要求）
  if (strlen(pattern) != 2) {
    fprintf(stderr, "Error: String B must contain exactly 2 characters.\n");
    return EXIT_FAILURE;
  }

  // 执行模式匹配计算
  int count = CountPattern(str, pattern);

  // 输出结果
  printf("String A contains %d occurrences of String B.\n", count);

  return EXIT_SUCCESS;
}
