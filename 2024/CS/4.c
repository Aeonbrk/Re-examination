// 哈利·波特要考试了，他需要你的帮助。这门课学的是用魔咒将一种动物变成另一种动物的本事。例如将猫变成老鼠的魔咒是haha，将老鼠变成鱼的魔咒是hehe等等。反方向变化的魔咒就是简单地将原来的魔咒倒过来念，例如ahah可以将老鼠变成猫。另外，如果想把猫变成鱼，可以通过念一个直接魔咒lalala，也可以将猫变老鼠、老鼠变鱼的魔咒连起来念：hahahehe。

// 现在哈利·波特的手里有一本教材，里面列出了所有的变形魔咒和能变的动物。老师允许他自己带一只动物去考场，要考察他把这只动物变成任意一只指定动物的本事。于是他来问你：带什么动物去可以让最难变的那种动物（即该动物变为哈利·波特自己带去的动物所需要的魔咒最长）需要的魔咒最短？例如：如果只有猫、鼠、鱼，则显然哈利·波特应该带鼠去，因为鼠变成另外两种动物都只需要念4个字符；而如果带猫去，则至少需要念6个字符才能把猫变成鱼；同理，带鱼去也不是最好的选择。
// 输入格式:

// 输入说明：输入第1行给出两个正整数N
// (≤100)和M，其中N是考试涉及的动物总数，M是用于直接变形的魔咒条数。为简单起见，我们将动物按1~N编号。随后M行，每行给出了3个正整数，分别是两种动物的编号、以及它们之间变形需要的魔咒的长度(≤100)，数字之间用空格分隔。
// 输出格式:

// 输出哈利·波特应该带去考场的动物的编号、以及最长的变形魔咒的长度，中间以空格分隔。如果只带1只动物是不可能完成所有变形要求的，则输出0。如果有若干只动物都可以备选，则输出编号最小的那只。
// 输入样例:
// 6 11
// 3 4 70
// 1 2 1
// 5 4 50
// 2 6 50
// 5 6 60
// 1 3 70
// 4 6 60
// 3 6 80
// 5 1 100
// 2 4 60
// 5 2 80

// 输出样例:
// 4 70

// 就是最短路径的变体

#include <stdbool.h>  // 使用标准布尔类型
#include <stdio.h>

#define MAX_ANIMAL_NUM 105  // 最大动物数量
#define INF 99999           // 定义无穷大，表示不可达

int graph[MAX_ANIMAL_NUM][MAX_ANIMAL_NUM];  // 邻接矩阵存储图的边权 ->
                                            // 矩阵实现方便（直接包含边的权值）
int distance[MAX_ANIMAL_NUM];               // 存储起点到各节点的最短距离
bool visited[MAX_ANIMAL_NUM];               // 标记节点是否已访问
int n, m;                                   // n: 动物总数, m: 魔咒条数

/**
 * 使用Dijkstra算法计算从起点到所有节点的最短路径
 * @param start_node 起始动物编号
 * 需要直接背诵的程度
 */
void dijkstra(int start_node) {
  // 初始化距离数组和访问标记
  // 这也就是为什么main函数循环永远是从1开始
  for (int i = 1; i <= n; i++) {
    distance[i] = INF;
    visited[i] = false;
  }
  distance[start_node] = 0;  // 起点到自身距离为0

  // 遍历所有节点，每次找到一个最短路径节点
  for (int step = 0; step < n; step++) {
    int current_node = -1;
    int min_distance = INF;
    // 寻找当前未访问节点中距离最小的
    for (int node = 1; node <= n; node++) {
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
      // 如果未访问、存在边且可优化距离
      if (!visited[neighbor] && graph[current_node][neighbor] != 0 &&
          distance[current_node] + graph[current_node][neighbor] <
              distance[neighbor]) {
        distance[neighbor] =
            distance[current_node] + graph[current_node][neighbor];
      }
    }
  }
}

int main() {
  int animal_a, animal_b, spell_length;
  int best_animal = 0;       // 最佳动物编号
  int min_max_length = INF;  // 最小的最长魔咒长度

  // 初始化邻接矩阵
  for (int i = 0; i < MAX_ANIMAL_NUM; i++) {
    for (int j = 0; j < MAX_ANIMAL_NUM; j++) {
      graph[i][j] = 0;  // 默认无边
    }
  }

  // 读取输入数据
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d%d", &animal_a, &animal_b, &spell_length);
    // 无向图，两个方向权值相同，赋值相同
    graph[animal_a][animal_b] = spell_length;
    graph[animal_b][animal_a] = spell_length;
  }

  printf("\n");

  // 遍历每个动物作为起点，计算其到其他动物的最短路径
  // 如果使用Floyd的话一次结束，但是代码实现困难，不划算
  for (int current_animal = 1; current_animal <= n; current_animal++) {
    dijkstra(current_animal);

    int current_max = 0;           // 当前起点的最长最短路径
    bool has_unreachable = false;  // 标记是否存在不可达节点

    // 遍历所有动物，计算最长距离并检查不可达情况
    // distance[0] 始终为 current_animal
    for (int target = 1; target <= n; target++) {
      if (distance[target] == INF) {
        has_unreachable = true;
        break;
      }
      if (distance[target] > current_max) {
        current_max = distance[target];
      }
    }

    // 存在不可达动物则跳过
    // 审题 "变成任意一只指定动物" 这是前提
    if (has_unreachable) continue;

    // 更新最优解：更小的最长距离 或 相同距离但编号更小
    if (current_max < min_max_length ||
        (current_max == min_max_length && current_animal < best_animal)) {
      min_max_length = current_max;
      best_animal = current_animal;
    }
  }

  // 输出结果
  if (best_animal == 0) {
    printf("Not exist.\n");
  } else {
    printf("%d %d\n", best_animal, min_max_length);
  }

  return 0;
}
