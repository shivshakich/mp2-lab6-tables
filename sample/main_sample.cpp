#include <locale>
#include <string>

#include "../include/tarrayhash.h"
#include "../include/ttreetable.h"
#include "../include/tavltree.h"

using std::cout;
using std::endl;
using std::cin;

void sample_array_hash();
void sample_tree();
void sample_avltree();

int main() {
	char c;

	setlocale(LC_CTYPE, "Russian");

	//sample_array_hash();

	sample_tree();
	
	cout << endl;

	sample_avltree();

	return 0;
}

void sample_array_hash() {
	char c;

	cout << "Создаём пустую хэш-таблицу на массиве" << endl;

	TArrayHash h(20);

	Print(h);

	cin >> c;
}

void sample_tree() {
	const int N = 10;
	TTreeTable t;

	for (int i = 0; i < N; ++i)
		t.InsRecord(std::to_string(i), TPolynom());

	t.Print();
}

void sample_avltree() {
	const int N = 10;
	TAVLTree t;

	for (int i = 0; i < N; ++i)
		t.InsRecord(std::to_string(i), TPolynom());

	t.Print();
}