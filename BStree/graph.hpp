/*
 * @Author: huangjie 
 * @Date: 2019-11-23 20:49:45 
 * @brief 使用vector容器简单的实现图的邻接表存储
 * @Last Modified by: huangjie
 * @Last Modified time: 2019-11-23 22:39:31
 */
#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <cassert>



/*
@brief 图的类
*/
template <typename T>
class Graph
{
private:
    std::vector<std::vector<T>> vertex;
    int vertex_count;  
public:
    Graph():vertex_count(0) {}
    ~Graph();
    void add_vertex(T vname);   // 添加顶点
    void add_edge(T vname, T w);  // 添加边
    void show() const;                // 显示图
    void Topsort();             // 拓扑排序
};


/*
@brief 邻接表顶点添加
@param vname 顶点名
*/
template <typename T>
void Graph<T>::add_vertex(T vname)
{
    std::vector<T> edge;
    edge.push_back(vname);
    vertex.push_back(edge);
    vertex_count += 1;
}


/*
@brief 添加边
@param vname 顶点
*/
template <typename T>
void Graph<T>::add_edge(T vame, T w)
{
    auto iter = vertex.begin();
    for (iter; iter != vertex.end(); iter++)
    {
        if ((*iter).front() == vame)
        {
            (*iter).push_back(w);
            break;
        }
    }
    if (iter == vertex.end())
    {
        // 无这个顶点，先添加顶点
        std::vector<T> edge;
        edge.push_back(vame);
        edge.push_back(w);
        vertex.push_back(edge);
        vertex_count += 1;
        add_vertex(w);
        return;
    }
    add_vertex(w); //新的顶点
}


/*
@brief: 实现图的拓扑排序
*/
template <typename T>
void Graph<T>::Topsort()
{
    assert(vertex_count != 0);  //图不能为空
    std::map<T, int> indegree;  // 统计每个顶点的入度
    int amount = 0;
    // 先统计每个节点的入度
    for(auto iter : vertex)
    {
        for(auto it = iter.begin(); it != iter.end(); it++)
        {
            if(it == iter.begin())
                indegree.insert(std::pair<T, int>(*it, 0));
            else
                indegree[*it] ++;
        }
    }
    
    std::queue<T> qu; // 用来存放入度为0的节点
    for(auto iter : vertex)
    {
        if(indegree[iter[0]] == 0)
            qu.push(iter[0]);  // 入度为0的入队列
    }
    // 队列不为空
    while(!qu.empty())
    {
        T ver = qu.front();
        qu.pop();
        std::cout << ver << "->";
        for(auto iter : vertex)
        {
            // 找到这个结点的边
            if(iter[0] == ver)
            {
                for(int i = 1; i < iter.size(); i++)
                {
                    indegree[iter[i]]--;
                    if(indegree[iter[i]] == 0)
                        qu.push(iter[i]);
                }
            }
        }
        amount++;
    }
    std::cout<< std::endl;
    if(amount != vertex_count)
        std::cout << "Graph has a cycle\n";
}


/*
@brief: 打印建立的图
*/
template <typename T>
void Graph<T>::show() const
{
    assert(vertex_count != 0);
    std::cout << "建立的领接表如下\n";
    for(auto iter = vertex.begin(); iter != vertex.end(); iter++)
    {
        for(auto ite = (*iter).begin(); ite != (*iter).end(); ite++)
        {
            std::cout << *ite << "--> ";
        }
        std::cout << std::endl;
    }
}


/*
@brief:析构函数
*/
template <typename T>
Graph<T>::~Graph()
{
    std::vector<std::vector<T>>().swap(vertex);
}



#endif