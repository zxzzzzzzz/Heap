#ifndef INDEXMAXHEAP_H
#define INDEXMAXHEAP_H

#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

template<typename Item>
class IndexMaxHeap {

private:
	Item *data;
	int *indexes;
	int *reverse;

	int count;
	int capacity;

	void shiftUp(int k) {

		while (k > 1 && data[indexes[k / 2]] > data[indexes[k]]) {
			swap(indexes[k / 2], indexes[k]);
			reverse[indexes[k / 2]] = k / 2;
			reverse[indexes[k]] = k;
			k /= 2;
		}
	}

	void shiftDown(int k) {

		while (2 * k <= count) {
			int j = 2 * k;
			if (j + 1 <= count && data[indexes[j + 1]] > data[indexes[j]])
				j += 1;

			if (data[indexes[k]] <= data[indexes[j]])
				break;

			swap(indexes[k], indexes[j]);
			reverse[indexes[k]] = k;
			reverse[indexes[j]] = j;
			k = j;
		}
	}

public:
	IndexMaxHeap(int capacity) {

		data = new Item[capacity + 1];
		indexes = new int[capacity + 1];
		reverse = new int[capacity + 1];

		for (int i = 0; i <= capacity; i++)
			reverse[i] = 0;

		count = 0;
		this->capacity = capacity;
	}

	~IndexMaxHeap() {
		delete[] data;
		delete[] indexes;
		delete[] reverse;
	}

	int size() {
		return count;
	}

	bool isEmpty() {
		return count == 0;
	}

	// 传入的i对用户而言,是从0索引的
	void insert(int index, Item item) {
		assert(count + 1 <= capacity);
		assert(index + 1 >= 1 && index + 1 <= capacity);

		index += 1;
		data[index] = item;
		indexes[count + 1] = index;
		reverse[index] = count + 1;
		count++;
		shiftUp(count);
	}

	Item extractMax() {
		assert(count > 0);

		Item ret = data[indexes[1]];
		swap(indexes[1], indexes[count]);
		reverse[indexes[count]] = 0;
		reverse[indexes[1]] = 1;
		count--;
		shiftDown(1);
		return ret;
	}

	int extractMaxIndex() {
		assert(count > 0);

		int ret = indexes[1] - 1;
		swap(indexes[1], indexes[count]);
		reverse[indexes[count]] = 0;
		reverse[indexes[1]] = 1;
		count--;
		shiftDown(1);
		return ret;
	}

	Item getMax() {
		assert(count > 0);
		return data[indexes[1]];
	}

	int getMaxIndex() {
		assert(count > 0);
		return indexes[1] - 1;
	}

	bool contain(int index) {

		return reverse[index + 1] != 0;
	}

	Item getItem(int index) {
		assert(contain(index));
		return data[index + 1];
	}

	void change(int index, Item newItem) {

		assert(contain(index));
		index += 1;
		data[index] = newItem;


		// 找到indexes[j] = i, j表示data[i]在堆中的位置
		// 之后shiftUp(j), 再shiftDown(j)

		//        for( int j = 1 ; j <= count ; j ++ )
		//            if( indexes[j] == i ){
		//                shiftUp(j);
		//                shiftDown(j);
		//                return;
		//            }
		shiftUp(reverse[index]);
		shiftDown(reverse[index]);
	}


	
	// test reverse index
	/*bool testReverseIndex() {

		int *copyIndexes = new int[count + 1];
		int *copyReverseIndexes = new int[count + 1];

		for (int i = 0; i <= count; i++) {
			copyIndexes[i] = indexes[i];
			copyReverseIndexes[i] = reverse[i];
		}

		copyIndexes[0] = copyReverseIndexes[0] = 0;
		std::sort(copyIndexes, copyIndexes + count + 1);
		std::sort(copyReverseIndexes, copyReverseIndexes + count + 1);

		bool res = true;
		for (int i = 1; i <= count; i++)
			if (copyIndexes[i - 1] + 1 != copyIndexes[i] || copyReverseIndexes[i - 1] + 1 != copyReverseIndexes[i])
				res = res || false;

		delete[] copyIndexes;
		delete[] copyReverseIndexes;

		if (!res) {
			cout << "Error 1" << endl;
			return res;
		}

		for (int i = 1; i <= count; i++)
			if (reverse[indexes[i]] != i) {
				cout << "Error 2" << endl;
				return false;
			}

		return true;
	}*/
};


#endif // !MAXHEAP_H

//测试f反向索引堆的代码
//int main() {
//
//	int n = 1000000;
//
//	Priority* arr = new Priority[n];
//	srand(time(NULL));
//	for (int i = 0; i < n; i++)
//		arr[i] = rand() % n;
//	SortTestHelper::testSort("Heap Sort Using Index-Max-Heap", heapSortUsingIndexMaxHeap, arr, n);
//	delete[] arr;
//
//	return 0;
//}

