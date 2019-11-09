#include <iostream>
#include <chrono>
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
	int largest = i; // Initialize largest as root 
	int l = 2 * i + 1; // left = 2*i + 1 
	int r = 2 * i + 2; // right = 2*i + 2 

					   // If left child is larger than root 
	if (l < n && arr[l] > arr[largest])
		largest = l;

	// If right child is larger than largest so far 
	if (r < n && arr[r] > arr[largest])
		largest = r;

	// If largest is not root 
	if (largest != i)
	{
		swap(arr[i], arr[largest]);

		// Recursively heapify the affected sub-tree 
		heapify(arr, n, largest);
	}
}

// main function to do heap sort 
void heapSort(int arr[], int n)
{
	// Build heap (rearrange array) 
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// One by one extract an element from heap 
	for (int i = n - 1; i >= 0; i--)
	{
		// Move current root to end 
		swap(arr[0], arr[i]);

		// call max heapify on the reduced heap 
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

// A function to do counting sort of arr[] according to 
// the digit represented by exp. 
void countSort(int arr[], int n, int exp)
{
	int *output = new int[n]; // output array 
	int i, count[10] = { 0 };

	// Store count of occurrences in count[] 
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	// Change count[i] so that count[i] now contains actual 
	//  position of this digit in output[] 
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Build the output array 
	for (i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	// Copy the output array to arr[], so that arr[] now 
	// contains sorted numbers according to current digit 
	for (i = 0; i < n; i++)
		arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using  
// Radix Sort 
void radixsort(int arr[], int n)
{
	// Find the maximum number to know number of digits 
	int m = getMax(arr, n);

	// Do counting sort for every digit. Note that instead 
	// of passing digit number, exp is passed. exp is 10^i 
	// where i is current digit number 
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, n, exp);
}
int shellSort(int arr[], int n)
{
	// Start with a big gap, then reduce the gap 
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		// Do a gapped insertion sort for this gap size. 
		// The first gap elements a[0..gap-1] are already in gapped order 
		// keep adding one more element until the entire array is 
		// gap sorted  
		for (int i = gap; i < n; i += 1)
		{
			// add a[i] to the elements that have been gap sorted 
			// save a[i] in temp and make a hole at position i 
			int temp = arr[i];

			// shift earlier gap-sorted elements up until the correct  
			// location for a[i] is found 
			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
				arr[j] = arr[j - gap];

			//  put temp (the original a[i]) in its correct location 
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
		/*It will initialize the C with zero*/
		C[i] = 0;
	}
	for (int j = 1;j < n;j++)
	{
		/*It will count the occurence of every element x in A
		and increment it at position x in C*/
		C[A[j]]++;
	}
	for (int i = 1;i <= k;i++)
	{
		/*It will store the last
		occurence of the element i */
		C[i] += C[i - 1];
	}
	for (int j = n-1;j >= 1;j--)
	{
		/*It will place the elements at their
		respective index*/
		B[C[A[j]]] = A[j];
		/*It will help if an element occurs
		more than one time*/
		C[A[j]] = C[A[j]] - 1;
	}
}
int main()
{
	const int size = 10;
	int arr[size];
	int out[size];


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
	t2 = std::chrono::high_resolution_clock::now();
	auto bogoduration = duration_cast<microseconds>(t2 - t1).count();
	printArray(arr, size);

	cout << "time sort" << endl;
	randomGenrator(arr, size);
	t1 = std::chrono::high_resolution_clock::now();
	t2 = std::chrono::high_resolution_clock::now();
	auto timeduration = duration_cast<microseconds>(t2 - t1).count();
	printArray(arr, size);

	cout << "odd even sort" << endl;
	randomGenrator(arr, size);
	t1 = std::chrono::high_resolution_clock::now();
	t2 = std::chrono::high_resolution_clock::now();
	auto oddduration = duration_cast<microseconds>(t2 - t1).count();
	printArray(arr, size);

	cout << "cocktail sort" << endl;
	randomGenrator(arr, size);
	t1 = std::chrono::high_resolution_clock::now();
	t2 = std::chrono::high_resolution_clock::now();
	auto cocktailduration = duration_cast<microseconds>(t2 - t1).count();
	printArray(arr, size);

	cout << bubbleduration << " microseconds" << endl;
	cout << selectionduration << " microseconds" << endl;
	cout << heapduration << " microseconds" << endl;
	cout << radixduration << " microseconds" << endl;
	cout << shellduration << " microseconds" << endl;
	cout << countingduration << " microseconds" << endl;
	cout << bogoduration << " microseconds" << endl;
	cout << timeduration << " microseconds" << endl;
	cout << oddduration << " microseconds" << endl;
	cout << cocktailduration << " microseconds" << endl;


	//random number update
	//start time capture
	//function call
	//end time capture
	//calculate time
	//check correctness



	//random number update
	//start time capture
	//function call
	//end time capture
	//calculate time
	//check correctness
	system("pause");
	return 0;
}