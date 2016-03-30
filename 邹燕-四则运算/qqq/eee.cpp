#include <iostream>
#include <cstdlib>
#include <ctime>
 
using namespace std;
 

class cal
{
public:
    
    cal();
    
    ~cal();
    
    void CreateEx(int numOfNode);
    
    int Count();
   
    void Display();
     
private:
   
    bool OperIsHigher();
    
    int GetPriOfOper(const char oper);
 
private:
    int intR;
    
    char oper;
       
    cal *lhs;
        // 表达式的左节点
    cal *rhs;
        // 表达式的右节点
    bool isRoot;
        // 该表达式是否为最终的表达式
    cal *Parent;
        // 表达式的父节点
    bool isLeft;
        // 是否为左节点(为了输出是加括号用)
};
cal::cal()
: intR(0)
, oper('\0')
, lhs(NULL)
, rhs(NULL)
, Parent(NULL)
, isLeft(false)
{
     
}
 
cal::~cal()
{
    if(lhs != NULL)
    {
        delete lhs;
    }
 
    if (rhs != NULL)
    {
        delete rhs;
    }
}
 
void cal::CreateEx(int numOfNode)
{
    if (1 == numOfNode)
    {
        return ;
    }
    else
    {
        int mode = rand() % 4;
        if (0 == mode)
        {
            oper = '+';
        }
        else if (1 == mode)
        {
            oper = '-';
        }
        else if (2 == mode)
        {
            oper = '*';
        }
        else
        {
            oper = '/';
        }
 
        lhs = new cal();
        rhs = new cal();
        lhs->Parent = this;
        lhs->isLeft = true;
        rhs->Parent = this;
        rhs->isLeft = false;
 
        int numOfNodeLeft = numOfNode- rand() % numOfNode;
        if (numOfNodeLeft == numOfNode)
        {  
				numOfNodeLeft = 1;
        }
 
        lhs->CreateEx(numOfNodeLeft);
        rhs->CreateEx(numOfNode - numOfNodeLeft);
    }
}
 
 
int cal::Count()
{
    if (lhs != NULL && rhs != NULL)
    {
        int lResult = 0;
        int rResult = 0;
 
        lResult = lhs->Count();
        rResult = rhs->Count();
 
        while (lResult >= 5000 || lResult <= 0)
        {
            lResult = lhs->Count();
        }
 
        while (rResult >= 5000 || rResult <= 0)
        {
            rResult = rhs->Count();
        }
 
        if ('+' == oper)
        {
            intR = lResult + rResult;
        }
 
        else if ('-' == oper)
        {
            intR = lResult - rResult;
            if (intR < 0)
            {
                cal *temp = lhs;
                lhs = rhs;
                lhs->isLeft = true;
                rhs = temp;
                rhs->isLeft = false;
                intR = rResult - lResult;
            }
        }
 
        else if ('*' == oper)
        {
            int getNum = 0;
            intR = lResult * rResult;
            while(intR >= 3000)
            {
                lResult = lhs->Count();
                rResult = rhs->Count();
                getNum++;
 
                if (getNum > 3000)
                {
                    int mode = rand() % 2;
                    if (0 == mode)
                    {
                        oper = '+';
                        intR = lResult + rResult;
                    }
                    else if (1 == mode)
                    {
                        oper = '-';
                        intR = lResult - rResult;
                        if (intR < 0)
                        {
                            cal *temp = lhs;
                            lhs = rhs;
                            lhs->isLeft = true;
                            rhs = temp;
                            rhs->isLeft = false;
                            intR = rResult - lResult;
                        }
                    }
 
                    return intR;
                }
 
                intR = lResult * rResult;
            }
        }
 
        else if ('/' == oper)
        {
            int getNum = 0;
            while (0 == lResult || 0 == rResult || lResult % rResult != 0)
            {
                lResult = lhs->Count();
                rResult = rhs->Count();
                getNum++;
                if(getNum > 2000)
                {
                    int mode = rand() % 2;
                    if (0 == mode)
                    {
                        oper = '+';
                        intR = lResult + rResult;
                    }
                    else if (1 == mode)
                    {
                        oper = '-';
                        intR = lResult - rResult;
                        if (intR < 0)
                        {
                            cal *temp = lhs;
                            lhs = rhs;
                            lhs->isLeft = true;
                            rhs = temp;
                            rhs->isLeft = false;
                            intR = rResult - lResult;
                        }
                    }
 
                    return intR;
                }
            }
 
            intR = lResult / rResult;
        }
    }
    else
    {
        intR = rand() % 5000;
        while (intR == 0)
        {
            intR = rand() % 5000;
        }
    }
 
    return intR;
}
 
void cal::Display()
{
    if(lhs != NULL && rhs != NULL)
    {
        if (!OperIsHigher())
        {
            cout << '(';
        }
        lhs->Display();
        cout << " " << oper << " ";
        rhs->Display();
        if (!OperIsHigher())
        {
            cout << ')';
        }
    }
    else
    {
        cout << intR;
    }
}
 
bool cal::OperIsHigher()
{
    if (NULL == Parent)
    {
        return true;
    }
    if (isLeft)
    {
        return GetPriOfOper(this->oper) >= GetPriOfOper(Parent->oper);
    }
    else
    {
        return GetPriOfOper(this->oper) > GetPriOfOper(Parent->oper);
    }
}
 
int cal::GetPriOfOper(const char oper)
{
    if ('\0' == oper)
    {
        return 3;
    }
    else if ('/' == oper || '*' == oper)
    {
        return 2;
    }
    else if ('+' == oper || '-' == oper)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int main()
{
    cal *pRoot = NULL;
 
    int numOfcal = 0;
 
    int numOfNumber = 0;
 
    cout << "please input the number of arithmetic expressions:" << endl;
 
    cin >> numOfcal;
 
    int intR = 0;
    srand((int)time(0));
 
    for (int i = 0; i < numOfcal; i++)
    {
        pRoot = new cal();
        numOfNumber = rand() %7 + 2;
        pRoot->CreateEx(numOfNumber);
        intR = pRoot->Count();
        while (intR >= 5000 || intR <= 0)
        {
            intR = pRoot->Count();
       }
        pRoot->Display();
        cout << " = " << intR;
        cout << endl;
        delete pRoot;
    }
	 cin >> numOfcal;
    return 0;
}