# 分类总结

## 2024&2023

### **1. 数字处理与排序**

- **问题**：提取数字中的奇数位并按位权从小到大排序。
- **核心思路**：
  - 分解数字的每一位，筛选出奇数。

  ```C
  while (num > 0) {
    int digit = num % 10;
    if (digit % 2 != 0) {
      digits[count++] = digit;
    }
    num /= 10;
  }
  ```

  - 使用快速排序（`qsort`）对奇数位降序排列（因位权从小到大等价于数字从高位到低位降序）。

  ```c
  qsort(digits, count, sizeof(int), compare);

  int compare(const void *a, const void *b) {
    /**
     * *(int *)a 和 *(int *)b 是将 void * 类型的指针转换为 int *
    * 类型，并解引用得到实际的整数值
    */
    return (*(int *)b - *(int *)a);
  }
  ```

  - 重新组合排序后的数字。

### **2. 字符串处理**

- **问题1**：去除字符串中间部分的星号，保留首尾星号。
  - **核心思路**：
    - 遍历字符串，标记首部星号和非星号字符的位置。
      - 从前往后遍历
    - 单独处理尾部星号，最后拼接首尾星号和中间字母。
      - 从后往前遍历
- **问题2**：统计主字符串中子串的出现次数。
  - **核心思路**：
    - 暴力匹配法：遍历主字符串的每个可能的子串起始位置，逐字符比较是否完全匹配
      - 边界检查 `pattern_len == 0 || str_len < pattern_len -> return 0;`
      - 这个性价比最高

  ```c
  // 命令行输入一连串字符的最佳选择
  if (fgets(str, sizeof(str), stdin) == NULL) {
    fprintf(stderr, "Error: Failed to read input.\n");
    return EXIT_FAILURE;
  }

  // 去除换行符（fgets会保留输入中的换行符）
  str[strcspn(str, "\n")] = '\0';
  ```

### **3. 链表操作**

- **问题1**：单链表的冒泡排序（升序）。
  - **核心思路**：
    - 通过交换相邻节点的数据（而非节点本身），模拟冒泡排序过程。
    - 维护已排序部分的尾指针，减少遍历次数。
      - 使用传统数组那样的双层循环最傻瓜简单，但是循环次数肯定变多
- **问题2**：将链表中的指定节点移动到头部。
  - **核心思路**：
    - 遍历链表找到目标节点及其前驱。
    - 调整指针，将目标节点脱离原位置并链接到链表头部。

  ```c
  /* 将指定节点移动到链表头部 */
  LinkedList* liftToHead(LinkedList* cur, LinkedList* pre, LinkedList* L) {
    if (pre == NULL) return L;  // 已经是头节点，直接返回

    pre->next = cur->next;  // 前驱节点跳过当前节点
    cur->next = L;          // 当前节点指向原头节点
    return cur;             // 返回新头节点
  }

  /* 处理所有移动操作并更新链表 */
  void changeList(LinkedList* L_ptr, int index[], int num) {
    for (int i = 0; i < num; i++) {
      LinkedList* current = L_ptr;
      LinkedList* pre = NULL;

      // 遍历查找目标节点
      while (current != NULL && current->data != index[i]) {
        pre = current;
        current = current->next;
      }

      if (current != NULL) {  // 找到目标节点时更新链表
        L_ptr = liftToHead(current, pre, L_ptr);
        PrintList(L_ptr);  // 打印每次移动后的链表状态
      }
    }
  }
  ```

### **4. 图算法**

