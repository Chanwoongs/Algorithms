#include <stack>
#include <iostream>
#include <vector>

// 미로 탐색에 사용할 좌표 구조체.
struct Location2D
{
    Location2D(int row = 0, int col = 0)
        : row(row), col(col)
    {

    }

    // 행.
    int row;
    // 열.
    int col;
};

// 맵 배열.
int mapSize = 6;
std::vector<std::vector<char>> map
{
    {'1','1','1','1','1','1'},
    {'e','0','1','0','0','1'},
    {'1','0','0','0','1','1'},
    {'1','0','1','0','1','1'},
    {'1','0','1','0','0','x'},
    {'1','1','1','1','1','1'}
};

// 이동 가능 여부 판단 함수.
bool IsValidLocation(int row, int col)
{
    if (row < 0 || col < 0) return false;
    if (row >= mapSize || col >= mapSize) return false;

    return map[row][col] == '0' || map[row][col] == 'x';
}

// 시작 지점 검색 함수.
void FindStartLocation(int& row, int& col)
{
    for (int i = 0; i < mapSize; i++)
    {
        for (int j = 0; j < mapSize; j++)
        {
            // 맵 출력.
            std::cout << map[i][j] << ' ';

            // 시작 지점을 나타내는 문자 검색.
            if (map[i][j] == 'e')
            {
                row = i;
                col = j;
            }
        }
        std::cout << '\n';
    }
}

// 미로 탈출 함수.
void EscapeMaze()
{
    // 위치 저장을 위한 변수 선언.
    int row = 0;
    int col = 0;

    // 탐색 시작을 위해 시작 위치 찾기.
    FindStartLocation(row, col);

    // 스택 선언.
    std::stack<Location2D> stack;

    // 탐색 시작을 위해 시작 위치 스택에 삽입.
    stack.push(Location2D(row, col));

    // 미로 탐색.
    while (!stack.empty())
    {
        // 현재 위치 반환.
        Location2D current = stack.top();
        stack.pop();

        // 탐색 위치 출력.
        std::cout << "(" << current.row << ", " << current.col << ") ";
        
        // 탈출 조건 확인
        if (map[current.row][current.col] == 'x')
        {
            std::cout << "\n미로 탐색 성공\n";

            return;
        }

        // 탐색 진행.
        // 방문한 현재 위치는 재방문 방지를 위해 표시.
        map[current.row][current.col] = '.';

        // 상/하/좌/우 위치 중 이동 가능한 위치를 스택에 삽입.
        if (IsValidLocation(current.row - 1, current.col))
        {
            stack.push(Location2D(current.row - 1, current.col));
        }
        if (IsValidLocation(current.row + 1, current.col))
        {
            stack.push(Location2D(current.row + 1, current.col));
        }
        if (IsValidLocation(current.row, current.col - 1))
        {
            stack.push(Location2D(current.row, current.col - 1));
        }
        if (IsValidLocation(current.row, current.col + 1))
        {
            stack.push(Location2D(current.row, current.col + 1));
        }

    }
}

int main()
{
    // 미로 탐색.
    EscapeMaze();
}