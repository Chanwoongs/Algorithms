#include <iostream>
#include <queue>
#include <vector>
#include <string>

// 미로 탐색 예제.
// 위치 구조체.
struct Location
{
    Location(int row = 0, int col = 0)
        : row(row), col(col)
    {

    }

    int row;
    int col;
};

// 맵 선언.
int mazeSize = 6;
char startMark = 'e';
char destinationMark = 'x';

std::vector<std::vector<char>> map = 
{
    {'1','1','1','1','1','1'},
    {'e','0','1','0','0','1'},
    {'1','0','0','0','1','1'},
    {'1','0','1','0','1','1'},
    {'1','0','1','0','0','x'},
    {'1','1','1','1','1','1'}
};

// 이동하려는 위치가 이동 가능한 위치인지 확인하는 함수.
bool IsValid(int row, int col)
{
    // Out of index 검사.
    if (row < 0 || row >= mazeSize || col < 0 || col >= mazeSize)
    {
        return false;
    }

    return map[row][col] == '0' || map[row][col] == destinationMark;
}

// 맵 출력 및 시작 위치 검색 함수.
void FindStartLocation(int& row, int& col)
{
    for (int  i = 0; i < mazeSize; i++)
    {
        for (int j = 0; j < mazeSize; j++)
        {
            // 시작 위치를 찾았으면 전달한 파라미터에 출력,
            if (map[i][j] == startMark)
            {
                row = i;
                col = j;
            }

            // 맵 출력.
            std::cout << map[i][j];
        }

        // 개행.
        std::cout << '\n';
    }
}

void EscapeMaze()
{
    // 시작 위치.
    int row = 0;
    int col = 0;
    FindStartLocation(row, col);

    // 탐색에 사용할 큐 선언.
    std::queue<Location> queue;
    // 시작 위치 추가.
    queue.emplace(Location(row, col));

    // 탐색.
    while (!queue.empty())
    {
        // 큐에서 가장 앞에 위치한 데이터를 추출.
        Location current = queue.front();
        queue.pop();

        // 탐색한 위치 출력.
        std::cout << "(" << current.row << ", " << current.col << ") ";

        // 탈출 조건.
        if (map[current.row][current.col] == destinationMark)
        {
            std::cout << "\n미로 탐색 성공\n";
            return;
        }

        // 방문한 위치를 다른 문자로 설정.
        map[current.row][current.col] = '.';

        // 탐색할 위치를 큐에 넣기.
        // 상/하/좌/우
        if (IsValid(current.row - 1, current.col))
        {
            queue.emplace(Location(current.row - 1, current.col));
        }
        if (IsValid(current.row + 1, current.col))
        {
            queue.emplace(Location(current.row + 1, current.col));
        }
        if (IsValid(current.row, current.col - 1))
        {
            queue.emplace(Location(current.row, current.col - 1));
        }
        if (IsValid(current.row, current.col + 1))
        {
            queue.emplace(Location(current.row, current.col + 1));
        }
    }

    // 탐색 실패.
    std::cout << "\n미로 탐색 실패\n";
}

int main()
{
    EscapeMaze();

    return 0;
}