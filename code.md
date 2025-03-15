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

</br>

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

### 10-16

#### ctype.h

| **函数**   | **功能**                                                     | **详细说明**                                                 |
| ---------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| `isalnum`  | 检查 `ch` 是否为字母或数字                                   | 如果 `ch` 是字母（`a-z` 或 `A-Z`）或数字（`0-9`），返回非零值；否则返回0。 |
| `isalpha`  | 检查 `ch` 是否为字母                                         | 如果 `ch` 是字母（`a-z` 或 `A-Z`），返回非零值；否则返回0。  |
| `isblank`  | 检查 `ch` 是否为空白字符（`\t` 或 `\`）                                                     \| 如果 `ch` 是制表符（`\t`）或空格（``），返回非零值；否则返回0。仅适用于C++11及以上版本。 |                                                              |
| `iscntrl`  | 检查 `ch` 是否为控制字符（ASCII值在0~31）                    | 如果 `ch` 是控制字符（如换行符、回车符等），返回非零值；否则返回0。 |
| `isdigit`  | 检查 `ch` 是否为数字（`0` ~ `9`）                            | 如果 `ch` 是数字（`0-9`），返回非零值；否则返回0。           |
| `isgraph`  | 检查 `ch` 是否为可显示字符，不包括空格                       | 如果 `ch` 是可显示字符（如字母、数字、标点符号等），且不是空格，返回非零值；否则返回0。 |
| `islower`  | 检查 `ch` 是否为小写字母（`a` ~ `z`）                        | 如果 `ch` 是小写字母（`a-z`），返回非零值；否则返回0。       |
| `isprint`  | 检查 `ch` 是否为可打印字符，包括空格                         | 如果 `ch` 是可打印字符（包括字母、数字、标点符号和空格），返回非零值；否则返回0。 |
| `ispunct`  | 检查 `ch` 是否为标点字符，即除字母、数字和空格以外的所有可打印字符 | 如果 `ch` 是标点符号（如 `!`, `@`, `#`, `$` 等），返回非零值；否则返回0。 |
| `isspace`  | 检查 `ch` 是否为空白字符（`\t`, `\n`, `\v`, `\f`, `\r`）     | 如果 `ch` 是空格、制表符、换行符、垂直制表符、换页符或回车符，返回非零值；否则返回0。 |
| `isupper`  | 检查 `ch` 是否为大写字母（`A` ~ `Z`）                        | 如果 `ch` 是大写字母（`A-Z`），返回非零值；否则返回0。       |
| `isxdigit` | 检查 `ch` 是否为16进制字符（`0` ~ `9` 或 `A` ~ `F` 或 `a` ~ `f`） | 如果 `ch` 是16进制字符（`0-9`, `A-F`, `a-f`），返回非零值；否则返回0。 |
| `tolower`  | 将 `ch` 字符转换为小写字母                                   | 如果 `ch` 是大写字母（`A-Z`），返回其对应的小写字母；否则返回 `ch` 本身。 |
| `toupper`  | 将 `ch` 字符转换为大写字母                                   | 如果 `ch` 是小写字母（`a-z`），返回其对应的大写字母；否则返回 `ch` 本身。 |

#### **1. 字符串处理**

- **问题1**：删除字符串中的字母和数字，并统计重复字符及其次数。
  - **核心思路**：
    - 使用`isalnum()`过滤字母和数字，保留其他字符。
      - 来自与 `ctype.h`
    - 用数组`counts[256]`统计每个ASCII字符的出现次数。
      - `counts[(unsigned char)str[i]]++;`
    - 遍历统计数组输出重复次数大于1的字符。

- **问题2**：删除字符串中的字母和数字，并将重复字符减为一个。
  - **核心思路**：
    - 先过滤非字母数字字符到临时字符串。
    - 通过双重循环检查临时字符串中的每个字符是否已存在于结果字符串，避免重复添加。

- **问题3**：复制字符串中的元音字母到新字符串。
  - **核心思路**：
    - 遍历源字符串，使用`isVowel()`判断字符是否为元音（大小写均支持）。
      - 先使用 `tolower()` 函数
    - 将符合条件的字符按顺序复制到目标字符串。

