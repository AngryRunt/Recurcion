﻿// Practice_2_Recursion.cpp : Defines the entry point for the console application.
//


#include <iostream>
using namespace std;

const int CONST_MAX				= 1000;
const int CONST_Dash			= -1;	// кодирование в массиве символа "-"
const int CONST_Forvard_Slash	= -2;	// кодирование в массиве символа прямая косая черта  "/"
const int CONST_Back_Slash		= -3;	// кодирование в массиве символа обратная косая черта  "\"

const int CONST_Flag_Value  = 1;		// флаг указывающих что печатать надо значения вершин
const int CONST_Flag_Number = 2;		// флаг указывающих что печатать надо номера вершин


struct Node_Tree
{
    Node_Tree* Left;
    Node_Tree* Right;
    int Value;
    int Num_Order;
};

struct Queue_Tree
{
    Node_Tree* Value;
    Queue_Tree* Next;
};

class BTree
{
public:
    BTree();
    ~BTree();
    void Run();
private:
    Node_Tree* Arr_Node;

    void Print_Tree(int Flag);
    int Get_Height(Node_Tree* Root);
    int Get_Widht(Node_Tree* Root);
    int Get_HeightL(Node_Tree* Root);
    void Full_Array(int** Array_PRN, const Node_Tree* Root, int Left_Border, int Right_Border, int Cur_Height, int Flag);
    void Prn_Tree_Height_Direct(const Node_Tree* Root);
    void Prn_Tree_Height_Reverse(const Node_Tree* Root);
    void Prn_Tree_Height_Symmetric(const Node_Tree* Root);
    int Prn_Tree_Height_Direct_2(const Node_Tree* Root, int Flag);
    void Prn_Tree_Height_Reverse_Odd_Value(const Node_Tree* Root);
    void Prn_Tree_Height_Direct_Even_Level(const Node_Tree* Root, int Level);
    void Prn_Tree_Width(Node_Tree* Root);
    void Prn_Tree_HLeaf(const Node_Tree* Root, int Cur_Level, int Height);
    void Prn_Tree_HLeaf_2(const Node_Tree* Root, int Cur_Level, int Height);
    void Prn_Tree_SumPrevNodes(const Node_Tree* Root, const int sum);
    int Prn_Tree_SumExistentNodes(const Node_Tree* Root);
    void Prn_Tree_SumNotExistentNodes(const Node_Tree* Root, int sum);
    void Prn_Tree_SumWithoutPrevNodes(const Node_Tree* Root);

    void Clear_Order_1(Node_Tree* Root);
    int Create_Order_Row_2(Node_Tree* Root);
    int Max_Order_Row_3(Node_Tree* Root);
    void Delete_Not_Max_Order_4(Node_Tree* Root, int Max, int Current, int Flag);
    void Prn_Max_Order_5(Node_Tree* Root, int Max, int Current, int Flag);

