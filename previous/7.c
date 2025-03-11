/**
 * @brief 判断小括号是否匹配
 *
 * 该函数使用一个简化的栈来检查括号是否匹配。
 * 遇到左括号时入栈(top++)，遇到右括号时出栈(top--)
 *
 * @param str 要检查的字符串
 * @return 0表示括号匹配，-1表示不匹配
 */
int isMarry(const char *str) {
  int top = -1;  // 栈顶指针，-1表示空栈

  // 遍历输入字符串中的每个字符
  while (*str) {
    if (*str == '(') {
      ++top;  // 遇到左括号，入栈
    } else if (*str == ')') {
      if (top == -1) return -1;  // 遇到右括号但栈为空，说明右括号多了
      top--;                     // 遇到右括号，出栈
    }
    str++;
  }

  // 如果栈为空，说明括号匹配
  return (top == -1) ? 0 : -1;
}

/**
 * @brief 对多个字符串进行字典排序（使用冒泡排序算法）
 *
 * @param parr 字符串指针数组
 * @param n 数组中字符串的数量
 */
void Sort(char *parr[], int n) {
  int i, j;

  // 冒泡排序
  for (i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {  // 修正 j <= n-1 为 j < n
      char *str1 = parr[i];        // 获取两个待比较字符串
      char *str2 = parr[j];

      // 跳过两个字符串的共同前缀
      while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
      }

      // 比较第一个不同的字符，如果str1大于str2则交换位置
      if (*str1 > *str2 || (*str1 == '\0' && *str2 != '\0')) {
        char *temp = parr[i];
        parr[i] = parr[j];
        parr[j] = temp;
      }
    }
  }
}

/**
 * @brief 测试函数，用于展示函数功能
 *
 * @param void
 * @return 可选返回值（此处未使用）
 */
void testBracketMatching() {
  const char *testStrings[] = {"(())", "(()", "())", "()()", ""};

  for (int i = 0; i < 5; i++) {
    int result = isMarry(testStrings[i]);
    printf("String \"%s\": %s\n", testStrings[i],
           result == 0 ? "Brackets match" : "Brackets do not match");
  }
}

/**
 * @brief 测试字符串排序功能
 */
void testStringSorting() {
  char *strings[] = {"zebra", "apple", "banana", "cat", "dog"};
  int n = 5;

  printf("Before sorting:\n");
  for (int i = 0; i < n; i++) {
    printf("%s\n", strings[i]);
  }

  Sort(strings, n);

  printf("\nAfter sorting:\n");
  for (int i = 0; i < n; i++) {
    printf("%s\n", strings[i]);
  }
}
