#include "iostream"
#include "string"
#include "queue"
using namespace std;

#define max 45000

typedef struct
{
    int x, y;    //x表示第一行的数，y表示第二行的数
    string op;  //存储ABC操作
}Node;

Node start;
Node final;
bool isvisit[45000];
Node array[max]; //定义一个数组作为队列

void Operate(Node *node, int type)
{
    if(type == 1)   //进行A操作，上下行互换
    {
        int swap = node->x;
        node->x = node->y;
        node->y = swap;

        node->op = node->op + 'A'; //给op字符串加上A
    }
    
    else if (type == 2)
    {
        node->x = (node->x % 10) * 1000 + node->x / 10;
        node->y = (node->y % 10) * 1000 + node->y / 10;

        node->op = node->op + 'B';
    }

    else if (type == 3)
    {
        int i = node->x / 1000 * 1000;
        int j = node->x - i;
        int a = j / 100;
        int b = (j - a * 100)/10;
        int i1 = node->y / 1000 * 1000;
        int j1 = node->y - i1;
        int c = j1 / 100;
        int d = (j1 - c * 100)/10;
        node->x = i + c*100 + a*10 + node->x%10;
        node->y = i1 + d*100 + b*10 + node->y%10;

        node->op = node->op + 'C';
    }
}

bool is_final(Node node)   //判断是否已经成功
{
    if(node.x == final.x && node.y == final.y)
        return true;
    return false;
}

int cantor(int n, int size) //参数n为要求康托展开的数，size为全排列的位数
{
    int arr[8];
    int f[] = {1,1,2,6,24,120,720,5040,40320};
    int sum = 0;
    
    for (int i = size -1; i >= 0; i--) //将n的各个位上的数存到arr中
    {
        arr[i] = n % 10;
        n /= 10;
    }
    //求康托展开
    for (int i = 0; i < size - 1; i++)
    {
        int counter = 0;
        for(int j = i+1; j < size; j++)
            if(arr[i] > arr[j])
                counter++;
        sum += f[size- i-1] * counter;
    }

    return sum;
}

int main()
{
    int n; //不超过的步数
    
    start.x = 1234;
    start.y = 8765;
    start.op = "";
   
    while(cin>>n && n != -1)
    {   
        //Node array[max];  //定义一个数组作为队列
        final.x = 0;
        final.y = 0;
        for (int i = 0; i < 45000; i++ )
        {
            isvisit[i] = 0;
        }
        for (int i = 0; i < max-1; i++)
        {
            array[i].x = 0;
            array[i].y = 0;
        }
        int fp = 0;
        int rp = 0; //fp,rp分别指向队列头和尾

        bool sign = false;//判断结束的标识
        int num; //输入矩阵
        Node top,temp;
        
        //输入第一行的数，将4个数转化为一个四位数
        for (int i = 0; i < 4; i++)
        {
            cin>>num;
            final.x *= 10;
            final.x += num;
        }
        //输入第二行的数，将4个数转化为一个四位数
        for (int i = 0; i < 4; i++)
        {
            cin>>num;
            final.y *= 10;
            final.y += num;
        }
       
        array[fp] = start; //start入队
        rp++;

        while(fp != rp)   //队列非空
        {
            
            top = array[fp];//取队首元素

            //判断是否超过给定的长度
            if (top.op.size() > n)
                break;
            else if (is_final(top))
            {
                sign = true;
                break;
            }
            //进行ABC操作
            for (int i = 1; i < 4; i++)
            {
                temp = top;
                Operate(&temp, i);  //首先进行A操作
                num = cantor(temp.x * 10000 + temp.y, 8);//当前的队首元素为top给了temp进行康托展开
                //判断该状态是否被访问过，如果没有被访问过，则将其设为已访问，并将该状态入队
                if (!isvisit[num])
                {
                    isvisit[num] = true;  
                    array[rp++] = temp;//没有访问过入队
                }
            }
            fp++;  //删除队首元素
        }
        if(sign)
        {
            if(top.op.size() == 0)
                cout<<"0"<<endl;
            else
                cout<<top.op.size()<<" "<<top.op<<endl;
        }
        else
            cout<<-1<<endl;
    }
    
    return 0;
}                                 
