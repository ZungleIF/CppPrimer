#pragma once
#include <tuple>
#include <vector>
#include <string>
#include <bitset>
#include <utility>
#include <boost>
// tuple, #include <tuple>
// make_tuple and get<i>(t)
// 17.1
void ch_17_1() {
	std::tuple<int, int, int>{1, 2, 3};
}

// 17.2
void ch_17_2() {
	std::tuple<std::string, std::vector<std::string>, std::pair<std::string, int>> tu;
}

// 17.3
// TextQuery.h �� 
//using std::tuple
//	<std::string,
//	 std::shared_ptr<std::vector<std::string>>>,
//	 std::shared_ptr<std::set<std::vector<std::string>>::size_type>>
//	= QueryResult;
// tuple �� ����ϸ� ������ ���� ������ �ʿ䰡 ������ 
// Ŭ���� QueryResult �� ����� ��� ����̳� �ٸ� ������ �߰��ϰ� ���� �� �����ϴ�
// ==> Refactoring �� tuple �� ������� �� ���� �� �����ϴ�
	
// 17.4
//using matches = std::tuple<std::vector<Sales_data>::size_type,
//                           std::vector<Sales_data>::const_iterator,
//                           std::vector<Sales_data>::const_iterator>;
//vector<matches> findBook(const vector<vector<Sales_data>>& files,
//                         const string& book_name) {
//  vector<matches> ret;
//  for (auto store = files.cbegin(); store != files.cend(); store + ) {
//    auto find = equal_range(store->begin(), store->end(), book_name, compareIsbn);
//    if (find.first != find.second) {
//      ret.push_back(make_tuple(store - files.cbegin(), find.first, find.second));
//    }
//  }
//  return ret;
//}

// 17.6
//struct matches_ {
//  std::vector<Sales_data>::size_type sz;
//  std::vector<Sales_data>::const_iterator begin;
//  std::vector<Sales_data>::const_iterator end;
//};
//std::vector<matches_> findBook_(const std::vector<std::vector<Sales_data>>& files,
//                                const std::string& book_name);
//vector<matches_> findBook_(const vector<vector<Sales_data>>& files,
//                           const string& book_name) {
//  vector<matches_> ret;
//  for (auto store = files.cbegin(); store != files.cend(); store++) {
//    auto find = equal_range(store->begin(), store->end(), book_name, compareIsbn);
//    if (find.first != find.second) {
//      ret.push_back({ static_cast<size_t>(store - files.cbegin()), find.first, find.second });
//    }
//  }
//  return ret;
//}

// 17.7
// tuple �� ��ȯ�ϴ� ���� ������ �� �ξ� �����ϳ�, �� ������ ����� �� ��ġ ���� �� �ִ�.
// class Ÿ���� ����� ������ ����� ó���� ������ �׶��׶� �ʿ�� �߰��ϴ� ���� refactoring ��
// ���� �̵��� �� �ִ�.

// 17.8
// Sales_data() �� ����� ��� �⺻�ʱ�ȭ �Ѵ�. ���� isbn ���� �ȸ� �μ��� ���⸸�� ��µȴ�.

// 17.10
void ch17_10();

// 17.11
struct TFAnswer {

};