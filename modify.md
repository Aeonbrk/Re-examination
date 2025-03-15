# C 语言代码问题与修改笔记

## 问题一：字符串交换函数

### 原始代码

```c
void swap(char* pa, char* pb) {
  char* temp;
  temp = pa;
  pa = pb;
  pb = temp;
}
```

**解释**：

1. 原始代码只是交换了两个指针的值，并没有交换指针所指向的字符串内容。
   1. 于是要注意是值传递还是地址传递

### 修改后代码

```c
void swap(char* pa, char* pb) {
  char temp[100];
  // 字符串的交换、复制等都要使用 strncpy 函数
  strcpy(temp, pa);
  strcpy(pa, pb);
  strcpy(pb, temp);
}
```

**解释**：

1. 修改后的代码使用 `strcpy` 函数将两个字符串的内容进行交换，确保实际字符串内容被交换。

---

## 问题二：字符串操作

### 原始代码

```c
char pa[] = "ABCDE";  // 应该修改为 pa[100]
char* pb = "EFG";
// 或者改为 char pb[] = "EFG"; 字符数组
// 或者是动态内存分配 char* pb = malloc(4); strcpy(pb, "EFG");
pb[1] = 'A';  // pb 指向的内容是常量，不能修改 -> 字符串字面量的不可变性
pb = pa;
strcpy(pa, "ABCDEFGXYZ");  // pa 指向内存空间不够
pb = "D";
```

**解释**：

1. `char* pb = "EFG";` 定义了一个指向字符串字面量的指针，字符串字面量是常量，不可修改。
2. `pb[1] = 'A';` 试图修改常量字符串，会导致未定义行为。
3. `strcpy(pa, "ABCDEFGXYZ");` 试图将超过 `pa` 初始分配空间的字符串复制到 `pa` 中，会导致内存溢出。
   1. 所以最好使用 `strncpy()` 函数来规定复制的字符个数
   2. `char * strncpy ( char * destination, const char * source, size_t num );`
      1. 将源字符串的前 num 个字符复制到目标字符串。如果在复制完 num 个字符之前找到源 C 字符串的末尾（由空字符标识），则目标字符串将用零填充，直到总共写入 num 个字符为止。

4. 正确的做法是使用字符数组或动态内存分配。

---

## 问题三：字符串字面量的不可修改性

### 原始代码

```c
char a[] = "House";
char* b = "House";
a[2] = 'r';
b = a;
b[2] = 'r';  // 字符串字面量的不可修改性
```

**解释**：

1. `char* b = "House";` 定义了一个指向字符串字面量的指针，字符串字面量是常量，不可修改。
2. `b[2] = 'r';` 试图修改常量字符串，会导致未定义行为。

### 修改后代码

```c
char a[] = "House";  // 可修改的字符数组
char* b = a;         // 将指针 b 指向数组 a
a[2] = 'r';          // 直接修改数组 a
b[2] = 'r';          // 通过指针 b 修改数组 a
```

**解释**：

1. 修改后的代码将 `b` 指向可修改的字符数组 `a`，从而避免了修改常量字符串的问题。
   1. 或者改为 `char b[] = "House";`

---

## 问题四：内存管理

### 原始代码

```c
p = malloc(sizeof(int) * 10);
q = malloc(sizeof(int) * 20);
p = q;
free(p);
free(q);
```

**解释**：

1. `malloc` 返回的是 `void*` 类型需要显式的类型转换。
2. `p = q;` 导致 `p` 指向 `q` 分配的内存，而 `p` 原先分配的内存已经，会造成内存泄漏。

### 修改后代码

```c
p = (int*)malloc(sizeof(int) * 10);
q = (int*)malloc(sizeof(int) * 20);
p = q;
free(p);
```

**解释**：

1. 添加了显示的类型转换。
2. 修改后的代码只释放 `p` 指向的内存，避免了内存泄漏和重复释放的问题。

