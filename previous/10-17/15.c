#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义函数：将 file1.doc 的内容复制到 file2.doc
// 中，并在每一行前加上行号（格式：行号*）， 同时返回 file1.doc
// 中除空格外的字符总数
int copyFileWithLineNumber(const char *sourceFile, const char *destFile) {
  // 打开源文件，采用只读模式
  FILE *src = fopen(sourceFile, "r");
  if (src == NULL) {
    printf("Error opening source file.\n");
    return -1;
  }
  // 打开目标文件，采用写模式
  FILE *dest = fopen(destFile, "w");
  if (dest == NULL) {
    printf("Error opening destination file.\n");
    fclose(src);
    return -1;
  }

  int nonSpaceCount = 0;  // 用于记录除空格外的字符数
  char buffer[1024];      // 用于存放每行读取的数据
  int lineNum = 1;        // 行号初始化

  // 循环逐行读取源文件内容
  while (fgets(buffer, sizeof(buffer), src) != NULL) {
    // 遍历当前行的所有字符，统计除空格外的字符数
    for (int i = 0; buffer[i] != '\0'; i++) {
      if (buffer[i] != ' ') {
        nonSpaceCount++;
      }
    }
    // 将行号和“*”前缀写入目标文件，然后写入该行原始内容
    fprintf(dest, "%d*%s", lineNum, buffer);
    lineNum++;
  }

  // 关闭文件
  fclose(src);
  fclose(dest);

  // 返回除空格外的字符总数
  return nonSpaceCount;
}

int main() {
  // ----------------- 问题一 -----------------
  // 有一篇文章，共有 4 行文章，每行有 60 个字符，
  // 统计其中的英文大写字母、小写字母、数字、空格及其他字符的个数。

  // 定义各类字符计数器
  int uppercase = 0, lowercase = 0, digit = 0, space = 0, other = 0;

  // 打开文件读取文章内容
  FILE *articleFile = fopen("article.txt", "r");
  if (articleFile == NULL) {
    printf("Error opening article file. Using default text instead.\n");

    // 如果文件打开失败，使用默认的文章数组
    char article[4][61] = {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123"
        "4567",  // 26大写 +26小写+8数字=60字符
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ7654"
        "3210",  // 26小写+26大写+8数字=60字符
        "1234567890 abcdefghijklmnopqrstuvwxyz "
        "ABCDEFGHIJKLMNOPQRSTUV",  // 11+27+22=60字符
        " !@#$%^&*()_+-=[]{}|;:',.<>/"
        "?`~ABCDEFGHIJKLMNOPQRSTUVWXYZabc"  // 1+30+26+3=60字符
    };

    // 遍历文章的每一行和每个字符进行统计
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 60; j++) {
        char ch = article[i][j];
        if (ch >= 'A' && ch <= 'Z') {
          uppercase++;
        } else if (ch >= 'a' && ch <= 'z') {
          lowercase++;
        } else if (ch >= '0' && ch <= '9') {
          digit++;
        } else if (ch == ' ') {
          space++;
        } else {
          other++;
        }
      }
    }
  } else {
    // 从文件中读取并统计字符
    char buffer[61];  // 每行60个字符加上'\0'
    int lineCount = 0;

    while (fgets(buffer, sizeof(buffer), articleFile) != NULL &&
           lineCount < 4) {
      // 去掉可能的换行符
      buffer[strcspn(buffer, "\n")] = '\0';

      // 确保每行恰好有60个字符
      int len = strlen(buffer);
      if (len > 60) {
        buffer[60] = '\0';  // 截断过长的行
      }

      // 统计字符
      for (int j = 0; buffer[j] != '\0' && j < 60; j++) {
        char ch = buffer[j];
        if (ch >= 'A' && ch <= 'Z') {
          uppercase++;
        } else if (ch >= 'a' && ch <= 'z') {
          lowercase++;
        } else if (ch >= '0' && ch <= '9') {
          digit++;
        } else if (ch == ' ') {
          space++;
        } else {
          other++;
        }
      }

      lineCount++;
    }

    fclose(articleFile);

    // 如果文件行数少于4行，提示用户
    if (lineCount < 4) {
      printf("Warning: Article file has fewer than 4 lines (%d lines read).\n",
             lineCount);
    }
  }

  // 使用 printf 输出结果，输出语言为英文
  printf("Uppercase letters: %d\n", uppercase);
  printf("Lowercase letters: %d\n", lowercase);
  printf("Digits: %d\n", digit);
  printf("Spaces: %d\n", space);
  printf("Other characters: %d\n", other);

  // ----------------- 问题二 -----------------
  // 将 file1.doc 的内容复制到 file2.doc 中，并在 file2.doc
  // 的每一行前添加行号（格式：行号*）， 最后返回 file1.doc
  // 中（不包括空格）的字符个数。

  // 为了测试，首先创建一个 sample file1.doc，并写入示例内容
  FILE *f1 = fopen("file1.doc", "w");
  if (f1 == NULL) {
    printf("Error creating file1.doc\n");
    return 1;
  }
  // 写入多行示例内容，每行结尾加换行符
  fprintf(f1, "This is the first line.\n");
  fprintf(f1, "Second line with numbers 123456.\n");
  fprintf(f1, "Third line, with punctuation!\n");
  fclose(f1);

  // 调用函数完成复制操作，并获取 file1.doc 中除空格外的字符数
  int count = copyFileWithLineNumber("file1.doc", "file2.doc");
  if (count >= 0) {
    printf("Non-space character count in file1.doc: %d\n", count);
  }

  return 0;
}