- **问题**：选择最优动物，使得最难变形的魔咒长度最短。

  - **核心思路**：
    - 对每个动物作为起点，使用 **Dijkstra 算法**计算到其他动物的最短路径。
    - 对每个起点，记录其最长最短路径，最终选择最长路径最小的动物。

  ```c
  int graph[MAX_ANIMAL_NUM][MAX_ANIMAL_NUM];  // 邻接矩阵存储图的边权 ->
                                              // 矩阵实现方便（直接包含边的权值）
  int distance[MAX_ANIMAL_NUM];               // 存储起点到各节点的最短距离
  bool visited[MAX_ANIMAL_NUM];               // 标记节点是否已访问
  int n, m;                                   // 顶点数和边数

  void dijkstra(int start_node) {
    // 初始化距离数组和访问标记
    for (int i = 1; i <= n; i++) {
      distance[i] = INF;
      visited[i] = false;
    }
    distance[start_node] = 0;  // 起点到自身距离为0

    // 遍历所有节点，每次找到一个最短路径节点
    for (int step = 1; step <= n; step++) {
      // 记录初始化默认
      int current_node = -1;
      int min_distance = INF;
      // 找到距离起点最近的节点作为当前处理节点 -> 一开始就是起点本身
      for (int node = 1; node <= n; node++) {
        // 若没被访问过并且距离小于最小路径
        if (!visited[node] && distance[node] < min_distance) {
          current_node = node;
          min_distance = distance[node];
        }
      }
      // 所有剩余节点不可达，提前结束
      if (current_node == -1) return;
      visited[current_node] = true;

      // 更新当前节点的邻居节点距离
      for (int neighbor = 1; neighbor <= n; neighbor++) {
        // 检查是否有从当前节点到邻居节点的边
        // 检查通过当前节点到达邻居节点是否比已知路径更短，如果是，更新到该邻居的最短距离
        if (!visited[neighbor] && graph[current_node][neighbor] != 0 &&
            distance[current_node] + graph[current_node][neighbor] <
                distance[neighbor]) {
          distance[neighbor] =
              distance[current_node] + graph[current_node][neighbor];
        }
      }
    }
  }
  ```

### **5. 排序与搜索**

- **问题1**：结构体数组的冒泡排序和折半查找。
  - **核心思路**：
    - 按成绩对结构体数组升序排列。
    - 使用二分查找在排序后的数组中快速定位目标成绩。
      - `int mid = floor(left + right) / 2;`
      - `int mid = left + (right - left) / 2;`
- **问题2**：统计文件中的不同单词及其频率。
  - **核心思路**：
    - 遍历文件，将单词标准化（小写化、去除非字母字符）。
    - 使用结构数组存储单词及其计数，通过遍历检查重复项。
- 统一涉及到文件操作

#### 1. **写入文件**

- **`fputc()`**: 写入单个字符到文件流。

     ```c
     int fputc(int c, FILE *fp);
     ```

  - 成功返回写入的字符，失败返回 `EOF`。
  - 示例：

       ```c
       FILE *fp = fopen("example.txt", "w");
       if (fp) {
           fputc('A', fp);
           fclose(fp);
       }
       ```

- **`fputs()`**: 写入字符串到文件流。

     ```c
     int fputs(const char *s, FILE *fp);
     ```

  - 成功返回非负值，失败返回 `EOF`。
  - 示例：

       ```c
       FILE *fp = fopen("example.txt", "w");
       if (fp) {
           fputs("Hello, World!\n", fp);
           fclose(fp);
       }
       ```

- **`fprintf()`**: 格式化写入字符串到文件流。

     ```c
     int fprintf(FILE *fp, const char *format, ...);
     ```

  - 示例：

       ```c
       FILE *fp = fopen("example.txt", "w");
       if (fp) {
           fprintf(fp, "Value: %d\n", 42);
           fclose(fp);
       }
       ```

---

#### 2. **读取文件**

- **`fgetc()`**: 从文件流中读取单个字符。

     ```c
     int fgetc(FILE *fp);
     ```

  - 返回读取的字符，失败返回 `EOF`。
  - 示例：

       ```c
       FILE *fp = fopen("example.txt", "r");
       if (fp) {
           int ch = fgetc(fp);
           printf("Read character: %c\n", ch);
           fclose(fp);
       }
       ```

