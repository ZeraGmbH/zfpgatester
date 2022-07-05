#include <gtest/gtest.h>
#include "textfilehandler.h"


TEST(FILE_HANDLER, OPEN_NON_EXISTING_FILE) {
    TextFileHandler f("Test.txt", "", false);
    EXPECT_FALSE(f.fileExists());
}

TEST(FILE_HANDLER, CREATE_FILE_AND_OPEN) {
    TextFileHandler f("Test.txt", "", true);
    EXPECT_TRUE(f.fileExists());
}

TEST(FILE_HANDLER, OPEN_EXISTING_FILE) {
    TextFileHandler f("Test.txt", "", false);
    EXPECT_TRUE(f.fileExists());
}

TEST(FILE_HANDLER, FILE_WRITE) {
    TextFileHandler f("Test.txt", "", false);
    std::vector<QString> writeData = {"0000", "1111"};

    EXPECT_TRUE(f.writeFile(writeData, false));
}

TEST(FILE_HANDLER, FILE_READ) {
    TextFileHandler f("Test.txt", "", false);
    std::vector<QString> readData;

    EXPECT_TRUE(f.readFile(2, readData));
}

TEST(FILE_HANDLER, VERIFY_FILE_READ_WRITE) {
    TextFileHandler f("Test.txt", "", false);
    std::vector<QString> writeData;
    std::vector<QString> readData;

    writeData.push_back("0000");
    writeData.push_back("1111");

    f.writeFile(writeData, false);
    f.readFile(2, readData);

    EXPECT_EQ(readData.at(0), writeData.at(0));
    EXPECT_EQ(readData.at(1), writeData.at(1));
}

TEST(FILE_HANDLER, VERIFY_FILE_READ_WRITE_APPEND) {
    TextFileHandler f("Test.txt", "", false);
    std::vector<QString> writeData1, writeData2;
    std::vector<QString> readData;

    writeData1.push_back("0000");
    writeData1.push_back("1111");
    f.writeFile(writeData1, false);

    writeData2.push_back("2222");
    writeData2.push_back("3333");
    f.writeFile(writeData2, true);
    f.readFile(4, readData);

    EXPECT_EQ(readData.at(0), writeData1.at(0));
    EXPECT_EQ(readData.at(1), writeData1.at(1));
    EXPECT_EQ(readData.at(2), writeData2.at(0));
    EXPECT_EQ(readData.at(3), writeData2.at(1));
}

TEST(FILE_HANDLER, DELETE_EXISTING_FILE) {
    TextFileHandler f("Test.txt", "", false);
    f.deleteFile();
    EXPECT_FALSE(f.fileExists());
}
