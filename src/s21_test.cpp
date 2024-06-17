#include <gtest/gtest.h>

#include "s21_containers.h"
#include "s21_containersplus.h"

TEST(list_test, list_constructor_default_test) {
  s21::list<int> lst;
  ASSERT_EQ(lst.empty(), true);
  ASSERT_EQ(lst.size(), 0);
}

TEST(list_test, list_constructor_size_test) {
  s21::list<int> lst(5);
  ASSERT_EQ(lst.empty(), false);
  ASSERT_EQ(lst.size(), 5);
}

TEST(list_test, list_constructor_initializer_test) {
  s21::list<int> lst({1, 2, 3, 4});
  ASSERT_EQ(lst.size(), 4);
  ASSERT_EQ(lst.front(), 1);
  ASSERT_EQ(lst.back(), 4);
}

TEST(list_test, list_constructor_copy_test) {
  s21::list<int> lst({1, 2, 3, 4});
  s21::list<int> lst1(lst);
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 4);
}

TEST(list_test, list_constructor_move_test) {
  s21::list<int> lst({1, 2, 3, 4});
  s21::list<int> lst1(std::move(lst));
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(lst.empty(), true);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 4);
}

TEST(list_test, operator_constructor_move_test) {
  s21::list<int> lst({1, 2, 3, 4});
  s21::list<int> lst1({4, 2});
  lst1 = std::move(lst);
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(lst.size(), 4);
  ASSERT_EQ(lst.empty(), false);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 4);
  ASSERT_EQ(lst.front(), 1);
  ASSERT_EQ(lst.back(), 4);
}

TEST(list_test, front_test) {
  s21::list<int> lst({1, 2, 3, 4});
  ASSERT_EQ(lst.front(), 1);
}

TEST(list_test, back_test) {
  s21::list<int> lst({1, 2, 3, 4});
  ASSERT_EQ(lst.back(), 4);
}

TEST(list_test, iterator_begin_test) {
  s21::list<int> lst({1, 2, 3, 4});
  ASSERT_EQ(lst.begin().ptr->value, 1);
}

TEST(list_test, iterator_operator_get_value_test) {
  s21::list<int> lst({1, 2, 3, 4});
  auto it = lst.begin();
  ASSERT_EQ(*it, 1);
}

TEST(list_test, iterator_operator_next_value_test) {
  s21::list<int> lst({1, 2, 3, 4});
  auto it = lst.begin();
  ++it;
  ASSERT_EQ(*it, 2);
}

TEST(list_test, iterator_operator_eq_test) {
  s21::list<int> lst({1, 2, 3, 4});
  auto it = lst.begin();
  auto it1 = lst.begin();
  ASSERT_EQ(it == it1, true);
}

TEST(list_test, iterator_operator_not_eq_test) {
  s21::list<int> lst({1, 2, 3, 4});
  auto it = lst.begin();
  auto it1 = lst.end();
  ASSERT_EQ(it != it1, true);
}

TEST(list_test, size_test) {
  s21::list<int> lst({1, 2, 3, 4});
  ASSERT_EQ(lst.size(), 4);
}

TEST(list_test, max_size_test) {
  s21::list<int> lst({1, 2, 3, 4});
  ASSERT_EQ(lst.max_size(), 1152921504606846975);
}

TEST(list_test, empty_test) {
  s21::list<int> lst;
  ASSERT_EQ(lst.empty(), true);
  ASSERT_EQ(lst.size(), 0);
}

TEST(list_test, clear_test) {
  s21::list<int> lst({1, 2, 3, 4});
  lst.clear();
  ASSERT_EQ(lst.empty(), true);
  ASSERT_EQ(lst.size(), 0);
}

TEST(list_test, insert_test) {
  s21::list<int> lst({1, 2, 3, 4});
  auto it = lst.begin();
  ++it;
  ASSERT_EQ(lst.insert(it, 6).ptr->value, 6);
  ASSERT_EQ(lst.size(), 5);
}

TEST(list_test, erase_test) {
  s21::list<int> lst({1, 6, 2, 3, 4});
  auto it = lst.begin();
  ++it;
  lst.erase(it);
  it = lst.begin();
  ++it;
  ASSERT_EQ(*it, 2);
  ASSERT_EQ(lst.size(), 4);
}

TEST(list_test, push_back_test) {
  s21::list<int> lst({1, 6, 2, 3, 4});
  lst.push_back(7);
  ASSERT_EQ(lst.size(), 6);
}

TEST(list_test, pop_back_test) {
  s21::list<int> lst({1, 6, 2, 3, 4});
  lst.pop_back();
  ASSERT_EQ(lst.size(), 4);
}

TEST(list_test, push_front_test) {
  s21::list<int> lst({1, 6, 2, 3, 4});
  lst.push_front(10);
  ASSERT_EQ(lst.begin().ptr->value, 10);
  ASSERT_EQ(lst.size(), 6);
}

TEST(list_test, pop_front_test) {
  s21::list<int> lst({1, 6, 2, 3, 4});
  lst.pop_front();
  ASSERT_EQ(lst.begin().ptr->value, 6);
  ASSERT_EQ(lst.size(), 4);
}

TEST(list_test, swap_test) {
  s21::list<int> lst({1, 6, 2, 3, 4});
  s21::list<int> lst1({10, 9, 8, 7, 6, 8});
  lst.swap(lst1);
  ASSERT_EQ(lst.begin().ptr->value, 10);
  ASSERT_EQ(lst1.begin().ptr->value, 1);
  ASSERT_EQ(lst.size(), 6);
  ASSERT_EQ(lst1.size(), 5);
}

TEST(list_test, constructor_struct_test) {
  typedef struct test {
    int i;
    char data;
  } test_t;
  test_t t1;
  t1.i = 0;
  t1.data = 'a';
  test_t t2;
  t2.i = 1;
  t2.data = 'b';
  s21::list<test> lst({t1, t2});
  ASSERT_EQ(lst.begin().ptr->value.i, 0);
  ASSERT_EQ(lst.size(), 2);
}

TEST(list_test, sort_test) {
  s21::list<int> lst({6, 5, 12, 10, 9, 1});
  lst.sort();
  int i = 0, res = 1, pr_v = 0;
  for (auto it = lst.begin(); i < (int)lst.size(); ++it) {
    if (pr_v > *it) {
      res = 0;
    }
    pr_v = *it;
    i++;
  }
  ASSERT_EQ(lst.begin().ptr->value, 1);
  ASSERT_EQ(lst.size(), 6);
  ASSERT_EQ(res, 1);
}

TEST(list_test, merge_test) {
  s21::list<int> lst({6, 5, 12, 10, 9, 1});
  s21::list<int> lst1({6, 5, 12, 10, 9, 1});
  lst.sort();
  lst1.sort();
  lst.merge(lst1);
  ASSERT_EQ(lst.begin().ptr->value, 1);
  ASSERT_EQ(lst.size(), 12);
  ASSERT_EQ(lst1.empty(), 1);
  ASSERT_EQ(lst1.size(), 0);
}

TEST(list_test, splice_test) {
  s21::list<int> lst({6, 5, 12, 10, 9, 1});
  s21::list<int> lst1({6, 5, 12, 10, 9, 1});
  auto it = lst1.begin();
  for (int i = 0; i < 3; ++it) {
    i++;
  }
  lst.splice(it, lst1);
  ASSERT_EQ(lst.begin().ptr->value, 6);
  ASSERT_EQ(lst.size(), 9);
  ASSERT_EQ(lst1.begin().ptr->value, 6);
  ASSERT_EQ(lst1.size(), 3);
}

TEST(list_test, reverse_test) {
  s21::list<int> lst({6, 5, 12, 10, 9, 1});
  lst.reverse();
  auto it = lst.begin();
  ASSERT_EQ(*it, 1);
  ++it;
  ASSERT_EQ(*it, 9);
  ++it;
  ASSERT_EQ(*it, 10);
  ++it;
  ASSERT_EQ(*it, 12);
  ++it;
  ASSERT_EQ(*it, 5);
  ++it;
  ASSERT_EQ(*it, 6);
  ASSERT_EQ(lst.size(), 6);
}

