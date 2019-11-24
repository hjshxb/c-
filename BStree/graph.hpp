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
    void show();                // 显示图
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
        return;
    }
    add_vertex(w); //新的顶点
}



/*
@brief: 打印建立的图
*/
template <typename T>
void Graph<T>::show()
{
    std::cout << "建立的领接表如下\n";
    for (auto iter = vertex.begin(); iter != vertex.end(); iter++)
    {
        for (auto ite = (*iter).begin(); ite != (*iter).end(); ite++)
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