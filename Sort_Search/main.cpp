#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#pragma warning(disable:4996)
/**
 * @brief 创建数组并将随机生成的数填入数组中
 *
 * @return int* 返回创建好的数组指针
 */
int* CreateArr(int len)
{
    srand((unsigned int)time(NULL));
    int* arr = (int*)malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++)
    {
        arr[i] = rand() % 100;
    }
    return arr;
}

// 交换两个元素的值
void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * @brief 输出数组内容
 *
 * @param arr 被输出的数组
 * @param len 数组内包含的元素个数
 */
void ShowArr(int* arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%4d", arr[i]);
    }
}

/**
 * @brief 冒泡排序
 *
 * @param arr 被排序的数组
 * @param len 数组内元素个数
 */
void Bubble(int* arr, int len)
{
    // 冒泡排序优化，当不再交换数据是表明排序已经完成，即可停止排序
    int swap;
    for (int i = 0; i < len; i++)
    {
        swap = 0;
        for (int j = 0; j < len - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int tmp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = tmp;
                swap = 1;
            }
        }
        if (swap == 0)
        {
            break;
        }
    }
}

/// <summary>
/// 使用双向冒泡（鸡尾酒）排序算法对整数数组进行原地升序排序。
/// </summary>
/// <param name="a">指向要排序的整数数组的指针。函数将在该数组上原地交换元素。</param>
/// <param name="n">数组中的元素数量,若 n <= 1，则不进行任何操作。</param>
void DoubleBubble(int* a, int n)
{
    int left = 0;
    int right = n - 1;
    while (left < right)
    {
        int flag = 0;

        for (int i = left; i < right; i++)
        {
            if (a[i] > a[i + 1])
            {
                swap(&a[i], &a[i + 1]);
                flag = 1;
            }
        }
        right--;
        if (flag == 0)
        {
            break;
        }
        flag = 0;
        for (int i = right; i > left; i--)
        {
            if (a[i] < a[i - 1])
            {
                swap(&a[i], &a[i - 1]);
                flag = 1;
            }
        }
        left++;
        if (flag == 0)
        {
            break;
        }
    }
}
/**
 * @brief 普通查找（顺序查找遍历数组中的每一个元素进行比对查找）
 *
 * @param arr 被查找的数组
 * @param len 数组内元素个数
 * @param target 查找的目标元素
 * @return int 返回目标元素再在数组中的位置
 */
int FindNormal(int* arr, int len, int target)
{
    for (int i = 0; i < len; i++)
    {
        if (arr[i] == target)
        {
            return i + 1;
        }
    }
    return 0;
}

/**
 * @brief 折半查找
 *
 * @param arr 被查找的数组
 * @param len 数组元素个数
 * @param target 查找目标
 * @return int 返回目标所在数组中的位置
 */
int FindHalf(int* arr, int len, int target)
{
    int front = 0;
    int rear = len;
    while (front < rear)
    {
        int mid = front + (rear - front) / 2;
        {
            if (arr[mid] < target)
            {
                front = mid + 1;
            }
            else if (arr[mid] > target)
            {
                rear = mid;
            }
            else
            {
                return mid + 1;
            }
        }
    }
}

/**
 * @brief 插入排序
 *
 * @param arr 被排序数组
 * @param len 数组元素个数
 */
void InsertSort(int* a, int len)
{
    int i, key;

    // 从数组中的第二个元素开始处理，第一个元素默认已经有序
    for (i = 1; i < len; i++)
    {
        // 当当前元素小于前一个元素时才需要进行插入操作
        if (a[i] < a[i - 1])
        {
            // 把a[i]插入到前面
            int tmp = a[i];
            int j = i - 1;
            do
            {
                a[j + 1] = a[j];
                j--;
            } while (j >= 0 && tmp < a[j]);
            a[j + 1] = tmp;
        }
    }
}

/**
 * @brief 折半插入排序在插入排序的基础上改变了寻找插入位置的逻辑
 *
 * @param a 被排序的数组
 * @param n 数组元素个数
 */
void HalfInsertSort(int* a, int n)
{
    // 从第二个数开始做插入
    for (int i = 1; i < n; i++)
    {
        // 当小于前一个数时才需要插入
        if (a[i] < a[i - 1])
        {
            // 找到插入位置
            int tmp = a[i];
            int left = 0;
            int right = i - 1;
            while (left <= left)
            {
                int mid = (left + right) / 2;
                if (tmp < a[mid])
                {
                    // 缩小查找范围到mid左边
                    right = mid - 1;
                }
                else
                {
                    // 缩小查找范围到mid右边
                    left = mid + 1;
                }
            }
            // 元素后移腾出位置
            for (int j = i - 1; j >= left; j--)
            {
                a[j + 1] = a[j];
            }
            // 插入到目标位置
            a[left] = tmp;
        }
    }
}