TEST(list_test, unique_test) {
  s21::list<int> lst({6, 6, 6, 5, 5, 10, 9, 9, 9, 9, 1, 1, 1});
  lst.unique();
  auto it = lst.begin();
  ASSERT_EQ(*it, 6);
  ++it;
  ASSERT_EQ(*it, 5);
  ++it;
  ASSERT_EQ(*it, 10);
  ++it;
  ASSERT_EQ(*it, 9);
  ++it;
  ASSERT_EQ(*it, 1);
  ASSERT_EQ(lst.size(), 5);
}

TEST(queue_test, list_constructor_default_test) {
  s21::queue<int> que;
  ASSERT_EQ(que.empty(), true);
  ASSERT_EQ(que.size(), 0);
}

TEST(queue_test, list_constructor_size_test) {
  s21::queue<int> que(5);
  ASSERT_EQ(que.empty(), false);
  ASSERT_EQ(que.size(), 5);
}

TEST(queue_test, list_constructor_initializer_test) {
  s21::queue<int> lst({1, 2, 3, 4});
  ASSERT_EQ(lst.size(), 4);
  ASSERT_EQ(lst.front(), 1);
  ASSERT_EQ(lst.back(), 4);
}

TEST(queue_test, list_constructor_copy_test) {
  s21::queue<int> lst({1, 2, 3, 4});
  s21::queue<int> lst1(lst);
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 4);
}

TEST(queue_test, list_constructor_move_test) {
  s21::queue<int> lst({1, 2, 3, 4});
  s21::queue<int> lst1(std::move(lst));
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(lst.empty(), true);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 4);
}

TEST(queue_test, operator_constructor_move_test) {
  s21::queue<int> lst({1, 2, 3, 4});
  s21::queue<int> lst1({1, 2, 4});
  lst1 = std::move(lst);
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(lst.empty(), false);
  ASSERT_EQ(lst.size(), 4);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 4);
  ASSERT_EQ(lst.front(), 1);
  ASSERT_EQ(lst.back(), 4);
}

TEST(queue_test, front_test) {
  s21::queue<int> lst({1, 2, 3, 4});
  ASSERT_EQ(lst.front(), 1);
}

TEST(queue_test, back_test) {
  s21::queue<int> lst({1, 2, 3, 4});
  ASSERT_EQ(lst.back(), 4);
}

TEST(queue_test, empty_test) {
  s21::queue<int> lst({1, 2, 3, 4});
  ASSERT_EQ(lst.empty(), false);
}

TEST(queue_test, size_test) {
  s21::queue<int> lst({1, 2, 3, 4});
  ASSERT_EQ(lst.size(), 4);
}

TEST(queue_test, push_test) {
  s21::queue<int> lst({1, 2, 3, 4});
  lst.push(10);
  ASSERT_EQ(lst.size(), 5);
  ASSERT_EQ(lst.empty(), false);
  ASSERT_EQ(lst.front(), 1);
  ASSERT_EQ(lst.back(), 10);
}

TEST(queue_test, pop_test) {
  s21::queue<int> lst({1, 2, 3, 4});
  lst.pop();
  ASSERT_EQ(lst.size(), 3);
  ASSERT_EQ(lst.empty(), false);
  ASSERT_EQ(lst.front(), 2);
  ASSERT_EQ(lst.back(), 4);
}

TEST(queue_test, swap_test) {
  s21::queue<int> lst({1, 2, 3, 4});
  s21::queue<int> lst1({6, 7, 8, 9, 10});
  lst.swap(lst1);
  ASSERT_EQ(lst.size(), 5);
  ASSERT_EQ(lst.empty(), false);
  ASSERT_EQ(lst.front(), 6);
  ASSERT_EQ(lst.back(), 10);
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(lst1.empty(), false);
  ASSERT_EQ(lst1.front(), 1);
  ASSERT_EQ(lst1.back(), 4);
}

TEST(stack_test, list_constructor_default_test) {
  s21::stack<int> que;
  ASSERT_EQ(que.empty(), true);
  ASSERT_EQ(que.size(), 0);
}

TEST(stack_test, list_constructor_size_test) {
  s21::stack<int> que(5);
  ASSERT_EQ(que.empty(), false);
  ASSERT_EQ(que.size(), 5);
}

TEST(stack_test, list_constructor_initializer_test) {
  s21::stack<int> lst({1, 2, 3, 4});
  ASSERT_EQ(lst.size(), 4);
  ASSERT_EQ(lst.top(), 1);
}

TEST(stack_test, list_constructor_copy_test) {
  s21::stack<int> lst({1, 2, 3, 4});
  s21::stack<int> lst1(lst);
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(lst1.top(), 1);
}

TEST(stack_test, list_constructor_move_test) {
  s21::stack<int> lst({1, 2, 3, 4});
  s21::stack<int> lst1(std::move(lst));
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(lst.empty(), true);
  ASSERT_EQ(lst1.top(), 1);
}

TEST(stack_test, operator_constructor_move_test) {
  s21::stack<int> lst({1, 2, 3, 4});
  s21::stack<int> lst1({1, 2});
  lst1 = std::move(lst);
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(lst.empty(), false);
  ASSERT_EQ(lst.size(), 4);
  ASSERT_EQ(lst1.top(), 1);
  ASSERT_EQ(lst.top(), 1);
}

TEST(stack_test, top_test) {
  s21::stack<int> lst({1, 2, 3, 4});
  ASSERT_EQ(lst.top(), 1);
}

TEST(stack_test, empty_test) {
  s21::stack<int> lst({1, 2, 3, 4});
  ASSERT_EQ(lst.empty(), false);
}

TEST(stack_test, size_test) {
  s21::stack<int> lst({1, 2, 3, 4});
  ASSERT_EQ(lst.size(), 4);
}

TEST(stack_test, push_test) {
  s21::stack<int> lst({1, 2, 3, 4});
  lst.push(10);
  ASSERT_EQ(lst.size(), 5);
  ASSERT_EQ(lst.empty(), false);
  ASSERT_EQ(lst.top(), 10);
}

TEST(stack_test, pop_test) {
  s21::stack<int> lst({1, 2, 3, 4});
  lst.pop();
  ASSERT_EQ(lst.size(), 3);
  ASSERT_EQ(lst.empty(), false);
  ASSERT_EQ(lst.top(), 2);
}

TEST(stack_test, swap_test) {
  s21::stack<int> lst({1, 2, 3, 4});
  s21::stack<int> lst1({6, 7, 8, 9, 10});
  lst.swap(lst1);
  ASSERT_EQ(lst.size(), 5);
  ASSERT_EQ(lst.empty(), false);
  ASSERT_EQ(lst.top(), 6);
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(lst1.empty(), false);
  ASSERT_EQ(lst1.top(), 1);
}

TEST(map_test, list_constructor_default_test) {
  s21::map<int, int> que;
  ASSERT_EQ(que.empty(), true);
  ASSERT_EQ(que.size(), 0);
}

TEST(map_test, list_constructor_initializer_test) {
  s21::map<int, int> lst({{4, 4}, {2, 2}, {3, 3}, {1, 1}});
  ASSERT_EQ(lst.size(), 4);
  ASSERT_EQ(lst.begin().ptr->value_.first, 1);
  ASSERT_EQ(lst.begin().ptr->value_.second, 1);
}

TEST(map_test, list_constructor_copy_test) {
  s21::map<int, int> lst1({{4, 4}, {2, 2}, {3, 3}, {1, 1}});
  s21::map<int, int> lst(lst1);
  ASSERT_EQ(lst.size(), 4);
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(lst.begin().ptr->value_.first, 1);
  ASSERT_EQ(lst.begin().ptr->value_.second, 1);
  ASSERT_EQ(lst1.begin().ptr->value_.first, 1);
  ASSERT_EQ(lst1.begin().ptr->value_.second, 1);
}

