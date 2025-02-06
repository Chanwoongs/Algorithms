#include <iostream>

void SelectionSort(int* array, int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        // 최소값 저장할 변수.
        int minIndex = i;

        for (int j = i + 1; j < length; j++)
        {
            if (array[j] < array[minIndex])
            {
                minIndex = j;
            }
        }

        // 값 바꾸기.
        std::swap<int>(array[i], array[minIndex]);
    }
}

// 출력 함수.
void PrintArray(int* array, int length)
{
    for (int ix = 0; ix < length; ++ix)
    {
        std::cout << array[ix] << " ";
    }

    std::cout << "\n";
}

int main()
{
    // 자료 집합.
    int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

    // 배열 길이.
    int length = _countof(array);

    // 출력.
    std::cout << "정렬 전: ";
    PrintArray(array, length);

    // 정렬.
    SelectionSort(array, length);

    std::cout << "정렬 후: ";
    PrintArray(array, length);
}