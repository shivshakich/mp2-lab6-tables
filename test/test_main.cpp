#include "../gtest/gtest.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

#include "../include/ttreetable.h"
    TTreeTable t(TRecord{ "muhahah" });
    t.Print();
}
