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
int mapSize = 0;
std::vector<std::vector<char>> map;

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

bool ParseMap1(const char* path)
{
    FILE* file = nullptr;
    fopen_s(&file, path, "rb");

    int mapIndex = 0;
    char buffer[256];
    int mapSize = 0;
    int row = 0, col = 0;

    if (file != nullptr)
    {
        fscanf_s(file, "%s %d\n", buffer, 256, &mapSize);

        map.resize(mapSize);
        for (int i = 0; i < mapSize; i++)
        {
            map[i].resize(mapSize);
        }

        while (!feof(file))
        {
            col = 0;
            fgets(buffer, 256, file);
            char* remain = nullptr;
            char* token = strtok_s(buffer, ",", &remain);

            map[row][col++] = token[0];

            while (token != NULL)
            {
                token = strtok_s(nullptr, ",", &remain);
                if (token != NULL)
                {
                    map[row][col++] = token[0];
                }
            }
            row++;
        }
    }

    return false;
}

bool ParseMap2(const char* path)
{
    FILE* file = nullptr;
    fopen_s(&file, path, "rb");

    if (file)
    {
        // 첫 줄 읽기.
        char buffer[256] = {};
        if (!fgets(buffer, 256, file))
        {
            fclose(file);
            return false;
        }

        // 맵 사이즈.
        sscanf_s(buffer, "size %d", &mapSize);

        // 줄 데이터 저장을 위한 심시 배열 선언.
        std::vector<char> line;
        line.reserve(mapSize);

        // 맵 데이터 해석을 위한 루프.
        while (fgets(buffer, 256, file))
        {
            // 첫칸 처리.
            char* context = nullptr;
            char* splitString = strtok_s(buffer, ",", &context);
            if (splitString)
            {
                line.emplace_back(splitString[0]);
            }

            // 둘째 부터는 루프.
            while (context)
            {
                splitString = strtok_s(nullptr, ",", &context);
                if (!splitString)
                {
                    break;
                }

                line.emplace_back(splitString[0]);
;           }
            // context가 nullptr일 때는 buffer를 넣어주고,
            // context가 있을 땐 nullptr을 넣어준다.

            map.emplace_back(line);
            line.clear();
        }

        fclose(file);
        return true;
    }

    return false;
}

// 미로 탈출 함수.
void EscapeMaze()
{
    ParseMap2("../Assets/Map.txt");

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