/// <summary>
/// 对数组区间 a[left..right] 进行一次原地划分，以 a[left] 作为枢轴元素并将小于枢轴的元素移到左侧，大于枢轴的元素移到右侧。返回枢轴元素最终所在的索引。要求 left 和 right 为有效索引且 left ≤ right。
/// </summary>
/// <param name="a">指向整型数组的指针。函数会就地修改该数组中索引范围 [left..right] 的元素</param>
/// <param name="left">要划分的区间的左端索引（包含）</param>
/// <param name="right">要划分的区间的右端索引（包含）</param>
/// <returns>枢轴元素在划分完成后所在的位置索引（即最终的分界位置）</returns>
int Part(int* a, int left, int right)
{
    int pivot = a[left]; // pivot变量暂时存放枢轴元素
    while (left < right)
    {
        while (left < right && a[right] >= pivot)
        {
            right--;
        }
        a[left] = a[right];
        while (left < right && a[left] <= pivot)
        {
            left++;
        }
        a[right] = a[left];
    }
    a[left] = pivot;
    return left;
}

/**
 * @brief 快速排序
 *
 * @param arr 被排序的数组
 * @param left 数组的最左端元素
 * @param right 数组的最右端元素
 */
void QuickSort(int* arr, int left, int right)
{
    if (left < right)
    {
        int p = Part(arr, left, right);

        QuickSort(arr, left, p - 1);

        QuickSort(arr, p + 1, right);
    }
}

/**
 * @brief 希尔排序(利用了插入排序的优势，提高了排序效率)
 * 增量大的时候分组多，但是组内元素少，效率高
 * 随着增量越来越小，虽然组内元素越来越多，但是也越来越有序，效率也较高
 * @param arr 被排序的数组
 * @param n 数组内元素个数
 */
void ShellSort(int* a, int n)
{
    for (int d = n / 2; d >= 1; d /= 2)
    {
        for (int i = d; i < n; i++)
        {
            if (a[i] < a[i - d])
            {
                int tmp = a[i];
                int j = i - d;
                do
                {
                    a[j + d] = a[j];
                    j -= d;
                } while (j > 0 && a[j] > tmp);
                a[j + d] = tmp;
            }
        }
    }
}

/// <summary>
/// 将数组中以索引 i 为根的子树调整为最大堆，在必要时递归下沉并交换元素
/// </summary>
/// <param name="arr">要堆化的整数数组（以 0 为基索引），函数会就地修改该数组</param>
/// <param name="n">数组的元素个数（长度），用于界限检查，防止访问越界</param>
/// <param name="i">要进行堆化的子树根节点的索引（0 基）</param>
void HeapFiy(int arr[], int n, int i)
{
    // 初始化最大值为根节点
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // 如果左子节点存在且大于根节点则将左子节点的下标赋值给最大值
    if ((left < n) && (arr[left] > arr[largest]))
    {
        largest = left;
    }

    // 如果右子节点存在且大于当前根节点，则将右子节点的下标赋值给最大值下标
    if ((right < n) && (arr[right] > arr[largest]))
    {
        largest = right;
    }

    // 如果最大值不是根节点，交换根节点和当前最大值
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        HeapFiy(arr, n, largest);
    }
}

/**
 * @brief 堆排序
 *
 * @param arr 被排序的数组
 * @param n 数组内元素个数
 */
void HeapSort(int arr[], int n)
{
    // 从下往上进行大顶堆的构建（从最后一个非叶子节点开始）
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        HeapFiy(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);

        HeapFiy(arr, i, 0);
    }
}

/**
 * @brief 数组拷贝函数
 *
 * @param src 被拷贝的数组
 * @param len 背拷贝的数组长度
 * @return int* 返回新数组的首元素指针
 */
int* CopyArray(int* src, int len)
{
    int* dest = (int*)malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++)
    {
        dest[i] = src[i];
    }
    return dest;
}

/// <summary>
/// 将已排序的子数组 a[l..mid] 和 a[mid+1..r] 合并为一个有序区间 a[l..r]。使用临时缓冲区进行稳定合并
/// </summary>
/// <param name="a">指向整数数组的指针，包含要合并的两个已排序子数组</param>
/// <param name="l">左子数组的起始索引</param>
/// <param name="mid">左子数组的结束索引；右子数组从 mid+1 开始</param>
/// <param name="r">右子数组的结束索引</param>
void Merge(int a[], int l, int mid, int r)
{
    int* tmp = (int*)malloc(sizeof(int) * (r - l + 1));
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r)
    {
        if (a[i] <= a[j])
        {
            tmp[k++] = a[i++];
        }
        else
        {
            tmp[k++] = a[j++];
        }
    }

    while (i <= mid)
    {
        tmp[k++] = a[i++];
    }
    while (j <= r)
    {
        tmp[k++] = a[j++];
    }
    for (i = l, k = 0; i <= r; i++, k++)
    {
        a[i] = tmp[k];
    }
    free(tmp);
}