    void Exch_Numbers(Node_Tree* Root);
    void Move_Odd_Down(Node_Tree* Root);

};
//-------------------------------------------------------------------------------------------
BTree::BTree()
{
    Arr_Node = new Node_Tree[15];
    Arr_Node[0].Left = &Arr_Node[1];	Arr_Node[0].Right = &Arr_Node[8];	Arr_Node[0].Value = 1;
    Arr_Node[1].Left = &Arr_Node[2];	Arr_Node[1].Right = &Arr_Node[5];	Arr_Node[1].Value = 2;
    Arr_Node[2].Left = &Arr_Node[3];	Arr_Node[2].Right = &Arr_Node[4];	Arr_Node[2].Value = 37;
    Arr_Node[3].Left = NULL;			Arr_Node[3].Right = NULL;			Arr_Node[3].Value = 4;
    Arr_Node[4].Left = NULL;			Arr_Node[4].Right = &Arr_Node[14];	Arr_Node[4].Value = 52;
    Arr_Node[5].Left = &Arr_Node[6];	Arr_Node[5].Right = &Arr_Node[7];	Arr_Node[5].Value = 6;
    Arr_Node[6].Left = NULL;			Arr_Node[6].Right = NULL;			Arr_Node[6].Value = 7;
    Arr_Node[7].Left = NULL;			Arr_Node[7].Right = NULL;			Arr_Node[7].Value = 81;
    Arr_Node[8].Left = &Arr_Node[9];	Arr_Node[8].Right = &Arr_Node[12];	Arr_Node[8].Value = 9;
    Arr_Node[9].Left = &Arr_Node[10];	Arr_Node[9].Right = &Arr_Node[11];	Arr_Node[9].Value = 10;
    Arr_Node[10].Left = &Arr_Node[13];	Arr_Node[10].Right = NULL;			Arr_Node[10].Value = 11;
    Arr_Node[11].Left = NULL;			Arr_Node[11].Right = NULL;			Arr_Node[11].Value = 12;
    Arr_Node[12].Left = NULL;			Arr_Node[12].Right = NULL;			Arr_Node[12].Value = 13;
    Arr_Node[13].Left = NULL;			Arr_Node[13].Right = NULL;			Arr_Node[13].Value = 14;
    Arr_Node[14].Left = NULL;			Arr_Node[14].Right = NULL;			Arr_Node[14].Value = 65;
}
//-------------------------------------------------------------------------------------------
BTree::~BTree()
{
    delete[] Arr_Node;
}
//----------------------------------------------------------------------------
// Нахождение высоты дерева
//----------------------------------------------------------------------------
int BTree::Get_Height(Node_Tree* Root)
{
    int Left_Height = 0;
    int Right_Height = 0;

    if (Root->Left != NULL)
    {
        Left_Height = Get_Height(Root->Left);
    }
    if (Root->Right != NULL)
    {
        Right_Height = Get_Height(Root->Right);
    }
    if (Left_Height > Right_Height)
    {
        return Left_Height + 1;
    }
    return Right_Height + 1;
}
//----------------------------------------------------------------------------
// Высота листа с минимальным уровнем (ближнего листа к корню) в дереве
//----------------------------------------------------------------------------
int BTree::Get_HeightL(Node_Tree* Root)
{
    int Left_Height  = CONST_MAX;
    int Right_Height = CONST_MAX;

    if (Root->Left != NULL)
    {
        Left_Height = Get_HeightL(Root->Left);
    }
    if (Root->Right != NULL)
    {
        Right_Height = Get_HeightL(Root->Right);
    }
    if ((Left_Height == Right_Height) && (Left_Height == CONST_MAX))
    {
        return 1;
    }

    if (Left_Height > Right_Height)
    {
        return Right_Height + 1;
    }
    return Left_Height + 1;
}
//----------------------------------------------------------------------------
// Нахождение ширины дерева
//----------------------------------------------------------------------------
int BTree::Get_Widht(Node_Tree* Root)
{
    int Left_Height = 0;
    int Right_Height = 0;

    if (Root->Left != NULL)
    {
        Left_Height = Get_Widht(Root->Left);
    }
    if (Root->Right != NULL)
    {
        Right_Height = Get_Widht(Root->Right);
    }
    return (Left_Height + Right_Height) + 1;
}
//----------------------------------------------------------------------------
// Заполнение матрицы для форматированного вывода дерева
// int **Array_PRN        - заполняемый массив
// const Node_Tree* Root     - корень текущего поддерева
// int Left_Border        - левая граница текущего поддерева
// int Right_Border       - правая граница текущего поддерева
// int Cur_Height         - текущая высота (относительно корня дерева на которой мы находимся)
// int Flag               - что мы выводим на экран
//                        Flag = 1  - значения вершин
//                        Flag = 2  - номер вершины в пути с четными вершинами вершин
//----------------------------------------------------------------------------
void BTree::Full_Array(int** Array_PRN, const Node_Tree* Root, int Left_Border, int Right_Border, int Cur_Height, int Flag)
{
    int i;
    int Medium = (Right_Border + Left_Border) / 2;					// находим местоположение корня для текущего поддерева в массиве
    if (Root->Left != NULL)
    {
        for (i = (Left_Border + Medium) / 2; i < Medium; i++)
        {
            Array_PRN[Cur_Height][i] = CONST_Dash;
        }
        Array_PRN[Cur_Height][(Left_Border + Medium) / 2] = CONST_Forvard_Slash;

        Full_Array(Array_PRN, Root->Left, Left_Border, Medium, Cur_Height + 1, Flag);
    }
    if (Root->Right != NULL)
    {
        for (i = Medium; i < (Right_Border + Medium) / 2; i++)
        {
            Array_PRN[Cur_Height][i] = CONST_Dash;
        }
        Array_PRN[Cur_Height][(Right_Border + Medium) / 2] = CONST_Back_Slash;
        Full_Array(Array_PRN, Root->Right, Medium, Right_Border, Cur_Height + 1, Flag);
    }
    if (Flag == 2)
    {
        Array_PRN[Cur_Height][Medium] = Root->Num_Order;
    }
    else
    {
        Array_PRN[Cur_Height][Medium] = Root->Value;
    }
    return;
}
//----------------------------------------------------------------------------
// Распечатка дерева
// int Flag               - что мы выводим на экран
//                        Flag = 1  - значения вершин
//                        Flag = 2  - номер вершины в пути с четными вершинами вершин
//----------------------------------------------------------------------------
void BTree::Print_Tree(int Flag)
{
    int Tree_Widht;
    int Tree_Height;
    int** Array_PRN;
    int i, j;

    Tree_Height = Get_Height(&Arr_Node[0]);			// получение высоты дерева
    Tree_Widht  = Get_Widht(&Arr_Node[0]);			// получение ширины дерева
    printf("\n");
    printf("tree_Height = %d\n", Tree_Height);
    printf("tree_Widht = %d\n", Tree_Widht);


    Array_PRN = new int* [Tree_Height];				// формирование двумерного массива для вывода
    for (i = 0; i < Tree_Height; i++)				// на экран дерева
    {
        Array_PRN[i] = new int[Tree_Widht * 4];
    }
    for (i = 0; i < Tree_Height; i++)
    {
        for (j = 0; j < Tree_Widht * 4; j++)
        {
            Array_PRN[i][j] = 0;
        }
    }

    Full_Array(Array_PRN, &Arr_Node[0], 0, Tree_Widht * 4, 0, Flag); // заполняем двумерный массив деревом

    printf("\n");
    for (i = 0; i < Tree_Height; i++)
    {
        printf("\n");
        for (j = 0; j < Tree_Widht * 4; j++)
        {
            if (Array_PRN[i][j] > 0)
            {
                printf("%d", Array_PRN[i][j]);
            }
            else if (Array_PRN[i][j] == CONST_Dash)
            {
                printf("-");
            }
            else if (Array_PRN[i][j] == CONST_Forvard_Slash)
            {
                printf("/");
            }
            else if (Array_PRN[i][j] == CONST_Back_Slash)
            {
                printf("\\");
            }
            else printf(" ");
        }
    }
    printf("\n");
    for (i = 0; i < Tree_Height; i++)
    {
        delete[] Array_PRN[i];
    }
    delete[] Array_PRN;

}
//----------------------------------------------------------------------------
// - 1 - Прямой обход дерева в глубину
//----------------------------------------------------------------------------

