#include <iostream>
#include <vector>

// 힙 만들기(Heapify) 함수.
void Heapify(std::vector<int>& array, int length, int i)
{
    while (true)
    {
        // 힙 구성을 위한 인덱스 변수.
        int largest = i;
        // 왼쪽 자손 인덱스.
        int left = 2 * i + 1;
        // 오른쪽 자손 인덱스.
        int right = 2 * i + 2;

        if (left < length && array[left] > array[largest])
        {
            largest = left;
        }

        if (right < length && array[right] > array[largest])
        {
            largest = right;
        }
        
        if (largest == i)
        {
            break;
        }

        std::swap(array[i], array[largest]);

        i = largest;
    }
}

// 힙 정렬 함수(HeapSort).
void HeapSort(std::vector<int>& array)
{
    // 전체 크기.
    int length = (int)array.size();

    // 힙 구성.
    for (int i = length / 2 - 1; i >= 0; i--)
    {
        // 힙 만들기.
        Heapify(array, length, i);
    }

    // 정렬.
    for (int i = (int)array.size() - 1; i > 0; i--)
    {
        std::swap(array[i], array[0]);
        Heapify(array, i, 0);
    }
}

// 배열 출력 함수.
void PrintArray(std::vector<int>& array)
{
    for (int i = 0; i < (int)array.size(); ++i)
    {
        std::cout << array[i] << (i < (int)array.size() - 1 ? ", " : "");
    }

    std::cout << "\n";
}

int main()
{
    std::vector<int> array = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

    HeapSort(array); 

    PrintArray(array);
}