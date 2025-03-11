
# 分类总结

```txt
Previous Problems
These include various fundamental C programming exercises:

1.c: Sorting mixed integers and floats
2.c: Finding minimum in a rotated sorted array
3.c: Creating a reverse ordered doubly linked list
4.c: Set operations using linked lists
5.c: Extracting numbers from strings
6.c: Finding substring positions
7.c: Bracket matching and string sorting
8.c: Linked list operations (deleting nodes and merging)
9.c: Array partitioning and moving elements in linked lists

2023 and 2024 CS Problems
These are likely course assignments or exam problems for specific years:

1.c: Pattern counting in strings
2.c: Word counting in text files
3.c: Student data management and binary search
4.c: Linked list manipulation game
1.c: Extracting and sorting odd digits in a number
2.c: String processing with asterisks
3.c: Bubble sort for linked lists
4.c: Graph problem (Harry Potter's magical transformation)
```

## 2024&2023

### **1. 数字处理与排序**

- **问题**：提取数字中的奇数位并按位权从小到大排序。
- **核心思路**：
  - 分解数字的每一位，筛选出奇数。
  - 使用快速排序（`qsort`）对奇数位降序排列（因位权从小到大等价于数字从高位到低位降序）。
  - 重新组合排序后的数字。

### **2. 字符串处理**

- **问题1**：去除字符串中间部分的星号，保留首尾星号。
  - **核心思路**：
    - 遍历字符串，标记首部星号和非星号字符的位置。
    - 单独处理尾部星号，最后拼接首尾星号和中间字母。
- **问题2**：统计主字符串中子串的出现次数。
  - **核心思路**：
    - 暴力匹配法：遍历主字符串的每个可能的子串起始位置，逐字符比较是否完全匹配。

### **3. 链表操作**

- **问题1**：单链表的冒泡排序（升序）。
  - **核心思路**：
    - 通过交换相邻节点的数据（而非节点本身），模拟冒泡排序过程。
    - 维护已排序部分的尾指针，减少遍历次数。
- **问题2**：将链表中的指定节点移动到头部。
  - **核心思路**：
    - 遍历链表找到目标节点及其前驱。
    - 调整指针，将目标节点脱离原位置并链接到链表头部。

### **4. 图算法**

- **问题**：选择最优动物，使得最难变形的魔咒长度最短。
  - **核心思路**：
    - 对每个动物作为起点，使用 **Dijkstra 算法**计算到其他动物的最短路径。
    - 对每个起点，记录其最长最短路径，最终选择最长路径最小的动物。

### **5. 排序与搜索**

- **问题1**：结构体数组的冒泡排序和折半查找。
  - **核心思路**：
    - 按成绩对结构体数组升序排列。
    - 使用二分查找在排序后的数组中快速定位目标成绩。
- **问题2**：统计文件中的不同单词及其频率。
  - **核心思路**：
    - 遍历文件，将单词标准化（小写化、去除非字母字符）。
    - 使用结构数组存储单词及其计数，通过遍历检查重复项。

---

## Previous

### 1-9

#### 1. **数字处理与排序**

- **问题**：输入混合整数和浮点数，分别按从大到小和从小到大排序后输出。
- **核心思路**：
     使用字符串分割区分整数和浮点数，分别存入数组。整数用降序快速排序，浮点数用升序快速排序，最后合并输出。

#### 2. **数组与二分查找**

- **问题**：在循环有序数组中查找最小值。
- **核心思路**：
     二分法调整左右指针，比较中间元素与右边界元素。若中间值大于右边界，最小值在右侧；否则在左侧，逐步缩小范围。

#### 3. **链表操作**

- **问题**：逆序构建双向链表；删除链表最小值节点；合并递增链表为递减链表；移动最大值节点至末尾。
- **核心思路**：
  - **逆序构建**：头插法插入新节点，调整前驱指针。
  - **删除最小值**：遍历链表记录最小值及其前驱，调整指针删除。
  - **合并链表**：头插法合并，每次取较小元素插入头部。
  - **移动最大值**：遍历找到最大值，交换数据或调整指针移至尾部。

### 4. **集合运算与链表处理**

- **问题**：实现集合的添加、删除、并集、交集操作
- **核心思路**：
     用链表存储集合元素，添加时检查重复。并集遍历两个链表去重，交集遍历检查共同元素。

#### 5. **字符串处理与转换**

- **问题**：提取字符串中的连续数字并处理溢出；查找子串首次出现位置。
- **核心思路**：
  - **数字提取**：遍历识别数字区间，转换时用长整型防溢出。
  - **子串查找**：暴力匹配，逐个位置检查子串是否匹配。

#### 6. **栈的应用与字符串排序**

- **问题**：括号匹配检查；字符串数组字典排序。
- **核心思路**：
  - **括号匹配**：计数器模拟栈，左括号入栈，右括号出栈。
  - **字典排序**：冒泡排序，比较字符串字典序并交换指针顺序。

#### 7. **分治与数组分割**

- **问题**：将数组分割为左部不大于右部的两部分。
- **核心思路**：
     类似快速排序的 `partition`，双指针法交换元素，确定基准位置，使左侧元素均不大于右侧。
