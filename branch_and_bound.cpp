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
    node->path.push_back(0);
    // node->matrix.print();
    node->level = 0;

    return node;
}

Node *create_node(Node *parent, int vertex)
{
    Node *new_node = new Node(parent->matrix);
    new_node->path = parent->path;
    new_node->path.push_back(vertex);
    new_node->vertex = vertex;
    new_node->level = parent->level + 1;
    new_node->matrix.set_INF(parent->vertex, vertex);
    return new_node;
}

void branch_and_bound::branch_and_bound_tsp(std::string file_name)
{
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
            while (!queue.empty())
            {
                Node *free_node = queue.top();
                queue.pop();
                delete free_node;
            }
            node->traceback();
            std::cout << "Cost: " << node->cost << std::endl;
            std::cout << "OPT: " << node->matrix.OPT << std::endl;
            delete node;
            break;
        }

        for (int i = 0; i < node->matrix.number_of_vertices; i++)
        {
            if (node->matrix.get(node->vertex, i) != std::numeric_limits<int>::max())
            {
                Node *new_node = create_node(node, i);
                new_node->cost = node->cost + node->matrix.get(node->vertex, i) + new_node->matrix.reduce_matrix();
                queue.push(new_node);

                // new_node->print();
                // new_node->traceback();
            }
        }

        delete node;
    }
}

struct FixedComparator
{
    bool operator()(const Node *ln, const Node *rn)
    {
        return ln->cost + (ln->matrix.number_of_vertices - ln->level) * 100000 > rn->cost + (rn->matrix.number_of_vertices - rn->level) * 100000;
        // prawy jest lepszy bo ma mniejszy koszt
        // ale lewy ma wiekszy poziom wiec moze powinien byc lepszy ((?))
    }
};

// void branch_and_bound::branch_and_bound_tsp_fixed(std::string file_name)
// {
//     adjency_matrix matrix = adjency_matrix(file_name);
//     // matrix.print();
//     int best_cost = matrix.max_int;
//     std::vector<int> best_path;

//     Node *head = create_head(matrix);

//     std::priority_queue<Node *, std::vector<Node *>, FixedComparator> queue;

//     queue.push(head);

//     while (!queue.empty())
//     {
//         Node *node = queue.top();
//         queue.pop();
//         if (node->cost > best_cost)
//         {
//             delete node;
//             while (!queue.empty())
//             {
//                 Node *free_node = queue.top();
//                 queue.pop();
//                 delete free_node;
//             }
//         }

//         if (node->level == node->matrix.number_of_vertices - 1)
//         {
//             if (node->cost < best_cost)
//             {
//                 best_cost = node->cost;
//                 best_path = node->path;
//                 node->print();
//             }
//             else
//             {
//                 delete node;
//                 continue;
//             }
//             if (queue.empty())
//             {
//                 node->traceback();
//                 std::cout << node->cost << std::endl;
//                 std::cout << "OPT: " << node->matrix.OPT << std::endl;
//                 delete node;
//                 break;
//             }
//             Node *new_top = queue.top();
//             if (node->cost < new_top->cost)
//             {
//                 queue.pop();
//                 delete new_top;
//                 queue.push(node);
//                 break;
//             }
//         }

//         for (int i = 0; i < node->matrix.number_of_vertices; i++)
//         {
//             if (node->matrix.get(node->vertex, i) != std::numeric_limits<int>::max())
//             {
//                 Node *new_node = create_node(node, i);
//                 new_node->cost = node->cost + node->matrix.get(node->vertex, i) + new_node->matrix.reduce_matrix();
//                 queue.push(new_node);

//                 // new_node->print();
//                 new_node->traceback();
//             }
//         }

//         delete node;
//     }
// }