void BTree::Prn_Tree_Height_Direct(const Node_Tree* Root)
{
    printf(" %d ;", Root->Value);
    if (Root->Left != NULL)
    {
        Prn_Tree_Height_Direct(Root->Left);
    }
    if (Root->Right != NULL)
    {
        Prn_Tree_Height_Direct(Root->Right);
    }
}
//----------------------------------------------------------------------------
// - 2 -  Обратный обход дерева в глубину
//----------------------------------------------------------------------------
void BTree::Prn_Tree_Height_Reverse(const Node_Tree* Root)
{
    if (Root->Left != NULL)
    {
        Prn_Tree_Height_Reverse(Root->Left);
    }
    if (Root->Right != NULL)
    {
        Prn_Tree_Height_Reverse(Root->Right);
    }
    printf(" %d ;", Root->Value);
}
//----------------------------------------------------------------------------
// - 3 -  Симметричный обход дерева в глубину
//----------------------------------------------------------------------------
void BTree::Prn_Tree_Height_Symmetric(const Node_Tree* Root)
{
    if (Root->Left != NULL)
    {
        Prn_Tree_Height_Symmetric(Root->Left);
    }
    printf(" %d ;", Root->Value);
    if (Root->Right != NULL)
    {
        Prn_Tree_Height_Symmetric(Root->Right);
    }
}
//----------------------------------------------------------------------------
// - 4 -  Прямой обход дерева (вершины через одну)
//----------------------------------------------------------------------------
int BTree::Prn_Tree_Height_Direct_2(const Node_Tree* Root, int Flag)
{
    if (Flag)   //проверяем поднят или олпущен флаг, если поднят - печатаем
    {
        printf(" %d ;", Root->Value);
    }
    Flag = !Flag;   // переворачиваем флаг
    if (Root->Left != NULL) // идём налево
    {
        Flag = Prn_Tree_Height_Direct_2(Root->Left, Flag); // идём налево и получаем флаг слева
    }
    if (Root->Right != NULL) // идём направо
    {
        Flag = Prn_Tree_Height_Direct_2(Root->Right, Flag); //идём направо и получаем флаг справа
    }
    return Flag;  // передаем флаг назад
}
//----------------------------------------------------------------------------
// - 5 -  Обратный обход дерева в глубину (вершины нечетные)
//----------------------------------------------------------------------------
void BTree::Prn_Tree_Height_Reverse_Odd_Value(const Node_Tree* Root)
{
    if (Root->Left != NULL)
    {
        Prn_Tree_Height_Reverse_Odd_Value(Root->Left);
    }
    if (Root->Right != NULL)
    {
        Prn_Tree_Height_Reverse_Odd_Value(Root->Right);
    }
    if (Root->Value % 2) printf(" %d ;", Root->Value);
}
//----------------------------------------------------------------------------
// - 6 -  Прямой обход дерева (четные уровни)
//----------------------------------------------------------------------------
void BTree::Prn_Tree_Height_Direct_Even_Level(const Node_Tree* Root, int Level)
{
    if(!(Level % 2))
    {
        printf(" %d ;", Root->Value);
    }
    if(Root->Left != NULL)
    {
        Prn_Tree_Height_Direct_Even_Level(Root->Left, Level + 1);
    }
    if(Root->Right != NULL)
    {
        Prn_Tree_Height_Direct_Even_Level(Root->Right, Level + 1);
    }
}
//-------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------
// - 7 -  Обход дерева в ширину
//----------------------------------------------------------------------------
void BTree::Prn_Tree_Width(Node_Tree* Root)
{
    Queue_Tree* Queue_Head = NULL;
    Queue_Tree* Queue_Tail = NULL;
    Queue_Tree* Queue_Delete = NULL;

    if (Root != NULL)
    {
        Queue_Head = new  Queue_Tree;
        Queue_Head->Value = Root;
        Queue_Head->Next = NULL;
    }
    else
    {
        cout << " \n Дерево пустое \n";
        return;
    }
    Queue_Tail = Queue_Head;
    while (Queue_Head != NULL)
    {
        printf(" %d ;", Queue_Head->Value->Value);
        if (Queue_Head->Value->Left != NULL)
        {
            Queue_Tail->Next = new Queue_Tree;
            Queue_Tail = Queue_Tail->Next;
            Queue_Tail->Next = NULL;
            Queue_Tail->Value = Queue_Head->Value->Left;
        }
        if (Queue_Head->Value->Right != NULL)
        {
            Queue_Tail->Next = new Queue_Tree;
            Queue_Tail = Queue_Tail->Next;
            Queue_Tail->Next = NULL;
            Queue_Tail->Value = Queue_Head->Value->Right;
        }
        Queue_Delete = Queue_Head;
        Queue_Head = Queue_Head->Next;
        delete Queue_Delete;
    }
}
//----------------------------------------------------------------------------
// - 8 -  Распечатать самый низкий лист(листья) в дереве
//----------------------------------------------------------------------------
void BTree::Prn_Tree_HLeaf(const Node_Tree* Root, int Cur_Level, int Height)
{
    if (Cur_Level == Height) printf(" %d ;", Root->Value);
    if (Root->Left != NULL)
    {
        Prn_Tree_HLeaf(Root->Left, Cur_Level + 1, Height);
    }
    if (Root->Right != NULL)
    {
        Prn_Tree_HLeaf(Root->Right, Cur_Level + 1, Height);
    }
}
//----------------------------------------------------------------------------
// - 9 -  Распечатать самый высокий лист(листья) в дереве
//----------------------------------------------------------------------------
void BTree::Prn_Tree_HLeaf_2(const Node_Tree* Root, int Cur_Level, int Height)
{
    if ((Cur_Level == Height) && (Root->Left == NULL) && (Root->Right == NULL))
    {
        if ((Root->Left == NULL) && (Root->Right == NULL))
        {
            printf(" %d ;", Root->Value);
        }
        return;
    }
    if (Root->Left != NULL)
    {
        Prn_Tree_HLeaf_2(Root->Left, Cur_Level + 1, Height);
    }
    if (Root->Right != NULL)
    {
        Prn_Tree_HLeaf_2(Root->Right, Cur_Level + 1, Height);
    }
}