TEST(map_test, list_constructor_move_test) {
  s21::map<int, int> lst1({{4, 4}, {2, 2}, {3, 3}, {1, 1}});
  s21::map<int, int> lst(std::move(lst1));
  ASSERT_EQ(lst.size(), 4);
  ASSERT_EQ(lst1.size(), 0);
  ASSERT_EQ(lst.begin().ptr->value_.first, 1);
  ASSERT_EQ(lst.begin().ptr->value_.second, 1);
}

TEST(map_test, operator_constructor_move_test) {
  s21::map<int, int> lst1({{4, 4}, {2, 2}, {3, 3}, {1, 1}});
  s21::map<int, int> lst({{1, 2}, {4, 3}});
  lst = std::move(lst1);
  ASSERT_EQ(lst.size(), 4);
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(lst.begin().ptr->value_.first, 1);
  ASSERT_EQ(lst.begin().ptr->value_.second, 1);
  ASSERT_EQ(lst1.begin().ptr->value_.first, 1);
  ASSERT_EQ(lst1.begin().ptr->value_.second, 1);
}

TEST(map_test, begin_test) {
  s21::map<int, int> lst({{4, 4}, {2, 2}, {3, 3}, {1, 1}});
  ASSERT_EQ(lst.size(), 4);
  ASSERT_EQ(lst.begin().ptr->value_.first, 1);
  ASSERT_EQ(lst.begin().ptr->value_.second, 1);
}

TEST(map_test, end_test) {
  s21::map<int, int> lst({{4, 4}, {2, 2}, {3, 3}, {1, 1}});
  ASSERT_EQ(lst.size(), 4);
}

TEST(map_test, iterator_next_test) {
  s21::map<int, int> lst(
      {{15, 4}, {3, 3}, {5, 4}, {17, 3}, {23, 1}, {21, 2}, {1, 1}});
  auto it = lst.begin();
  ASSERT_EQ(it.ptr->value_.first, 1);
  ++it;
  ASSERT_EQ(it.ptr->value_.first, 3);
  ++it;
  ASSERT_EQ(it.ptr->value_.first, 5);
  ++it;
  ASSERT_EQ(it.ptr->value_.first, 15);
  ++it;
  ASSERT_EQ(it.ptr->value_.first, 17);
  ++it;
  ASSERT_EQ(it.ptr->value_.first, 21);
  ++it;
  ASSERT_EQ(it.ptr->value_.first, 23);
  ASSERT_EQ(lst.size(), 7);
}

TEST(map_test, iterator_back_test) {
  s21::map<int, int> lst(
      {{15, 4}, {3, 3}, {5, 4}, {17, 3}, {23, 1}, {21, 2}, {1, 1}});
  auto it = lst.begin();
  ASSERT_EQ(it.ptr->value_.first, 1);
  ++it;
  ASSERT_EQ(it.ptr->value_.first, 3);
  --it;
  ASSERT_EQ(it.ptr->value_.first, 1);
  ASSERT_EQ(lst.size(), 7);
}

TEST(map_test, iterator_eq_test) {
  s21::map<int, int> lst(
      {{15, 4}, {3, 3}, {5, 4}, {17, 3}, {23, 1}, {21, 2}, {1, 1}});
  auto it = lst.end();
  ASSERT_EQ(lst.size(), 7);
  ASSERT_EQ(it == lst.end(), true);
}

TEST(map_test, iterator_not_eq_test) {
  s21::map<int, int> lst(
      {{15, 4}, {3, 3}, {5, 4}, {17, 3}, {23, 1}, {21, 2}, {1, 1}});
  auto it = lst.end();
  ASSERT_EQ(lst.size(), 7);
  ASSERT_EQ(it != lst.begin(), true);
}

TEST(map_test, clear_test) {
  s21::map<int, int> lst(
      {{15, 4}, {3, 3}, {5, 4}, {17, 3}, {23, 1}, {21, 2}, {1, 1}});
  lst.clear();
  ASSERT_EQ(lst.empty(), true);
  ASSERT_EQ(lst.size(), 0);
}

TEST(map_test, insert_test) {
  s21::map<int, int> lst(
      {{15, 4}, {3, 3}, {5, 4}, {17, 3}, {23, 1}, {21, 2}, {1, 1}});
  auto it = lst.insert({4, 3});
  ASSERT_EQ(lst.size(), 8);
  ASSERT_EQ(it.second, true);
  ASSERT_EQ(it.first.ptr->value_.second, 3);
  ASSERT_EQ(it.first.ptr->value_.first, 4);
}

TEST(map_test, contains_test) {
  s21::map<int, int> lst(
      {{15, 4}, {3, 3}, {5, 4}, {17, 3}, {23, 1}, {21, 2}, {1, 1}});
  ASSERT_EQ(lst.contains(17), true);
  ASSERT_EQ(lst.contains(18), false);
  s21::map<int, int> lst1;
  ASSERT_EQ(lst1.contains(18), false);
}

TEST(map_test, insert_by_key_test) {
  s21::map<int, int> lst(
      {{15, 4}, {3, 3}, {5, 4}, {17, 3}, {23, 1}, {21, 2}, {1, 1}});
  auto test = lst.insert(17, 25);
  ASSERT_EQ(test.first.ptr->value_.first, 17);
  ASSERT_EQ(test.first.ptr->value_.second, 25);
  ASSERT_EQ(test.second, true);
  test = lst.insert(10, 25);
  ASSERT_EQ(test.second, false);
  ASSERT_EQ(test.first, nullptr);
}

TEST(map_test, insert_or_assign_test) {
  s21::map<int, int> lst(
      {{15, 4}, {3, 3}, {5, 4}, {17, 3}, {23, 1}, {21, 2}, {1, 1}});
  auto test = lst.insert_or_assign(17, 25);
  ASSERT_EQ(test.first.ptr->value_.first, 17);
  ASSERT_EQ(test.first.ptr->value_.second, 25);
  ASSERT_EQ(test.second, true);
  ASSERT_EQ(lst.size(), 7);
  test = lst.insert_or_assign(10, 25);
  ASSERT_EQ(test.first.ptr->value_.first, 10);
  ASSERT_EQ(test.first.ptr->value_.second, 25);
  ASSERT_EQ(test.second, true);
  ASSERT_EQ(lst.size(), 8);
}

TEST(map_test, erase_test) {
  s21::map<int, int> lst(
      {{15, 4}, {3, 3}, {5, 4}, {17, 3}, {23, 1}, {21, 2}, {1, 1}});
  auto it = lst.begin();
  lst.erase(it);
  ASSERT_EQ(lst.size(), 6);
}

TEST(map_test, swap_test) {
  s21::map<int, int> lst(
      {{15, 4}, {3, 3}, {5, 4}, {17, 3}, {23, 1}, {21, 2}, {1, 1}});
  s21::map<int, int> lst1({{1, 1}, {2, 2}, {3, 3}});
  lst.swap(lst1);
  ASSERT_EQ(lst.size(), 3);
  ASSERT_EQ(lst1.size(), 7);
}

TEST(map_test, merge_test) {
  s21::map<int, int> lst(
      {{15, 4}, {3, 3}, {5, 4}, {17, 3}, {23, 1}, {21, 2}, {1, 1}});
  s21::map<int, int> lst1({{1, 2}, {2, 2}, {30, 30}});
  lst.merge(lst1);
  ASSERT_EQ(lst.size(), 9);
  ASSERT_EQ(lst1.size(), 3);
  ASSERT_EQ(lst[1], 1);
}

TEST(map_test, max_size_test) {
  s21::map<int, int> lst(
      {{15, 4}, {3, 3}, {5, 4}, {17, 3}, {23, 1}, {21, 2}, {1, 1}});
  ASSERT_EQ(lst.max_size(), 576460752303423487);
}

TEST(map_test, at_test) {
  s21::map<int, int> lst(
      {{15, 4}, {3, 3}, {5, 4}, {17, 3}, {23, 1}, {21, 2}, {1, 1}});
  lst.at(1) = 10;
  ASSERT_EQ(lst.begin().ptr->value_.second, 10);
}

TEST(map_test, operator_test) {
  s21::map<int, int> lst(
      {{15, 4}, {3, 3}, {5, 4}, {17, 3}, {23, 1}, {21, 2}, {1, 1}});
  lst[10] = 52;
  ASSERT_EQ(lst.at(10), 52);
}

