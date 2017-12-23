#include <iostream>
#include <cmath>
using namespace std;

typedef struct Point
{//二维坐标上的点
    int x;
    int y;
}Point;

int Distance(Point a, Point b)
{//两点间距离
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

bool ascendX(Point a, Point b)
{//按x的值升序排序
    return a.x < b.x;
}

bool ascendY(Point a, Point b)
{//按y的值升序排序
    return a.y < b.y;
}

int ClosestPoints(Point points[], int length, Point &a, Point &b)
{// 求出最近点对记录，并将两点记录再a、b中
    int distance;                       //最近的两点距离
    int d1, d2;                         //分割后两个子集中各自最小点对距离
    Point a1, b1, a2, b2;               //保存分割后两个子集中最小点对
    int i = 0, j = 0, k = 0, x = 0;

    if (length < 2)
        return 65536;    //若子集长度小于2,则返回最大距离
    else if (length == 2)
    {//若子集长度等于2，直接返回该两点的距离
        a = points[0];
        b = points[1];
        distance = Distance(points[0], points[1]);
    }
    else
    {//用分治法求解
        Point *p1 = new Point[length];              //新建两个子集
        Point *p2 = new Point[length];

        sort(points, points + length, ascendX);     //根据横坐标对二维点进行排序
        int mid = points[(length - 1) / 2].x;       //确定中间的分割线

        for (i = 0; i < length / 2; i++)                   //存储两个部分的点
            p1[i] = points[i];
        for (int j = 0, i = length / 2; i < length; i++)
            p2[j++] = points[i];

        d1 = ClosestPoints(p1, length / 2, a1, b1);             //分别求两部分的最近点和距离
        d2 = ClosestPoints(p2, length - length / 2, a2, b2);

        if (d1 < d2) { distance = d1; a = a1; b = b1; }        //记录最近点和距离
        else { distance = d2; a = a2; b = b2; }

        //求解跨分割线并在δ×2δ区间内的最近点对
        Point *p3 = new Point[length];

        for (i = 0, k = 0; i < length; i++)              //取得中间2δ宽度的所有点对共k个
            if (abs(points[i].x - mid) <= distance)
                p3[k++] = points[i];

        sort(p3, p3 + k, ascendY);                       // 以y的值大小排序矩阵内的点集合

        for (i = 0; i < k; i++)
        {
            if (p3[j].x - mid >= 0)                          //找到右边点在对侧相邻的6个点进行比较
                continue;
            x = 0;
            for (j = i + 1; j <= i + 6 + x && j < k; j++)
            {
                if (p3[j].x - mid < 0)
                {//  假如i点是位于分界的左边，则跳过
                    x++;
                    continue;
                }
                if (Distance(p3[i], p3[j]) < distance)
                {//如果跨分割线的两点距离小于已知最小距离，则记录该距离和两点
                    distance = Distance(p3[i], p3[j]);
                    a = p3[i];
                    b = p3[j];
                }
            }
        }
    }
    return distance;
}

void SetPoints(Point *points, int length)
{//随机生成二维坐标点
    srand(unsigned(time(NULL)));
    for (int i = 0; i < length; i++)
    {
        points[i].x = (rand() % 100);
        points[i].y = (rand() % 100);
    }
}

int main()
{
    int num;
    Point a, b;
    int diatance;

    cout << "二维点个数:";
    cin >> num;

    Point *points = new Point[num];
    SetPoints(points, num);
    diatance = ClosestPoints(points, num, a, b);

    cout << endl << "二维点坐标：" << endl;
    for (int i = 0; i < num; i++)
        cout << "(" << points[i].x << "," << points[i].y << ")" << endl;
    cout << endl << "最近点对为：" << "(" << a.x << "," << a.y << ")和" << "(" << b.x << "," << b.y << ")" << endl ;
    cout << "最近点对距离为：" << diatance << endl;
}