//---------------------------------------------------------------------------
// 10-1 Очистка путей в дереве с четными вершинами (цепочек)
//---------------------------------------------------------------------------
void BTree::Clear_Order_1(Node_Tree* Root)
{
    if (Root->Left != NULL)
    {
        Clear_Order_1(Root->Left);
    }
    if (Root->Right != NULL)
    {
        Clear_Order_1(Root->Right);
    }
    Root->Num_Order = 0;
}
//---------------------------------------------------------------------------
// 10-2 Создание путей в дереве с четными вершинами
//---------------------------------------------------------------------------
int BTree::Create_Order_Row_2(Node_Tree* Root)
{
    int Left_Height = 0;
    int Right_Height = 0;

    if (Root->Left != NULL)
    {
        Left_Height = Create_Order_Row_2(Root->Left);
    }
    if (Root->Right != NULL)
    {
        Right_Height = Create_Order_Row_2(Root->Right);
    }
    if ((Root->Left == NULL) && (Root->Right == NULL))
    {
        if (Root->Value % 2 == 0)
        {
            Root->Num_Order = 1;
        }
        return Root->Num_Order;
    }
    else
    {
        if (Root->Value % 2 == 0)
        {
            if (Left_Height > Right_Height)
            {
                Root->Num_Order = Left_Height + 1;
            }
            else
            {
                Root->Num_Order = Right_Height + 1;
            }
            return Root->Num_Order;
        }
        else return 0;
    }
    return 0;
}
//---------------------------------------------------------------------------
// 10-3 Определение длинны максимального пути с четными вершинами
//---------------------------------------------------------------------------
int BTree::Max_Order_Row_3(Node_Tree* Root)
{
    int Left_Height = 0;
    int Right_Height = 0;
    int MaxOrder = Root->Num_Order;

    if (Root->Left != NULL)
    {
        Left_Height = Max_Order_Row_3(Root->Left);
        if (MaxOrder < Left_Height)
        {
            MaxOrder = Left_Height;
        }
    }
    if (Root->Right != NULL)
    {
        Right_Height = Max_Order_Row_3(Root->Right);
        if (MaxOrder < Right_Height)
        {
            MaxOrder = Right_Height;
        }
    }

    return MaxOrder;
}
//---------------------------------------------------------------------------
// 10-4 Удаление всех путей кроме максимальных путей с четными вершинами
// если Flag = 1 то на предыдущем уровне мы находились в цепочке с максимальным путем
// если Flag = 0 в противном слечае
// Current - текущяя позиция в максимальном пути (т.е. мы движемся по максимальному пути)
// Max - Длинная максимального пути
//---------------------------------------------------------------------------
void BTree::Delete_Not_Max_Order_4(Node_Tree* Root, int Max, int Current, int Flag)
{
    int Left_Height		= 0;
    int Right_Height	= 0;
    int Local_Flag		= 0;

    Local_Flag = Flag;
    if (Root->Num_Order == Max)								// обнаружена первая вершина максимального пути
    {
        Current = Max - 1;
        Local_Flag = 1;
    }
    else if ((Root->Num_Order == Current) && (Flag == 1))	// обнаружена любая другая вершина максимального пути (не первая)
    {
        Current = Current - 1;
        Local_Flag = 1;
    }
    else
    {
        Current = 0;										// вершина не расположена максимальном пути с четными вершинами
        Local_Flag = 0;
        Root->Num_Order = 0;
    }

    if (Root->Left != NULL)
    {
        Delete_Not_Max_Order_4(Root->Left, Max, Current, Local_Flag);
    }
    if (Root->Right != NULL)
    {
        Delete_Not_Max_Order_4(Root->Right, Max, Current, Local_Flag);
    }

    return;
}
//---------------------------------------------------------------------------
// 10-5 Распечатываем самые длинные пути в дереве с четными вершинами
//---------------------------------------------------------------------------
void BTree::Prn_Max_Order_5(Node_Tree* Root, int Max, int Current, int Flag)
{
    int Left_Height = 0;
    int Right_Height = 0;
    int LocalFlag = 0;

    LocalFlag = Flag;
//	if ((Root->Num_Order == Max) && (Flag1 == 1))
    if ((Root->Num_Order == Max))
    {
        cout  << "\n way: "<< Root->Value;
        Current = Max - 1;
        LocalFlag = 1;
    }
    else if ((Root->Num_Order == Current) && (LocalFlag == 1))
    {
        cout << " -- "<< Root->Value ;
        Current = Current - 1;
        if (Root->Num_Order == 1)
        {
            LocalFlag = 0;
            Root->Num_Order = 0;
        }
    }
    else
    {
        Root->Num_Order = 0;
        LocalFlag = 0;
    }

    if (Root->Left != NULL)
    {
        Prn_Max_Order_5(Root->Left, Max, Current, LocalFlag);
    }
    if (Root->Right != NULL)
    {
        Prn_Max_Order_5(Root->Right, Max, Current, LocalFlag);
    }

    return;
}

