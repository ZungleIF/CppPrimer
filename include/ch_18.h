// 18.1
// (a) range_error r("error);
//     throw r;
// (b) exception *p = &r;
//     throw *p;
// (a) range_error (b) exception
// throw p �� ��� p �� &exception
// ��ġ�� catch ������ �� ���ܸ� ����Ϸ��� ��� �ּҰ���
// �����ϹǷ� ������ �� �� �ִ�. 
// (ex. p.what() )

// 18.2
// ������ Ǯ��� ��ġ�ϴ� catch ���� �˻��س��ư���.
// �׿� ���ÿ� ������ü���� ��� �Ҹ� ��Ų��.
// ���� ��ġ�ϴ� catch ���� ã�� ���� ���,
// terminate �Լ��� ȣ���� ���α׷��� �����Ų��.

// 18.3
//void exercise(int *b, int *e) {
//  vector<int> v(b, e);
//  int *p = new int[v.size()];
//  ifstream in("ants");
//  // Exception gets thrown here
//}
// 1. exercise �Լ��� ȣ���ϴ� �κ��� try..catch ������ �ѷ��Ѵ�.
// 2. �Լ� ���ο��� ó���Ѵ�
//    a. ifstream::is_open �� ���� ������ ���������� ���ȴ��� Ȯ��
//    b. �Լ� ���ο��� try..catch ���� ����Ѵ�.

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