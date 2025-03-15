// 问题一
// 编写完整程序，采用结构数组和指向结构的指针，接收输入的 100 个学生信
// 息（包括学号和 C 语言课程期末总成绩），输出最高、最低成绩和分别对应的
// 学号（可能有多个同学都是最高分，可能有多个同学都是最低分）

// 问题二
// 编写完整程序：利用 2 个函数对输入的两个分数进行加、减、乘、除四则运
// 算和输出用分数表示的结果。（注：输入格式为：%ld/%ld%c%ld/%ld，输出格式
// 为%ld/%ld），例如：输 入 1/4+1/3，输出：7/12

#include <stdio.h>
#include <stdlib.h>

// 问题一：学生结构定义
typedef struct {
  long id;      // 学号
  float score;  // C语言成绩
} Student;

// 问题二：分数结构定义
typedef struct {
  long numerator;    // 分子
  long denominator;  // 分母
} Fraction;

// 问题一：处理学生成绩的函数
void processStudentScores() {
  Student students[100];    // 学生数组
  Student *ptr = students;  // 指向学生结构的指针
  int n, i;
  float maxScore = 0, minScore = 100;

  // 输入学生数量
  printf("Enter number of students (max 100): ");
  scanf("%d", &n);
  if (n > 100) n = 100;  // 限制最大数量为100

  // 输入学生信息
  printf("Enter student ID and score for each student:\n");
  for (i = 0; i < n; i++) {
    printf("Student %d (ID Score): ", i + 1);
    scanf("%ld %f", &(ptr + i)->id, &(ptr + i)->score);

    // 更新最高分和最低分
    if ((ptr + i)->score > maxScore) {
      maxScore = (ptr + i)->score;
    }
    if ((ptr + i)->score < minScore) {
      minScore = (ptr + i)->score;
    }
  }

  // 输出最高分学生
  printf("\nHighest score: %.2f, IDs: ", maxScore);
  for (i = 0; i < n; i++) {
    if ((ptr + i)->score == maxScore) {
      printf("%ld ", (ptr + i)->id);
    }
  }

  // 输出最低分学生
  printf("\nLowest score: %.2f, IDs: ", minScore);
  for (i = 0; i < n; i++) {
    if ((ptr + i)->score == minScore) {
      printf("%ld ", (ptr + i)->id);
    }
  }
  printf("\n");
}

// 问题二：计算最大公约数
long gcd(long a, long b) {
  // 使用辗转相除法
  long temp;
  if (a < b) {
    temp = a;
    a = b;
    b = temp;
  }

  while (b != 0) {
    temp = a % b;
    a = b;
    b = temp;
  }
  return a;
}

// 问题二：分数化简函数
Fraction simplify(Fraction f) {
  // 处理负数情况
  if (f.denominator < 0) {
    f.numerator = -f.numerator;
    f.denominator = -f.denominator;
  }

  // 分子为0的情况
  if (f.numerator == 0) {
    f.denominator = 1;
    return f;
  }

  // 约分
  long d = gcd(labs(f.numerator), labs(f.denominator));
  f.numerator /= d;
  f.denominator /= d;

  return f;
}

// 问题二：分数计算函数
Fraction calculate(Fraction f1, Fraction f2, char op) {
  Fraction result;

  switch (op) {
    case '+':  // 加法：a/b + c/d = (a*d + b*c)/(b*d)
      result.numerator =
          f1.numerator * f2.denominator + f1.denominator * f2.numerator;
      result.denominator = f1.denominator * f2.denominator;
      break;

    case '-':  // 减法：a/b - c/d = (a*d - b*c)/(b*d)
      result.numerator =
          f1.numerator * f2.denominator - f1.denominator * f2.numerator;
      result.denominator = f1.denominator * f2.denominator;
      break;

    case '*':  // 乘法：a/b * c/d = (a*c)/(b*d)
      result.numerator = f1.numerator * f2.numerator;
      result.denominator = f1.denominator * f2.denominator;
      break;

    case '/':  // 除法：a/b ÷ c/d = (a*d)/(b*c)
      result.numerator = f1.numerator * f2.denominator;
      result.denominator = f1.denominator * f2.numerator;
      break;
  }

  return simplify(result);  // 返回化简后的结果
}

// 问题二：处理分数计算的函数
void fractionCalculator() {
  Fraction f1, f2, result;
  char op;

  printf("\nEnter two fractions with operation (e.g., 1/4+1/3): ");
  scanf("%ld/%ld%c%ld/%ld", &f1.numerator, &f1.denominator, &op, &f2.numerator,
        &f2.denominator);

  // 检查分母是否为0
  if (f1.denominator == 0 || f2.denominator == 0) {
    printf("Error: denominator cannot be zero.\n");
    return;
  }

  // 检查除法时除数是否为0
  if (op == '/' && f2.numerator == 0) {
    printf("Error: division by zero.\n");
    return;
  }

  // 计算结果
  result = calculate(f1, f2, op);

  // 输出结果
  printf("Result: %ld/%ld\n", result.numerator, result.denominator);
}

int main() {
  int choice;

  printf("Select problem to solve:\n");
  printf("1. Student Score Processing\n");
  printf("2. Fraction Calculator\n");
  printf("Enter choice (1 or 2): ");
  scanf("%d", &choice);

  if (choice == 1) {
    processStudentScores();
  } else if (choice == 2) {
    fractionCalculator();
  } else {
    printf("Invalid choice.\n");
  }

  return 0;
}
