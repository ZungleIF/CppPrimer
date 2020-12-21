#include "TextQuery.h"
#include "Message.h"
#include "StrBlob.h"
#include "StrVec.h"
#include "String.h"
#include "Sales_data.h"
#include "function_call_op.h"
#include "TableCalc.h"
#include "Quote.h"
#include "RadixSort.h"
#include "Template.h"
#include "ch_17.h"
#include "ch_18.h"
using namespace std;

int main() {
	//StrBlob blob{ "owo", "what's", "this?" };
	//for (auto iter = blob.begin(); iter != blob.end(); iter++) {
	//	cout << *iter << "\tcurr: " << iter.get_curr() << "\n";
	//}
	//StrBlob blob2{ "hewwo", "wwowd" };
	//blob = blob2;
	//for (auto iter = blob.begin(); iter != blob.end(); iter++) {
	//	cout << *iter << "\tcurr: " << iter.get_curr() << "\n";
	//}
	//Folder aFolder;
	//Message aMessage("hi");
	//aMessage.add(aFolder);

	//cout << "Creating an instance of StrVec" << endl;
	//StrVec sv{ "owo", "what's", "this?" };
	//cout << "Printing an instance of StrVec" << endl;
	//for (auto str : sv) {
	//	cout << str;
	//}
	//cout << endl;
	//cout << "Self-substuting StrVec" << endl;
	//sv = sv;
	//for (auto str : sv) {
	//	cout << str;
	//}
	//cout << endl;
	////sv.resize(15);
	//cout << "size(): " << sv.size() << "\tcapacity(): " << sv.capacity() << "\n";
	//String mystring("hewow,wawd");
	//String mystring2;
	//String mystring3(mystring), mystring4(mystring);
	//cout << mystring << endl;
	//cin >> mystring2;
	//cout << mystring2 << endl;
	//cout << "mystring + mystring2: " << endl;
	//cout << mystring + mystring2 << endl;
	//cout << "mystring3 += mystring2: " << endl;
	//cout << (mystring3 += mystring2) << endl;
	//cout << "mystring4.append(mystring2): " << endl;
	//cout << mystring4.append(mystring2) << endl;

	//Sales_data sd1("mybook", 14, 5.9), sd2("mybook", 123, 5.9), sd3("otherbook", 2, 19.9);
	//try
	//{
	//	cout << "sd1 + sd2: " << sd1 + sd2 << endl;
	//	cout << "sd1 + sd3: " << sd1 + sd3 << endl;
	//}
	//catch (const logic_error e)
	//{
	//	cerr << e.what() << endl;
	//}

	//StrVec sv2;
	//sv2 = { "notices", "your", "bulge" };
	//for (auto str : sv2) {
	//	cout << str;
	//}
	//cout << endl;

	//vector<string> vec_in;
	//readStrToVec(vec_in);
	//for_each(vec_in.begin(), vec_in.end(), PrintString());
	//cout << endl;

	//vector<string> vec = { "shit", "fuck", "this", "shit" };
	//for_each(vec.begin(), vec.end(), PrintString());
	//cout << "to ";
	//change_if(vec, string("shit"), string("owo"));
	//for_each(vec.begin(), vec.end(), PrintString());
	//cout << endl;
	//
	//vector<string> vec_str{ "The", "thread", "0x35bc", "has", "exited", "with", "code", "0", "(0x0)" };
	//StringLenRange slr(1, 10);
	//for_each(vec_str.begin(), vec_str.end(), ref(slr));
	//slr.printCount();
	//cout << "Test text" << endl;
	//TableCalc tb;
	//Quote q("1234", 3);
	/*Bulk_quote bq("2345", 9.99, 15, 0.15);
	Quote& _q = bq;*/
	//Bulk_quote _bq = std::move(bq);
	//Quote* pq = &bq;

	//print_total(cout, q, 30);
	//print_total(cout, bq, 30);
	//print_total(cout, _bq, 30);

	/*vector<int> vec = { 4, 521, 444, 23, 9, 98, 100, 8, 1102, 424 };
	radixSort(vec);
	for (auto num : vec) {
		cout << num << " ";
	}
	cout << endl;*/

	//ifstream file("C:\\Users\\pc\\Desktop\\test_text.txt");
	//TextQuery tq(file);
	//Query left("Version"), right("(bugfix)");
	//left.eval(tq).printResult(), right.eval(tq).printResult();
	//Query combined = left & right;
	//combined.eval(tq).printResult();

	//Sales_data sd1, sd2;
	//cout << compare(sd1, sd2) << endl;

	//vector<int> vec{ 1, 4, 565, 42 , 420 };
	//list<string> lis{ "hello", "world", "owo", "what's", "this?" };
	//cout << *zungleif::find(vec.begin(), vec.end(), 4) << endl;
	//cout << *zungleif::find(lis.begin(), lis.end(), "owo") << endl;

	//char arr[10];
	//cout << zungleif::getArrSize(arr) << endl;
	//zungleif::Blob<string> str_blob_;
	//zungleif::Blob<std::string> str_blob{ "hello", "world", "owo", "what's", "this?" };
	//cout << str_blob[4] << endl;
	//auto it = str_blob.begin();
	//cout << *it << endl;
	//zungleif::BlobPtr<string> ptr(str_blob, 2);
	//cout << *ptr++ << endl;
	//cout << *ptr << endl;

	/*const zungleif::Blob<string> b{ "Hee", "Jun", "Yoon" };
	auto it = b.begin();
	*it = "Lee";
	cout << *it << endl;
	zungleif::Screen<1920, 1080> scr;*/
	//zungleif::vector<std::string> vec{ "hellow" , "fuck" };
	//cout << *vec.begin() << endl;
	//zungleif::vector<int> int_vec{ 1,2,3 };
	//cout << std::boolalpha << (bool)nullptr;

	////zungleif::Blob<std::string> blob(vec.begin(), vec.end());
	////cout << *blob.begin() << endl;
	//zungleif::Blob<int> b{ 1, 3, 4, 5 };
	//cout << *b.begin() << endl;
	//int a = 323;
	//zungleif::shared_ptr<int> sptr;
	//zungleif::shared_ptr<int> sptr_ = zungleif::make_shared<int>(3232);
	//sptr = sptr_;
	//cout << *sptr << "use count: " << sptr.use_count() << endl;
	//zungleif::compare<const char*>("owo", "what");
	//int lval = 3;
	//zungleif::flip(zungleif::test_func, 42, lval);
	//cout << lval << endl;
	//
	//zungleif::test_template_2();
	//zungleif::print(cout, "hello");
	//zungleif::print(cout, 1, "test", 'c');
	//zungleif::print(cout, 1, "2", Sales_data("my_book", 5, 0.1), string("hmm"), 3.14);

	//StrVec strv;
	//strv.emplace_back("hi", "OwO", "what's this");
	//for_each(strv.begin(), strv.end(),
	//				 [](const string& str) {
	//					 cout << str << endl;
	//				 }
	//);
	//zungleif::make_shared<pair<int, int>>( 1,2 );

	//unordered_multiset<Sales_data> sdms;
	//sdms.insert({Sales_data("book", 3, 0.1), Sales_data("his book", 4, 0.5)});
	//for_each(sdms.begin(), sdms.end(), 
	//				 [](const Sales_data& sd) {
	//					 cout << sd;
	//				 }
	//);
	//cout << endl;
	//cout << *sdms.find(Sales_data("book", 3, 0.1)) << endl;
	//vector<int> vi{1, 2, 2, 3, 4, 5, 2, 6, 7, 2, 1, 3, 10};
	//vector<double> dv{3.14, 8.23121, 1.23, 323.123, 3.14, 3.14, 16.78676};
	//vector<string> sv{"string", "owo", "owo", "owo", "lol", "trololo", "owo"};
	//cout << zungleif::count(vi, 2) << " " << zungleif::count(dv, 3.14) << " " 
	//	<< zungleif::count(sv, string("owo")) << endl;
	//vector<const char*> ccv{ "hello", "owo", "whats", "this", "owo", "owo" };
	//cout << zungleif::count(ccv, "owo") << endl;
	return 0;
}