- **`fgets()`**: 从文件流中读取一行字符串。

     ```c
     char *fgets(char *buf, int n, FILE *fp);
     ```

  - 读取最多 `n-1` 个字符，遇到换行符 `\n` 或文件末尾停止。
  - 示例：

       ```c
       FILE *fp = fopen("example.txt", "r");
       if (fp) {
           char buffer[100];
           fgets(buffer, sizeof(buffer), fp);
           printf("Read line: %s", buffer);
           fclose(fp);
       }
       ```

- **`fscanf()`**: 格式化读取数据。

     ```c
     int fscanf(FILE *fp, const char *format, ...);
     ```

  - 遇到第一个空格或换行符停止读取。
  - 示例：

       ```c
       FILE *fp = fopen("example.txt", "r");
       if (fp) {
           int num;
           fscanf(fp, "%d", &num);
           printf("Read number: %d\n", num);
           fclose(fp);
       }
       ```

---

#### 3. **二进制 I/O**

- **`fread()`**: 从文件中读取数据块。

     ```c
     size_t fread(void *ptr, size_t size_of_elements, size_t number_of_elements, FILE *fp);
     ```

  - 示例：

       ```c
       FILE *fp = fopen("data.bin", "rb");
       if (fp) {
           int arr[5];
           fread(arr, sizeof(int), 5, fp);
           for (int i = 0; i < 5; i++) {
               printf("%d ", arr[i]);
           }
           fclose(fp);
       }
       ```

- **`fwrite()`**: 向文件中写入数据块。

     ```c
     size_t fwrite(const void *ptr, size_t size_of_elements, size_t number_of_elements, FILE *fp);
     ```

  - 示例：

       ```c
       FILE *fp = fopen("data.bin", "wb");
       if (fp) {
           int arr[] = {1, 2, 3, 4, 5};
           fwrite(arr, sizeof(int), 5, fp);
           fclose(fp);
       }
       ```

---

## Previous

### 1-9

#### 1. **数字处理与排序**

- **问题**：输入混合整数和浮点数，分别按从大到小和从小到大排序后输出。
- **核心思路**：
  - 使用字符串分割区分整数和浮点数，分别存入数组。整数用降序快速排序，浮点数用升序快速排序，最后合并输出。
  - `strtok, strchr, atof, atoi`
    - **`strtok`**
      - **功能**: 将字符串按指定分隔符分割成子字符串（token）。
      - **特点**: `strtok` 会修改原始字符串，在分割时插入 `\0` 来标记每个 token 的结束，非线程安全。
    - **`strchr`**
      - **功能**: 在字符串中查找指定字符的首次出现位置。
      - **特点**: 返回指向该字符的指针，未找到返回 `NULL`。
    - **`atof`**
      - **功能**: 将字符串转换为浮点数（`double`）。
      - **特点**: 支持小数点和科学计数法，非法输入返回 `0.0`。
    - **`atoi`**
      - **功能**: 将字符串转换为整数（`int`）。
      - **特点**: 支持正负号，非法输入返回 `0`。

  ```c
  // 挺重要的字符处理
  // strtok 将字符串分割成多个子字符串
  char *token = strtok(str, " ");
  while (token != NULL) {
    // 判断是否为浮点数
    // strchr 在字符串中查找某个字符首次出现的位置
    if (strchr(token, '.') != NULL) {
      // 将字符串转换为浮点数
      num_float[count_float++] = atof(token);
    } else {
      // 将字符串转换为整数
      num_int[count_int++] = atoi(token);
    }
    token = strtok(NULL, " ");
  }
  ```

  ```c
  // 快排一定要会写，如果题目没有显式要求实现快排，在使用 qsort 替代
  void my_qsort(void *base, size_t num, size_t size,
                int (*compare)(const void *, const void *)) {
    if (num <= 1) return;  // 如果元素个数为 0 或 1，则无需排序

    // 定义左右指针
    char *left = (char *)base;
    char *right = (char *)base + (num - 1) * size;

    // 选择最右边的元素作为基准值
    char pivot[size];
    memcpy(pivot, right, size);

    // 分区过程
    char *i = left - size;
    char *j = right;
    while (1) {
      // 从左向右找到第一个大于等于 pivot 的元素
      do {
        i += size;
      } while (i < right && compare(i, pivot) < 0);

      // 从右向左找到第一个小于等于 pivot 的元素
      do {
        j -= size;
      } while (j > left && compare(j, pivot) > 0);

      // 如果指针相遇或交叉，则退出循环
      if (i >= j) break;

      // 交换 i 和 j 指向的元素
      char temp[size];
      memcpy(temp, i, size);
      memcpy(i, j, size);
      memcpy(j, temp, size);
    }

    // 将 pivot 放到正确的位置
    memcpy(right, i, size);
    memcpy(i, pivot, size);

    // 递归排序左右两部分
    size_t left_count = (i - left) / size;
    my_qsort(base, left_count, size, compare);                // 排序左半部分
    my_qsort(i + size, num - left_count - 1, size, compare);  // 排序右半部分
  }
  ```