- **问题4**：密码翻译（对称字母替换）。
  - **核心思路**：
    - 对每个字母字符，计算其对称字符：`A→Z`（公式：`'A' + 'Z' - c`），`a→z`同理。
      - `original[j] = 'A' + 'Z' - cipher[j];  *// 155 - cipher[j] 的简化形式*`
      - `original[j] = 'a' + 'z' - cipher[j];  *// 219 - cipher[j] 的简化形式*`
    - 非字母字符保持不变。

- **问题5**：比较两个身份证号码的出生日期先后。
  - **核心思路**：

    - 边界条件先确定下来。
    - 提取身份证号中第7-14位（8）的日期字符串（YYYYMMDD格式）

      ```c
      char birth[9];
      // 字符串不可以直接使用 = 赋值
      strncpy(birth, id + 6, 8);
      // 这一点特别留意，估计也是改卷老师最主动注意的地方
      birth1[8] = '\0';
      ```

    - 直接使用字符串比较函数`strcmp`判断先后顺序。

      - 同样的字符串不可以使用 `<,>,==`  等符号。

- **问题6**：统计文章中各类字符数量（大写字母、小写字母等）。
  - **核心思路**：
    - 遍历每个字符，通过ASCII范围判断类别。
    - 使用计数器分别统计不同类别字符的数量。

- **问题7**：候选人得票统计。
  - **核心思路**：
    - 输入候选人姓名，通过字符串比较匹配候选人。
    - 使用计数器统计每个候选人的票数和无效票数。

#### **2. 链表操作**

- **问题1**：创建单链表（带头结点）。
  - **核心思路**：
    - 使用尾插法逐个添加节点。
    - 头结点不存储数据，仅作为链表起始标记。

- **问题2**：反转单链表（带头结点和不带头结点）。
  - **核心思路**：
    - **带头结点**：三指针法（`prev`、`current`、`next`）逐个反转节点指针，最后将头结点指向新首节点。
    - **不带头结点**：类似三指针法，返回反转后的新头节点（原尾节点）。

    ```c
    // 核心
    while (current != NULL) {
      next = current->next;  // 保存下一个节点
      current->next = prev;  // 当前节点指向前一个节点
      prev = current;        // 移动前一个节点指针
      current = next;        // 移动当前节点指针
    }
    ```

- **问题3**：求两个链表的交集（修改L1，删除非交集节点）。
  - **核心思路**：
    - 遍历L1的每个节点，检查其值是否存在于L2中。
    - 若不存在，直接删除该节点（调整指针并释放内存）。

    ```c
    // 遍历L1的每个节点，检查是否在L2中存在
    while (p1->next != NULL) {
      found = 0;
      L2_cur = L2;  // 重置L2的遍历指针
      // 在L2中查找当前L1节点的值
      while (L2_cur != NULL) {
        // p1 一直多一个 dummy 节点
        if (p1->next->data == L2_cur->data) {
          found = 1;
          break;
        }
        L2_cur = L2_cur->next;
      }
      // 如果在L2中没找到，则从L1中删除该节点
      if (!found) {
        cur1 = p1->next;        // 保存要删除的节点
        p1->next = cur1->next;  // 绕过要删除的节点
        free(cur1);             // 释放节点内存
      } else {
        p1 = p1->next;  // 移动到下一个节点
      }
    }
    ```

#### **3. 循环链表/约瑟夫环**

- **问题1**：约瑟夫环模拟。
  - **核心思路**：
    - 创建包含`n`个节点的循环链表，依次编号1~n。
    - 从首节点开始报数，每报到`k`时删除当前节点，直到只剩一个节点。
    - 关键操作：维护`prev`指针以快速删除节点，最终返回剩余节点的编号。
      - 先确定尾节点，确定 `prev` 节点的起始位置

