
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "bstree.hpp"
#include "graph.hpp"

using namespace std;

/*
@brief: 获取随机数
@param: buffer
@param: count 生成数量
@param: min max 生成数据所在区间 
*/
void random_get(int *buffer, int count, int min, int max)
{
    srand((unsigned int)time(0));
    buffer[0] = rand() % min + (max-min);
    cout << buffer[0] << "\t";
    for (int i = 1; i < count; i++)
    {
        int num = rand() % min + (max-min);
        for (int j = 0; j < i;)
        {
            if (num == buffer[j])
            {
                num = rand() % min + (max-min);
                j = 0;
                continue;
            }
            j++;
        }
        buffer[i] = num;
        cout <<  buffer[i] << "\t";
    }
    cout << endl;
}


int main()
{
    int datacount;
    cout << "输入生成数量\n";
    cin >> datacount;
    cout << "输入生成区间\n";
    int min, max;
    cin >> min >> max;
    int *number = new int[datacount];
    random_get(number, datacount, min, max);
    // 建立二叉排序树
    Bstree<int> bstree;
    for (int i = 0; i < datacount; i++)
        bstree.insert(number[i]);
    bstree.inorder();
    cout << endl;
    cout << "树的高度" << bstree.treehigh() << endl;
    // cout << "树的叶子数" << bstree.countleaf() << endl;
    cout << "请插入数值！\n";
    cin >> bstree;
    cout << bstree;
    cout << "树的高度" << bstree.treehigh() << endl;
    // cout << "树的叶子数" << bstree.countleaf() << endl;
    // 测试深拷贝
    Bstree<int> treeclone;
    treeclone = bstree;
    cout << "输出深拷贝的树\n" << treeclone << "输入插入值\n";
    cin >> treeclone;
    cout << "输出深拷贝的树\n" << treeclone;
    cout << "输出源树\n" << bstree;
    // 测试查找
    for (int i = 0; i < 2; i++)
    {
        cout << "输入查找的数字\n";
        int key;
        cin >> key;
        auto get = treeclone.find(key);
        if (get)
            cout << "地址为" << get << endl;
        else
            cout << "二叉树中无该值\n";
    }
    cout << "最大值为：" << bstree.findmax() << endl;
    cout << "最小值为：" << bstree.findmin() << endl;
    // 测试删除
    cout << "请输入要删除的值\n";
    int num;
    cin >> num;
    bstree.remove(num);
    cout << "删除后的树：\n" << bstree; 
    // 测试图的建立以及拓扑
    bstree.buildgraph();
    cout << "邻接表为：\n";
    bstree.showgraph();
    cout << "拓扑排序为：\n";
    bstree.Topsoft();
    delete [] number;
    return 0;
}