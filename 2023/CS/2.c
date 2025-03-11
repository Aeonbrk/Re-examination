/**
 * 给定一个英语文件，统计有多少不同单词及每个单词的数量。
 * 要求用结构数组完成，可以用 strcmp 函数判断字符串是否已存在。
 * ⭐⭐⭐
 */

// isalpha()
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_NUM 5000  // 最大不同单词数量
#define MAX_WORD_LEN 100   // 单词最大长度

typedef struct Word {
  char* word;
  int num;
} Word;

// 函数声明
// 这三个函数即使没时间实现也要把思想写明白
// 思考的完备性
int isWordExist(Word words[], int count, char* newWord);
void toLowerCase(char* str);
void removeNonAlpha(char* str);

int main() {
  char filename[100];
  printf("Enter the filename: ");
  scanf("%s", filename);

  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error opening file!\n");
    return 1;
  }

  Word words[MAX_WORD_NUM];
  int wordCount = 0;          // 不同单词的数量
  char buffer[MAX_WORD_LEN];  // 临时存储读取的单词

  // 初始化结构数组
  for (int i = 0; i < MAX_WORD_NUM; i++) {
    words[i].word = NULL;
    words[i].num = 0;
  }

  // 读取文件中的单词
  // 这也的读入形式也就意味着文件里的英文单词必须之间存在空格
  // 读入一个 string -> 以空格为分界线
  while (fscanf(file, "%s", buffer) == 1 && wordCount < MAX_WORD_NUM) {
    // 处理单词，转为小写并移除非字母字符
    toLowerCase(buffer);
    removeNonAlpha(buffer);

    // 跳过空字符串
    if (strlen(buffer) == 0) {
      continue;
    }

    // 检查单词是否已存在
    int index = isWordExist(words, wordCount, buffer);

    if (index != -1) {
      // 单词已存在，增加计数
      words[index].num++;
    } else {
      // 添加新单词
      words[wordCount].word = (char*)malloc(strlen(buffer) + 1);
      if (words[wordCount].word == NULL) {
        printf("Memory allocation failed!\n");
        break;
      }
      strcpy(words[wordCount].word, buffer);
      words[wordCount].num = 1;
      wordCount++;
    }
  }

  // 关闭文件
  fclose(file);

  // 输出结果
  printf("Total unique words: %d\n", wordCount);
  printf("Word frequencies:\n");
  for (int i = 0; i < wordCount; i++) {
    printf("%s: %d\n", words[i].word, words[i].num);
  }

  // 释放动态分配的内存
  for (int i = 0; i < wordCount; i++) {
    free(words[i].word);
  }

  return 0;
}

/**
 * 检查单词是否已存在于结构数组中
 *
 * @param words 单词结构数组
 * @param count 当前单词数量
 * @param newWord 待检查的新单词
 * @return 若存在，返回索引；否则返回-1
 */
int isWordExist(Word words[], int count, char* newWord) {
  for (int i = 0; i < count; i++) {
    if (strcmp(words[i].word, newWord) == 0) {
      return i;
    }
  }
  return -1;
}

/**
 * 将字符串转换为小写
 *
 * @param str 需要转换的字符串
 */
void toLowerCase(char* str) {
  for (int i = 0; str[i]; i++) {
    str[i] = tolower(str[i]);
  }
}

/**
 * 移除字符串中的非字母字符
 *
 * @param str 需要处理的字符串
 */
void removeNonAlpha(char* str) {
  int i, j = 0;
  for (i = 0; str[i]; i++) {
    if (isalpha(str[i])) {
      str[j++] = str[i];
    }
  }
  str[j] = '\0';
}