```c
int josephus(int n, int k) {
  // 边界条件处理
  if (n <= 0 || k <= 0) return -1;
  if (n == 1) return 1;

  Person *head = createCircle(n);
  Person *current = head;
  Person *prev = NULL;

  // 查找尾节点，使其指向头节点
  // 为什么要先找到尾节点呢? -> 确定prev节点的起始位置
  while (current->next != head) {
    current = current->next;
  }
  prev = current;
  current = head;

  // 模拟报数过程
  while (current->next != current) {  // 当环中只剩一个节点时停止
    // 报数k-1次，找到第k个人
    for (int i = 0; i < k - 1; i++) {
      prev = current;
      current = current->next;
    }

    // 删除第k个人
    prev->next = current->next;
    // 这样才可以删除
    Person *temp = current;
    current = current->next;
    free(temp);
  }

  // 记录最后一个人的编号
  int result = current->number;
  free(current);  // 释放最后一个节点

  return result;
}
```

#### **4. 数组操作**

- **问题1**：递归分治法求数组最大值和最小值。

  - **核心思路**：

    - 将数组分为两部分，递归求解左右部分的最大最小值。
    - 合并结果时比较左右部分的最大最小值。

    ```c
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
    ```

- **问题2**：有序数组插入元素。

  - **核心思路**：
    - 遍历找到第一个大于目标值的位置作为插入点。
    - 将插入点后的元素后移腾出空间，插入目标值。

- **问题3**：二维数组鞍点查找。

  - **核心思路**：
    - 对每个元素检查是否为行最大值和列最小值。
    - 使用双重循环遍历所有元素进行条件判断。
      - 先确定 `isRowMax`， 在确定 `isColMin`

- **问题4**：数组统计（最大值、最小值、平均值）。
  - **核心思路**：

    - 遍历数组，动态更新最大值、最小值和总和。

      - 遍历的时候顺便求

      ```c
      for (i = 0; i < n; i++) {
        if (arr[i] > *max) {
          *max = arr[i];
        }
        if (arr[i] < *min) {
          *min = arr[i];
        }
        sum += arr[i];
      }
      ```

    - 累加求和后计算平均值。

#### **5. 数学运算**

- **问题1**：质因数分解。
  - **核心思路**：
    - 从2开始依次试除，记录所有能整除的质因子。
      - `num % i == 0`
    - 通过循环分解直至商为1。
      - `num /= i`
- **问题2**：素数判断。
  - **核心思路**：
    - 检查2到平方根范围内是否存在能整除的数。
      - `int i = 2; i <= sqrt(n); i++`
    - 若存在则为非素数，否则为素数。
      - `if (n % i == 0) return 0;`
- **问题3**：分数四则运算。

  - **核心思路**：
    - 定义分数结构体，根据运算符进行分子分母运算。
    - 计算最大公约数化简分数结果。

    ```c
    // 9 & 6 -> 3
    long gcd(long a, long b) {
      // 使用辗转相除法
      long temp;
      if (a < b) {
        temp = a;
        a = b;
        b = temp;
      }
    
      // core code
      while (b != 0) {
        temp = a % b;
        a = b;
        b = temp;
      }
      return a;
    }
    ```

#### **6. 文件操作**

- **问题**：文件复制并添加行号。
  - **核心思路**：
    - 逐行读取源文件内容，统计非空格字符数。
    - 在每行前添加行号后写入目标文件。

  ```c
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
  ```

#### **7. 数据结构应用**

- **问题**：学生成绩处理（结构数组）。
  - **核心思路**：
    - 定义学生结构体存储学号和成绩。
    - 遍历结构数组记录最高分和最低分，二次遍历输出对应学号（可能存在多个同分的）。

> 求质因数、删除字符串中的英文和数字并将重复字符减为一个、约瑟夫环、链表逆序（全部都逆序或者是一个范围内逆序），这4个问题考过填空

---

</br>

### 17

#### **1. 数组操作**

- **问题1**：用指针实现数组逆序存放。
  - **核心思路**：
    - 使用双指针法，分别指向数组头部和尾部。
      - 头指针向后移动，尾指针向前移动，依次交换元素直到指针相遇。
    - 通过指针运算直接操作内存地址，**实现原地逆序**。
  
  ```c
  void reverseArray(int *arr, int size) {
    int *start = arr;           // 指向数组头部的指针
    int *end = arr + size - 1;  // 指向数组尾部的指针
  
    while (start < end) {
      // 交换头尾元素
      int temp = *start;
      *start = *end;
      *end = temp;
  
      // 移动指针
      start++;
      end--;
    }
  }
  ```

