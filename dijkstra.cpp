#include <iostream>
#include <vector>
#include <queue>
#include <limits>


struct Node
{
    std::vector<int> links;
    std::vector<int> costs;
};

struct NodeWithScore
{
    NodeWithScore(const Node* node, int index, int score): node(node), index(index), score(score) {};
    const Node* node;
    int index;
    int score;

    bool operator < (const NodeWithScore& rhs) const
    {
        return this->score > rhs.score;
    }
};

std::vector<int> search(const std::vector<Node>& graph, int source_index)
{
    std::vector<int> path_lengths(graph.size(), std::numeric_limits<int>::max());
    path_lengths[source_index] = 0;

    std::priority_queue<NodeWithScore> q{};
    for (int i{0}; i < path_lengths.size(); i++)
    {
        q.emplace(&graph[i], i, path_lengths[i]);
    }

    int nodes_procesed{0};
    while (nodes_procesed != graph.size() && !q.empty())
    {
        auto next_node_with_score = q.top();
        auto node = *next_node_with_score.node;

        for (int i{0}; i <  node.links.size(); i++)
        {
            const auto link_index = node.links[i];
            const auto link_cost = node.costs[i];

            auto new_score{path_lengths[next_node_with_score.index] + link_cost};
            auto old_score{path_lengths[link_index]};
            if (new_score < old_score)
            {
                path_lengths[link_index] = new_score;
                q.emplace(&graph[link_index], link_index, new_score);
            }
        }

        q.pop();
        nodes_procesed++;
    }

    return path_lengths;
}



int main()
{
    std::vector<Node> graph{};
    graph.push_back({{1, 2}, {1, 4}});
    graph.push_back({{2, 3}, {2, 6}});
    graph.push_back({{3}, {3}});
    graph.push_back({});

    auto result = search(graph, 0);

    for (auto path_length : result)
    {
        std::cout << path_length << "," << std::endl;
    }


    return 0;
}