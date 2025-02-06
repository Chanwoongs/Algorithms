#include <iostream>

// 두 값을 서로 교환하는 함수.
void Swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

// 버블 정렬 함수.
void BubbleSort(int* array, int length)
{
    // 정렬.
    for (int i = 0; i < length - 1; ++i)
    {
        for (int j = 0; j < length - 1 - i; ++j)
        {
            // 두개씩 비교.
            if (array[j] > array[j + 1])
            {
                // 교환.
                Swap(array[j], array[j + 1]);
            }
        }
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
    // 배열.
    int array[] = { 5, 3, 2, 8, 10, 15, 20, 23 };

    // 배열 길이.
    int length = sizeof(array) / sizeof(int);

    // 출력.
    std::cout << "정렬 전: ";
    PrintArray(array, length);

    // 정렬.
    BubbleSort(array, length);

    std::cout << "정렬 후: ";
    PrintArray(array, length);

    std::cin.get();
}