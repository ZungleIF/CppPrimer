#include "TextQuery.h"
#include <sstream>
#include <iterator>

using namespace std;
TextQuery::TextQuery(ifstream &file_in) {
	string temp_str;
	TextQuery::file_lines temp_lines;
	while (getline(file_in, temp_str)) {
		temp_lines.push_back(temp_str);
	}
	file = make_shared<TextQuery::file_lines>(temp_lines);
	vector<string>::size_type line_num = 1;
	for (auto words : *file) {
		istringstream words_in(words);
		while (words_in >> temp_str) {
			if (word_map.find(temp_str) != word_map.end()) {
				// The word is already in the map
			}
			else {
				word_map[temp_str] = make_shared<line_no_set>();

			}
			word_map[temp_str]->insert(line_num);
		}
		++line_num;
	}
}

QueryResult TextQuery::query(const string &query_word) const {
	if (word_map.find(query_word) != word_map.end()) {
		// Word found in the word_map
		return QueryResult(query_word, file, word_map.at(query_word));
	}
	else {
		// Word not found, delivers an empty word set as a result
		return QueryResult(query_word, file, make_shared<line_no_set>());
	}
}

void QueryResult::printResult() const {
	cout << "Result for query " << query_word << ": " << endl;
	for (auto line : *query_set) {
		cout << "(Line " << line << " ): " << file->at(line - 1) << endl;
	}
}

Query::Query(const string& query_str) : qb_ptr(shared_ptr<Query_base>(new WordQuery(query_str))) {}

istream& operator<<(istream& is, const Query& rhs)	{ return is << rhs.rep(); }
Query operator~(const Query& rhs)					{ return std::shared_ptr<Query_base>(new NotQuery(rhs)); }
Query operator&(const Query& lhs, const Query& rhs) { return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs)); }
Query operator|(const Query& lhs, const Query& rhs) { return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs)); }

QueryResult NotQuery::eval(const TextQuery& tq) const {
	auto exclude = query.eval(tq);
	QueryResult::line_no_set temp;
	for (size_t i = 1; i < exclude.file->size(); i++)
		temp.insert(i);
	for (auto i : *exclude.query_set) {
		temp.erase(i);
	}
	return QueryResult(query.rep(), exclude.file, make_shared<TextQuery::line_no_set>(temp));
}


QueryResult AndQuery::eval(const TextQuery& tq) const {
	auto left = lhs.eval(tq), right = rhs.eval(tq);
	QueryResult::line_no_set temp;
	for (auto leftLine : *left.query_set) {
		for (auto rightLine : *right.query_set) {
			if (leftLine == rightLine) {
				temp.insert(rightLine);
			}
			else if (leftLine < rightLine) {
				break;
			}
			else if (rightLine < leftLine) {
				continue;
			}
		}
	}
	return QueryResult(rep(), left.file, make_shared<QueryResult::line_no_set>(temp));
}


QueryResult OrQuery::eval(const TextQuery& tq) const {
	auto left = lhs.eval(tq), right = rhs.eval(tq);
	QueryResult::line_no_set temp;
	copy(left.query_set->begin(), left.query_set->end(), inserter(temp, temp.begin()));
	copy(right.query_set->begin(), right.query_set->end(), inserter(temp, temp.begin()));
	return QueryResult(rep(), left.file, make_shared<QueryResult::line_no_set>(temp));
}