---

## 问题五：字符串反转

### 原始代码

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
  char* src = "hello, world";
  char *dest, *d, *p;
  int len, i;
  len = strlen(src);
  dest = (char*)malloc(len);
  p = src[len];
  d = dest;
  while (len-- != 0) d++ = p--;
  printf("%s", dest);
}
```

**解释**：

1. `dest = (char*)malloc(len);` 只分配了 `len` 个字节，没有考虑到字符串的结尾需要一个额外的字节来存储 `\0`。
2. `p = src[len];` 错误地将 `p` 指向了字符串的末尾（`\0`），导致后续操作错误。
3. `d++ = p--;` 的操作顺序是错误的。

### 修改后代码

```c
void main() {
  char* src = "hello, world";
  char *dest, *d, *p;
  int len, i;
  len = strlen(src);
  dest = (char*)malloc(sizeof(char) * (len + 1));
  p = &src[len - 1];
  d = dest;
  while (len-- != 0) *(d++) = *(p--);
  *d = '\0';
  printf("%s", dest);
}
```

**解释**：

1. `dest = (char*)malloc(sizeof(char) * (len + 1));` 分配了 `len + 1` 个字节，确保有足够的空间存储字符串及其结尾的 `\0`。
2. `p = &src[len - 1];` 将 `p` 指向字符串的最后一个字符，而不是字符串的末尾（`\0`），以便正确进行反转操作。
3. `*(d++) = *(p--);` 先将 `p` 指向的字符赋值给 `d` 指向的位置，然后 `p` 自减，`d` 自加，实现字符串的反转。
4. `*d = '\0';` 在反转后的字符串末尾添加 `\0`，确保字符串正确终止。

---

## 问题六：字符串复制

### 原始代码

```c
void main() {
  char data[] = "There are some mistakes in the program";
  char* point;
  char array[30];
  int i, length;
  length = 0;
  while (data[length] != '\0') length++;
  for (i = 0; i < length; i++, point++) *point = data[i];
  array = point;
  printf("%s\n", array);
}
```

**解释**：

1. `array = point;` 试图将指针赋值给数组，这是非法的。**数组名是一个常量指针，不能被重新赋值**。
2. `point` 未初始化，导致未定义行为。在 `for` 循环中使用未初始化的指针 `point` 会导致程序崩溃或不可预测的结果。

### 修改后代码

```c
void main() {
  char data[] = "There are some mistakes in the program";
  char* point;
  char array[100];
  int i, length;
  length = 0;
  while (data[length] != '\0') {
    length++;
  }
  point = array;
  for (i = 0; i <= length; i++, point++) {
    *point = data[i];
  }
  printf("%s\n", array);
}
```

**解释**：

1. 修改后的代码正确地将字符串复制到 `array` 中，并确保终止符 `\0` 被复制。`point` 被初始化为指向 `array` 的起始位置，确保复制操作从正确的内存地址开始。
2. `array` 的大小被增大到 100，以避免潜在的缓冲区溢出问题。
3. `for` 循环的条件改为 `i <= length`，确保字符串的终止符 `\0` 也被复制到 `array` 中，从而保证 `printf` 输出正确。

---

## 问题七：Eratosthenes 筛选法求素数

### 原始代码

```c
#include <stdio.h>
void main() {
  int prime[201] = {0};
  int d, i;
  for (d = 2;d < 200; d++)
    if (prime[d] == 0)
      for (k = d + 1; k <= 200; k++)
        if (k % d == 0) prime[k] = 1;
  for (i = 2; i <= 200; i++)
    if(prime[i]==0)
      printf("%d\t", i);
}
```

**解释**：

1. 原始代码的效率较低，因为内层循环从 `d + 1` 开始，且每次检查 `k % d == 0`。这种方法虽然能够正确筛选出素数，但时间复杂度较高，尤其是在处理较大范围的数时。

### 修改后代码

```c
for (d=2; d*d < 200; d++)
  if (prime[d] == 0)
    for (k = 2*d; k<=200; k = k+d)
      prime[k]=1;
