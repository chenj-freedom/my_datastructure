/* ���������㷨���ο����ӣ����������㷨��������ͼչʾ����
 * https://blog.csdn.net/chenj_freedom/article/details/80346354
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define DIFFTIME_MS(start, end) (clock_t)((float)(end - start) / CLOCKS_PER_SEC * 1000) //��ʱ ��λ������
#define TESTNUM 80000 //���Ե������С
//#define PRINT_SWITCH  //��ӡ����Ŀ���

void PrintArray(int* _array, int _len) {
	for (int i = 0; i < _len; i++) {
		printf("%d ", _array[i]);
	}
	printf("\n");
}

/* ð������
 * �㷨������
 * step1���Ƚ����ڵ�Ԫ�ء������һ���ȵڶ����󣬾ͽ�������������
 * step2����ÿһ������Ԫ����ͬ���Ĺ������ӿ�ʼ��һ�Ե���β�����һ�ԣ�����������Ԫ��Ӧ�û�����������
 * step3��������е�Ԫ���ظ����ϵĲ��裬�������һ����
 * step4���ظ�����1~3��ֱ��������ɡ�
 *
 * @param _array������������
 * @param _len�����鳤��
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

/* ð�������Ż�
 * �㷨������
 * �ڻ���ð������Ļ����ϣ�����һ����־λ����¼�Ƿ��з������ݽ�����
 * ���û�з������ݽ�����˵�������Ѿ����򣬲���Ҫ�����ˡ�
 *
 * @param _array������������
 * @param _len�����鳤��
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

/* ѡ������
 * �㷨������
 * ������δ�����������ҵ���С����Ԫ�أ���ŵ��������е���ʼλ�ã�
 * Ȼ���ٴ�ʣ��δ����Ԫ���м���Ѱ����С����Ԫ�أ�Ȼ��ŵ�������
 * ���е�ĩβ���Դ����ƣ�ֱ������Ԫ�ؾ�������ϡ� 
 *
 * @param _array������������
 * @param _len�����鳤��
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

/* ��������
 * �㷨������
 * ͨ�������������У�����δ�������ݣ��������������дӺ���ǰɨ�裬�ҵ���Ӧλ�ò����롣
 * step1���ӵ�һ��Ԫ�ؿ�ʼ����Ԫ�ؿ�����Ϊ�Ѿ�������
 * step2��ȡ����һ��Ԫ�أ����Ѿ������Ԫ�������дӺ���ǰɨ�裻
 * step3�������Ԫ�أ������򣩴�����Ԫ�أ�����Ԫ���Ƶ���һλ�ã�
 * step4���ظ�����3��ֱ���ҵ��������Ԫ��С�ڻ��ߵ�����Ԫ�ص�λ�ã�
 * step5������Ԫ�ز��뵽��λ�ú�
 * step6���ظ�����2~5��
 *
 * @param _array������������
 * @param _len�����鳤��
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

/* ϣ��������С��������
 * �㷨������
 * ϣ�������ǰ����а��±��һ���������飬��ÿ��ʹ��ֱ�Ӳ��������㷨����
 * ���������𽥼��٣�ÿ������Ĺؼ���Խ��Խ�࣬����������1ʱ����������ǡ���ֳ�һ�飬�㷨����ֹ��
 *
 * @param _array������������
 * @param _len�����鳤��
 */
