#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// 计算级数：sum = 1 - x + (x^2/2!) + ... + ((-1)^n)*(x^n/n!)
double calculateSeries1(double x, int n) {
  double sum = 0;
  double term = 1;
  int i;

  // 逐项计算并累加
  for (i = 0; i <= n; i++) {
    sum += term;
    // 计算下一项
    term = term * (-x) / (i + 1);
  }

  return sum;
}

// 计算级数：sum = 1 + x - x^2/2! + x^3/3! - ... + (-1)^(n+1)*x^n/n!
double calculateSeries2(double x, int n) {
  double sum = 0;
  double term = 1;
  int i;

  // 逐项计算并累加
  for (i = 0; i <= n; i++) {
    sum += term;
    // 计算下一项，注意符号交替
    term = term * x / (i + 1) * (i % 2 == 0 ? -1 : 1);
  }

  return sum;
}

// 检查数字num中是否包含数字d
bool containsDigit(int num, int d) {
  // 当num为0时特殊处理
  if (num == 0) {
    return d == 0;
  }

  // 逐位检查
  while (num > 0) {
    if (num % 10 == d) {
      return true;
    }
    num /= 10;
  }

  return false;
}

// 寻找符合条件的数：该数和该数的平方中都含有输入的数字d
void findNumbersWithDigit(int d) {
  int i, square;

  printf(
      "Numbers from 1-100 that contain digit %d in both the number and its "
      "square:\n",
      d);

  // 遍历1-100
  for (i = 1; i <= 100; i++) {
    square = i * i;

    // 检查数字i和i的平方是否都包含数字d
    if (containsDigit(i, d) && containsDigit(square, d)) {
      printf("%d (square: %d)\n", i, square);
    }
  }
}

// 计算一个数的所有约数之和（不包括自身）
int factor(int j) {
  int sum = 1;  // 1总是所有数的约数
  int i;

  // 查找约数并求和
  for (i = 2; i <= sqrt(j); i++) {
    if (j % i == 0) {
      sum += i;
      // 如果i和j/i不同，则加上j/i
      if (i != j / i) {
        sum += j / i;
      }
    }
  }

  return sum;
}

// 查找互满数
void findAmicableNumbers(int limit) {
  int i, sum_i;

  printf("Amicable numbers within %d:\n", limit);

  // 从1开始遍历到limit
  for (i = 1; i < limit; i++) {
    sum_i = factor(i);

    // 确保i < sum_i以避免重复输出
    if (i < sum_i && sum_i <= limit && factor(sum_i) == i) {
      printf("(%d, %d)\n", i, sum_i);
    }
  }
}

int main() {
  double x;
  int n, d;

  // 计算级数1
  printf("Enter x and n for series 1 (1 - x + x^2/2! + ...): ");
  scanf("%lf %d", &x, &n);
  printf("Sum of series 1 = %lf\n\n", calculateSeries1(x, n));

  // 计算级数2
  printf("Enter x and n for series 2 (1 + x - x^2/2! + ...): ");
  scanf("%lf %d", &x, &n);
  printf("Sum of series 2 = %lf\n\n", calculateSeries2(x, n));

  // 查找包含特定数字的数
  printf("Enter a digit (0-9) to find numbers containing it: ");
  scanf("%d", &d);
  findNumbersWithDigit(d);
  printf("\n");

  // 查找互满数
  findAmicableNumbers(30000);

  return 0;
}
