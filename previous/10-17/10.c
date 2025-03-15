// 删除输入的字符串中的大小写字母和数字，并统计有重复的字符及其重复次数

// 删除字符串中的英文和数字并将重复字符减为一个

// 写一个函数，将一个字符串中的元音字母复制到另一个字符串，然后输出

#include <ctype.h>
#include <stdio.h>
#include <string.h>

// 函数声明
void removeAlphaNum(char *str);
void removeDuplicates(char *str);
void copyVowels(const char *source, char *dest);
int isVowel(char c);

int main() {
  char str[100], result[100];
  int choice;

  printf("Choose function to execute (1-3): ");
  scanf("%d", &choice);
  getchar();  // 清除输入缓冲区中的换行符

  printf("Enter a string: ");
  fgets(str, sizeof(str), stdin);
  str[strcspn(str, "\n")] = '\0';  // 移除换行符

  switch (choice) {
    case 1:
      // 第一个功能：删除字母和数字并统计重复字符
      removeAlphaNum(str);
      break;
    case 2:
      // 第二个功能：删除字母和数字并移除重复字符
      removeDuplicates(str);
      break;
    case 3:
      // 第三个功能：复制元音字母
      copyVowels(str, result);
      printf("Vowels extracted: %s\n", result);
      break;
    default:
      printf("Invalid choice!\n");
  }

  return 0;
}

// 函数1：删除大小写字母和数字，并统计重复字符
void removeAlphaNum(char *str) {
  char filtered[200] = "";
  int counts[256] = {0};  // 用于计数每个字符出现的次数
  int j = 0;

  // 过滤字母和数字
  for (int i = 0; str[i]; i++) {
    // isalnum()
    if (!isalnum(str[i])) {  // 如果不是字母或数字
      filtered[j++] = str[i];
      counts[(unsigned char)str[i]]++;  // 统计字符
    }
  }
  filtered[j] = '\0';

  // 输出过滤后的字符串
  printf("After removing alphanumeric characters: %s\n", filtered);

  // 输出重复字符及次数
  printf("Repeated characters:\n");
  for (int i = 0; i < 256; i++) {
    if (counts[i] > 1) {
      printf("'%c' appears %d times\n", i, counts[i]);
    }
  }
}

// 函数2：删除字母和数字，并将重复字符减为一个
void removeDuplicates(char *str) {
  char filtered[200] = "";
  char result[200] = "";
  int j = 0;

  // 过滤字母和数字
  for (int i = 0; str[i]; i++) {
    if (!isalnum(str[i])) {
      filtered[j++] = str[i];
    }
  }
  filtered[j] = '\0';

  // 移除重复字符
  int k = 0;
  for (int i = 0; filtered[i]; i++) {
    // 检查当前字符是否已存在于结果中
    int found = 0;
    for (int j = 0; j < k; j++) {
      if (result[j] == filtered[i]) {
        found = 1;
        break;
      }
    }

    if (!found) {
      result[k++] = filtered[i];
    }
  }
  result[k] = '\0';

  printf("After removing alphanumeric characters and duplicates: %s\n", result);
}

// 函数3：判断字符是否为元音字母
int isVowel(char c) {
  c = tolower(c);
  return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

// 函数3：将源字符串中的元音字母复制到目标字符串
void copyVowels(const char *source, char *dest) {
  int j = 0;

  for (int i = 0; source[i]; i++) {
    if (isVowel(source[i])) {
      dest[j++] = source[i];
    }
  }
  dest[j] = '\0';
}
