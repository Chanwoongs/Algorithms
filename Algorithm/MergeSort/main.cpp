#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// 병합 함수 (Merge).
// array: 병합할 배열 변수.
// leftArray: 왼쪽 배열 변수.
// rightArray: 오른쪽 배열 변수.
void Merge(
    int* array,
    int* leftArray, int leftArrayLength,
    int* rightArray, int rightArrayLength)
{
    // 인덱스 변수 선언.
    int leftIndex = 0;
    int rightIndex = 0;
    int mergedIndex = 0;

    // 왼쪽/오른쪽 배열의 요소를 비교하면서 작은 순서로 array에 값 할당.
    while (leftIndex < leftArrayLength && rightIndex < rightArrayLength)
    {
        // 왼쪽/오른쪽 비교.
        if (leftArray[leftIndex] <= rightArray[rightIndex])
        {
            array[mergedIndex] = leftArray[leftIndex];
            ++leftIndex;
        }
        else
        {
            array[mergedIndex] = rightArray[rightIndex];
            ++rightIndex;
        }
        ++mergedIndex;
    }
    
    // 위 과정에서 남은 왼쪽 배열 요소를 최종 배열에 복사.
    while (leftIndex < leftArrayLength)
    {
        array[mergedIndex] = leftArray[leftIndex];
        ++leftIndex;
        ++mergedIndex;
    }

    // 위 과정에서 남은 오른쪽 배열 요소를 최종 배열에 복사.
    while (rightIndex < rightArrayLength)
    {
        array[mergedIndex] = rightArray[rightIndex];
        ++rightIndex;
        ++mergedIndex;
    }
}

// 정렬 함수 (MergeSort).
void MergeSort(int* array, int length)
{
    // 탈출 조건.
    if (length <= 1)
    {
        return;
    }

    // 배열 분할(나누기).
    int mid = length / 2;

    // 왼쪽/오른쪽 배열의 공간 확보.
    int* leftArray = new int[mid];
    int* rightArray = new int[length - mid];

    // 값 복사.
    memcpy(leftArray, array, sizeof(int) * mid);
    memcpy(rightArray, array + mid, sizeof(int) * (length - mid));

    // 재귀적 호출.
    MergeSort(leftArray, mid);
    MergeSort(rightArray, length - mid);

    // 병합.
    Merge(array, leftArray, mid, rightArray, length - mid);

    // 메모리 해제.
    delete[] leftArray;
    delete[] rightArray;
}

// 배열 출력 함수.
void PrintArray(int array[], int length)
{
    for (int ix = 0; ix < length; ++ix)
    {
        std::cout << array[ix] << (ix < length - 1 ? ", " : "");
    }

    std::cout << "\n";
}

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    int array[] = { 18, 19, 21, 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16, 11, 25, 30 };
    int length = _countof(array);

    std::cout << "정렬 전 출력\n";
    PrintArray(array, length);

    MergeSort(array, length);

    std::cout << "정렬 후 출력\n";
    PrintArray(array, length);
}