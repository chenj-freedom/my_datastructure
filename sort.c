/* 各种排序算法，参考链接（包含各种算法描述，动图展示）：
 * https://blog.csdn.net/chenj_freedom/article/details/80346354
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define DIFFTIME_MS(start, end) (clock_t)((float)(end - start) / CLOCKS_PER_SEC * 1000) //耗时 单位：毫秒
#define TESTNUM 80000 //测试的数组大小
//#define PRINT_SWITCH  //打印数组的开关

void PrintArray(int* _array, int _len) {
	for (int i = 0; i < _len; i++) {
		printf("%d ", _array[i]);
	}
	printf("\n");
}

/* 冒泡排序
 * 算法描述：
 * step1：比较相邻的元素。如果第一个比第二个大，就交换它们两个；
 * step2：对每一对相邻元素作同样的工作，从开始第一对到结尾的最后一对，这样在最后的元素应该会是最大的数；
 * step3：针对所有的元素重复以上的步骤，除了最后一个；
 * step4：重复步骤1~3，直到排序完成。
 *
 * @param _array：待排序数组
 * @param _len：数组长度
 */
void BubbleSort(int* _array, int _len) {
	int i = 0, j = 0;

	for (i = 0; i < _len; i++) {
		for (j = 0; j < _len - i - 1; j++) {
			if (_array[j] > _array[j + 1]) {
				int temp = _array[j + 1];
				_array[j + 1] = _array[j];
				_array[j] = temp;
			}
		}
	}
}

/* 冒泡排序优化
 * 算法描述：
 * 在基础冒泡排序的基础上，增加一个标志位来记录是否有发生数据交换，
 * 如果没有发生数据交换，说明序列已经有序，不需要再排了。
 *
 * @param _array：待排序数组
 * @param _len：数组长度
 */
void BubbleSortOptimize(int* _array, int _len) {
	int i = 0, j = 0;
	int flag = 0;

	for (i = 0; i < _len; i++) {
		for (j = 0; j < _len - i - 1; j++) {
			if (_array[j] > _array[j + 1]) {
				flag = 1;
				int temp = _array[j + 1];
				_array[j + 1] = _array[j];
				_array[j] = temp;
			}
		}

		if (flag == 0) break;
	}
}

/* 选择排序
 * 算法描述：
 * 首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置，
 * 然后，再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序
 * 序列的末尾。以此类推，直到所有元素均排序完毕。 
 *
 * @param _array：待排序数组
 * @param _len：数组长度
 */
void SelectionSort(int* _array, int _len) {
	int i = 0, j = 0;
	int minIndex = 0;
	
	for (i = 0; i < _len; i++) {
		minIndex = i;

		for (j = i + 1; j < _len; j++) {
			if (_array[j] < _array[minIndex]) {
				minIndex = j;
			}
		}

		if (minIndex != i) {
			int temp = _array[i];
			_array[i] = _array[minIndex];
			_array[minIndex] = temp;
		}
	}
}

/* 插入排序
 * 算法描述：
 * 通过构建有序序列，对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。
 * step1：从第一个元素开始，该元素可以认为已经被排序；
 * step2：取出下一个元素，在已经排序的元素序列中从后向前扫描；
 * step3：如果该元素（已排序）大于新元素，将该元素移到下一位置；
 * step4：重复步骤3，直到找到已排序的元素小于或者等于新元素的位置；
 * step5：将新元素插入到该位置后；
 * step6：重复步骤2~5。
 *
 * @param _array：待排序数组
 * @param _len：数组长度
 */
void InsertionSort(int* _array, int _len) {
	int i = 0, j = 0;
	int preIndex = 0;
	int current = 0;

	for (i = 1; i < _len; i++) {
		current = _array[i];
		preIndex = i - 1;
		while (preIndex >= 0 && _array[preIndex] > current) {
			_array[preIndex + 1] = _array[preIndex];
			preIndex--;
		}

		_array[preIndex + 1] = current;
	}
}

/* 希尔排序（缩小增量排序）
 * 算法描述：
 * 希尔排序是把序列按下标的一定增量分组，对每组使用直接插入排序算法排序；
 * 随着增量逐渐减少，每组包含的关键词越来越多，当增量减至1时，整个序列恰被分成一组，算法便终止。
 *
 * @param _array：待排序数组
 * @param _len：数组长度
 */
