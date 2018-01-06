#include<iostream>
#include<vector>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/timer.hpp>
 
boost::thread_group grp;//线程组，管理所有子线程
 
void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
 
//插入排序
void insertionSort(int *arr, unsigned int size) {
	for (unsigned int i = 1; i != size; ++i) {
		for (int j = i; j != 0; --j) {
			if (arr[j] < arr[j - 1]) {
				swap(&arr[j], &arr[j - 1]);
			}
			else {
				break;
			}
		}
	}
}
 
//QuickSort的辅助函数，选取一个随机元素作为子数组的划分
int partition(int *arr, int start, int end) {
	int part_index = start + float(rand()) * 
		(end - start) / RAND_MAX; 
	int part_elem = arr[part_index];
	swap(&arr[part_index], &arr[end]);
	int j = start - 1;
	for (unsigned int i = start; i != end + 1; ++i) {
		if (arr[i] <= part_elem) {
			++j;
			swap(&arr[j], &arr[i]);
		}
	}
	return j;
}
 
bool acquire_thread() {
	//将当前CPU支持的线程数作为最大线程数
	static int valid_threads = boost::thread::hardware_concurrency() - 1;
	static boost::mutex mt;
	mt.lock();
	if (valid_threads < 1) {
		mt.unlock();
		return false;
	}
	valid_threads--;
	mt.unlock();
	return true;
}
 
void concurrent_quicksort(int *arr, int start, int end) {
	if (start >= end) {
		return;
	}
	//在子数组长度小于150时切换到插入排序
	if (end - start < 150) {
		insertionSort(&arr[start], end - start + 1);
		return;
	}
	int part_index = partition(arr, start, end);
	if (acquire_thread()) {
		grp.create_thread(boost::bind(concurrent_quicksort,
			arr, start, part_index - 1));
	}
	else {
		concurrent_quicksort(arr, start, part_index - 1);
	}
	concurrent_quicksort(arr, part_index + 1, end);
}
 
void generateArray(int **arr, int min, int max, unsigned int size) {
	srand(time(0));
	*arr = new int[size];
	for (unsigned int i = 0; i != size; ++i) {
		(*arr)[i] = rand();
	}
}
 
//检验一个数组是否被正确地排序
bool validate_sorted_array(int *arr, unsigned int size) {
	for (unsigned int i = 0; i < size - 1; ++i) {
		if (arr[i] > arr[i + 1]) {
			return false;
		}
	}
	return true;
}
 
int main() {
	unsigned int siz = 8000000;
	int *array;
	std::vector<int> test(siz);
	for (int i = 0; i != siz; ++i) {
		test[i] = rand();
	}
	generateArray(&array, 0, siz, siz);
	std::cout << "-Start sorting-\n";
	boost::timer timer;
	concurrent_quicksort(array, 0, siz - 1);
	grp.join_all();
	std::cout << "elapsed:" << timer.elapsed() << "s\n";
	std::cout << (validate_sorted_array(array, siz) ?
		"correctly sorted" : "incorrectly sorted") << "\n";
	delete [] array;
	return 0;
}