/// <summary>
/// 对数组的指定区间执行递归归并排序。该函数在区间长度大于1时将数组分为两半并调用 Merge 合并
/// </summary>
/// <param name="a">要排序的整型数组。排序在原数组上进行，函数会修改该数组的内容</param>
/// <param name="l">要排序区间的左边界索引</param>
/// <param name="r">要排序区间的右边界索引</param>
void MergeSort(int a[], int l, int r)
{
    if (l < r)
    {
        int mid = (l + r) / 2;
        MergeSort(a, l, mid);
        MergeSort(a, mid + 1, r);
        Merge(a, l, mid, r);
    }
}

int main(int argc, char** argv)
{
    clock_t start, end;
    double bubble_time, bubble_pro_time, insert_time, quick_time, shell_time, heap_time,merge_time;
    srand((unsigned int)time(NULL));
    int len = 30;
    printf("请输入数组长度:\n");
    printf(">>");
    scanf("%d", &len);
    printf("===== 排序算法性能测试 (数组大小: %d) =====\n", len);

    int* init_arr = CreateArr(len);
    printf("\n1. 原始随机数组: \n");
    ShowArr(init_arr, len);

    int* sorted = CopyArray(init_arr, len);
    ShellSort(sorted, len); // 先给它排序，作为折半查找的目标数组

    printf("\n--- 测试冒泡排序 ---\n");
    int* arr_bubble = CopyArray(init_arr, len);
    start = clock();
    Bubble(arr_bubble, len);
    end = clock();
    printf("排序后数组: \n");
    bubble_time = ((double)end - (double)start) / CLOCKS_PER_SEC;
    ShowArr(arr_bubble, len);
    printf("冒泡排序所用时长为%.6lf秒\n", bubble_time);


    printf("\n--- 测试双向冒泡排序 ---\n");
    int* arr_doublebubble = CopyArray(init_arr, len);
    start = clock();
    DoubleBubble(arr_doublebubble, len);
    end = clock();
    printf("排序后数组: \n");
    bubble_pro_time = ((double)end - (double)start) / CLOCKS_PER_SEC;
    ShowArr(arr_doublebubble, len);

    printf("\n--- 测试插入排序 ---\n");
    int* arr_insert = CopyArray(init_arr, len);
    start = clock();
    InsertSort(arr_insert, len);
    end = clock();
    printf("排序后数组: \n");
    insert_time = ((double)end - (double)start) / CLOCKS_PER_SEC;
    ShowArr(arr_insert, len);

    printf("\n--- 测试快速排序 ---\n");
    int* arr_quick = CopyArray(init_arr, len);
    QuickSort(arr_quick, 0, len - 1);
    printf("排序后数组: \n");
    ShowArr(arr_quick, len);

    printf("\n--- 测试希尔排序 ---\n");
    int* arr_shell = CopyArray(init_arr, len);
    ShellSort(arr_shell, len);
    printf("排序后数组: \n");
    ShowArr(arr_shell, len);

    printf("\n--- 测试堆排序 ---\n");
    int* arr_heap = CopyArray(init_arr, len);
    HeapSort(arr_heap, len);
    printf("排序后数组: \n");
    ShowArr(arr_heap, len);

    printf("\n--- 测试归并排序 ---\n");
    int* arr_merge = CopyArray(init_arr, len);
    HeapSort(arr_merge, len);
    printf("排序后数组: \n");
    ShowArr(arr_merge, len);

    printf("\n===== 查找功能演示 =====\n");
    printf("\n目标数组 (已排序): \n");
    ShowArr(sorted, len);
    printf("\n");
    printf("冒泡排序所需时间为%.6lf秒\n", bubble_time);
    printf("双向冒泡排序所需时间为%.6lf秒\n", bubble_pro_time);
    int target;
    printf("\n请输入你想要查找的数：\n");
    printf(">>");
    scanf("%d", &target);

    int pos_normal = FindNormal(init_arr, len, target); // 在原始无序数组中查找
    if (pos_normal == 0)
    {
        printf("普通查找: 当前所有数中并没有您想要查找的数 %d\n", target);
    }
    else
    {
        printf("普通查找: 找到您想要查找的数 %d，它在原始数组中的第%d个位置\n", target, pos_normal);
    }

    int pos_half = FindHalf(sorted, len, target); // 在有序副本中查找
    if (pos_half == 0)
    {
        printf("折半查找: 当前所有数中并没有您想要查找的数 %d\n", target);
    }
    else
    {
        printf("折半查找: 找到您想要查找的数 %d，它在有序数组中的第%d个元素\n", target, pos_half);
    }
    return 0;
}