TEST(set_test, set_constructor_default_test) {
  s21::set<int> set;
  ASSERT_EQ(set.empty(), true);
  ASSERT_EQ(set.size(), 0);
}

TEST(set_test, begin_test) {
  s21::set<int> set({4, 14, 12, 2, 13, 15, 1});
  ASSERT_EQ(set.size(), 7);
  ASSERT_EQ(set.begin().ptr->value_, 1);
}

TEST(set_test, end_test) {
  s21::set<int> set({4, 14, 12, 2, 13, 15, 1});
  ASSERT_EQ(set.size(), 7);
}

TEST(set_test, set_constructor_initializer_test) {
  s21::set<int> set({4, 14, 12, 2, 13, 15, 1});
  ASSERT_EQ(set.size(), 7);
}

TEST(set_test, list_constructor_copy_test) {
  s21::set<int> set({4, 14, 12, 2, 13, 15, 1});
  s21::set<int> lst1(set);
  ASSERT_EQ(set.size(), 7);
  ASSERT_EQ(lst1.size(), 7);
  ASSERT_EQ(set.begin().ptr->value_, 1);
  ASSERT_EQ(lst1.begin().ptr->value_, 1);
}

TEST(set_test, list_constructor_move_test) {
  s21::set<int> lst1({4, 14, 12, 2, 13, 15, 1});
  s21::set<int> lst(std::move(lst1));
  ASSERT_EQ(lst.size(), 7);
  ASSERT_EQ(lst1.size(), 0);
  ASSERT_EQ(lst.begin().ptr->value_, 1);
}

TEST(set_test, operator_constructor_move_test) {
  s21::set<int> lst1({4, 14, 12, 2, 13, 15, 1});
  s21::set<int> lst({1, 2, 4, 3});
  lst = std::move(lst1);
  ASSERT_EQ(lst.size(), 7);
  ASSERT_EQ(lst1.size(), 7);
  ASSERT_EQ(lst.begin().ptr->value_, 1);
  ASSERT_EQ(lst1.begin().ptr->value_, 1);
}

TEST(set_test, iterator_next_test) {
  s21::set<int> lst1({4, 14, 12, 2, 13, 15, 1});
  auto it = lst1.begin();
  ASSERT_EQ(it.ptr->value_, 1);
  ++it;
  ASSERT_EQ(it.ptr->value_, 2);
  ++it;
  ASSERT_EQ(it.ptr->value_, 4);
  ++it;
  ASSERT_EQ(it.ptr->value_, 12);
  ++it;
  ASSERT_EQ(it.ptr->value_, 13);
  ++it;
  ASSERT_EQ(it.ptr->value_, 14);
  ++it;
  ASSERT_EQ(it.ptr->value_, 15);
  ASSERT_EQ(lst1.size(), 7);
}

TEST(set_test, iterator_back_test) {
  s21::set<int> lst1({4, 14, 12, 2, 13, 15, 1});
  auto it = lst1.begin();
  ASSERT_EQ(it.ptr->value_, 1);
  ++it;
  ASSERT_EQ(it.ptr->value_, 2);
  --it;
  ASSERT_EQ(it.ptr->value_, 1);
  ASSERT_EQ(lst1.size(), 7);
}

TEST(set_test, iterator_eq_test) {
  s21::set<int> lst({4, 14, 12, 2, 13, 15, 1});
  auto it = lst.end();
  ASSERT_EQ(lst.size(), 7);
  ASSERT_EQ(it == lst.end(), true);
}

TEST(set_test, iterator_not_eq_test) {
  s21::set<int> lst({4, 14, 12, 2, 13, 15, 1});
  auto it = lst.end();
  ASSERT_EQ(lst.size(), 7);
  ASSERT_EQ(it != lst.begin(), true);
}

TEST(set_test, size_test) {
  s21::set<int> lst({4, 14, 12, 2, 13, 15, 1});
  ASSERT_EQ(lst.size(), 7);
}

TEST(set_test, empty_test) {
  s21::set<int> lst({4, 14, 12, 2, 13, 15, 1});
  ASSERT_EQ(lst.empty(), false);
  s21::set<int> lst1;
  ASSERT_EQ(lst1.empty(), true);
}

TEST(set_test, clear_test) {
  s21::set<int> lst({4, 14, 12, 2, 13, 15, 1});
  lst.clear();
  ASSERT_EQ(lst.size(), 0);
  ASSERT_EQ(lst.empty(), true);
}

TEST(set_test, insert_test) {
  s21::set<int> lst({4, 14, 12, 2, 13, 15, 1});
  auto it = lst.insert(16);
  ASSERT_EQ(lst.size(), 8);
  ASSERT_EQ(it.second, true);
  ASSERT_EQ(it.first.ptr->value_, 16);
}

TEST(set_test, erase_test) {
  s21::set<int> lst({4, 14, 12, 2, 13, 15, 1});
  lst.erase(lst.begin());
  ASSERT_EQ(lst.size(), 6);
  ASSERT_EQ(lst.begin().ptr->value_, 2);
}

TEST(set_test, swap_test) {
  s21::set<int> lst({4, 14, 12, 2, 13, 15, 1});
  s21::set<int> lst1({1, 2, 3});
  lst.swap(lst1);
  ASSERT_EQ(lst.size(), 3);
  ASSERT_EQ(lst1.size(), 7);
}

TEST(set_test, merge_test) {
  s21::set<int> lst({4, 14, 12, 2, 13, 15, 1});
  s21::set<int> lst1({1, 2, 30});
  lst.merge(lst1);
  ASSERT_EQ(lst.size(), 8);
  ASSERT_EQ(lst1.size(), 3);
}

TEST(set_test, find_test) {
  s21::set<int> lst({4, 14, 12, 2, 13, 15, 1});
  auto it = lst.find(14);
  ASSERT_EQ(it.ptr->value_, 14);
}

TEST(set_test, contains_test) {
  s21::set<int> lst({4, 14, 12, 2, 13, 15, 1});
  ASSERT_EQ(lst.contains(14), true);
}

TEST(set_test, max_size_test) {
  s21::set<int> lst({4, 14, 12, 2, 13, 15, 1});
  ASSERT_EQ(lst.max_size(), 576460752303423487);
}

TEST(vector_test, check_initilizer_list) {
  s21::vector<int> vector_i = {1, 2, 3, 4, 5};
  s21::vector<char> vector_c = {'a', 'b', 'c', 'd', 'e'};
  s21::vector<double> vector_d = {1.123, 2.234, 4.343, 0.01, 0};
  int res_arr_i[5] = {1, 2, 3, 4, 5};
  char res_arr_c[5] = {'a', 'b', 'c', 'd', 'e'};
  double res_arr_d[5] = {1.123, 2.234, 4.343, 0.01, 0};
  for (int i = 0; i < (int)vector_i.size(); i++) {
    ASSERT_EQ(vector_i[i], res_arr_i[i]);
    ASSERT_EQ(vector_c[i], res_arr_c[i]);
    ASSERT_EQ(vector_d[i], res_arr_d[i]);
  }
}

TEST(vector_test, check_initilizer_list_2) {
  s21::vector<int> vector_i = {1, 2, 3, 4, 5};
  s21::vector<char> vector_c = {'a', 'b', 'c', 'd', 'e'};
  s21::vector<double> vector_d = {1.123, 2.234, 4.343, 0.01, 0};
  s21::vector<int> vector_i_2(5);
  s21::vector<char> vector_c_2(5);
  s21::vector<double> vector_d_2(5);
  for (int i = 0; i < (int)vector_i_2.size(); i++) {
    vector_i_2.at(i) = vector_i[i];
    vector_c_2.at(i) = vector_c[i];
    vector_d_2.at(i) = vector_d[i];
  }
  for (int i = 0; i < (int)vector_i.size(); i++) {
    ASSERT_EQ(vector_i[i], vector_i_2[i]);
    ASSERT_EQ(vector_c[i], vector_c_2[i]);
    ASSERT_EQ(vector_d[i], vector_d_2[i]);
  }
}

