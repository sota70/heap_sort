#include <cstring>
#include <iostream>
#include <string>

#define NULL_NUM -1

int divide(int num, int divider);
int main();

class heap_tree {

public:
  heap_tree(int _capacity) : capacity(_capacity) {
    tree = (int *)malloc(sizeof(int) * _capacity);
    memset(tree, NULL_NUM, sizeof(int) * _capacity);
    tail = 0;
  }

  ~heap_tree() { free(tree); }

  void insert(int new_node) {
    int current_node = tail + 1;
    int parent_node;
    _insert(new_node, current_node);
    while (current_node > 1) {
      parent_node = divide(current_node, 2);
      if (tree[current_node] >= tree[parent_node]) {
        break;
      }
      _swap(current_node, parent_node);
      current_node = parent_node;
    }
  }

  int remove_root() {
    int root_node = tree[1];
    int current_node = 1;
    int left_child, right_child, swap_child;
    _insert(tree[tail], 1);
    _insert(NULL_NUM, tail);
    tail--;
    while (current_node * 2 <= tail) {
      left_child = current_node * 2;
      right_child = current_node * 2 + 1;
      swap_child = right_child <= tail && tree[right_child] < tree[left_child]
                       ? right_child
                       : left_child;
      if (tree[current_node] <= tree[swap_child]) {
        break;
      }
      _swap(current_node, swap_child);
      current_node = swap_child;
    }
    return root_node;
  }

  int *get_tree() { return tree; }

private:
  int *tree;
  int capacity;
  int tail;

  void _insert(int new_node, int pos) {
    if (tail >= capacity) {
      return;
    }
    if (tree[pos] == NULL_NUM) {
      tree[pos] = new_node;
      tail++;
      return;
    }
    tree[pos] = new_node;
  }

  void _swap(int pos1, int pos2) {
    if (tree[pos1] == tree[pos2]) {
      return;
    }
    tree[pos1] = tree[pos1] ^ tree[pos2];
    tree[pos2] = tree[pos1] ^ tree[pos2];
    tree[pos1] = tree[pos1] ^ tree[pos2];
  }
};

int divide(int num, int divider) {
  int divide_count = 0;
  if (num < 1 || divider < 1) {
    return -1;
  }
  while (num >= divider) {
    num -= divider;
    divide_count++;
  }
  return divide_count;
}

int main() {
  int tree_capacity = 20;
  int nums[] = {20, 1, 50, 2, 5, 3, 100, 8, 14, 21};
  int nums_size = sizeof(nums) / sizeof(int);
  heap_tree tree(tree_capacity);
  for (int i = 0; i < nums_size; i++) {
    printf("%d, ", nums[i]);
  }
  printf("\n");
  for (int i = 0; i < nums_size; i++) {
    tree.insert(nums[i]);
  }
  for (int i = 0; i < nums_size; i++) {
    printf("%d ", tree.remove_root());
  }
  printf("\n");
  return 0;
}
