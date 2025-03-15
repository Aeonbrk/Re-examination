// 将数组中的元素排序，并求出其中位数
#include <stdio.h>
#include <stdlib.h>

int main() {
  float arr[100];  // arr 可能不够用，需要用动态内存

  int i, j, n, m;
  float k;  // // 错误语句 -> int k;
  scanf("%d", &n);

  // float* arr = (float*)malloc(sizeof(float) * n);

  for (i = 0; i < n; ++i) {
    scanf("%f", &arr[i]);
  }

  for (i = 0; i < n; ++i) {
    for (j = 0; j < n - i;
         ++j) {  // 错误语句 -> for (j = 0; j < n - i - 1; ++j)
      if (arr[j] > arr[j + 1]) {
        k = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = k;
      }
    }
  }

  m = (n + 1) / 2 - 1;
  printf("the Medians is %f\\n", arr[m]);
  return 0;
}

/*
功能：给数组 a 从 1 到 n 随机赋值，并且无重复值
时间复杂度：O(n^2)
缺点：时间复杂度过高
改进：使用哈希表替代 for 循环
int b[n];
int count = b[a[i]]++;
if(count>1)
  i--;
*/
for (int i = 0; i < n + i) {
  a[i] = randint(1, n);

  for (int j = 0; j < i + j) {
    if (a[j] == a[i]) {
      i--;
    }
  }
}

/*
功能：给数组 a 从 1 到 n 随机赋值，并且无重复值
时间复杂度：O(n²)
缺点：时间复杂度，tag[a[i]]=1
改进：使用哈希表替代 for 循环
int b[n];
int count = b[a[i]]++;
if(count>1)
  i--;
*/
for (i = 0; i < n; i++) {
  a[i] = i + 1;
  for (j = 0; j < n; j++) swap(a[rand(0, n - 1)], a[rand(0, n - 1)]);
}

/*
功能：给数组 a 赋值并随机交换数组 a 任意两个值位置 时间复杂度：O(n²)
缺点：a 数组赋值还没完成就开始随机交换数值，容易使得里面的 0 值交换而无意义
改进：
for (i = 0; i < n; i++) a[i] = i + 1;
for (i = 0; i < n - 1; i++) {
  int j = rand(i, n - 1);
  swap(a[i], a[j]);
}
*/
int tag[100] = {0};

for (int i = 0; i < n; ++i) {
  a[i] = randint(1, n);

  for (int j = 0; j < i; ++j) {
    if (tag[a[i]] == 1) {
      i--;
    } else {
      tag[a[i]] = 1;
    }
  }
}