void ShellSort(int* _array, int _len) {
	int gap = 0;
	int i = 0, j = 0;
	int preIndex = 0;
	int current = 0;

	for (gap = _len / 2; gap > 0; gap /= 2) { //条件gap>0，即直到1为止；循环操作 gap /= 2
		for (i = gap; i < _len; i++) {
			current = _array[i];
			preIndex = i - gap;
			while (preIndex >= 0 && _array[preIndex] > current) {
				_array[preIndex + gap] = _array[preIndex];
				preIndex -= gap;
			}

			_array[preIndex + gap] = current;
		}
	}
}

/* 快速排序
 * 算法描述：
 * 通过一趟排序将待排序列分割成独立的两部分，其中一部分序列的关键字
 * 均比另一部分的关键字小，则可分别对这两部分序列继续进行排序，以达到整个序列有序。
 * step1： 设置两个变量i、j，排序开始的时候：i=0，j=N-1；
 * step2：以第一个数组元素作为关键数据，赋值给key，即key=_array[0]；
 * step3：从j开始向前搜索，即由后开始向前搜索(j--)，找到第一个小于key的值_array[j]，将_array[j]和_array[i]互换；
 * step4：从i开始向后搜索，即由前开始向后搜索(i++)，找到第一个大于key的_array[i]，将_array[i]和_array[j]互换；
 * step5：重复第3、4步，直到i=j；
 *
 * @param _array：待排序序列
 * @param _left：待排序序列的开始索引（左索引）
 * @param _right：待排序序列的结束索引（右索引）
 */
void QuickSort(int* _array, int _left, int _right) {
	if (_left >= _right) return;

	int key = _array[_left];
	int i = _left, j = _right;

	while (1) {
		while (i < j) {
			if (_array[j] < key) {
				int temp = _array[j];
				_array[j] = _array[i];
				_array[i] = temp;
				break;
			}
			j--;
		}

		if (i >= j) break;

		while (i < j) {
			if (_array[i] > key) {
				int temp = _array[i];
				_array[i] = _array[j];
				_array[j] = temp;
				break;
			}
			i++;
		}

		if (i >= j) break;
	}

	QuickSort(_array, _left, i-1);
	QuickSort(_array, j+1, _right);
}

/* merge _array[first..mid] and _array[mid+1..last] */
void Merge(int* _array, int first, int mid, int last, int* _merge_array) {
	int i = first, j = mid;
	int m = mid+1, n = last;
	int k = 0;

	while (i <= j && m <= n) {
		if (_array[i] < _array[m]) {
			_merge_array[k] = _array[i];
			k++;
			i++;
		} else {
			_merge_array[k] = _array[m];
			k++;
			m++;
		}
	}

	while (i <= j) {
		_merge_array[k] = _array[i];
		k++;
		i++;
	}

	while (m <= n) {
		_merge_array[k] = _array[m];
		k++;
		m++;
	}

	for (i = 0; i < k; i++) {
		_array[i + first] = _merge_array[i];
	}
}

/* 归并排序
 * 算法描述：
 * 将已有序的子序列合并，得到完全有序的序列；即先使每个子序列有序，再使子序列段间有序。
 * 该算法是分治法的典型应用，分割到最后就是两个元素的合并。
 *
 * @param _array：待排序序列
 * @param _left：待排序序列的开始索引（左索引）
 * @param _right：待排序序列的结束索引（右索引）
 * @param _temp：该算法中间运算需要用到的临时数组
 */
void MergeSort(int* _array, int _left, int _right, int* _temp) {
	if (_left < _right) {
		int mid = (_right + _left) / 2;
		MergeSort(_array, _left, mid, _temp);
		MergeSort(_array, mid+1, _right, _temp);
		Merge(_array, _left, mid, _right, _temp);
	}
}