TEST(vector_test, check_initilizer_list_3) {
  s21::vector<int> vector_i = {1, 2, 3, 4, 5};
  s21::vector<char> vector_c = {'a', 'b', 'c', 'd', 'e'};
  s21::vector<double> vector_d = {1.123, 2.234, 4.343, 0.01, 0};
  s21::vector<int> vector_i_2(5);
  s21::vector<char> vector_c_2(5);
  s21::vector<double> vector_d_2(5);
  vector_i_2 = vector_i;
  vector_c_2 = vector_c;
  vector_d_2 = vector_d;
  for (int i = 0; i < (int)vector_i.size(); i++) {
    ASSERT_EQ(vector_i[i], vector_i_2[i]);
    ASSERT_EQ(vector_c[i], vector_c_2[i]);
    ASSERT_EQ(vector_d[i], vector_d_2[i]);
  }
}

TEST(vector_test, check_initilizer_list_4) {
  s21::vector<int> vector_i = {1, 2, 3, 4, 5};
  s21::vector<char> vector_c = {'a', 'b', 'c', 'd', 'e'};
  s21::vector<double> vector_d = {1.123, 2.234, 4.343, 0.01, 0};
  s21::vector<int> vector_i_2(vector_i);
  s21::vector<char> vector_c_2(vector_c);
  s21::vector<double> vector_d_2(vector_d);
  vector_i = vector_i_2;
  vector_c = vector_c_2;
  vector_d = vector_d_2;
  for (int i = 0; i < (int)vector_i.size(); i++) {
    ASSERT_EQ(vector_i[i], vector_i_2[i]);
    ASSERT_EQ(vector_c[i], vector_c_2[i]);
    ASSERT_EQ(vector_d[i], vector_d_2[i]);
  }
}

TEST(vector_test, check_operator_appropriation) {
  s21::vector<int> vector_i = {1, 2, 3, 4, 5};
  s21::vector<char> vector_c = {'a', 'b', 'c', 'd', 'e'};
  s21::vector<double> vector_d = {1.123, 2.234, 4.343, 0.01, 0};
  s21::vector<int> vector_i_2(vector_i);
  s21::vector<char> vector_c_2(vector_c);
  s21::vector<double> vector_d_2(vector_d);
  vector_i = vector_i_2;
  vector_c = vector_c_2;
  vector_d = vector_d_2;
  for (int i = 0; i < (int)vector_i.size(); i++) {
    ASSERT_EQ(vector_i[i], vector_i_2[i]);
    ASSERT_EQ(vector_c[i], vector_c_2[i]);
    ASSERT_EQ(vector_d[i], vector_d_2[i]);
  }
}

TEST(vector_test, check_operator_equal) {
  s21::vector<int> vector_i = {1, 2, 3, 4, 5};
  s21::vector<char> vector_c = {'a', 'b', 'c', 'd', 'e'};
  s21::vector<double> vector_d = {1.123, 2.234, 4.343, 0.01, 0};
  s21::vector<int> vector_i_2(vector_i);
  s21::vector<char> vector_c_2(vector_c);
  s21::vector<double> vector_d_2(vector_d);
  bool res_i = vector_i == vector_i_2;
  bool res_c = vector_c == vector_c_2;
  bool res_d = vector_d == vector_d_2;
  ASSERT_EQ(res_i, 1);
  ASSERT_EQ(res_c, 1);
  ASSERT_EQ(res_d, 1);
  vector_i.push_back(6);
  vector_c.push_back('f');
  vector_d.push_back(5.12);
  res_i = vector_i == vector_i_2;
  res_c = vector_c == vector_c_2;
  res_d = vector_d == vector_d_2;
  ASSERT_EQ(res_i, 0);
  ASSERT_EQ(res_c, 0);
  ASSERT_EQ(res_d, 0);
}

TEST(vector_test, check_operator_not_equal) {
  s21::vector<int> vector_i = {1, 2, 3, 4, 5};
  s21::vector<char> vector_c = {'a', 'b', 'c', 'd', 'e'};
  s21::vector<double> vector_d = {1.123, 2.234, 4.343, 0.01, 0};
  s21::vector<int> vector_i_2(vector_i);
  s21::vector<char> vector_c_2(vector_c);
  s21::vector<double> vector_d_2(vector_d);
  bool res_i = vector_i != vector_i_2;
  bool res_c = vector_c != vector_c_2;
  bool res_d = vector_d != vector_d_2;
  ASSERT_EQ(res_i, 0);
  ASSERT_EQ(res_c, 0);
  ASSERT_EQ(res_d, 0);
  vector_i.push_back(6);
  vector_c.push_back('f');
  vector_d.push_back(5.12);
  res_i = vector_i != vector_i_2;
  res_c = vector_c != vector_c_2;
  res_d = vector_d != vector_d_2;
  ASSERT_EQ(res_i, 1);
  ASSERT_EQ(res_c, 1);
  ASSERT_EQ(res_d, 1);
}

TEST(vector_test, check_size) {
  s21::vector<int> vector_i = {1, 2, 3, 4, 5};
  s21::vector<char> vector_c = {'a', 'b', 'c', 'd', 'e',
                                'f', 'g', 'h', 'i', 'j'};
  s21::vector<double> vector_d = {};
  ASSERT_EQ(vector_i.size(), 5);
  ASSERT_EQ(vector_c.size(), 10);
  ASSERT_EQ(vector_d.size(), 0);
}

TEST(vector_test, check_capicity) {
  s21::vector<int> vector_i = {1, 2, 3, 4, 5};
  s21::vector<char> vector_c = {'a', 'b', 'c', 'd', 'e',
                                'f', 'g', 'h', 'i', 'j'};
  s21::vector<double> vector_d = {};
  ASSERT_EQ(vector_i.capacity(), 5);
  ASSERT_EQ(vector_c.capacity(), 10);
  ASSERT_EQ(vector_d.capacity(), 0);
}

TEST(vector_test, check_max_size) {
  s21::vector<int> vector_i = {1, 2, 3, 4, 5};
  s21::vector<char> vector_c = {'a', 'b', 'c', 'd', 'e',
                                'f', 'g', 'h', 'i', 'j'};
  s21::vector<double> vector_d = {};
  ASSERT_EQ(vector_i.max_size(), 768614336404564650);
  ASSERT_EQ(vector_c.max_size(), 768614336404564650);
  ASSERT_EQ(vector_d.max_size(), 768614336404564650);
}

TEST(vector_test, check_clear) {
  s21::vector<int> vector_i = {1, 2, 3, 4, 5};
  s21::vector<char> vector_c = {'a', 'b', 'c', 'd', 'e',
                                'f', 'g', 'h', 'i', 'j'};
  s21::vector<double> vector_d = {};
  vector_i.clear();
  vector_c.clear();
  vector_d.clear();
  ASSERT_EQ(vector_i.size(), 0);
  ASSERT_EQ(vector_i.capacity(), 0);
  ASSERT_EQ(vector_i.data(), nullptr);
  ASSERT_EQ(vector_c.size(), 0);
  ASSERT_EQ(vector_c.capacity(), 0);
  ASSERT_EQ(vector_c.data(), nullptr);
  ASSERT_EQ(vector_d.size(), 0);
  ASSERT_EQ(vector_d.capacity(), 0);
  ASSERT_EQ(vector_d.data(), nullptr);
}

TEST(vector_test, check_push_back) {
  s21::vector<int> vector_i = {0, 1, 2, 3, 4};
  s21::vector<char> vector_c = {'a', 'a', 'a', 'a', 'a'};
  s21::vector<double> vector_d = {0, 1, 2, 3, 4};
  s21::vector<int> vector_i_2;
  s21::vector<char> vector_c_2;
  s21::vector<double> vector_d_2;
  for (int i = 0; i < 5; i++) {
    vector_i_2.push_back(i);
    vector_c_2.push_back('a');
    vector_d_2.push_back(i);
  }
  for (int i = 0; i < (int)vector_i.size(); i++) {
    ASSERT_EQ(vector_i[i], vector_i_2[i]);
    ASSERT_EQ(vector_c[i], vector_c_2[i]);
    ASSERT_EQ(vector_d[i], vector_d_2[i]);
  }
}