void ShellSort(int* _array, int _len) {
	int gap = 0;
	int i = 0, j = 0;
	int preIndex = 0;
	int current = 0;

	for (gap = _len / 2; gap > 0; gap /= 2) { //����gap>0����ֱ��1Ϊֹ��ѭ������ gap /= 2
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

/* ��������
 * �㷨������
 * ͨ��һ�����򽫴������зָ�ɶ����������֣�����һ�������еĹؼ���
 * ������һ���ֵĹؼ���С����ɷֱ�������������м������������Դﵽ������������
 * step1�� ������������i��j������ʼ��ʱ��i=0��j=N-1��
 * step2���Ե�һ������Ԫ����Ϊ�ؼ����ݣ���ֵ��key����key=_array[0]��
 * step3����j��ʼ��ǰ���������ɺ�ʼ��ǰ����(j--)���ҵ���һ��С��key��ֵ_array[j]����_array[j]��_array[i]������
 * step4����i��ʼ�������������ǰ��ʼ�������(i++)���ҵ���һ������key��_array[i]����_array[i]��_array[j]������
 * step5���ظ���3��4����ֱ��i=j��
 *
 * @param _array������������
 * @param _left�����������еĿ�ʼ��������������
 * @param _right�����������еĽ�����������������
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

/* �鲢����
 * �㷨������
 * ��������������кϲ����õ���ȫ��������У�����ʹÿ��������������ʹ�����жμ�����
 * ���㷨�Ƿ��η��ĵ���Ӧ�ã��ָ����������Ԫ�صĺϲ���
 *
 * @param _array������������
 * @param _left�����������еĿ�ʼ��������������
 * @param _right�����������еĽ�����������������
 * @param _temp�����㷨�м�������Ҫ�õ�����ʱ����
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
	printf("��ʼ���� %d ������ԭʼ�����������...\n", TESTNUM);
	for (int i = 0; i < TESTNUM; i++) {
		array[i] = (int)((double)(rand()) / RAND_MAX * TESTNUM) % TESTNUM;
	}
	printf("���ɳɹ�...\n");
#ifdef PRINT_SWITCH
	PrintArray(array, TESTNUM);
#endif

	getchar();

	printf("��ʼ���Ը�������ĺ�ʱ...\n");

	clock_t difftime = 0, startClock = 0, endClock = 0;
	int temp[TESTNUM] = { 0 };

	////////////////////////////////////////����ð������/////////////////////////////////////////////////////
	printf("����ð������...\n");
	for (int i = 0; i < TESTNUM; i++) {
		temp[i] = array[i];
	}

	startClock = clock();
	BubbleSort(temp, TESTNUM);
	endClock = clock();
	difftime = DIFFTIME_MS(startClock, endClock); //ms
	
#ifdef PRINT_SWITCH
	printf("����������:\n");
	PrintArray(temp, TESTNUM);
#endif

	printf("ð������ %d���� ��ʱ��%ld ms...\n", TESTNUM, difftime);

	getchar();

	////////////////////////////////////////����ð�������Ż�/////////////////////////////////////////////////////
	printf("����ð�������Ż�...\n");
	for (int i = 0; i < TESTNUM; i++) {
		temp[i] = array[i];
	}

	startClock = clock();
	BubbleSortOptimize(temp, TESTNUM);
	endClock = clock();
	difftime = DIFFTIME_MS(startClock, endClock); //ms
	
#ifdef PRINT_SWITCH
	printf("����������:\n");
	PrintArray(temp, TESTNUM);
#endif

	printf("ð�������Ż� %d���� ��ʱ��%ld ms...\n", TESTNUM, difftime);

	getchar();

	////////////////////////////////////////����ѡ������/////////////////////////////////////////////////////
	printf("����ѡ������...\n");
	for (int i = 0; i < TESTNUM; i++) {
		temp[i] = array[i];
	}

	startClock = clock();
	SelectionSort(temp, TESTNUM);
	endClock = clock();
	difftime = DIFFTIME_MS(startClock, endClock); //ms
	
#ifdef PRINT_SWITCH
	printf("����������:\n");
	PrintArray(temp, TESTNUM);
#endif

	printf("ѡ������ %d���� ��ʱ��%ld ms...\n", TESTNUM, difftime);

	getchar();

	////////////////////////////////////////���Բ�������/////////////////////////////////////////////////////
	printf("���Բ�������...\n");
	for (int i = 0; i < TESTNUM; i++) {
		temp[i] = array[i];
	}

	startClock = clock();
	InsertionSort(temp, TESTNUM);
	endClock = clock();
	difftime = DIFFTIME_MS(startClock, endClock); //ms
	
#ifdef PRINT_SWITCH
	printf("����������:\n");
	PrintArray(temp, TESTNUM);
#endif

	printf("�������� %d���� ��ʱ��%ld ms...\n", TESTNUM, difftime);

	getchar();

	////////////////////////////////////////����ϣ������/////////////////////////////////////////////////////
	printf("����ϣ������...\n");
	for (int i = 0; i < TESTNUM; i++) {
		temp[i] = array[i];
	}

	startClock = clock();
	ShellSort(temp, TESTNUM);
	endClock = clock();
	difftime = DIFFTIME_MS(startClock, endClock); //ms

#ifdef PRINT_SWITCH
	printf("����������:\n");
	PrintArray(temp, TESTNUM);
#endif

	printf("ϣ������ %d���� ��ʱ��%ld ms...\n", TESTNUM, difftime);

	getchar();

	////////////////////////////////////////���Կ�������/////////////////////////////////////////////////////
	printf("���Կ�������...\n");
	for (int i = 0; i < TESTNUM; i++) {
		temp[i] = array[i];
	}

	startClock = clock();
	QuickSort(temp, 0, TESTNUM - 1);
	endClock = clock();
	difftime = DIFFTIME_MS(startClock, endClock); //ms
	
#ifdef PRINT_SWITCH
	printf("����������:\n");
	PrintArray(temp, TESTNUM);
#endif

	printf("�������� %d���� ��ʱ��%ld ms...\n", TESTNUM, difftime);

	getchar();

	////////////////////////////////////////���Թ鲢����/////////////////////////////////////////////////////
	printf("���Թ鲢����...\n");
	for (int i = 0; i < TESTNUM; i++) {
		temp[i] = array[i];
	}

	int temp1[TESTNUM] = { 0 };

	startClock = clock();
	MergeSort(temp, 0, TESTNUM - 1, temp1);
	endClock = clock();
	difftime = DIFFTIME_MS(startClock, endClock); //ms
	
#ifdef PRINT_SWITCH
	printf("����������:\n");
	PrintArray(temp, TESTNUM);
#endif

	printf("�鲢���� %d���� ��ʱ��%ld ms...\n", TESTNUM, difftime);

	getchar();
	getchar();
	getchar();
}
