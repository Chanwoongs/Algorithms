﻿#include <iostream>

#include "RedBlackTree.h"
#include "Windows.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// 명령 구분을 위한 열거형.
enum class Command
{
    None,
    Insert,
    Delete,
    Find,
    Print,
    Quit
};

// 화면 지우는 함수.
void ClearScreen()
{
    system("cls");
}

void ProcessCommandInput(int& commandInput)
{
    // 입력 처리.
    char inputBuffer[100] = {};

    while (true)
    {
        // 입력 안내 출력 및 입력 저장.
        std::cout << "명령 숫자를 입력하세요.\n";
        std::cout << "(1) 노드추가, (2) 노드 삭제, (3) 노드 검색, (4) 노드 출력, (5) 종료\n";
        std::cin >> inputBuffer;

        // atoi: ascii to integer.
        if (commandInput = atoi(inputBuffer))
        {
            // 예외 처리.
            if (commandInput <= (int)Command::None || commandInput > (int)Command::Quit)
            {
                ClearScreen();
                std::cout << "오류: 잘못된 숫자를 입력했습니다.\n";
                continue;
            }
            break;
        }

        // 예외 처리.
        ClearScreen();
        std::cout << "오류: 명령은 숫자만 입력해야 합니다.\n";
    }
}

// 파라미터 입력 처리 함수.
void ProcessParamInput(int& param)
{
    // 입력 처리 버퍼.
    char inputBuffer[100];

    // 입력 처리 루프.
    while (true)
    {
        std::cout << "파라미터를 입력하세요. (1-200)\n";
        std::cin >> inputBuffer;

        // 검증.
        if (param = atoi(inputBuffer))
        {
            // 예외 처리.
            if (param < 1 || param > 200)
            {
                // 예외 처리.
                ClearScreen();
                std::cout << "오류: 파라미터는 1-200 사이의 숫자만 입력해야 합니다.\n";
                
                continue;
            }

            break;
        }

        // 예외 처리.
        ClearScreen();
        std::cout << "오류: 파라미터는 숫자만 입력해야 합니다.\n";
    }
}

// 명령 처리 함수.
void ProcessCommand(int commandInput, RedBlackTree& tree)
{
    // 입력 값을 열거형으로 변환.
    Command command = (Command)commandInput;
    if (command == Command::Print)
    {
        ClearScreen();

        // @TODO: 트리 출력 처리.
        return;
    }

    // 프로그램 종료.
    if (command == Command::Quit)
    {
        return;
    }

    // 1, 2, 3 명령 처리 (파라미터 입력이 추가로 필요함).
    int param = 0;
    ProcessParamInput(param);

    // 명령 처리.
    switch (command)
    {
        // 노드 추가.
        case Command::Insert:
        {
            ClearScreen();
            tree.Insert(param);
        } break;
        case Command::Delete:
        {
            // @Todo:
        } break;
        case Command::Find:
        { 
            // @Todo:
        } break;
    }
}

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // 레드 블랙 트리 생성.
    RedBlackTree tree;

    while (true)
    {
        // 명령 입력 처리.
        int commandInput = 0;
        ProcessCommandInput(commandInput);

        // 명령 처리.
        ProcessCommand(commandInput, tree);

        // 종료 처리.
        if (commandInput == (int)Command::Quit)
        {
            break;
        }
    }
}