#### 2. **数组与二分查找**

- **问题**：在循环有序数组中查找最小值。
- **核心思路**：
     二分法调整左右指针，比较中间元素与右边界元素。若中间值大于右边界，最小值在右侧；否则在左侧，逐步缩小范围。

  ```c
  /**
   * 在循环有序数组中找到最小值。
   *
   * @param nums  循环有序数组
   * @param n     数组长度
   * @return      数组中的最小值
   */
  int findMin(int nums[], int n) {
    int left = 0;
    int right = n - 1;

    while (left < right) {
      int mid = left + (right - left) / 2;

      if (nums[mid] > nums[right]) {
        // 最小值在右半部分（mid右侧）
        left = mid + 1;
      } else if (nums[mid] < nums[right]) {
        // 最小值在左半部分（包含mid）
        right = mid;
      } else {
        // 当nums[mid] == nums[right]时，无法确定最小值位置，缩小右边界
        right--;
      }
    }

    // 最终left和right相遇，返回该位置的元素
    return nums[left];
  }
  ```

#### 3. **链表操作**

- **问题**：逆序构建双向链表；删除链表最小值节点；合并递增链表为递减链表；移动最大值节点至末尾。

- **核心思路**：
  - **逆序构建**：头插法插入新节点，调整前驱指针。 --> 模拟一下
  - **删除最小值**：遍历链表记录最小值及其前驱，调整指针删除。
  - **合并链表**：头插法合并，每次取较小元素插入头部。

  ```c
  /**
   * 合并两个递增有序链表为一个递减有序链表
   * 思路: 采用头插法，每次将较小的节点插入到结果链表的头部
   * 我靠！头插法真的用的很多！！！
   *
   * @param La 第一个递增有序链表（带头结点）
   * @param Lb 第二个递增有序链表（带头结点）
   * @return 合并后的递减有序链表
   */
  node *Union(node *La, node *Lb) {
    // 边界条件检查
    if (La == NULL) return Lb;
    if (Lb == NULL) return La;

    node *p = La->next;  // La的数据节点
    node *q = Lb->next;  // Lb的数据节点
    node *temp;          // 临时节点指针

    La->next = NULL;  // 将La作为结果链表，初始化为空

    // 同时处理两个链表中的节点
    while (p && q) {
      if (p->data <= q->data) {
        // 取出p节点
        temp = p->next;
        // 头插法插入p
        p->next = La->next;
        La->next = p;
        // 继续处理p链表的下一个节点
        p = temp;
      } else {
        // 取出q节点
        temp = q->next;
        // 头插法插入q
        q->next = La->next;
        La->next = q;
        // 继续处理q链表的下一个节点
        q = temp;
      }
    }

    // 处理剩余节点
    if (q) p = q;  // 如果q还有剩余节点，将p指向q
    while (p) {
      temp = p->next;
      // 头插法插入剩余节点
      p->next = La->next;
      La->next = p;
      p = temp;
    }

    free(Lb);  // 释放Lb的头结点
    return La;
  }

  /**
   * 合并两个递增有序链表为一个递减有序链表（无头结点版本）
   * 思路: 采用头插法，每次将较小的节点插入到结果链表的头部
   *
   * @param La 第一个递增有序链表（无头结点）
   * @param Lb 第二个递增有序链表（无头结点）
   * @return 合并后的递减有序链表
   */
  node *Union(node *La, node *Lb) {
    if (La == NULL) return Lb;
    if (Lb == NULL) return La;

    node *result = NULL;  // 结果链表，初始为空
    node *p = La;         // 第一个链表的当前节点
    node *q = Lb;         // 第二个链表的当前节点
    node *temp;           // 临时节点指针

    // 同时处理两个链表中的节点
    while (p && q) {
      if (p->data <= q->data) {
        // 取出p节点
        // 因为当前节点得移动
        temp = p->next;
        // 头插法插入p到结果链表
        p->next = result;
        result = p;
        // 继续处理p链表的下一个节点
        p = temp;
      } else {
        // 取出q节点
        temp = q->next;
        // 头插法插入q到结果链表
        q->next = result;
        result = q;
        // 继续处理q链表的下一个节点
        q = temp;
      }
    }

    // 处理剩余节点
    node *remaining = p ? p : q;
    while (remaining) {
      temp = remaining->next;
      // 头插法插入剩余节点
      remaining->next = result;
      result = remaining;
      remaining = temp;
    }

    return result;  // 返回合并后的链表
  }
  ```

  - **移动最大值**：遍历找到最大值，交换数据或调整指针移至尾部。