TEST(vector_test, check_pop_back) {
  s21::vector<int> vector_i = {0, 1, 2, 3, 4};
  s21::vector<char> vector_c = {'a', 'a', 'a', 'a', 'a'};
  s21::vector<double> vector_d = {0, 1, 2, 3, 4};
  s21::vector<int> vector_i_2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::vector<char> vector_c_2 = {'a', 'a', 'a', 'a', 'a',
                                  'a', 'a', 'a', 'a', 'a'};
  s21::vector<double> vector_d_2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i = 0; i < 5; i++) {
    vector_i_2.pop_back();
    vector_c_2.pop_back();
    vector_d_2.pop_back();
  }
  for (int i = 0; i < (int)vector_i.size(); i++) {
    ASSERT_EQ(vector_i[i], vector_i_2[i]);
    ASSERT_EQ(vector_c[i], vector_c_2[i]);
    ASSERT_EQ(vector_d[i], vector_d_2[i]);
  }
}

TEST(vector_test, check_shrink_to_fit) {
  s21::vector<int> vector_i = {0, 1, 2, 3, 4};
  s21::vector<char> vector_c = {'a', 'a', 'a', 'a', 'a'};
  s21::vector<double> vector_d = {0, 1, 2, 3, 4};
  s21::vector<int> vector_i_2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::vector<char> vector_c_2 = {'a', 'a', 'a', 'a', 'a',
                                  'a', 'a', 'a', 'a', 'a'};
  s21::vector<double> vector_d_2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector_i_2.push_back(1);
  vector_c_2.push_back('1');
  vector_d_2.push_back(1);
  ASSERT_EQ(vector_i_2.capacity(), 20);
  ASSERT_EQ(vector_c_2.capacity(), 20);
  ASSERT_EQ(vector_d_2.capacity(), 20);
  vector_i_2.shrink_to_fit();
  vector_c_2.shrink_to_fit();
  vector_d_2.shrink_to_fit();
  ASSERT_EQ(vector_i_2.capacity(), 11);
  ASSERT_EQ(vector_c_2.capacity(), 11);
  ASSERT_EQ(vector_d_2.capacity(), 11);
}

TEST(vector_test, check_resize) {
  s21::vector<int> vector_i = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::vector<char> vector_c = {'a', 'a', 'a', 'a', 'a',
                                'a', 'a', 'a', 'a', 'a'};
  s21::vector<double> vector_d = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::vector<int> vector_i_2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::vector<char> vector_c_2 = {'a', 'a', 'a', 'a', 'a',
                                  'a', 'a', 'a', 'a', 'a'};
  s21::vector<double> vector_d_2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector_i_2.resize(15);
  vector_c_2.resize(15);
  vector_d_2.resize(15);
  for (int i = 0; i < (int)vector_i_2.size(); i++) {
    if (i <= 9) {
      ASSERT_EQ(vector_i[i], vector_i_2[i]);
      ASSERT_EQ(vector_c[i], vector_c_2[i]);
      ASSERT_EQ(vector_d[i], vector_d_2[i]);
    } else {
      ASSERT_EQ(0, vector_i_2[i]);
      ASSERT_EQ('\0', vector_c_2[i]);
      ASSERT_EQ(0, vector_d_2[i]);
    }
  }
}

TEST(vector_test, check_resize_2) {
  s21::vector<int> vector_i = {0, 1, 2, 3, 4};
  s21::vector<char> vector_c = {'a', 'a', 'a', 'a', 'a'};
  s21::vector<double> vector_d = {0, 1, 2, 3, 4};
  s21::vector<int> vector_i_2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::vector<char> vector_c_2 = {'a', 'a', 'a', 'a', 'a',
                                  'a', 'a', 'a', 'a', 'a'};
  s21::vector<double> vector_d_2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector_i_2.resize(5);
  vector_c_2.resize(5);
  vector_d_2.resize(5);
  for (int i = 0; i < (int)vector_i_2.size(); i++) {
    ASSERT_EQ(vector_i[i], vector_i_2[i]);
    ASSERT_EQ(vector_c[i], vector_c_2[i]);
    ASSERT_EQ(vector_d[i], vector_d_2[i]);
  }
}

TEST(vector_test, check_reserve) {
  s21::vector<int> vector_i = {0, 1, 2, 3, 4};
  s21::vector<char> vector_c = {'a', 'a', 'a', 'a', 'a'};
  s21::vector<double> vector_d = {0, 1, 2, 3, 4};
  s21::vector<int> vector_i_2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::vector<char> vector_c_2 = {'a', 'a', 'a', 'a', 'a',
                                  'a', 'a', 'a', 'a', 'a'};
  s21::vector<double> vector_d_2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector_i_2.reserve(5);
  vector_c_2.reserve(5);
  vector_d_2.reserve(5);
  for (int i = 0; i < (int)vector_i_2.size(); i++) {
    ASSERT_EQ(vector_i[i], vector_i_2[i]);
    ASSERT_EQ(vector_c[i], vector_c_2[i]);
    ASSERT_EQ(vector_d[i], vector_d_2[i]);
  }
  ASSERT_EQ(5, vector_i_2.size());
  ASSERT_EQ(5, vector_c_2.size());
  ASSERT_EQ(5, vector_d_2.size());
  ASSERT_EQ(5, vector_i_2.capacity());
  ASSERT_EQ(5, vector_c_2.capacity());
  ASSERT_EQ(5, vector_d_2.capacity());
}

TEST(vector_test, check_assign) {
  s21::vector<int> vector_i = {0, 1, 2, 3, 4};
  s21::vector<char> vector_c = {'a', 'a', 'a', 'a', 'a'};
  s21::vector<double> vector_d = {0, 1, 2, 3, 4};
  s21::vector<int> vector_i_2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::vector<char> vector_c_2 = {'a', 'a', 'a', 'a', 'a',
                                  'a', 'a', 'a', 'a', 'a'};
  s21::vector<double> vector_d_2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector_i_2.assign(5, 10);
  vector_c_2.assign(5, 'a');
  vector_d_2.assign(5, 10);
  for (int i = 0; i < (int)vector_i_2.size(); i++) {
    ASSERT_EQ(10, vector_i_2[i]);
    ASSERT_EQ('a', vector_c_2[i]);
    ASSERT_EQ(10, vector_d_2[i]);
  }
  ASSERT_EQ(5, vector_i_2.size());
  ASSERT_EQ(5, vector_c_2.size());
  ASSERT_EQ(5, vector_d_2.size());
  ASSERT_EQ(5, vector_i_2.capacity());
  ASSERT_EQ(5, vector_c_2.capacity());
  ASSERT_EQ(5, vector_d_2.capacity());
}

TEST(vector_test, check_erase) {
  s21::vector<int> vector_i = {0, 1, 2, 3, 4};
  s21::vector<char> vector_c = {'a', 'a', 'a', 'a', 'a'};
  s21::vector<double> vector_d = {0, 1, 2, 3, 4};
  vector_i.erase(vector_i.end());
  vector_c.erase(vector_c.end());
  vector_d.erase(vector_d.end());
  for (int i = 0; i < (int)vector_i.size(); i++) {
    ASSERT_EQ(vector_i[i], vector_i[i]);
    ASSERT_EQ(vector_c[i], vector_c[i]);
    ASSERT_EQ(vector_d[i], vector_d[i]);
  }
  ASSERT_EQ(4, vector_i.size());
  ASSERT_EQ(4, vector_c.size());
  ASSERT_EQ(4, vector_d.size());
}

