#include <vector>
#include <iostream>
#include <stack>
#include <queue>

struct GraphNode
{
    int value{};
    std::vector<int> links{};
    bool visited{};
};

GraphNode* bfs(std::vector<GraphNode>& graph, GraphNode* current, int target, std::queue<GraphNode*>& queue)
{
    queue.push(current);

    while (!queue.empty())
    {
        auto node = queue.front();
        if (!node->visited && node->value == target)
        {
            return node;
        }
        queue.pop();
        for (auto index : node->links)
        {
            queue.push(&graph[index]);
        }
    }
    return nullptr;
}

GraphNode* dfs(std::vector<GraphNode>& graph, GraphNode* current, int target)
{
    if (current->visited)
    {
        return nullptr;
    }
    if (current->value == target)
    {
        return current;
    }
    current->visited = true;
    for (auto index : current->links)
    {
        auto result = dfs(graph, &graph[index], target);
        if (result)
        {
            return result;
        }
    }
    return nullptr;
}

int main()
{
    std::vector<GraphNode> graph{};
    graph.push_back({10, {1, 2}, false});
    graph.push_back({11, {0, 3, 4}, false});
    graph.push_back({12, {0, 5, 6}, false});
    graph.push_back({13, {1}, false});
    graph.push_back({46, {1}, false});
    graph.push_back({55, {2}, false});
    graph.push_back({4, {2}, false});

    auto dfs_result = dfs(graph, &graph[0], 55);
    if (!dfs_result)
    {
        std::cout << "dfs: No result!" << std::endl;
    }
    else
    {
        std::cout << "dfs: Yep!" << std::endl;
    }

    std::queue<GraphNode*> q{};
    auto bfs_result = bfs(graph, &graph[0], 55, q);
    if (!bfs_result)
    {
        std::cout << "bfs: No result!" << std::endl;
    }
    else
    {
        std::cout << "bfs: Yep!" << std::endl;
    }
    

    return 0;
}