// 有两字符数组 s 和 t，求 t 在 s 中出现第一次的开始位置，如果没有则输出"No"，
// 有则输出开始位置。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findStart(char* s, char* t) {
  if (s == NULL || t == NULL) {
    return -1;  // 错误处理：空指针情况
  }

  int len_s = strlen(s);
  int len_t = strlen(t);

  // 特殊情况处理：空字符串
  if (len_t == 0) {
    return 0;
  }

  // 如果 t 比 s 长，不可能找到
  if (len_t > len_s) {
    return -1;
  }

  // 遍历 s 中的每个位置作为可能的起始点
  for (int i = 0; i <= len_s - len_t; i++) {
    int j;
    // 从当前位置开始比较
    for (j = 0; j < len_t; j++) {
      if (s[i + j] != t[j]) {
        break;  // 不匹配，终止内层循环
      }
    }

    // 如果内层循环正常结束（j到达len_t），说明找到了完全匹配
    if (j == len_t) {
      return i;
    }
  }

  // 未找到匹配
  return -1;
}

int main() {
  char s[100], t[100];

  // 输入两个字符串
  printf("Enter the source string: ");
  scanf("%s", s);

  printf("Enter the target string: ");
  scanf("%s", t);

  int result = findStart(s, t) + 1;

  if (result != 0) {
    printf("Found at position: %d\n", result);
  } else {
    printf("No\n");
  }

  return 0;
}
