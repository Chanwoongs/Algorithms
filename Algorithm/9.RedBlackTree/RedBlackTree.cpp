#include "RedBlackTree.h"

Node* RedBlackTree::Nil = nullptr;

Node* RedBlackTree::CreateNode(int data, Color color)
{
    Node* newNode = new Node(data, color);
    newNode->SetLeft(Nil);
    newNode->SetRight(Nil);

    return newNode;
}

RedBlackTree::RedBlackTree()
{
    if (Nil == nullptr)
    {
        Nil = new Node(0, Color::Black);
    }

    root = Nil;
}

RedBlackTree::~RedBlackTree()
{
    DestroyRecursive(root);
    SafeDelete(Nil);
}

bool RedBlackTree::Find(int data, Node** outNode)
{
    // 트리가 비었다면, 검색 실패.
    if (root == Nil)
    {
        return false;
    }

    // 재귀적으로 검색 진행.
    return FindRecursive(data, root, outNode);
}

bool RedBlackTree::FindRecursive(int data, Node* node, Node** outNode)
{
    // 재귀 탈출 조건 (검색 실패).
    if (node == Nil)
    {
        return false;
    }

    // 검색에 성공했으면 true 및 outNode 반환.
    if (node->Data() == data)
    {
        *outNode = node;
        return true;
    }

    if (node->Data() > data)
    {
        return FindRecursive(data, node->Left(), outNode);
    }
    else
    {
        return FindRecursive(data, node->Right(), outNode);
    }

    return false;
}

bool RedBlackTree::Insert(int data)
{
    // 먼저 중복되는 데이터가 있는지 확인.
    Node* node = nullptr;
    if (Find(data, &node))
    {
        std::cout << "오류 - 노드 추가 실패: 이미 같은 값이 있습니다. 입력 값 " << data << '\n';
        return false;
    }

    Insert(CreateNode(data, Color::Red));

    return true;
}

void RedBlackTree::Remove(int data)
{
    // TODO
}

void RedBlackTree::Insert(Node* newNode)
{
    // 트리가 비어있는 경우, 루트로 설정.
    if (root == Nil)
    {
        root = newNode;
        root->SetColor(Color::Black);

        return;
    }

    // 트리가 비어있지 않으면, 재귀적으로 위치ㅔ 검색 후 삽입.
    InsertRecursive(root, newNode);

    // 삽입된 노드 값 정리.
    newNode->SetColor(Color::Red);
    newNode->SetLeft(Nil);
    newNode->SetRight(Nil);

    // 삽입 후 재정렬 처리.
    RestructureAfterInsert(newNode);
}

void RedBlackTree::InsertRecursive(Node* node, Node* newNode)
{
    // 새 노드의 데이터가 현재 노드보다 작으면, 왼쪽 하위 트리로 삽입 진행.
    if (node->Data() > newNode->Data())
    {
        // 왼쪽 자손이 없다면, 삽입 처리.
        if (node->Left() == Nil)
        {
            node->SetLeft(newNode);
            newNode->SetParent(node);
            return;
        }

        // 자손이 있으면, 하위 트리로 삽입 과정 진행.
        InsertRecursive(node->Left(), newNode);
    }
    else
    {
        // 오른쪽 자손이 없다면, 삽입.
        if (node->Right() == Nil)
        {
            node->SetRight(newNode);
            newNode->SetParent(node);
            return;
        }

        // 자손이 있으면, 하위 트리로 삽입 과정 진행.
        InsertRecursive(node->Right(), newNode);
    }
}