TEST(vector_test, check_swap) {
  s21::vector<int> vector_i = {0, 1, 2, 3, 4};
  s21::vector<char> vector_c = {'a', 'a', 'a', 'a', 'a'};
  s21::vector<double> vector_d = {0, 1, 2, 3, 4};
  s21::vector<int> vector_i_2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::vector<char> vector_c_2 = {'a', 'a', 'a', 'a', 'a',
                                  'a', 'a', 'a', 'a', 'a'};
  s21::vector<double> vector_d_2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector_i_2.swap(vector_i);
  vector_c_2.swap(vector_c);
  vector_d_2.swap(vector_d);
  for (int i = 0; i < (int)vector_i_2.size(); i++) {
    ASSERT_EQ(i, vector_i_2[i]);
    ASSERT_EQ('a', vector_c_2[i]);
    ASSERT_EQ(i, vector_d_2[i]);
  }
  for (int i = 0; i < (int)vector_i.size(); i++) {
    ASSERT_EQ(i, vector_i[i]);
    ASSERT_EQ('a', vector_c[i]);
    ASSERT_EQ(i, vector_d[i]);
  }
  ASSERT_EQ(5, vector_i_2.size());
  ASSERT_EQ(5, vector_c_2.size());
  ASSERT_EQ(5, vector_d_2.size());
  ASSERT_EQ(10, vector_i.size());
  ASSERT_EQ(10, vector_c.size());
  ASSERT_EQ(10, vector_d.size());
  ASSERT_EQ(5, vector_i_2.capacity());
  ASSERT_EQ(5, vector_c_2.capacity());
  ASSERT_EQ(5, vector_d_2.capacity());
  ASSERT_EQ(10, vector_i.capacity());
  ASSERT_EQ(10, vector_c.capacity());
  ASSERT_EQ(10, vector_d.capacity());
}

TEST(array_test, array_constructor_default_test) {
  s21::array<int> array;
  ASSERT_EQ(array.empty(), true);
  ASSERT_EQ(array.size(), 0);
}

TEST(array_test, array_constructor_initializer_test) {
  s21::array<int> array({4, 2, 3, 1});
  ASSERT_EQ(array.size(), 4);
}

TEST(array_test, array_constructor_copy_test) {
  s21::array<int> lst1({4, 2, 3, 1});
  s21::array<int> lst(lst1);
  ASSERT_EQ(lst.size(), 4);
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(*(lst.begin()), 4);
  ASSERT_EQ(*(lst.end()), 1);
}

TEST(array_test, array_constructor_move_test) {
  s21::array<int> lst1({4, 2, 3, 1});
  s21::array<int> lst(std::move(lst1));
  ASSERT_EQ(lst.size(), 4);
  ASSERT_EQ(lst1.size(), 0);
  ASSERT_EQ(*(lst.begin()), 4);
  ASSERT_EQ(*(lst.end()), 1);
}

TEST(array_test, array_constructor_operator_test) {
  s21::array<int> lst1({4, 2, 3, 1});
  s21::array<int> lst({2, 1});
  lst = std::move(lst1);
  ASSERT_EQ(lst.size(), 4);
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(*(lst.begin()), 4);
  ASSERT_EQ(*(lst.end()), 1);
}

TEST(array_test, array_begin_test) {
  s21::array<int> lst1({4, 2, 3, 1});
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(*(lst1.begin()), 4);
}

TEST(array_test, array_end_test) {
  s21::array<int> lst1({4, 2, 3, 1});
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(*(lst1.end()), 1);
}

TEST(array_test, at_test) {
  s21::array<int> lst({4, 2, 3, 1});
  lst.at(0) = 3;
  ASSERT_EQ(*(lst.begin()), 3);
}

TEST(array_test, at_operator_test) {
  s21::array<int> lst({4, 2, 3, 1});
  lst[0] = 3;
  ASSERT_EQ(*(lst.begin()), 3);
}

TEST(array_test, front_test) {
  s21::array<int> lst({4, 2, 3, 1});
  ASSERT_EQ(lst.front(), 4);
}

TEST(array_test, back_test) {
  s21::array<int> lst({4, 2, 3, 1});
  ASSERT_EQ(lst.back(), 1);
}

TEST(array_test, data_test) {
  s21::array<int> lst({4, 2, 3, 1});
  *(lst.data()) = 3;
  ASSERT_EQ(lst.front(), 3);
}

TEST(array_test, empty_test) {
  s21::array<int> lst({4, 2, 3, 1});
  ASSERT_EQ(lst.empty(), false);
}

TEST(array_test, size_test) {
  s21::array<int> lst({4, 2, 3, 1});
  ASSERT_EQ(lst.size(), 4);
}

TEST(array_test, max_size_test) {
  s21::array<int> lst({4, 2, 3, 1});
  ASSERT_EQ(lst.max_size(), 4611686018427387903);
}

TEST(array_test, swap_test) {
  s21::array<int> lst({4, 2, 3, 1});
  s21::array<int> lst1({10, 20, 30, 11, 15});
  lst.swap(lst1);
  ASSERT_EQ(lst.size(), 5);
  ASSERT_EQ(lst1.size(), 4);
  ASSERT_EQ(lst.front(), 10);
  ASSERT_EQ(lst1.front(), 4);
  ASSERT_EQ(lst.back(), 15);
  ASSERT_EQ(lst1.back(), 1);
}

TEST(array_test, fill_test) {
  s21::array<int> lst({4, 2, 3, 1});
  lst.fill(10);
  ASSERT_EQ(lst.size(), 4);
  ASSERT_EQ(lst[0], 10);
  ASSERT_EQ(lst[1], 10);
  ASSERT_EQ(lst[2], 10);
  ASSERT_EQ(lst[3], 10);
}

TEST(multiset_test, multiset_constructor_default_test) {
  s21::multiset<int> set;
  ASSERT_EQ(set.empty(), true);
  ASSERT_EQ(set.size(), 0);
}

TEST(multiset_test, begin_test) {
  s21::multiset<int> set({4, 4, 12, 2, 2, 2, 1});
  ASSERT_EQ(set.size(), 7);
  ASSERT_EQ(set.begin().ptr->value_, 1);
}

TEST(multiset_test, multiset_constructor_initializer_test) {
  s21::multiset<int> set({4, 4, 12, 2, 2, 2, 1});
  ASSERT_EQ(set.size(), 7);
}

TEST(multiset_test, multiset_constructor_copy_test) {
  s21::multiset<int> set({4, 4, 12, 2, 2, 2, 1});
  s21::multiset<int> lst1(set);
  ASSERT_EQ(set.size(), 7);
  ASSERT_EQ(lst1.size(), 7);
  ASSERT_EQ(set.begin().ptr->value_, 1);
  ASSERT_EQ(lst1.begin().ptr->value_, 1);
}

TEST(multiset_test, multiset_constructor_move_test) {
  s21::multiset<int> lst1({4, 4, 12, 2, 2, 2, 1});
  s21::multiset<int> lst(std::move(lst1));
  ASSERT_EQ(lst.size(), 7);
  ASSERT_EQ(lst1.size(), 0);
  ASSERT_EQ(lst.begin().ptr->value_, 1);
}

TEST(multiset_test, operator_constructor_move_test) {
  s21::multiset<int> lst1({4, 4, 12, 2, 2, 2, 1});
  s21::multiset<int> lst({1, 2, 4, 3});
  lst = std::move(lst1);
  ASSERT_EQ(lst.size(), 7);
  ASSERT_EQ(lst1.size(), 7);
  ASSERT_EQ(lst.begin().ptr->value_, 1);
  ASSERT_EQ(lst1.begin().ptr->value_, 1);
}

TEST(multiset_test, iterator_next_test) {
  s21::multiset<int> lst1({4, 4, 12, 2, 2, 2, 1, 4});
  auto it = lst1.begin();
  ASSERT_EQ(it.ptr->value_, 1);
  ++it;
  ASSERT_EQ(it.ptr->value_, 2);
  ++it;
  ASSERT_EQ(it.ptr->value_, 2);
  ++it;
  ASSERT_EQ(it.ptr->value_, 2);
  ++it;
  ASSERT_EQ(it.ptr->value_, 4);
  ++it;
  ASSERT_EQ(it.ptr->value_, 4);
  ++it;
  ASSERT_EQ(it.ptr->value_, 4);
  ++it;
  ASSERT_EQ(it.ptr->value_, 12);
  ASSERT_EQ(lst1.size(), 8);
}

