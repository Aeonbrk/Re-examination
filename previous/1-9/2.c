// 一个循环数组大小为n，知道是有序的，但不知道哪个方向有序，也不知道起点在哪里
// 设计一个算法找出数组里的最小值，要求时间复杂度O(logn)。

#include <stdio.h>

/**
 * 在循环有序数组中找到最小值。
 * 假设数组中的元素是唯一的。
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

/* 测试用例 */
int main() {
  // 测试用例1：典型循环数组
  int arr1[] = {3, 4, 5, 1, 2};
  printf("Test1: %d\n", findMin(arr1, 5));  // 应输出1

  // 测试用例2：完全有序数组
  int arr2[] = {1, 2, 3, 4, 5};
  printf("Test2: %d\n", findMin(arr2, 5));  // 应输出1

  // 测试用例3：数组长度为1
  int arr3[] = {2};
  printf("Test3: %d\n", findMin(arr3, 1));  // 应输出2

  // 测试用例4：最大旋转情况
  int arr4[] = {5, 1, 2, 3, 4};
  printf("Test4: %d\n", findMin(arr4, 5));  // 应输出1

  // 测试用例5：较大数组
  int arr5[] = {4, 5, 6, 7, 0, 1, 2};
  printf("Test5: %d\n", findMin(arr5, 7));  // 应输出0

  // 测试用例6：重复数组
  int arr6[] = {4, 4, 6, 7, 0, 1, 1};
  printf("Test6: %d\n", findMin(arr5, 7));  // 应输出0

  return 0;
}