```

**解释**：

1. 修改后的代码优化了筛选过程，内层循环从 `2*d` 开始，并以 `d` 为步长，提高了效率。这种方法减少了不必要的计算，因为对于每个素数 `d`，其倍数 `2*d, 3*d, 4*d, ...` 都是合数，可以直接标记为合数，而不需要逐个检查。
1. 此外，外层循环的条件改为 `d*d < 200`，这是因为如果 `d` 的平方已经超过了 200，那么 `d` 的倍数已经在前面的循环中被标记过了，因此不需要再继续处理。这样进一步减少了循环次数，提高了代码的执行效率。

---

## 问题八：浮点数比较

### 原始代码

```c
// 输入 3.5，输出结果是什么？为什么？如何修改？
void main() {
  float d;
  scanf("%f", &d);
  if (d == 3.5)
    putchar('Y');
  else
    putchar('N');
}
```

**解释**：

1. 输出结果是 `N`
2. 因为浮点数在计算机中是以二进制形式存储的，存在精度问题。3.5 在二进制中无法精确表示，因此 `d == 3.5` 的判断可能会失败。即使输入的是 3.5，存储在 `d` 中的值可能是一个接近 3.5 的浮点数，但不完全等于 3.5，导致条件判断为假。

### 修改后代码

```c
#include <math.h>  // 包含 fabs 函数的头文件
#include <stdio.h>

// 使用浮点数比较的容差方法
void main() {
  float d;
  scanf("%f", &d);
  if (fabs(d - 3.5) < 0.00001)  // 设置一个很小的容差值
    putchar('Y');
  else
    putchar('N');
}
```

**解释**：

1. 输出结果是 `Y`（如果输入的是 3.5）
2. 使用 `fabs(d - 3.5) < 0.00001` 来判断浮点数是否相等，而不是直接使用 `==`。这种方法通过设置一个很小的容差值（如 0.00001），来判断两个浮点数是否在可接受的误差范围内相等。这样可以避免浮点数精度问题导致的判断错误。

---

## 问题九：字符串倒序

### 原始代码

```c
// 哪一行出错？怎么修改？
(1) #include <stdio.h>
(2) int main() {
(3) char *src = "HELLO,UESTC";
(4) char *dest = NULL;
(5) int len = strlen(src);
(6) dest = (char *)malloc(len);
(7) char *d = dest;
(8) char *s = &src[len];
(9) while ( len-- != 0 )
(10) *d++ = *s--;
(11) printf("%s\n", dest);
(12) return 0; }
```

**解释**：

1. 第6行代码中，`malloc(len)`分配的内存空间不足以存储字符串的末尾的空字符`\0`，这会导致`printf`函数在输出时无法正确识别字符串的结束位置，从而导致未定义行为。应该修改为`malloc(len + 1)`，以分配足够的空间来存储字符串及其结束符。
2. 第8行代码中，`char *s = &src[len];`将指针`s`指向了`src`字符串的末尾字符的下一个位置，这会导致在倒序复制时从错误的位置开始。应该修改为`char *s = &src[len - 1];`，使`s`指向`src`字符串的最后一个字符。
3. 第10行代码中，`*d++ = *s--;`将字符从`s`复制到`d`，但缺少在复制完成后添加字符串结束符`\0`。应该在循环结束后添加`*d = '\0';`，以确保`dest`字符串正确结束。

### 修改后代码

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *src = "HELLO,UESTC";
    char *dest = NULL;
    int len = strlen(src);
    dest = (char *)malloc(len + 1);  // 分配足够的内存空间，包括结束符
    char *d = dest;
    char *s = &src[len - 1];  // 指向src字符串的最后一个字符
    while (len-- != 0)
        *d++ = *s--;  // 倒序复制字符
    *d = '\0';  // 添加字符串结束符
    printf("%s\n", dest);
    free(dest);  // 释放动态分配的内存
    return 0;
}
```