#### **2. 字符串处理**

- **问题1**：递归将整数转换为字符串。
  - **核心思路**：
    - 处理负数情况后，递归分解高位数字。
      - 递归终止条件：数字小于10时直接转换为字符。
    - 逐层返回时拼接字符到字符串末尾，注意递归过程中维护字符串的结束符`\0`。
  
  ```c
  // 递归法将整数 n 转换成字符串
  void intToStrHelper(int n, char *str, int *index) {
      // 递归终止条件：数字小于10
      if (n >= 10) {
          intToStrHelper(n / 10, str, index);
      }
    	int next = (*index)++;
      str[next] = n % 10 + '0';
  }
  
  void intToStr(int n, char *str) {
      int index = 0;
  
      // 处理负数
      if (n < 0) {
          str[index++] = '-';
          n = -n;
      }
  
      intToStrHelper(n, str, &index);
      str[index] = '\0'; // 添加字符串终止符
  }
  ```
- **问题2**：统计字符串中的单词数。
  - **核心思路**：
    - 使用状态标记法，遍历字符串时记录是否处于单词中。
      - 遇到空格/制表符/换行符时标记离开单词。
      - 从非分隔符进入单词时计数器加1。

#### **3. 数学问题**

- **问题1**：递归计算阶乘。
  - **核心思路**：
    - 基线条件：`n == 0 || n == 1`时返回1。
    - 递归公式：`n! = n * (n-1)!`，注意输入负数的错误处理。
  
  ```c
  int factorial(int n) {
    if (n < 0) {
      printf("Wrong input.");
      return n;
    } else if (n == 0)
      return 1;  // 修正：0! = 1
    else if (n == 1)
      return 1;
    else {
      return n * factorial(n - 1);
    }
  }
  ```
- **问题2**：计算数列 `a + aa + aaa + ...` 的和。
  - **核心思路**：
    - 通过迭代动态构建数列项：`term = term * 10 + a`。
    - 累加每项到总和中，避免重复计算幂次。
  
  ```c
  long long sumOfSeries(int a, int count) {
    long long sum = 0;
    long long term = 0;
  
    for (int i = 0; i < count; i++) {
      term = term * 10 + a;  // 构建当前项
      sum += term;
    }
  
    return sum;
  }
  ```

#### **4. 数字处理**

- **问题1**：分析不超过6位的正整数（位数统计、逐位输出、逆序输出）。
  - **核心思路**：
    - 分解数字时利用取模和除法逐位提取余数。
      - 逆序分解后存储到数组，正序输出时反向遍历数组。
    - 先计算总位数，再处理正序和逆序输出逻辑。

---

</br>

## FillTheBlank

### **1. 排序与选择算法**

- **问题1**：快速选择算法求数组第k小元素。
  - **核心思路**：
    - 使用快速排序的分区思想，每次确定基准值位置。
    - 根据基准值位置与k的关系递归处理左半或右半部分。
      - `pivotPos == k-1`时直接返回结果。

  ```c
  // 太重要了
  // 分区函数，将数组按基准值分成两部分，返回基准值位置
  int partition(int arr[], int low, int high) {
    int pivot = arr[low];  // 选择第一个元素作为基准值
    while (low < high) {
      // 从右向左找小于基准值的元素
      while (low < high && arr[high] >= pivot) {
        high--;
      }
      arr[low] = arr[high];  // 将小于基准值的元素放到左边
  
      // 从左向右找大于基准值的元素
      while (low < high && arr[low] <= pivot) {
        low++;
      }
      arr[high] = arr[low];  // 将大于基准值的元素放到右边
    }
  
    arr[low] = pivot;  // 将基准值放到最终位置
    return low;        // 返回基准值的位置
  }
  
  // 使用快速排序思想寻找第k小的元素
  int quickSelect(int arr[], int low, int high, int k) {
    if (low <= high) {
      int pivotPos = partition(arr, low, high);
  
      if (pivotPos == k - 1) {  // 找到第k小的元素
        return arr[pivotPos];
      } else if (pivotPos > k - 1) {  // 第k小的元素在左半部分
        return quickSelect(arr, low, pivotPos - 1, k);
      } else {  // 第k小的元素在右半部分
        return quickSelect(arr, pivotPos + 1, high, k);
      }
    }
    return -1;  // 表示未找到
  }
  ```