#### 4. **集合运算与链表处理**

- **问题**：实现集合的添加、删除、并集、交集操作
- **核心思路**：
  - 用链表存储集合元素，添加时检查重复。并集遍历两个链表去重，交集遍历检查共同元素。
  - 很综合

```c
typedef struct Set {
  int numb;
  struct Set* next;
} Set;

// 判断元素是否在集合中
// 单纯的遍历
int isInSet(Set* head, int num) {
  Set* current = head->next;
  while (current != NULL) {
    if (current->numb == num) {
      return 1;  // 找到了该元素
    }
    current = current->next;
  }
  return 0;  // 没有找到该元素
}

// 向集合中添加元素（如果元素已存在则不添加）
void addToSet(Set* head, int num) {
  // 先检查元素是否已经存在于集合中
  if (isInSet(head, num)) {
    printf("%d is already in the set\n", num);
    return;
  }

  // 创建新节点
  Set* newNode = (Set*)malloc(sizeof(Set));
  if (newNode == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }
  newNode->numb = num;

  // 插入到链表头部（头插法）
  // 题目没有要求，而对于单链表来说头插明显方便
  newNode->next = head->next;
  head->next = newNode;

  printf("%d added to the set\n", num);
}

// 从集合中删除元素
void removeFromSet(Set* head, int num) {
  Set* current = head;
  Set* temp;

  // 遍历链表查找要删除的元素
  while (current->next != NULL) {
    // 得知道前一个才能不断链，于是直接 current->next->numb
    if (current->next->numb == num) {
      temp = current->next;
      current->next = current->next->next;
      free(temp);
      printf("%d removed from the set\n", num);
      return;
    }
    current = current->next;
  }

  printf("%d not found in the set\n", num);
}

// 计算两个集合的并集
Set* unionSets(Set* set1, Set* set2) {
  Set* result = createSet();
  Set* current;

  // 添加第一个集合的所有元素
  current = set1->next;
  while (current != NULL) {
    addToSet(result, current->numb);
    current = current->next;
  }

  // 添加第二个集合的所有元素（addToSet会自动去重）
  // addToSet -> 已经存在就 return 了
  current = set2->next;
  while (current != NULL) {
    addToSet(result, current->numb);
    current = current->next;
  }

  return result;
}

// 计算两个集合的交集
Set* intersectSets(Set* set1, Set* set2) {
  Set* result = createSet();
  Set* current = set1->next;

  // 遍历第一个集合，检查每个元素是否在第二个集合中
  while (current != NULL) {
    if (isInSet(set2, current->numb)) {
      addToSet(result, current->numb);
    }
    current = current->next;
  }

  return result;
}
```