void RedBlackTree::RestructureAfterInsert(Node* newNode)
{
    // 부모 노드가 빨간색인 경우 (Red-Red Conflict).
    while (newNode != root && newNode->Parent()->GetColor() == Color::Red)
    {
        // 삼촌 구하기.
        if (newNode->Parent() == newNode->Parent()->Parent()->Left())
        {
            // 삼촌.
            Node* uncle = newNode->Parent()->Parent()->Right();

            // 삼촌 노드가 빨간색 일때 (Case 1).
            // 해결: 부모와 삼촌을 Black, 할아버지를 Red로 변경 후, 할아버지 기준으로 다시 검사.
            if (uncle->GetColor() == Color::Red)
            {
                newNode->Parent()->SetColor(Color::Black);
                uncle->Parent()->SetColor(Color::Black);
                newNode->Parent()->Parent()->SetColor(Color::Red);

                newNode = newNode->Parent()->Parent();

                continue;
            }

            // 삼촌이 검정색일 때.
            // 해결: 부모를 Black, 할아버지를 Red로 변경 후, 할아버지를 기준으로 회전.
            // Case 2 / Case 3.
            // Case 2: 지그재그 형태. 부모의 위치와 나의 위치가 반대(일직선으로 변경 후 Case 3 처리).
            if (newNode == newNode->Parent()->Right())
            {
                // 부모를 중심으로 회전 처리(일직선으로 만들기 위해).
                newNode = newNode->Parent();
                RotateToLeft(newNode);
            }

            // Case 3: 부모와 나의 위치가 일치할 때.
            newNode->Parent()->SetColor(Color::Black);
            newNode->Parent()->Parent()->SetColor(Color::Red);

            RotateToRight(newNode->Parent()->Parent());
        }
        else
        {
            // 삼촌.
            Node* uncle = newNode->Parent()->Parent()->Left();

            // 삼촌 노드가 빨간색 일때 (Case 1).
            // 해결: 부모와 삼촌을 Black, 할아버지를 Red로 변경 후, 할아버지 기준으로 다시 검사.
            if (uncle->GetColor() == Color::Red)
            {
                newNode->Parent()->SetColor(Color::Black);
                uncle->Parent()->SetColor(Color::Black);
                newNode->Parent()->Parent()->SetColor(Color::Red);

                newNode = newNode->Parent()->Parent();

                continue;
            }

            // 삼촌이 검정색일 때.
            // 해결: 부모를 Black, 할아버지를 Red로 변경 후, 할아버지를 기준으로 회전.
            // Case 2 / Case 3.
            // Case 2: 지그재그 형태. 부모의 위치와 나의 위치가 반대(일직선으로 변경 후 Case 3 처리).
            if (newNode == newNode->Parent()->Left())
            {
                // 부모를 중심으로 회전 처리(일직선으로 만들기 위해).
                newNode = newNode->Parent();
                RotateToRight(newNode);
            }

            // Case 3: 부모와 나의 위치가 일치할 때.
            newNode->Parent()->SetColor(Color::Black);
            newNode->Parent()->Parent()->SetColor(Color::Red);

            RotateToLeft(newNode->Parent()->Parent());
        }
    }

    // 루트 노드는 블랙.
    root->SetColor(Color::Black);
}

void RedBlackTree::RotateToLeft(Node* node)
{
    // 오른쪽 자식 노드.
    Node* right = node->Right();

    // 오른쪽 자식 노드의 왼쪽 자식 노드를 부모의 오른쪽 자식으로 등록.
    node->SetRight(right->Left());

    // 하위 노드의 부모 변경 처리.
    if (right->Left() != Nil)
    {
        right->Left()->SetParent(node);
    }

    // 오른쪽 자식 노드의 부모를 부모의 부모(조부모)로 설정.
    right->SetParent(node->Parent());
    
    // 부모가 root인 경우.
    if (right->Parent() == nullptr)
    {
        root = right;
    }
    // root가 아닐 때.
    else
    {
        // 조부모 기준 원래의 자식 위치로 복구.
        if (node == node->Parent()->Left())
        {
            node->Parent()->SetLeft(right);
        }
        else
        {
            node->Parent()->SetRight(right);
        }
    }

    // 좌회전 마무리.
    right->SetLeft(node);
    node->SetParent(right);
}

