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
// TextQuery.h 에 
//using std::tuple
//	<std::string,
//	 std::shared_ptr<std::vector<std::string>>>,
//	 std::shared_ptr<std::set<std::vector<std::string>>::size_type>>
//	= QueryResult;
// tuple 을 사용하면 상등연산을 따로 구현할 필요가 없지만 
// 클래스 QueryResult 를 사용할 경우 출력이나 다른 연산을 추가하고 싶을 때 용이하다
// ==> Refactoring 이 tuple 을 사용했을 때 보다 더 가능하다
	
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
// tuple 을 반환하는 것은 구현할 때 훨씬 간단하나, 그 내용을 사용할 때 골치 아플 수 있다.
// class 타입을 만들고 생성된 결과를 처리할 연산을 그때그때 필요시 추가하는 것이 refactoring 등
// 더욱 이득일 수 있다.

// 17.8
// Sales_data() 는 멤버를 모두 기본초기화 한다. 따라서 isbn 없이 팔린 부수와 매출만이 출력된다.

// 17.10
void ch17_10();

// 17.11
struct TFAnswer {

};