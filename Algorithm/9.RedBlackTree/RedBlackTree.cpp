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
    // @TODO: 모든 노드 삭제.
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
}
