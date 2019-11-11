#include <iostream>
#include <chrono>	//to use time 
#include <algorithm> //to use min function
using namespace std;
using namespace std::chrono;
void randomGenrator(int arr[], int size)
{
	for (int i = 0; i < size;i++)
	{
		arr[i] = rand()%1000+1;
	}
}

void printArray(int arr[], int size)
{
	for (int i = 0; i < size; i++)
		cout << i << "=> " << arr[i] << endl;
}
void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void bubbleSort(int arr[], int n)
{
	bool swaper;
	for (int i = 0; i < n - 1; i++)
	{
		swaper = false;
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(&arr[j], &arr[j + 1]);
				swaper = true;
			}
		}
		if (swaper == false)
			break;
	}
}

void selectionSort(int arr[], int n)
{
	int i, j, min_idx; 
	for (i = 0; i < n - 1; i++)
	{
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j; 
		swap(&arr[min_idx], &arr[i]);
	}
}
void heapify(int arr[], int n, int i)
{
	int largest = i; 
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && arr[l] > arr[largest])
		largest = l;
	if (r < n && arr[r] > arr[largest])
		largest = r;
	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		heapify(arr, n, largest);
	}
}
void heapSort(int arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);
	for (int i = n - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}

int getMax(int arr[], int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}
void countSort(int arr[], int n, int exp)
{
	int *output = new int[n];
	int i, count[10] = { 0 };
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];
	for (i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}
	for (i = 0; i < n; i++)
		arr[i] = output[i];
}
void radixsort(int arr[], int n)
{
	int m = getMax(arr, n);
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, n, exp);
}
int shellSort(int arr[], int n)
{
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < n; i += 1)
		{
			int temp = arr[i];
			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
				arr[j] = arr[j - gap];
			arr[j] = temp;
		}
	}
	return 0;
}

int k = 0;
void Counting_Sort(int A[], int B[], int n)
{
	int *C=new int[k];
	for (int i = 0;i<k + 1;i++)
	{
		C[i] = 0;
	}
	for (int j = 1;j < n;j++)
	{
		C[A[j]]++;
	}
	for (int i = 1;i <= k;i++)
	{
		C[i] += C[i - 1];
	}
	for (int j = n-1;j >= 1;j--)
	{
		B[C[A[j]]] = A[j];
		C[A[j]] = C[A[j]] - 1;
	}
}
bool isSorted(int a[], int n)
{
	while (--n > 0)
		if (a[n] < a[n - 1])
			return false;
	return true;
}
void shuffle(int a[], int n)
{
	for (int i = 0; i < n; i++)
		swap(a[i], a[rand() % n]);
}
void bogosort(int a[], int n)
{
	while (!isSorted(a, n))
		shuffle(a, n);
}

const int RUN = 32;

void insertionSort(int arr[], int left, int right)
{
	for (int i = left + 1; i <= right; i++)
	{
		int temp = arr[i];
		int j = i - 1;
		while (arr[j] > temp && j >= left)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = temp;
	}
}
void merge(int arr[], int l, int m, int r)
{
	int len1 = m - l + 1, len2 = r - m;
	int *left=new int[len1], *right=new int[len2];
	for (int i = 0; i < len1; i++)
		left[i] = arr[l + i];
	for (int i = 0; i < len2; i++)
		right[i] = arr[m + 1 + i];

	int i = 0;
	int j = 0;
	int k = l;
	while (i < len1 && j < len2)
	{
		if (left[i] <= right[j])
		{
			arr[k] = left[i];
			i++;
		}
		else
		{
			arr[k] = right[j];
			j++;
		}
		k++;
	}
	while (i < len1)
	{
		arr[k] = left[i];
		k++;
		i++;
	}
	while (j < len2)
	{
		arr[k] = right[j];
		k++;
		j++;
	}
}
void timSort(int arr[], int n)
{
	for (int i = 0; i < n; i += RUN)
		insertionSort(arr, i, min((i + 31), (n - 1)));
	for (int size = RUN; size < n; size = 2 * size)
	{
		for (int left = 0; left < n; left += 2 * size)
		{
			int mid = left + size - 1;
			int right = min((left + 2 * size - 1), (n - 1));
			merge(arr, left, mid, right);
		}
	}
}

