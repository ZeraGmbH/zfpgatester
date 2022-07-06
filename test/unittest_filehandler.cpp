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
    QString writeData = {"0000\n1111\n"};

    EXPECT_TRUE(f.writeFile(writeData, false));
}

TEST(FILE_HANDLER, FILE_READ) {
    TextFileHandler f("Test.txt", "", false);
    QString readData;

    EXPECT_TRUE(f.readFile(readData));
}

TEST(FILE_HANDLER, VERIFY_FILE_READ_WRITE) {
    TextFileHandler f("Test.txt", "", false);
    QString writeData = {"0000\n1111\n"};
    QString readData;

    f.writeFile(writeData, false);
    f.readFile(readData);

    EXPECT_EQ(readData, "0000\n1111\n");
}

TEST(FILE_HANDLER, VERIFY_FILE_READ_WRITE_APPEND) {
    TextFileHandler f("Test.txt", "", false);
    QString writeData1, writeData2;
    QString readData;

    writeData1 = "0000\n1111\n";
    f.writeFile(writeData1, false);

    writeData2 = "2222\n3333\n";
    f.writeFile(writeData2, true);
    f.readFile(readData);

    EXPECT_EQ(readData, "0000\n1111\n2222\n3333\n");
}

TEST(FILE_HANDLER, DELETE_EXISTING_FILE) {
    TextFileHandler f("Test.txt", "", false);
    f.deleteFile();
    EXPECT_FALSE(f.fileExists());
}
