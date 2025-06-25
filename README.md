✅ Supported Data Structures
1. Stack

    Array-based

    Fixed-size, generic element type

    Operations:

        push

        pop

        peek

        is_empty

        free_stack

3. Queue

    Singly linked list-based FIFO queue

    Dynamically allocated

    Operations:

        enqueue

        dequeue

        peek_queue

        is_queue_empty

        free_queue

4. Linked List

    Singly linked, generic node list

    Operations:

        push_front

        push_back

        filter_list

        transform_list

        print_list (with user-defined print function)

        free_list

5. Hash Map

    Separate chaining (linked list in buckets)

    Generic key-value store

    Operations:

        init_map

        insert_map

        get_map

        remove_map

        free_map

    Uses strdup to manage string keys

6. Matrix

    2D array abstraction

    Stores float values

    Operations:

        init_matrix

        set_element

        get_element

        print_matrix

        free_matrix

        Accessor utilities: get_matrix_rows, get_matrix_cols

7. Binary Tree

    Generic binary search tree

    Custom comparator support

    Operations:

        insert_tree

        traverse_tree_inorder, preorder, postorder

        print_tree (optional with structured formatting)

        free_tree

8. Graph

    DFS/BFS in algorithm.h

    Generic Graph

    Operations:  

        insert_edge  

        print_graph (with print_int) algorithm.h  

        has_edge  
        
        get_neighbors  
        
        remove_edge  

        free_graph  

🛠 Utilities (algorithm module)

    print_int, print_float, print_str

    transform_list (modifies each list node)

    filter_list (returns a new list)

    print_list with reverse option

    print_matrix

    print_tree

🧪 Usage Example

```c
int main(void) {
    LinkedList list;
    init_list(&list);

    for (int i = 1; i <= 10; ++i) {
        int value = i;
        push_back(&list, &value, sizeof(int));
    }

    transform_list(&list, square_int); // User-defined
    print_list(&list, print_int, 0);

    free_list(&list);
    return 0;
}  
```

💡 Goals & Philosophy

    Header-based modularity

    Avoid globals

    No external dependencies

    Clear learning value

    Fully heap-managed, generic memory-safe interfaces

📦 Future Ideas

    AVL Tree / Red-Black Tree

    Priority Queue (Heap)

    Dynamic Array (Vector-style)

    Thread-safe Queue

    Graph API

    Math / Equation Parser (Planned)

⚠️ Note on Memory

    Most structures require you to malloc elements manually

    Library handles internal freeing only, not user values (unless passed a destructor)

📄 License

MIT

Made for learning. Built to last. ❤️


