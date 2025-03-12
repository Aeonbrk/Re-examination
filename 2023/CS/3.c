/**
 * 用一个结构体来存储学生姓名、学号、分数三个信息。
 * 用冒泡进行成绩从低到高排序。
 * 用折半查找分数为543的学生信息。
 * 读入考生名字、编号、成绩。冒泡按成绩排序，然后输出成绩为x的所有考生信息。
 */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_STUDENT_NUMBER 1000
#define MAX_NAME_LENGTH 50
#define MAX_ID_LENGTH 20
#define MAX_SAME_SCORE 20

typedef struct Student {
  char name[MAX_NAME_LENGTH];
  char ID[MAX_ID_LENGTH];
  int score;
} Student;

Student students[MAX_STUDENT_NUMBER];
char* filename = "./students.txt";
int count = 0;

void init() {
  // 初始化结构体
  for (int i = 0; i < MAX_STUDENT_NUMBER; i++) {
    students[i].name[0] = '\0';
    students[i].ID[0] = '\0';
    students[i].score = 0;
  }

  // 读入数据
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error opening file!\n");
    return;
  }

  // 字符串数组变量本身就是首地址，不需要 &
  char line[100];  // Buffer to read each line
  while (fgets(line, sizeof(line), file)) {
    // 跳过空行
    if (line[0] == '\n' || line[0] == '\0') {
      continue;
    }

    // 读入数据
    // 如果成功，fscanf 返回成功读取并匹配的输入项的数量。
    // 如果到达文件末尾或发生读取错误，返回 EOF。
    // sscanf 类似，但是读入对象变为字符串 -> 自己跳过空格
    if (sscanf(line, "%s %s %d", students[count].name, students[count].ID,
               &students[count].score) == 3) {
      count++;
      if (count >= MAX_STUDENT_NUMBER) {
        break;
      }
    }
  }

  // 千万不要忘记
  fclose(file);
}

// 数组类型的冒泡排序，和2024（3）结合着看
// 这个就是传统的双循环冒泡
void bubbleSort() {
  for (int i = 0; i < count - 1; i++) {
    for (int j = 0; j < count - i - 1; j++) {
      if (students[j].score > students[j + 1].score) {
        Student temp = students[j];
        students[j] = students[j + 1];
        students[j + 1] = temp;
      }
    }
  }
}

void binarySearch(int targetScore) {
  // count == 97
  int left = 0, right = count - 1;
  while (left <= right) {
    // #include math.h
    // 或者是 left + (right - left) / 2
    int mid = floor(left + right) / 2;
    if (students[mid].score == targetScore) {
      printf("Found student: %s %s %d\n", students[mid].name, students[mid].ID,
             students[mid].score);
      return;
    } else if (students[mid].score < targetScore) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  printf("\n\nStudent with score %d not found.\n", targetScore);
}

int main() {
  init();
  bubbleSort();

  for (int i = 0; i < count; i++) {
    printf("%-15s  %-10s  %-4d\n", students[i].name, students[i].ID,
           students[i].score);
  }

  printf("Search Process:\n");
  binarySearch(543);
}
