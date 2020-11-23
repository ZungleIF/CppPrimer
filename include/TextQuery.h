#pragma once
#include <string>
#include <vector>
#include <set>
#include <map>
#include <memory>
#include <iostream>
#include <fstream>
#include "StrVec.h"
class QueryResult;
/*	Get a file and process every word to a map according to a set of lines the word has occured 
	Careful line_num starts at 1 but set index starts at 0
*/
class TextQuery {

public:
	typedef std::vector <std::string> file_lines;
	typedef std::set<file_lines::size_type> line_no_set;
	TextQuery(std::ifstream &file_in);
	QueryResult query(const std::string &query_word) const;
private:
	std::shared_ptr<file_lines> file;
	std::map<std::string, std::shared_ptr<line_no_set>> word_map;
};

class QueryResult {
	friend class NotQuery;
	friend class AndQuery;
	friend class OrQuery;
public:
	using file_lines = TextQuery::file_lines;
	using line_no_set = TextQuery::line_no_set;
	QueryResult() = default;
	QueryResult(const std::string &_query_word,
		std::shared_ptr<file_lines> _file,
		std::shared_ptr<line_no_set> word_set)
		: query_word(_query_word), file(_file), query_set(word_set) {}

	std::shared_ptr<file_lines> getFile() const { return file; }
	std::shared_ptr<line_no_set> getQuerySet() const { return query_set; }
	void printResult() const;
private:
	std::string query_word;
	std::shared_ptr<file_lines> file;
	std::shared_ptr<line_no_set> query_set;
};


/* Base class for querying */
class Query_base {
	friend class Query;
public:
	virtual ~Query_base() = default;
private:
	virtual QueryResult eval(const TextQuery&) const = 0;
	virtual std::string rep() const = 0;
};
/* 
	Class for Query_base encapsulation, contains a pointer to Query_base
	Eventually creates a tree of class types based on Query_base
*/



class Query {
	friend Query operator~(const Query&);
	friend Query operator&(const Query&, const Query&);
	friend Query operator|(const Query&, const Query&);
public:
	using line_no_set = TextQuery::line_no_set;
	Query(const std::string&);
	QueryResult eval(const TextQuery& tq) const { return qb_ptr->eval(tq); }
	std::string rep() const { return qb_ptr->rep(); }
private:
	Query(const std::shared_ptr<Query_base>& qb) : qb_ptr(qb) {}
	std::shared_ptr<Query_base> qb_ptr;
};

class WordQuery : public Query_base {
	friend class Query;
public:
	WordQuery(const std::string& word) : query_word(word) {}
private:
	QueryResult eval(const TextQuery& tq) const override { return tq.query(query_word); }
	std::string rep() const override { return query_word; }
	std::string query_word;
};

class NotQuery : public Query_base {
	friend Query operator~(const Query&);
	NotQuery(const Query& q) : query(q) {}
	QueryResult eval(const TextQuery&) const override;
	std::string rep() const override { return "( ~ " + query.rep() + ")"; }
	Query query;
};

class BinaryQuery : public Query_base {
protected:
	BinaryQuery(const Query& _lhs, const Query& _rhs, const std::string _binOp)
		: lhs(_lhs), rhs(_rhs), binOp(_binOp) {}
	Query lhs, rhs;
	std::string binOp;
	std::string rep() const override final { return "(" + lhs.rep() + " " + binOp + " " + rhs.rep() + ")"; }
};

class AndQuery : public BinaryQuery {
	friend Query operator&(const Query&, const Query&);
	AndQuery(const Query& lhs, const Query& rhs) : BinaryQuery(lhs, rhs, "&") {}
	QueryResult eval(const TextQuery&) const override;
};

class OrQuery : public BinaryQuery {
	friend Query operator|(const Query&, const Query&);
	OrQuery(const Query& lhs, const Query& rhs) : BinaryQuery(lhs, rhs, "|") {}
	QueryResult eval(const TextQuery&) const override;
};