- **问题2**：链表实现选择排序。

  - **核心思路**：
    - 遍历链表，每次在未排序部分找到最小值节点。
    - 交换当前节点与最小值节点的数据值，而非调整指针。
      - 外层循环控制当前处理位置，内层循环查找最小值。

  ```c
  // 带头结点的情况
  void selectionSort(Node* head) {
    Node *p, *q, *min;
  
    for (p = head->next; p != NULL && p->next != NULL; p = p->next) {
      min = p;  // 假设当前节点值最小
  
      // 查找p之后的最小节点
      for (q = p->next; q != NULL; q = q->next) {
        if (q->data < min->data) {
          min = q;
        }
      }
  
      // 如果找到更小的值，交换节点的值
      if (min != p) {
        int temp = p->data;
        p->data = min->data;
        min->data = temp;
      }
    }
  }
  ```

### **2. 数学计算与枚举**

- **问题1**：完美乘法等式（a*b=c，abc使用0-9各一次）。

  - **核心思路**：
    - 双重循环遍历a和b的可能范围（1~9876）。
    - 使用标记数组检查每个数字是否重复出现。
      - 对a、b、c分别拆解数字并标记，最后验证所有数字被使用。

  ```c
  // 检查并标记数字，返回是否有重复数字
  // 经典辅助函数，记住
  bool checkAndMark(int num, int used[]) {
    while (num > 0) {
      int digit = num % 10;
      if (used[digit]) return false;
      used[digit] = 1;
      num /= 10;
    }
    return true;
  }

  // 寻找完美乘法
  void findPerfectMultiplications() {
    printf("Perfect Multiplications:\n");

    for (int a = 1; a <= 9876; a++) {
      for (int b = 1; b * a <= 98765 && b <= 9876; b++) {
        int c = a * b;
        int used[10] = {0};  // 标记数字0-9是否使用

        // 依次检查 a, b, c 是否符合条件
        if (!checkAndMark(a, used) || !checkAndMark(b, used) ||
            !checkAndMark(c, used)) {
          continue;
        }

        // 检查是否用完所有 0-9 的数字
        bool allUsed = true;
        for (int i = 0; i < 10; i++) {
          if (!used[i]) {
            allUsed = false;
            break;
          }
        }

        if (allUsed) {
          printf("%d * %d = %d\n", a, b, c);
        }
      }
    }
  }
  ```

- **问题2**：互满数查找（约数之和互为对方）。
  - **核心思路**：
    - 计算每个数的约数和（排除自身），存入数组。

    ```c
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
    ```

    - 遍历检查是否存在数对`i`和`sum_i`满足`sum(sum_i) == i`。
- **问题3**：奇偶数列求和。
  - **核心思路**：
    - 奇数n：计算`1 + 1/3 + 1/5 + ... + 1/(2n-1)`。
    - 偶数n：计算`1/2 + 2/3 + 3/5 + ...`（分子递增，分母为质数序列）。
      - 分母生成规则需单独处理初始值。

### **3. 字符串操作**

- **问题1**：字符串子串删除。
  - **核心思路**：

    - 将删除位置后的字符前移覆盖目标子串。
      - 计算字符串长度，调整越界的删除长度。
      - 使用循环覆盖字符，自动处理字符串结束符。

    ```c
    void deleteSubstring(char* str, int n, int len) {
      // 获取字符串长度
      int length = strlen(str);
    
      // 检查参数有效性
      // 这个都要有，极致好拿的分
      if (n < 0 || n >= length || len <= 0) return;
    
      // 如果删除长度超出字符串范围，则调整为删到字符串末尾
      if (n + len > length) len = length - n;
    
      // 将后面的字符前移覆盖要删除的部分
      for (int i = n; i <= length - len; i++) {
        str[i] = str[i + len];
      }
    }
    ```

