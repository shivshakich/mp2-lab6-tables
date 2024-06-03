#include "../gtest/gtest.h"
#include "../include/ttreetable.h"

TEST(TTreeTable, test_sample) {
	const int N = 100;
	TTreeTable t;

	for (int i = 0; i < N; ++i)
		t.InsRecord(std::to_string(i), TPolynom());

	t.Print();
}