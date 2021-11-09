#include "branch_and_bound.h"

#define LOG(x) std::cout << x << std::endl;

struct Comparator
{
    bool operator()(const Node *ln, const Node *rn)
    {
        return ln->cost > rn->cost;
    }
};

Node *create_head(adjency_matrix &matrix)
{
    Node *node = new Node(matrix);

    node->cost += node->matrix.reduce_matrix();
    node->matrix.print();
    node->level = 0;

    return node;
}

Node *create_node(Node *parent, int vertex)
{
    Node *new_node = new Node(parent->matrix);
    new_node->parent = parent;
    new_node->vertex = vertex;
    new_node->level = parent->level + 1;
    new_node->matrix.set_INF(parent->vertex, vertex);
    return new_node;
}

void branch_and_bound::branch_and_bound_tsp()
{
    std::string file_name = "instances/m6.atsp";
    adjency_matrix matrix = adjency_matrix(file_name);

    matrix.print();

    Node *head = create_head(matrix);

    std::priority_queue<Node *, std::vector<Node *>, Comparator> queue;

    queue.push(head);

    while (!queue.empty())
    {
        Node *node = queue.top();
        queue.pop();

        if (node->level == node->matrix.number_of_vertices - 1)
        {
            node->traceback();
            std::cout << node->cost << std::endl;
            break;
        }

        for (int i = 0; i < node->matrix.number_of_vertices; i++)
        {
            if (node->matrix.get(node->vertex, i) != std::numeric_limits<int>::max())
            {
                Node *new_node = create_node(node, i);
                new_node->cost = node->cost + node->matrix.get(node->vertex, i) + new_node->matrix.reduce_matrix();
                // new_node->print();
                queue.push(new_node);
            }
        }

        // delete node;
    }
}