//----------------------------------------------------------------------------
// 11-1 При необходимости меняем местами корень с одним из его сыновей
//----------------------------------------------------------------------------
void BTree::Exch_Numbers(Node_Tree* Root)
{
    int NumLeft = 0;
    int NumRight = 0;
    int Tmp;

    if (Root->Value % 2 == 0) return;

    if (Root->Left != NULL)
    {
        NumLeft = Root->Left->Value;
    }
    if (Root->Right != NULL)
    {
        NumRight = Root->Right->Value;
    }

    if ((NumLeft > 0) && (NumLeft % 2 == 0))
    {
        Root->Left->Value = Root->Value;
        Root->Value = NumLeft;
        Exch_Numbers(Root->Left);
    }
    else if ((NumRight > 0) && (NumRight % 2 == 0))
    {
        Root->Right->Value = Root->Value;
        Root->Value = NumRight;
        Exch_Numbers(Root->Right);
    }
    return;
}
//----------------------------------------------------------------------------
// 11 -  Сместить нечетные вершины вниз
//----------------------------------------------------------------------------
void BTree::Move_Odd_Down(Node_Tree* Root)
{
    if (Root->Left != NULL)
    {
        Move_Odd_Down(Root->Left);
    }
    if (Root->Right != NULL)
    {
        Move_Odd_Down(Root->Right);
    }
    Exch_Numbers(Root);
}
//----------------------------------------------------------------------------
// 12 -  вставить сумму вершин от корня до этого листа
//----------------------------------------------------------------------------
void BTree::Prn_Tree_SumPrevNodes(const Node_Tree *Root, const int sum)
{
    printf(" %d ;", sum + Root->Value);
    if (Root->Left != NULL)
    {
        Prn_Tree_SumPrevNodes(Root->Left, sum + Root->Value);
    }
    if (Root->Right != NULL)
    {
        Prn_Tree_SumPrevNodes(Root->Right, sum + Root->Value);
    }
}
//----------------------------------------------------------------------------
// 13 -  В вершину вставить сумму листьев достижимых из данной вершины
//----------------------------------------------------------------------------
int BTree::Prn_Tree_SumExistentNodes(const Node_Tree* Root)
{
    int sum = Root->Value;
    if (Root->Left != NULL)
    {
        sum += Prn_Tree_SumExistentNodes(Root->Left);
    }
    if (Root->Right != NULL)
    {
        sum += Prn_Tree_SumExistentNodes(Root->Right);
    }
   // printf(" %d ;", sum);
    return sum;
}
//--------------------------------------------------------------------------
//----------------------------------------------------------------------------
// 14 -  В вершину вставить сумму листьев НЕ достижимых из данной вершины
//----------------------------------------------------------------------------
void BTree::Prn_Tree_SumNotExistentNodes(const Node_Tree *Root, int sum)
{
    printf(" %d ;", sum); // Печатаем сумму недоступных из данной вершины узлов,
    int sumleft = sum; // Сумма вершин слево
    int sumright = sum; // сумма вершин справо
    if (Root->Left != NULL)
    {
        // Получаем сумму левого поддерева
        sumleft += Prn_Tree_SumExistentNodes(Root->Left);
    }
    if (Root->Right != NULL)
    {
        // Получаем сумму правого поддерева
        sumright += Prn_Tree_SumExistentNodes(Root->Right);
    }
    if (Root->Left != NULL)
    {
        // передаём налево сумму правого поддерева и текущего узла,
        // так как они недоступны слево следующему узлу слево
        Prn_Tree_SumPrevNodes(Root->Left, sumright + Root->Value);
    }
    if (Root->Right != NULL)
    {
        // Передаём направо сумму левого поддерева и текщего узла,
        // так как они не доступны справо.
        Prn_Tree_SumPrevNodes(Root->Right, sumleft + Root->Value);
    }
}