**解释**：

1. 修改了第6行代码，将`malloc(len)`改为`malloc(len + 1)`，以确保分配的内存空间足够存储字符串及其结束符`\0`。
2. 修改了第8行代码，将`char *s = &src[len];`改为`char *s = &src[len - 1];`，使`s`指向`src`字符串的最后一个字符，以便正确进行倒序复制。
3. 在循环结束后添加了`*d = '\0';`，以确保`dest`字符串正确结束。
4. 添加了`free(dest);`，以释放动态分配的内存，避免内存泄漏。
   1. 这一点真的很容易漏掉欸

---

## 问题十：复制字符串

### 原始代码

```C
// // 哪一行出错？怎么修改？
(1) void fun() {
(2) char data[20] = "welcome to CHENGDU and UESTC";
(3) char *point;
(4) char array[200];
(5) int i, length = 0;
(6) point = array;
(7) while (data[length] != '0')
(8) length++;
(9) for (; i < length; i++) {
(10) *point = *data;
(11) point++;
(12) data++; }
(13) puts(data);
(14) free(data); }
```

**解释**：

1. **第2行**：`char data[20] = "welcome to CHENGDU and UESTC";`
   1. 这里定义了一个字符数组 `data`，大小为20，并初始化为字符串 "welcome to CHENGDU and UESTC"。然而，这个字符串的长度超过了20，会导致数组越界，应该将数组大小改为至少30（包括字符串末尾的`\0`）。
2. **第5行**：`int i, length = 0;`
   1. 变量 `i` 在后续的循环中使用，但没有初始化，可能会导致未定义行为。应该在声明时初始化 `i` 为0。
3. **第7行**：`while (data[length] != '0')`
   1. 这里应该是判断字符串结束符 `\0`，而不是字符 `'0'`。`'0'` 是字符0，而 `\0` 是字符串结束符。
4. **第10行**：`*point = *data;`
   1. 这里应该是将 `data[i]` 赋值给 `*point`，而不是 `*data`，因为 `data` 是一个数组，`*data` 始终指向数组的第一个元素。
5. **第12行**：`data++;`
   1. 这行代码会导致 `data` 指针移动，改变原始数组的起始位置，这不符合预期。应该直接使用 `data[i]` 来访问数组元素。
6. **第14行**：`free(data);`
   1. ``data` 是一个局部数组，不是通过 `malloc` 分配的，因此不能使用 `free` 释放。应该删除这行代码。

### 修改后代码

```c
// // 哪一行出错？怎么修改？
(1) void fun() {
(2) char data[100] = "welcome to CHENGDU and UESTC";
(3) char *point;
(4) char array[200];
(5) int i = 0, length = 0;
(6) point = array;
(7) while (data[length] != '\0')
(8) length++;
(9) for (; i < length; i++) {
(10) *point = data[i];
(11) point++;
(12) }
(13) puts(data);
(14) }
```

**解释**：

1. **第2行**：`char data[100] = "welcome to CHENGDU and UESTC";`
   1. 将数组大小改为100，确保有足够的空间存储字符串及其结束符。
2. **第5行**：`int i = 0, length = 0;`
   1. 初始化 `i` 为0，避免未定义行为。
3. **第7行**：`while (data[length] != '\0')`
   1. 修正为判断字符串结束符 `\0`，而不是字符 `'0'`。
4. **第10行**：`*point = data[i];`
   1. 使用 `data[i]` 来访问数组元素，避免指针移动。
5. **第12行**：删除 `data++;`
   1. 不再移动 `data` 指针，保持原始数组不变。
6. **第14行**：删除 `free(data);``
   1. ``data` 是局部数组，不需要释放。