void oddEvenSort(int arr[], int n)
{
	bool isSorted = false;

	while (!isSorted)
	{
		isSorted = true;
		for (int i = 1; i <= n - 2; i = i + 2)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(arr[i], arr[i + 1]);
				isSorted = false;
			}
		}
		for (int i = 0; i <= n - 2; i = i + 2)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(arr[i], arr[i + 1]);
				isSorted = false;
			}
		}
	}

	return;
}
void CocktailSort(int a[], int n)
{
	bool swapped = true;
	int start = 0;
	int end = n - 1;

	while (swapped) { 
		swapped = false;
		for (int i = start; i < end; ++i) {
			if (a[i] > a[i + 1]) {
				swap(a[i], a[i + 1]);
				swapped = true;
			}
		}
		if (!swapped)
			break;
		swapped = false;
		--end;
		for (int i = end - 1; i >= start; --i) {
			if (a[i] > a[i + 1]) {
				swap(a[i], a[i + 1]);
				swapped = true;
			}
		}
		++start;
	}
}
int main()
{
	int size=10;
	int counter = 1;
	while (counter<10)
	{
		cout << "enter size";
		cin >> size;
		int *arr=new int[size];
		int *out=new int[size];

		cout << "bubble sort" << endl;
		randomGenrator(arr, size);
		auto t1 = std::chrono::high_resolution_clock::now();
		bubbleSort(arr, size);
		auto t2 = std::chrono::high_resolution_clock::now();
		auto bubbleduration = duration_cast<microseconds>(t2 - t1).count();
		printArray(arr, size);

		cout << "selection sort" << endl;
		randomGenrator(arr, size);
		t1 = std::chrono::high_resolution_clock::now();
		selectionSort(arr, size);
		t2 = std::chrono::high_resolution_clock::now();
		auto selectionduration = duration_cast<microseconds>(t2 - t1).count();
		printArray(arr, size);

		cout << "heap sort" << endl;
		randomGenrator(arr, size);
		t1 = std::chrono::high_resolution_clock::now();
		heapSort(arr, size);
		t2 = std::chrono::high_resolution_clock::now();
		auto heapduration = duration_cast<microseconds>(t2 - t1).count();
		printArray(arr, size);

		cout << "radix sort" << endl;
		randomGenrator(arr, size);
		t1 = std::chrono::high_resolution_clock::now();
		radixsort(arr, size);
		t2 = std::chrono::high_resolution_clock::now();
		auto radixduration = duration_cast<microseconds>(t2 - t1).count();
		printArray(arr, size);

		cout << "shell sort" << endl;
		randomGenrator(arr, size);
		t1 = std::chrono::high_resolution_clock::now();
		shellSort(arr, size);
		t2 = std::chrono::high_resolution_clock::now();
		auto shellduration = duration_cast<microseconds>(t2 - t1).count();
		printArray(arr, size);

		cout << "counting sort" << endl;
		randomGenrator(arr, size);
		t1 = std::chrono::high_resolution_clock::now();
		//Counting_Sort(arr,out,size);
		t2 = std::chrono::high_resolution_clock::now();
		auto countingduration = duration_cast<microseconds>(t2 - t1).count();
		printArray(arr, size);

		cout << "bogo sort" << endl;
		randomGenrator(arr, size);
		t1 = std::chrono::high_resolution_clock::now();
		if (size<=10)
			bogosort(arr, size);
		t2 = std::chrono::high_resolution_clock::now();
		auto bogoduration = duration_cast<microseconds>(t2 - t1).count();
		printArray(arr, size);

		cout << "tim sort" << endl;
		randomGenrator(arr, size);
		t1 = std::chrono::high_resolution_clock::now();
		if(size<1000)
			timSort(arr, size);
		t2 = std::chrono::high_resolution_clock::now();
		auto timeduration = duration_cast<microseconds>(t2 - t1).count();
		printArray(arr, size);

		cout << "odd even sort" << endl;
		randomGenrator(arr, size);
		t1 = std::chrono::high_resolution_clock::now();
		oddEvenSort(arr, size);
		t2 = std::chrono::high_resolution_clock::now();
		auto oddduration = duration_cast<microseconds>(t2 - t1).count();
		printArray(arr, size);

		cout << "cocktail sort" << endl;
		randomGenrator(arr, size);
		t1 = std::chrono::high_resolution_clock::now();
		CocktailSort(arr, size);
		t2 = std::chrono::high_resolution_clock::now();
		auto cocktailduration = duration_cast<microseconds>(t2 - t1).count();
		printArray(arr, size);

		cout << "size of array is : " << size << endl;
		cout << "time for each of the sorting algorithm is:" << endl;
		cout << "bubble sort time=>    " << bubbleduration << " microseconds" << endl;
		cout << "selection sort time=> " << selectionduration << " microseconds" << endl;
		cout << "heap sort time=>      " << heapduration << " microseconds" << endl;
		cout << "radix sort time=>     " << radixduration << " microseconds" << endl;
		cout << "shell sort time=>     " << shellduration << " microseconds" << endl;
		cout << "counting sort time=>  " << countingduration << " microseconds" << endl;
		cout << "bogo sort time=>      " << bogoduration << " microseconds" << endl;
		cout << "time sort time=>      " << timeduration << " microseconds" << endl;
		cout << "oddeven sort time=>   " << oddduration << " microseconds" << endl;
		cout << "cocktail sort time=>  " << cocktailduration << " microseconds" << endl;
		counter = counter + 1;
	}
	system("pause");
	return 0;
}