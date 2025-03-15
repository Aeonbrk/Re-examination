#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 问题一：比较两个18位身份证号码的出生日期先后
 * 身份证的第7至14位数字代表出生日期（格式为YYYYMMDD）
 */
void compareIDBirthdate() {
  char id1[25], id2[25];
  // 提示用户输入两个18位身份证号码
  printf("Please enter the first 18-digit ID number: ");
  scanf("%s", id1);
  printf("Please enter the second 18-digit ID number: ");
  scanf("%s", id2);

  // 检查输入长度是否为18位
  if (strlen(id1) != 18 || strlen(id2) != 18) {
    printf("One of the ID numbers is not 18 digits long.\n");
    return;
  }

  // 提取身份证号码中的出生日期字符串（下标6到13，共8位）
  char birth1[9], birth2[9];
  strncpy(birth1, id1 + 6, 8);
  birth1[8] = '\0';
  strncpy(birth2, id2 + 6, 8);
  birth2[8] = '\0';

  // 直接比较出生日期字符串（YYYYMMDD格式，字符串比较即可）
  int cmp = strcmp(birth1, birth2);
  if (cmp < 0)
    printf("The first ID's birthdate is earlier.\n");
  else if (cmp > 0)
    printf("The second ID's birthdate is earlier.\n");
  else
    printf("Both IDs have the same birthdate.\n");
}

/**
 * 问题二：质因数分解
 * 将输入的一个数进行质因数分解，例如输入90，输出格式：90=2*3*3*5
 */
void primeFactorization() {
  int num, original;
  printf("Please enter an integer to factorize: ");
  scanf("%d", &num);
  original = num;
  if (num <= 1) {
    printf("%d cannot be factorized into prime factors in the usual way.\n",
           num);
    return;
  }
  printf("%d=", original);
  int first = 1;  // 标志位，用于控制输出格式，不在第一个因子前加乘号
  // 从2开始进行因数分解
  for (int i = 2; i <= num; i++) {
    while (num % i == 0) {
      if (first) {
        printf("%d", i);
        first = 0;
      } else {
        printf("*%d", i);
      }
      num /= i;
    }
  }
  printf("\n");
}

/**
 * 问题三：利用递归方法找出数组中的最大值和最小值
 * 函数原型：MinMaxValue(arr, n, &max, &min)
 * 其中 arr 是数组，n 是数组元素的个数，max、min 分别为输出的最大值和最小值
 */
void MinMaxValue(int arr[], int n, int *max, int *min) {
  // 基本情况：数组中只有一个元素
  if (n == 1) {
    *max = *min = arr[0];
    return;
  }
  // 基本情况：数组中只有两个元素
  if (n == 2) {
    if (arr[0] > arr[1]) {
      *max = arr[0];
      *min = arr[1];
    } else {
      *max = arr[1];
      *min = arr[0];
    }
    return;
  }
  // 递归分治法：将数组分为两部分
  int mid = n / 2;
  int max1, min1, max2, min2;
  // 递归求左半部分的最大值和最小值
  MinMaxValue(arr, mid, &max1, &min1);
  // 递归求右半部分的最大值和最小值
  MinMaxValue(arr + mid, n - mid, &max2, &min2);

  *max = (max1 > max2) ? max1 : max2;
  *min = (min1 < min2) ? min1 : min2;
}

/**
 * 辅助函数，用于输入数组并调用递归函数找出最大值和最小值
 */
void arrayMinMax() {
  int n;
  printf("Please enter the number of elements in the array: ");
  scanf("%d", &n);
  if (n <= 0) {
    printf("Invalid number of elements.\n");
    return;
  }
  int *arr = (int *)malloc(n * sizeof(int));
  if (arr == NULL) {
    printf("Memory allocation failed.\n");
    return;
  }
  printf("Please enter %d integers:\n", n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  int max, min;
  MinMaxValue(arr, n, &max, &min);
  printf("The maximum value is %d, and the minimum value is %d.\n", max, min);
  free(arr);
}

/**
 * 问题四：判断一个数是否为素数的函数
 * 若为素数，返回1；否则返回0
 */
int isPrime(int n) {
  if (n < 2) return 0;
  // 从2开始到 sqrt(n) 检查是否存在因子
  for (int i = 2; i <= sqrt(n); i++) {
    if (n % i == 0) return 0;
  }
  return 1;
}

/**
 * 辅助函数：输入一个整数，调用 isPrime 函数判断是否为素数
 */
void checkPrime() {
  int n;
  printf("Please enter an integer to check for prime: ");
  scanf("%d", &n);
  if (isPrime(n))
    printf("%d is a prime number.\n", n);
  else
    printf("%d is not a prime number.\n", n);
}

/**
 * 主函数：依次调用所有问题的函数
 */
int main() {
  // 问题一：比较两个身份证号的出生日期
  printf("Problem 1: ID Birthdate Comparison\n");
  compareIDBirthdate();
  printf("\n");

  // 问题二：质因数分解
  printf("Problem 2: Prime Factorization\n");
  primeFactorization();
  printf("\n");

  // 问题三：利用递归方法求数组的最大值和最小值
  printf("Problem 3: Recursive Min and Max of an Array\n");
  arrayMinMax();
  printf("\n");

  // 问题四：判断素数
  printf("Problem 4: Prime Number Check\n");
  checkPrime();
  printf("\n");

  return 0;
}
