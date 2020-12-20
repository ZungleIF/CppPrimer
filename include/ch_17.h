#pragma once
#include <tuple>
#include <vector>
#include <bitset>
#include <utility>
#include <string>
#include <regex>
#include <queue>
#include <iostream>
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
std::bitset<6> bit_num[] = { 1, 2, 3, 5, 8, 13, 21 };
void ch17_10() {
  std::bitset<6> temp;
  for (auto b : bit_num) {
    temp |= b;
  }
}
// 17.11 ~ 17.13
template <size_t N>
struct TFproblem {
  TFproblem() = default;

  void get_response();
  int score(const std::bitset<N>& answer) const;
  std::bitset<N> question;
};
template <size_t N>
std::ostream& operator<<(std::ostream& os, const TFproblem<N>& b) {
  std::string s = b.question.to_string('F', 'T');
  for (auto i = 0; i < s.size(); i++) {
    os << i << ": " << s[i] << std::endl;
  }
}
template <size_t N>
void TFproblem<N>::get_response() {
  std::string n;
  for (int i = 0; i < N; i++) {
    std::cin >> n;
    if (n == "T") question.set(i, 1);
    if (n == "F") question.set(i, 0);
  }
}

template<size_t N>
int TFproblem<N>::score(const std::bitset<N>& answer) const {
  int cnt = 0;
  for (int i = 0; i < N; i++) {
    if(question[i] == answer[i])  ++cnt;
  }
  return cnt;
}

// 17.14
// �������� ���������� �ǳ�, ���� ǥ������ ������ �� �� (runtime),
// regex_error Ÿ�� ���ܸ� throw �Ѵ�.
void ch17_14() {
  try {
    std::regex r1("[[:alnum:]+\\.");
    std::regex r2("");
  }
  catch (std::regex_error e) {
    std::cout << e.what() << "\ncode: " << e.code() << std::endl; 
  }
}

// 17.15
void ch17_15(std::string pattern = "[^c]ei") {
  std::string str;
  pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
  std::regex r;
  try {
    r = pattern;
  }
  catch (std::regex_error e) {
    std::cout << e.what() << "\ncode: " << e.code() << std::endl;
  }
  std::smatch sm;
  std::cout << "Enter a string: ";
  std::getline(std::cin, str);
  std::string test_str("receipt freind theif");
  if (std::regex_search(str, sm, r)) {
    std::cout << "It's a match: " << sm.str() << std::endl;
  }
  else {
    std::cout << "No match.\n";
  }
}

// 17.16
// std::regex r("[^c]ei");
// smatch::str() ���� ��ȯ�Ǵ� ���� _ei ���ڿ� ���̴�.

using namespace std;
// 17.17
void ch17_17() {
  string str, pattern("[[:alpha:]]*[^c]ei[[:alpha:]]*");
  regex r(pattern);
  getline(cin, str);
  sregex_iterator srit(str.begin(), str.end(), r), end;
  for_each(srit, end, [](const smatch sm){cout << sm.str() << endl;});
}

// 17.18
void ch17_18() {
  set<string> exclude{
    "neighbor", "albeit", "feint",
    "ceil", "ceiling", "eight"
  };
  string str, pattern("[[:alpha:]]*[^c]ei[[:alpha:]]*");
  regex r(pattern);
  getline(cin, str);
  sregex_iterator srit(str.begin(), str.end(), r), end;
  for_each(srit, end, [exclude](const smatch sm) 
           {
             if(exclude.find(sm.str()) == exclude.end())
              cout << sm.str() << endl;
           });
}

// 17.19
// matched == false �̸�, ssub_match::str() �� �� string �� ��ȯ�Ѵ�.

// 17.20, 17.22 
// TODO
class valid_phone {
  friend ostream& operator<<(ostream&, const valid_phone&);
public:
  valid_phone() : r("(\\()?(\\d{3})(\\))?([[:blank:]]*)?([-.])?(\\d{3})([[:blank:]]*)?([-.])?(\\d{3})") {}
  void check_pnum();
private:
  regex r;
  smatch m;
  vector<string> validated;
  void valid(const smatch&);
};

ostream& operator<<(ostream& os, const valid_phone& vp) {
  for(auto i : vp.validated)
    os << i << endl;
  return os;
}

void valid_phone::valid(const smatch& m) {
  if (m[1].matched && m[3].matched &&
      (!m[5].matched != m[4].matched)) {
     validated.push_back(m.str());
  } else {
    if (!m[3].matched) {
      if (m[4].matched && m[7].matched) {
        // unlimited length of space
        string s;
        for (auto i = 1; i <= 9; ++i) {
          if (i == 4 || i == 7) {
            s += " ";
          }
          s += m[i];
        }
        validated.push_back(s);
      } else if (!(m[4].matched && m[7].matched) && m[5].str() == m[8].str()) {
        validated.push_back(m.str());
      } else {

      }
    }
  }
}

void valid_phone::check_pnum() {
  // regex ���α׷��� '\' �� �Ѱ��ֱ� ���ؼ� '\\' �� ����Ѵ�
  regex r("(\\()?(\\d{3})(\\))?([[:blank:]]*)?([-.])?(\\d{3})([[:blank:]]*)?([-.])?(\\d{3})");
  string in;
  while (getline(cin, in)) {
    sregex_iterator it(in.begin(), in.end(), r), end;
    for_each(it, end, [this](const smatch& m)
             {
               valid(m);
             });
  }
}

// 17.23
// regex r("(\\d{5})|((\\d{5})-(\\d{4}))");