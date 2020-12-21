// 18.1
// (a) range_error r("error);
//     throw r;
// (b) exception *p = &r;
//     throw *p;
// (a) range_error (b) exception
// throw p 일 경우 p 는 &exception
// 매치된 catch 문에서 이 예외를 사용하려할 경우 주소값에
// 접근하므로 오류가 날 수 있다. 
// (ex. p.what() )

// 18.2
// 스택을 풀어가며 일치하는 catch 문을 검색해나아간다.
// 그와 동시에 지역객체들을 모두 소멸 시킨다.
// 만약 일치하는 catch 문을 찾지 못할 경우,
// terminate 함수를 호출해 프로그램을 종료시킨다.

// 18.3
//void exercise(int *b, int *e) {
//  vector<int> v(b, e);
//  int *p = new int[v.size()];
//  ifstream in("ants");
//  // Exception gets thrown here
//}
// 1. exercise 함수를 호출하는 부분을 try..catch 문으로 둘러싼다.
// 2. 함수 내부에서 처리한다
//    a. ifstream::is_open 을 통해 파일이 정상적으로 열렸는지 확인
//    b. 함수 내부에서 try..catch 문을 사용한다.

// 18.4
// overflow_error -> runtime_error -> exception

// 18.5
//int main() {
//  try {
//    // Use C++ std lib
//  } catch (exception e) {
//    cerr << e.what() << "\n";
//    abort();
//  }
//}