#### 5. **字符串处理与转换**

- **问题**：提取字符串中的连续数字并处理溢出；查找子串首次出现位置。
- **核心思路**：
  - **数字提取**：遍历识别数字区间，转换时用长整型防溢出。

  ```c
  // 将连续数字字符串转换为整数，处理溢出情况
  int str2int(char str[], int start, int end) {
    long long num = 0;  // 使用long long防止中间计算溢出

    for (int i = start; i < end; i++) {
      // 检查是否溢出
      // 这里的溢出检查学习下⭐
      if (num > INT_MAX / 10 ||
          (num == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10)) {
        return -1;  // 溢出标记
      }
      num = num * 10 + (str[i] - '0');
    }

    // 强制类型转换
    return (int)num;
  }

  // 从字符串中寻找连续数字并转换为整数存入数组
  void intFind(char str[], int arr[], int* count) {
    int len = strlen(str);
    int start = -1;  // 数字开始位置
    *count = 0;      // 初始化计数器

    // 关键是记录，纸上模拟一下就明白了
    for (int i = 0; i <= len; i++) {
      // 如果当前字符是数字且之前没有开始记录数字
      if (i < len && str[i] >= '0' && str[i] <= '9') {
        if (start == -1) {
          start = i;  // 标记数字开始位置
        }
      }
      // 如果当前不是数字但之前有数字序列，或到达字符串末尾
      else if (start != -1) {
        // 将连续数字转换为整数
        arr[*count] = str2int(str, start, i);
        (*count)++;
        start = -1;  // 重置数字开始标记
      }
    }

    // 如果没有找到任何数字
    if (*count == 0) {
      printf("The string does not contain any number!");
      exit(1);
    }
  }
  ```

  - **子串查找**：暴力匹配，逐个位置检查子串是否匹配。

  ```c
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
  ```

#### 6. **栈的应用与字符串排序**

- **问题**：括号匹配检查；字符串数组字典排序。
- **核心思路**：
  - **括号匹配**：计数器模拟栈，左括号入栈，右括号出栈。

  ```c
  int isMarry(const char *str) {
    int top = -1;  // 栈顶指针，-1表示空栈

    // 遍历输入字符串中的每个字符
    while (*str) {
      if (*str == '(') {
        top++;  // 遇到左括号，入栈
      } else if (*str == ')') {
        if (top == -1) return -1;  // 遇到右括号但栈为空，说明右括号多了
        top--;                     // 遇到右括号，出栈
      }
      str++; // 指针的++
    }

    // 如果栈为空，说明括号匹配
    return (top == -1) ? 0 : -1;
  }
  ```

  - **字典排序**：冒泡排序，比较字符串字典序并交换指针顺序。

  ```c
  void Sort(char *parr[], int n) {
    int i, j;

    // 冒泡排序
    for (i = 0; i < n - 1; i++) {
      for (j = i + 1; j < n; j++) {
        char *str1 = parr[i];  // 获取两个待比较字符串
        char *str2 = parr[j];

        // 跳过两个字符串的共同前缀
        // 如果都跳过了就不交换了呗
        while (*str1 && *str2 && *str1 == *str2) {
          str1++;
          str2++;
        }

        // 比较第一个不同的字符，如果str1大于str2则交换位置
        if (*str1 > *str2 || (*str1 == '\0' && *str2 != '\0')) {
          char *temp = parr[i];
          parr[i] = parr[j];
          parr[j] = temp;
        }
      }
    }
  }
  ```

#### 7. **分治与数组分割**