TEST(multiset_test, iterator_back_test) {
  s21::multiset<int> lst1({4, 4, 12, 2, 2, 2, 1});
  auto it = lst1.begin();
  ASSERT_EQ(it.ptr->value_, 1);
  ++it;
  ASSERT_EQ(it.ptr->value_, 2);
  --it;
  ASSERT_EQ(it.ptr->value_, 1);
  ASSERT_EQ(lst1.size(), 7);
}

TEST(multiset_test, iterator_eq_test) {
  s21::multiset<int> lst1({4, 4, 12, 2, 2, 2, 1});
  auto it = lst1.end();
  ASSERT_EQ(lst1.size(), 7);
  ASSERT_EQ(it == lst1.end(), true);
}

TEST(multiset_test, iterator_not_eq_test) {
  s21::multiset<int> lst1({4, 4, 12, 2, 2, 2, 1});
  auto it = lst1.end();
  ASSERT_EQ(lst1.size(), 7);
  ASSERT_EQ(it != lst1.begin(), true);
}

TEST(multiset_test, size_test) {
  s21::multiset<int> lst({4, 4, 12, 2, 2, 2, 1});
  ASSERT_EQ(lst.size(), 7);
}

TEST(multiset_test, empty_test) {
  s21::multiset<int> lst({4, 4, 12, 2, 2, 2, 1});
  ASSERT_EQ(lst.empty(), false);
  s21::set<int> lst1;
  ASSERT_EQ(lst1.empty(), true);
}

TEST(multiset_test, max_size_test) {
  s21::multiset<int> lst({4, 4, 12, 2, 2, 2, 1});
  ASSERT_EQ(lst.max_size(), 576460752303423487);
}

TEST(multiset_test, clear_test) {
  s21::multiset<int> lst({4, 4, 12, 2, 2, 2, 1});
  lst.clear();
  ASSERT_EQ(lst.size(), 0);
  ASSERT_EQ(lst.empty(), true);
}

TEST(multiset_test, insert_test) {
  s21::multiset<int> lst({4, 4, 12, 2, 2, 2, 1});
  auto it = lst.insert(10);
  ASSERT_EQ(lst.size(), 8);
  ASSERT_EQ(it.ptr->value_, 10);
}

TEST(multiset_test, erase_test) {
  s21::multiset<int> lst({4, 4, 12, 2, 2, 2, 1});
  lst.erase(lst.begin());
  ASSERT_EQ(lst.size(), 6);
  ASSERT_EQ(lst.begin().ptr->value_, 2);
}

TEST(multiset_test, swap_test) {
  s21::multiset<int> lst({4, 4, 12, 2, 2, 2, 1});
  s21::multiset<int> lst1({1, 2, 3});
  lst.swap(lst1);
  ASSERT_EQ(lst.size(), 3);
  ASSERT_EQ(lst1.size(), 7);
}

TEST(multiset_test, merge_test) {
  s21::multiset<int> lst({4, 4, 12, 2, 2, 2, 1});
  s21::multiset<int> lst1({1, 2, 3});
  lst.merge(lst1);
  ASSERT_EQ(lst.size(), 10);
  ASSERT_EQ(lst1.size(), 0);
}

TEST(multiset_test, find_test) {
  s21::multiset<int> lst({4, 4, 12, 2, 2, 2, 1});
  auto it = lst.find(14);
  if (it.ptr != nullptr) {
    ASSERT_EQ(it.ptr->value_, 14);
  }
  it = lst.find(12);
  ASSERT_EQ(it.ptr->value_, 12);
}

TEST(multiset_test, contains_test) {
  s21::multiset<int> lst({4, 4, 12, 2, 2, 2, 1});
  ASSERT_EQ(lst.contains(14), false);
}

TEST(multiset_test, count_test) {
  s21::multiset<int> lst({4, 4, 12, 2, 2, 2, 1});
  ASSERT_EQ(lst.count(2), 3);
}

TEST(multiset_test, equal_range_test) {
  s21::multiset<int> lst({4, 4, 12, 2, 2, 2, 1});
  ASSERT_EQ(*(lst.equal_range(2).first), 2);
  ASSERT_EQ(*(lst.equal_range(2).second), 2);
  ASSERT_EQ(*(++lst.equal_range(2).first), 2);
  ASSERT_EQ(*(--lst.equal_range(2).first), 1);
  ASSERT_EQ(*(++lst.equal_range(2).second), 4);
}

TEST(multiset_test, lower_bound_test) {
  s21::multiset<int> lst({4, 4, 12, 2, 2, 2, 1});
  ASSERT_EQ(*(lst.lower_bound(2)), 2);
}

TEST(multiset_test, upper_bound_test) {
  s21::multiset<int> lst({4, 4, 12, 2, 2, 2, 1});
  ASSERT_EQ(*(lst.upper_bound(2)), 4);
}

TEST(emplace_test, list_emplace_test) {
  s21::list<int> lst({4, 4, 12, 2, 2, 2, 1});
  auto iter = ++(++(++(++lst.begin())));
  lst.emplace(iter, 1, 2, 3, 4, 5, 6, 7, 8);
  ASSERT_EQ(lst.size(), 15);
}

TEST(emplace_front_test, list_emplace_front_test) {
  s21::list<int> lst({4, 4, 12, 2, 2, 2, 1});
  lst.emplace_front(1, 2, 3, 4, 5);
  ASSERT_EQ(lst.size(), 12);
}

TEST(emplace_back_test, list_emplace_back_test) {
  s21::list<int> lst({4, 4, 12, 2, 2, 2, 1});
  lst.emplace_back(1, 2, 3, 4, 5);
  ASSERT_EQ(lst.size(), 12);
}

TEST(emplace_back_test, vector_emplace_back_test) {
  s21::vector<int> lst({4, 4, 12, 2, 2, 2, 1});
  lst.emplace_back(1, 2, 3, 4, 5);
  ASSERT_EQ(lst.size(), 12);
}

TEST(emplace_test, vector_emplace_test) {
  s21::vector<int> lst({4, 4, 12, 2, 2, 2, 1});
  auto it = lst.begin();
  lst.emplace(it, 1, 2, 3, 4, 5);
  ASSERT_EQ(lst.size(), 12);
}

TEST(emplace_test, vector_emplace_test_1) {
  s21::vector<int> lst({4, 4, 12, 2, 2, 2, 1});
  auto it = lst.end();
  lst.emplace(it, 1, 2, 3, 4, 5);
  ASSERT_EQ(lst.size(), 12);
}

TEST(emplace_test, vector_emplace_test_2) {
  s21::vector<int> lst({4, 4, 12, 2, 2, 2, 1});
  auto it = lst.begin() + 4;
  lst.emplace(it, 1, 2, 3, 4, 5);
  ASSERT_EQ(lst.size(), 12);
}

TEST(emplace_back_test, queue_emplace_back_test) {
  s21::queue<int> lst({4, 4, 12, 2, 2, 2, 1});
  lst.emplace_back(1, 2, 3, 4, 5);
  ASSERT_EQ(lst.size(), 12);
}

TEST(emplace_front_test, stack_emplace_front_test) {
  s21::stack<int> lst({4, 4, 12, 2, 2, 2, 1});
  lst.emplace_front(1, 2, 3, 4, 5);
  ASSERT_EQ(lst.size(), 12);
}

TEST(emplace_test, multiset_emplace_test) {
  s21::multiset<int> lst({4, 4, 12, 2, 2, 2, 1});
  lst.emplace(1, 2, 3, 4, 5);
  ASSERT_EQ(lst.size(), 12);
}

TEST(emplace_test, map_emplace_test) {
  s21::map<int, int> lst(
      {{15, 4}, {3, 3}, {5, 4}, {17, 3}, {23, 1}, {21, 2}, {1, 1}});
  lst.emplace(std::pair<int, int>(2, 10), std::pair<int, int>(4, 15),
              std::pair<int, int>(29, 15));
  ASSERT_EQ(lst.size(), 10);
}

TEST(emplace_test, set_emplace_test) {
  s21::set<int> lst({5, 4, 12, 8, 3, 2, 1});
  lst.emplace(11, 22, 13, 14, 15);
  ASSERT_EQ(lst.size(), 12);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}