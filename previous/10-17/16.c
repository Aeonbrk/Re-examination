#include <stdio.h>
#include <string.h>

// 函数1：有序数组插入元素
void insertSorted(int arr[], int n, int num) {
  /* 在已排序数组中插入一个数 */
  int i, pos = n;

  // 寻找插入位置
  for (i = 0; i < n; i++) {
    if (arr[i] > num) {
      pos = i;
      break;
    }
  }

  // 移动元素，腾出位置
  for (i = n; i > pos; i--) {
    arr[i] = arr[i - 1];
  }

  // 插入元素
  arr[pos] = num;
}

// 函数2：找出二维数组中的鞍点
int findSaddlePoint(int matrix[3][4], int rows, int cols, int* row, int* col) {
  /* 找出鞍点：该行最大且该列最小的元素 */
  int i, j, k;
  int found = 0;

  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      // 检查是否是该行的最大值
      int isRowMax = 1;
      for (k = 0; k < cols; k++) {
        if (matrix[i][k] > matrix[i][j]) {
          isRowMax = 0;
          break;
        }
      }

      // 如果是该行的最大值，再检查是否是该列的最小值
      if (isRowMax) {
        int isColMin = 1;
        for (k = 0; k < rows; k++) {
          if (matrix[k][j] < matrix[i][j]) {
            isColMin = 0;
            break;
          }
        }

        // 如果同时满足两个条件，则找到鞍点
        if (isColMin) {
          *row = i;
          *col = j;
          found = 1;
          return found;  // 返回结果
        }
      }
    }
  }

  return found;  // 未找到鞍点返回0
}

// 函数3：求一维数组的最大值、最小值和平均值
void calculateStats(int arr[], int n, int* max, int* min, float* avg) {
  /* 计算数组的最大值、最小值和平均值 */
  int i;
  int sum = 0;

  *max = arr[0];
  *min = arr[0];

  for (i = 0; i < n; i++) {
    if (arr[i] > *max) {
      *max = arr[i];
    }
    if (arr[i] < *min) {
      *min = arr[i];
    }
    sum += arr[i];
  }

  *avg = (float)sum / n;
}

// 函数4：候选人得票统计
void countVotes() {
  /* 统计候选人得票情况 */
  int zhang = 0, wang = 0, li = 0, zhao = 0, invalid = 0;
  char name[20];
  int i, n;

  printf("Enter the number of voters: ");
  scanf("%d", &n);
  getchar();  // 消耗换行符

  printf("Please vote for: Zhang, Wang, Li or Zhao\n");

  for (i = 0; i < n; i++) {
    printf("Vote %d: ", i + 1);
    gets(name);

    if (strcmp(name, "Zhang") == 0) {
      zhang++;
    } else if (strcmp(name, "Wang") == 0) {
      wang++;
    } else if (strcmp(name, "Li") == 0) {
      li++;
    } else if (strcmp(name, "Zhao") == 0) {
      zhao++;
    } else {
      invalid++;
    }
  }

  printf("\nVoting Results:\n");
  printf("Zhang: %d votes\n", zhang);
  printf("Wang: %d votes\n", wang);
  printf("Li: %d votes\n", li);
  printf("Zhao: %d votes\n", zhao);
  printf("Invalid votes: %d\n", invalid);
}

// 主函数
int main() {
  int choice;

  do {
    printf("\n--------- Menu ---------\n");
    printf("1. Insert a number into a sorted array\n");
    printf("2. Find saddle point in a matrix\n");
    printf("3. Calculate statistics of an array\n");
    printf("4. Count votes for candidates\n");
    printf("0. Exit\n");
    printf("Choose a function (0-4): ");
    scanf("%d", &choice);

    switch (choice) {
      case 1: {
        // 有序数组插入元素
        int arr[11] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
        int n = 10;
        int num, i;

        printf("\nCurrent sorted array: ");
        for (i = 0; i < n; i++) {
          printf("%d ", arr[i]);
        }

        printf("\nEnter a number to insert: ");
        scanf("%d", &num);

        insertSorted(arr, n, num);

        printf("Array after insertion: ");
        for (i = 0; i <= n; i++) {
          printf("%d ", arr[i]);
        }
        printf("\n");
        break;
      }

      case 2: {
        // 找出二维数组中的鞍点
        int matrix[3][4] = {{12, 8, 9, 7}, {6, 17, 4, 11}, {5, 13, 16, 2}};
        int row, col;
        int i, j;

        printf("\nMatrix:\n");
        for (i = 0; i < 3; i++) {
          for (j = 0; j < 4; j++) {
            printf("%2d ", matrix[i][j]);
          }
          printf("\n");
        }

        if (findSaddlePoint(matrix, 3, 4, &row, &col)) {
          printf("Saddle point found at position [%d][%d] with value: %d\n",
                 row, col, matrix[row][col]);
        } else {
          printf("No saddle point found in the matrix.\n");
        }
        break;
      }

      case 3: {
        // 计算数组统计值
        int arr[10];
        int max, min, i;
        float avg;

        printf("\nEnter 10 numbers:\n");
        for (i = 0; i < 10; i++) {
          printf("Number %d: ", i + 1);
          scanf("%d", &arr[i]);
        }

        calculateStats(arr, 10, &max, &min, &avg);

        printf("Statistics:\n");
        printf("Maximum value: %d\n", max);
        printf("Minimum value: %d\n", min);
        printf("Average value: %.2f\n", avg);
        break;
      }

      case 4:
        // 候选人得票统计
        countVotes();
        break;

      case 0:
        printf("Exiting program. Goodbye!\n");
        break;

      default:
        printf("Invalid option! Please try again.\n");
    }

  } while (choice != 0);

  return 0;
}