void main() {
	int array[TESTNUM] = {0};
	srand((unsigned int)time(0));
	printf("开始生成 %d 个数的原始随机无序序列...\n", TESTNUM);
	for (int i = 0; i < TESTNUM; i++) {
		array[i] = (int)((double)(rand()) / RAND_MAX * TESTNUM) % TESTNUM;
	}
	printf("生成成功...\n");
#ifdef PRINT_SWITCH
	PrintArray(array, TESTNUM);
#endif

	getchar();

	printf("开始测试各种排序的耗时...\n");

	clock_t difftime = 0, startClock = 0, endClock = 0;
	int temp[TESTNUM] = { 0 };

	////////////////////////////////////////测试冒泡排序/////////////////////////////////////////////////////
	printf("测试冒泡排序...\n");
	for (int i = 0; i < TESTNUM; i++) {
		temp[i] = array[i];
	}

	startClock = clock();
	BubbleSort(temp, TESTNUM);
	endClock = clock();
	difftime = DIFFTIME_MS(startClock, endClock); //ms
	
#ifdef PRINT_SWITCH
	printf("排序后的数组:\n");
	PrintArray(temp, TESTNUM);
#endif

	printf("冒泡排序 %d个数 耗时：%ld ms...\n", TESTNUM, difftime);

	getchar();

	////////////////////////////////////////测试冒泡排序优化/////////////////////////////////////////////////////
	printf("测试冒泡排序优化...\n");
	for (int i = 0; i < TESTNUM; i++) {
		temp[i] = array[i];
	}

	startClock = clock();
	BubbleSortOptimize(temp, TESTNUM);
	endClock = clock();
	difftime = DIFFTIME_MS(startClock, endClock); //ms
	
#ifdef PRINT_SWITCH
	printf("排序后的数组:\n");
	PrintArray(temp, TESTNUM);
#endif

	printf("冒泡排序优化 %d个数 耗时：%ld ms...\n", TESTNUM, difftime);

	getchar();

	////////////////////////////////////////测试选择排序/////////////////////////////////////////////////////
	printf("测试选择排序...\n");
	for (int i = 0; i < TESTNUM; i++) {
		temp[i] = array[i];
	}

	startClock = clock();
	SelectionSort(temp, TESTNUM);
	endClock = clock();
	difftime = DIFFTIME_MS(startClock, endClock); //ms
	
#ifdef PRINT_SWITCH
	printf("排序后的数组:\n");
	PrintArray(temp, TESTNUM);
#endif

	printf("选择排序 %d个数 耗时：%ld ms...\n", TESTNUM, difftime);

	getchar();

	////////////////////////////////////////测试插入排序/////////////////////////////////////////////////////
	printf("测试插入排序...\n");
	for (int i = 0; i < TESTNUM; i++) {
		temp[i] = array[i];
	}

	startClock = clock();
	InsertionSort(temp, TESTNUM);
	endClock = clock();
	difftime = DIFFTIME_MS(startClock, endClock); //ms
	
#ifdef PRINT_SWITCH
	printf("排序后的数组:\n");
	PrintArray(temp, TESTNUM);
#endif

	printf("插入排序 %d个数 耗时：%ld ms...\n", TESTNUM, difftime);

	getchar();

	////////////////////////////////////////测试希尔排序/////////////////////////////////////////////////////
	printf("测试希尔排序...\n");
	for (int i = 0; i < TESTNUM; i++) {
		temp[i] = array[i];
	}

	startClock = clock();
	ShellSort(temp, TESTNUM);
	endClock = clock();
	difftime = DIFFTIME_MS(startClock, endClock); //ms

#ifdef PRINT_SWITCH
	printf("排序后的数组:\n");
	PrintArray(temp, TESTNUM);
#endif

	printf("希尔排序 %d个数 耗时：%ld ms...\n", TESTNUM, difftime);

	getchar();

	////////////////////////////////////////测试快速排序/////////////////////////////////////////////////////
	printf("测试快速排序...\n");
	for (int i = 0; i < TESTNUM; i++) {
		temp[i] = array[i];
	}

	startClock = clock();
	QuickSort(temp, 0, TESTNUM - 1);
	endClock = clock();
	difftime = DIFFTIME_MS(startClock, endClock); //ms
	
#ifdef PRINT_SWITCH
	printf("排序后的数组:\n");
	PrintArray(temp, TESTNUM);
#endif

	printf("快速排序 %d个数 耗时：%ld ms...\n", TESTNUM, difftime);

	getchar();

	////////////////////////////////////////测试归并排序/////////////////////////////////////////////////////
	printf("测试归并排序...\n");
	for (int i = 0; i < TESTNUM; i++) {
		temp[i] = array[i];
	}

	int temp1[TESTNUM] = { 0 };

	startClock = clock();
	MergeSort(temp, 0, TESTNUM - 1, temp1);
	endClock = clock();
	difftime = DIFFTIME_MS(startClock, endClock); //ms
	
#ifdef PRINT_SWITCH
	printf("排序后的数组:\n");
	PrintArray(temp, TESTNUM);
#endif

	printf("归并排序 %d个数 耗时：%ld ms...\n", TESTNUM, difftime);

	getchar();
	getchar();
	getchar();
}