//--------------------------------------------------------------------------
// 15 -  В лист вставить сумму всех вершин за исключением вершин от корня до этого листа
//----------------------------------------------------------------------------
void BTree::Prn_Tree_SumWithoutPrevNodes(const Node_Tree *Root)
{
    int sum = 0; //

    if (Root->Left != NULL)
    {
       sum += Prn_Tree_SumExistentNodes(Root->Left);
    }
    if (Root->Right != NULL)
    {
        sum += Prn_Tree_SumExistentNodes(Root->Right);
    }
    printf(" %d ;", sum);
    if (Root->Left != NULL)
    {
        Prn_Tree_SumWithoutPrevNodes(Root->Left);
    }
    if (Root->Right != NULL)
    {
        Prn_Tree_SumWithoutPrevNodes(Root->Right);
    }
}

//--------------------------------------------------------------------------
int MC_Carthy(int Value)
{
    int Result;
    if (Value > 100)
    {
        Result = Value - 10;
    }
    else
    {
        Result = MC_Carthy(MC_Carthy(Value + 11));
    }
    return Result;
}
//--------------------------------------------------------------------------
int Bizarre(int Value)
{
    int Result;
    if (Value == 1)
    {
        Result = 1;
    }
    else if (Value % 2 == 0)
    {
        Result = Bizarre((int)(Value / 2));
    }
    else // для нечетных n, больших 1
    {
        Result = Bizarre((int)(3 * Value + 1) / 2);
    }
    return Result;
}


