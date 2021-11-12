#include "branch_and_bound.h"

#define MAX_VALUE 100000

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
                // std::cout << std::endl
                //           << std::endl;
            }
        }

        delete node;
    }
}

struct FixedComparator
{
    bool operator()(const Node *ln, const Node *rn)
    {
        /* MAX_VALUE represents a constant mathematical ceiling of the edge cost in an instance, used to lower the priority of the nodes with low levels
        This strategy helps the algorithm in determining an optimal solution, that can be then used to reduce the number of nodes that need to be evaluated
        This approach is slower, but less memory-heavy, because by generating some solutions on the go, it allows the pruning of the tree */
        return ln->cost + (ln->matrix.number_of_vertices - ln->level) * MAX_VALUE > rn->cost + (rn->matrix.number_of_vertices - rn->level) * MAX_VALUE;
    }
};

void branch_and_bound::branch_and_bound_tsp_fixed(std::string file_name)
{
    adjency_matrix matrix = adjency_matrix(file_name);
    int OPT = matrix.OPT;
    // matrix.print();
    int best_cost = matrix.max_int;
    std::vector<int> best_path;

    Node *head = create_head(matrix);

    std::priority_queue<Node *, std::vector<Node *>, FixedComparator> queue;

    queue.push(head);
    Node *node;

    while (!queue.empty())
    {
        node = queue.top();
        queue.pop();

        if (node->cost >= best_cost)
        {
            if (node->level == node->matrix.number_of_vertices - 1)
            {
                delete node;
                break;
            }
            delete node;
            continue;
        }

        if (node->level == node->matrix.number_of_vertices - 1)
        {
            best_cost = node->cost;
            best_path = node->path;
            std::cout << "New solution: " << best_cost << std::endl;
            for (int i = 0; i < best_path.size(); i++)
            {
                std::cout << best_path[i] << " ";
            }
            std::cout << std::endl
                      << std::endl;
            continue;
        }

        for (int i = 0; i < node->matrix.number_of_vertices; i++)
        {
            if (node->matrix.get(node->vertex, i) != std::numeric_limits<int>::max())
            {
                Node *new_node = create_node(node, i);
                new_node->cost = node->cost + node->matrix.get(node->vertex, i) + new_node->matrix.reduce_matrix();

                if (new_node->cost < best_cost)
                {
                    queue.push(new_node);
                }
                else
                {
                    delete new_node;
                }

                // new_node->print();
                // new_node->traceback();
                // std::cout << "Cost: " << new_node->cost << std::endl;
            }
        }

        delete node;
    }

    while (!queue.empty())
    {
        Node *free_node = queue.top();
        queue.pop();
        delete free_node;
    }
    // node->traceback();
    // delete node;
    std::cout << "OPT: " << OPT << std::endl;
    std::cout << "Best solution: " << best_cost << std::endl;
    for (int i = 0; i < best_path.size(); i++)
    {
        std::cout << best_path[i] << " ";
    }
    std::cout << std::endl;
}