void RedBlackTree::RotateToRight(Node* node)
{
    // 왼쪽 자식 노드.
    Node* left = node->Left();

    // 왼쪽 자식 노드의 오른쪽 자식 노드를 부모의 왼쪽 자식으로 등록.
    node->SetLeft(left->Right());

    // 하위 노드의 부모 변경 처리.
    if (left->Right() != Nil)
    {
        left->Right()->SetParent(node);
    }

    // 왼쪽 자식 노드의 부모를 부모의 부모(조부모)로 설정.
    left->SetParent(node->Parent());

    // 부모가 root인 경우.
    if (left->Parent() == nullptr)
    {
        root = left;
    }
    // root가 아닐 때.
    else
    {
        // 조부모 기준 원래의 자식 위치로 복구.
        if (node == node->Parent()->Left())
        {
            node->Parent()->SetLeft(left);
        }
        else
        {
            node->Parent()->SetRight(left);
        }
    }

    // 좌회전 마무리.
    left->SetRight(node);
    node->SetParent(left);
}

Node* RedBlackTree::FindMinRecursive(Node* node)
{
    // 탈출 조건.
    if (node == Nil)
    {
        return nullptr;
    }

    // 왼쪽 하위 노드가 더 이상 없으면 현재 노드 반환.
    if (node->Left() == Nil)
    {
        return node;
    }

    return FindMinRecursive(node->Left());
}

Node* RedBlackTree::FindMaxRecursive(Node* node)
{
    // 탈출 조건.
    if (node == Nil)
    {
        return nullptr;
    }

    // 왼쪽 하위 노드가 더 이상 없으면 현재 노드 반환.
    if (node->Right() == Nil)
    {
        return node;
    }

    return FindMaxRecursive(node->Right());
}

void RedBlackTree::DestroyRecursive(Node* node)
{
    // 재귀 탈출 조건.
    if (node == Nil)
    {
        return;
    }

    // 왼쪽/오른쪽 자손.
    Node* left = node->Left();
    Node* right = node->Right();

    // 자식이 있는 경우.
    DestroyRecursive(left);
    DestroyRecursive(right);

    SafeDelete(node);
}

void RedBlackTree::Print(int depth, int blackCount)
{
    PrintRecursive(root, depth, blackCount);
}

void RedBlackTree::PrintRecursive(Node* node, int depth, int blackCount)
{
    // 탈출 조건.
    if (node == Nil)
    {
        return;
    }

    // 노드 색상이 검정이면 blackCount 증가.
    if (node->GetColor() == Color::Black) 
    {
        ++blackCount;
    }
    
    // 부모 표기 문자열 설정.
    int parentData = 0;
    const char* position = "Root";

    // 부모 노드가 있는지 확인.
    if (node->Parent())
    {
        // 부모 노드의 데이터 저장.
        parentData = node->Parent()->Data();

        // 부모 노드의 위치.
        if (node == node->Parent()->Left())
        {
            position = "Left";
        }
        else
        {
            position = "Right";
        }
    }

    // 검은색 출력을 위한 문자열.
    char blackCountString[50] = { };

    // 자손이 없으면 현재까지의 검은색 노드 수 설정.
    if (node->Left() == Nil && node->Right() == Nil)
    {
        sprintf_s(blackCountString, "------ %d", blackCount);
    }

    // Depth 출력.
    for (int i = 0; i < depth; i++)
    {
        std::cout << "  ";
    }

    // 노드 색상에 따른 콘솔 설정.
    if (node->GetColor() == Color::Red)
    {
        SetTextColor(TextColor::Red);
    }
    else
    {
        SetTextColor(TextColor::White);
    }

    // 현재 노드 값 출력.
    std::cout
        << node->Data() << " " << node->ColorString()
        << " [" << position << ", " << parentData << "] "
        << blackCountString << '\n';

    // 노드를 출력한 뒤에는 콘솔 원래대로.
    SetTextColor(TextColor::White);

    // 하위 노드 출력.
    PrintRecursive(node->Left(), depth + 1, blackCount);
    PrintRecursive(node->Right(), depth + 1, blackCount);
}

void SetTextColor(TextColor color)
{
    static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, (int)color);
}