//--------------------------------------------------------------------------
// Функция  меню
//--------------------------------------------------------------------------

void BTree::Run()
{
    int i;
    int Height;
    int HeightL;
    int LMax;

    while (true)
    {
        cout << "\n\n\n--------Меню-------:\n";
        cout << "1 -  Прямой обход дерева в глубину  \n";
        cout << "2 -  Обратный обход дерева в глубину \n";
        cout << "3 -  Симметричный обход дерева в глубину \n";
        cout << "4 -  Прямой обход дерева (вершины через одну) \n";
        cout << "5 -  Обратный обход дерева в глубину (вершины нечетные) \n";
        cout << "6 -  Прямой обход дерева (четные уровни) \n";
        cout << "7 -  Обход дерева в ширину \n";
        cout << "8 -  Распечатать самый низкий лист(листья) в дереве \n";
        cout << "9 -  Распечатать самый высокий лист(листья) в дереве \n";
        cout << "10 - Распечатать самые длинные пути в дереве с четными вершинами \n";
        cout << "11 - Сместить нечетные вершины вниз \n";
        cout << "12 - В лист вставить сумму вершин от корня до этого листа \n";
        cout << "13 - В вершину вставить сумму листьев достижимых из данной вершины \n";
        cout << "14 - В вершину вставить сумму листьев не достижимых из данной вершины \n";
        cout << "15 - В лист вставить сумму всех вершин за исключением вершин от корня до этого листа \n";
        cout << "0 - Выход -  \n";
        cin >> i;
        switch (i)
        {
            case 1:									//1 - Прямой обход дерева в глубину
            {
                cout << "1 -  Прямой обход дерева в глубину  \n";
                Print_Tree(CONST_Flag_Value);
                printf("\n\n - 1 - Прямой обход дерева в глубину - \n");
                Prn_Tree_Height_Direct(&Arr_Node[0]);
                break;
            }
            case 2:									//2 -  Обратный обход дерева в глубину
            {
                cout << "2 -  Обратный обход дерева в глубину \n";
                Print_Tree(CONST_Flag_Value);
                Prn_Tree_Height_Reverse(&Arr_Node[0]);
                break;
            }
            case 3:									//3 -  Симметричный обход дерева в глубину
            {
                cout << "3 -  Симметричный обход дерева в глубину \n";
                Print_Tree(1);
                Prn_Tree_Height_Symmetric(&Arr_Node[0]);
                break;
            }
            case 4:									//4  -  Прямой обход дерева (вершины через одну)
            {
                cout << "4 -  Прямой обход дерева (вершины через одну) \n";
                Print_Tree(CONST_Flag_Value);
                Prn_Tree_Height_Direct_2(&Arr_Node[0],1);
                break;
            }
            case 5:									// 5 -  Обратный обход дерева в глубину (вершины нечетные)
            {
                cout << "5 -  Обратный обход дерева в глубину (вершины нечетные) \n";
                Print_Tree(CONST_Flag_Value);
                Prn_Tree_Height_Reverse_Odd_Value(&Arr_Node[0]);
                break;
            }
            case 6:									// 6 -  Прямой обход дерева (четные уровни)
            {
                cout << "6 -  Прямой обход дерева (четные уровни) \n";
                Print_Tree(CONST_Flag_Value);
                Prn_Tree_Height_Direct_Even_Level(&Arr_Node[0], 1);
                break;
            }
            case 7:									// 7 -  Обход дерева в ширину
            {
                cout << "7 -  Обход дерева в ширину \n";
                Print_Tree(CONST_Flag_Value);
                Prn_Tree_Width(&Arr_Node[0]);
                break;
            }
            case 8:									// 8 -  Распечатать самый низкий лист(листья) в дереве
            {
                cout << "8 -  Распечатать самый низкий лист(листья) в дереве \n";
                Print_Tree(CONST_Flag_Value);
                Height = Get_Height(&Arr_Node[0]);				// находим высоту дерева
                Prn_Tree_HLeaf(&Arr_Node[0], 1, Height);		// Распечатываем листья на уровне = высота дерева
                break;
            }
            case 9:									// 9 -  Распечатать самый высокий лист(листья) в дереве
            {
                cout << "9 -  Распечатать самый высокий лист(листья) в дереве \n";
                Print_Tree(CONST_Flag_Value);
                HeightL = Get_HeightL(&Arr_Node[0]);			// находим высоту листа с минимальным уровнем
                Prn_Tree_HLeaf_2(&Arr_Node[0], 1, HeightL);		// Распечатываем листья на уровне = самый высокий лист
                break;
            }
            case 10:								// 10 -  Распечатать самые длинные пути в дереве с четными вершинами
            {
                cout << "10 - Распечатать самые длинные пути в дереве с четными вершинами \n";
                Print_Tree(CONST_Flag_Value);
                Clear_Order_1(&Arr_Node[0]);						// Очистка путей в дереве с четными вершинами (цепочек)
                Create_Order_Row_2(&Arr_Node[0]);					// Создание путей в дереве с четными вершинами
                Print_Tree(CONST_Flag_Number);						// Распечатка дерева с указанием максимальных путей с четными вершинами
                LMax = Max_Order_Row_3(&Arr_Node[0]);				// Определение длинны максимального пути с четными вершинами
                Delete_Not_Max_Order_4(&Arr_Node[0], LMax, 0, 0);	// Удаление всех путей кроме максимальных путей с четными вершинами
                Print_Tree(CONST_Flag_Number);						// Распечатка дерева с указанием максимальных путей с четными вершинами
                Prn_Max_Order_5(&Arr_Node[0], LMax, 0, 0);			// Распечатываем самые длинные пути в дереве с четными вершинами
                break;
            }
            case 11:								// 11 -  Сместить нечетные вершины вниз
            {
                Print_Tree(CONST_Flag_Value);
                Move_Odd_Down(&Arr_Node[0]);
                Print_Tree(CONST_Flag_Value);
                break;
            }
            case 12:								// 12 -  сумма вершин от корня до этого листа
            {
                Prn_Tree_SumPrevNodes(&Arr_Node[0], 0);
                break;
            }

                break;
            case 13:								// 13 -  сумма листьев доступных из вершины
            {
                Prn_Tree_SumExistentNodes(&Arr_Node[0]);
                break;
            }
            case 14:								// 14 -  сумма листьев не доступных из вершины
            {
                Prn_Tree_SumNotExistentNodes(&Arr_Node[0], 0);
                break;
            }
            case 15:								// 14 -  сумма листьев не доступных из вершины
            {
                Prn_Tree_SumWithoutPrevNodes(&Arr_Node[0]);
                break;
            }
            default:
                break;
        }
        getchar();
        getchar();

        if (i < 1)								// выход из меню программы
        {
            break;
        }
    }

}


//----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    int Val;
    setlocale(LC_ALL, "Russian");
    BTree Example_Tree;
    Example_Tree.Run();
/*	for (Val=1; Val<10; Val++)
	{
		printf("\n val %d :MC_Carthy %d", Val, MC_Carthy(Val));
	}
	for (Val = 10; Val < 30; Val++)
	{
		printf("\n val %d :Bizarre %d", Val, Bizarre(Val));
	}
*/
    printf("\n");
    getchar();
    return 0;
}
//----------------------------------------------------------------------------