- **问题**：将数组分割为左部不大于右部的两部分。
- **核心思路**：

  - 类似快速排序的 `partition`，双指针法交换元素，确定基准位置，使左侧元素均不大于右侧。

     ```c
     int partion(int arr[], int n) {
       int pos = 0;  // 选择第一个元素作为基准
       int i = 0, j = n - 1;
       int temp;
       while (i != j) {
         while (arr[j] >= arr[pos] && i < j) j--;  // 从右向左找小于基准的元素
         while (arr[i] <= arr[pos] && i < j) i++;  // 从左向右找大于基准的元素
         if (i < j) {                              // 交换两个元素
           temp = arr[i];
           arr[i] = arr[j];
           arr[j] = temp;
         }
       }
       // 将基准元素放到最终位置
       temp = arr[i];
       arr[i] = arr[pos];
       arr[pos] = temp;
       return i;  // 返回基准元素的位置
     }
     ```

---

### 10-

`ctype.h`

| **函数**    | **功能**                                                                                     | **详细说明**                                                                                       |
|-------------|---------------------------------------------------------------------------------------------|----------------------------------------------------------------------------------------------------|
| `isalnum`   | 检查 `ch` 是否为字母或数字                                                                  | 如果 `ch` 是字母（`a-z` 或 `A-Z`）或数字（`0-9`），返回非零值；否则返回0。                          |
| `isalpha`   | 检查 `ch` 是否为字母                                                                        | 如果 `ch` 是字母（`a-z` 或 `A-Z`），返回非零值；否则返回0。                                        |
| `isblank`   | 检查 `ch` 是否为空白字符（`\t` 或 ``）                                                     | 如果 `ch` 是制表符（`\t`）或空格（``），返回非零值；否则返回0。仅适用于C++11及以上版本。           |
| `iscntrl`   | 检查 `ch` 是否为控制字符（ASCII值在0~31）                                                   | 如果 `ch` 是控制字符（如换行符、回车符等），返回非零值；否则返回0。                                |
| `isdigit`   | 检查 `ch` 是否为数字（`0` ~ `9`）                                                           | 如果 `ch` 是数字（`0-9`），返回非零值；否则返回0。                                                 |
| `isgraph`   | 检查 `ch` 是否为可显示字符，不包括空格                                                      | 如果 `ch` 是可显示字符（如字母、数字、标点符号等），且不是空格，返回非零值；否则返回0。             |
| `islower`   | 检查 `ch` 是否为小写字母（`a` ~ `z`）                                                       | 如果 `ch` 是小写字母（`a-z`），返回非零值；否则返回0。                                             |
| `isprint`   | 检查 `ch` 是否为可打印字符，包括空格                                                        | 如果 `ch` 是可打印字符（包括字母、数字、标点符号和空格），返回非零值；否则返回0。                  |
| `ispunct`   | 检查 `ch` 是否为标点字符，即除字母、数字和空格以外的所有可打印字符                          | 如果 `ch` 是标点符号（如 `!`, `@`, `#`, `$` 等），返回非零值；否则返回0。                          |
| `isspace`   | 检查 `ch` 是否为空白字符（``, `\t`, `\n`, `\v`, `\f`, `\r`）                               | 如果 `ch` 是空格、制表符、换行符、垂直制表符、换页符或回车符，返回非零值；否则返回0。               |
| `isupper`   | 检查 `ch` 是否为大写字母（`A` ~ `Z`）                                                       | 如果 `ch` 是大写字母（`A-Z`），返回非零值；否则返回0。                                             |
| `isxdigit`  | 检查 `ch` 是否为16进制字符（`0` ~ `9` 或 `A` ~ `F` 或 `a` ~ `f`）                           | 如果 `ch` 是16进制字符（`0-9`, `A-F`, `a-f`），返回非零值；否则返回0。                              |
| `tolower`   | 将 `ch` 字符转换为小写字母                                                                  | 如果 `ch` 是大写字母（`A-Z`），返回其对应的小写字母；否则返回 `ch` 本身。                          |
| `toupper`   | 将 `ch` 字符转换为大写字母                                                                  | 如果 `ch` 是小写字母（`a-z`），返回其对应的大写字母；否则返回 `ch` 本身。                          |