- **问题2**：字符串插入操作。

  - **核心思路**：

    - 将原字符串从插入位置后的字符后移，腾出空间。
    - 复制子串到腾出的位置，保持字符串连续性。
      - 需先计算字符串长度，防止越界。

    ```c
    // 将str2插入到str1的第m+1个位置
    void insertString(char str1[], char str2[], int m) {
      /* 插入字符串，原字符后移 */
      int len1 = strlen(str1);
      int len2 = strlen(str2);
    
      // 将str1的字符向后移动len2个位置，为str2腾出空间
      for (int i = len1; i >= m; i--) {
        str1[i + len2] = str1[i];
      }
    
      // 将str2复制到str1中的m位置
      for (int i = 0; i < len2; i++) {
        str1[m + i] = str2[i];
      }
    }
    ```

### **4. 链表操作**

- **问题**：反转链表指定区间（m到n）。
  - **核心思路**：
    - 使用哑节点简化头节点处理。
    - 定位到m的前驱节点，反转区间内节点指针方向。
      - 通过临时指针调整`next`指向，完成局部反转。

  ```c
  ListNode* reverseBetween(ListNode* head, int m, int n) {
    // 特殊情况处理
    if (!head || m == n) return head;
  
    // 创建一个哑节点，避免处理头节点的特殊情况
    ListNode dummy;
    dummy.next = head;
  
    // 找到第m-1个节点
    ListNode* pre = &dummy;
    for (int i = 1; i < m; i++) {
      pre = pre->next;
    }
  
    // 当前节点是第m个节点
    ListNode* curr = pre->next;
    // 用于保存反转过程中的下一个节点
    ListNode* next;
  
    // 反转从m到n的节点
    // 这里的思路和全部reverse是一样的
    for (int i = m; i < n; i++) {
      next = curr->next;
      curr->next = next->next;
      next->next = pre->next;
      pre->next = next;
    }
  
    return dummy.next;
  }
  ```

### **5. 数据结构排序**

- **问题**：学生信息多级排序（学号、年龄、身高）。
  - **核心思路**：
    - 自定义`qsort`比较函数，实现三级优先级比较。
      - 先比较学号，相同则比较年龄，最后比较身高。
      - `qsort` 真的好用

  ```c
  // 比较两个学生
  int compareStudents(const void* a, const void* b) {
    // 则个一定要先转换类型
    Student* s1 = (Student*)a;
    Student* s2 = (Student*)b;
  
    /* 先比较学号 */
    if (s1->num != s2->num) {
      return s1->num - s2->num;
    }
  
    /* 学号相同比较年龄 */
    if (s1->age != s2->age) {
      return s1->age - s2->age;
    }
  
    /* 学号和年龄都相同比较身高 */
    return s1->height - s2->height;
  }
  
  // 排序学生数组
  void sortStudents(Student students[], int n) {
    /* 使用qsort函数排序 */
    qsort(students, n, sizeof(Student), compareStudents);
  }
  ```

### **6. 数值处理与检查**

- **问题1**：检查数字及其平方是否包含特定数字。
  - **核心思路**：
    - 分别对数字和平方数逐位拆解，检查是否包含目标数字。
      - 使用取余和除法循环提取每一位。
- **问题2**：计算两个级数的和。
  - **核心思路**：
    - 迭代计算每一项，累加到总和。
      - 级数1：符号交替，分母为递增阶乘。
        - `sum += term; term = term * (-x) / (i + 1);`
      - 级数2：符号交替规则不同，分母同样为阶乘。
        - `sum += term; term = term * x / (i + 1) * (i % 2 == 0 ? -1 : 1);`

```c
// 经典的如何求最大公约数和最小公倍数
// 必须会哈
// 求两个数的最大公约数
int gcd(int a, int b) {
  /* 使用欧几里得算法求最大公约数 */
  while (b != 0) {
    int temp = a % b;
    a = b;
    b = temp;
  }
  return a;
}

// 求两个数的最小公倍数
// 3, 6 -> 3 / 3 * 6 = 6
int lcm(int a, int b) {
  /* 最小公倍数 = 两数之积 / 最大公约数 */
  return a / gcd(a, b) * b;  // 先除后乘防止溢出
}
```
