#include "../gtest/gtest.h"
#include "../include/tscantable.h"

// CONSTRUCTORS

TEST(TScanTable, can_create_table) {
	ASSERT_NO_THROW(TScanTable t);
	ASSERT_NO_THROW(TScanTable t(10));

	TScanTable t1, t2(10);
	TRecord rec1, rec2 = { "name", TPolynom("x+y") };
	ASSERT_NO_THROW(TScanTable t(t1));
	ASSERT_NO_THROW(TScanTable t(t2));
	ASSERT_NO_THROW(TScanTable t(rec1));
	ASSERT_NO_THROW(TScanTable t(rec2));
	ASSERT_NO_THROW(TScanTable(TScanTable(rec2)));
}

TEST(TScanTable, check_default_constructor) {
	int n = 10;
	TScanTable t1, t2(n);
	
	ASSERT_EQ(t1.GetSize(), 0);
	ASSERT_EQ(t2.GetSize(), n);
	ASSERT_EQ(t1.GetDataCount(), 0);
	ASSERT_EQ(t2.GetDataCount(), 0);
	ASSERT_EQ(t1.GetEff(), 0);
	ASSERT_EQ(t2.GetEff(), 0);
}

TEST(TScanTable, check_record_conversion_constructor) {
	int n = 10;
	string name = "_name";
	TPolynom pol("x+y+z");
	TRecord rec1, rec2 = { name, pol };
	TScanTable t1(rec1), t2(rec2);

	ASSERT_EQ(t1.GetDataCount(), 1);
	ASSERT_EQ(t2.GetDataCount(), 1);

	t2.Reset();
	ASSERT_TRUE(t2.GetKey() == name);
	ASSERT_TRUE(t2.GetValue() == pol);
	t1.Reset();
	string s = t1.GetKey();
}

TEST(TScanTable, check_copy_constructor) {
	int n = 10;
	string name = "_name";
	TPolynom pol("x+y+z");
	TRecord rec1, rec2 = { name, pol };
	TScanTable t1(rec1), t2(rec2), t3, t4(n);
	TScanTable t5(t1), t6(t2), t7(t3), t8(t4);

	ASSERT_TRUE(t3 == t4);
	ASSERT_TRUE(t1 != t2);

	ASSERT_TRUE(t5 == t1);
	ASSERT_TRUE(t6 == t2);
	ASSERT_TRUE(t7 == t3);
	ASSERT_TRUE(t8 == t4);
}

// FIND, INS, DEL

TEST(TScanTable, insert_method_puts_record_in_the_end_of_the_array) {
	const int N = 10;
	int number[N];
	TScanTable t(N);

	TPolynom tmpPol;
	for (int i = 0; i < N; ++i) {
		int tmp = number[i] = 3 * i + 2;
		tmpPol = TPolynom(tmp);
		t.InsRecord(std::to_string(tmp), tmpPol);
	}

	ASSERT_EQ(t.GetDataCount(), N);

	int i = 0;
	for (t.Reset(); !t.IsEnd(); t.GoNext()) {
		ASSERT_NO_THROW(t.GetKey());
		ASSERT_NO_THROW(t.GetValue());
		ASSERT_EQ(std::to_string(number[i]), t.GetKey());
		TPolynom pol(t.GetValue());
		ASSERT_TRUE(TPolynom(number[i]) == pol);
		++i;
	}
	ASSERT_ANY_THROW(t.GetKey());
	ASSERT_ANY_THROW(t.GetValue());
}

TEST(TScanTable, find_method) {
	const int N = 10;
	int number[N];
	TScanTable t(N);

	for (int i = 0; i < N; ++i) {
		int tmp = number[i] = i;
		t.InsRecord(std::to_string(tmp), TPolynom(tmp));
	}

	int i = 0;
	for (t.Reset(); !t.IsEnd(); t.GoNext()) {
		bool find;
		ASSERT_NO_THROW(find = t.FindRecord(std::to_string(i)));
		ASSERT_TRUE(find);
		ASSERT_EQ(i, t.GetCurrPos());
		++i;
	}
	for (; i < 2 *N; ++i) {
		bool find;
		ASSERT_NO_THROW(find = t.FindRecord(std::to_string(i)));
		ASSERT_FALSE(find);
		ASSERT_EQ(t.GetCurrPos(), N);
	}
}

// OPERATOR=
