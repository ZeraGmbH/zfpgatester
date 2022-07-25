#include <gtest/gtest.h>
#include <QTemporaryFile>
#include "filewrapper.h"

TEST(FILE_WRAPPER, lSeekNonexistingFile)
{
    FileWrapper testFile(-1);
    EXPECT_FALSE(testFile.lSeek(0));
}

TEST(FILE_WRAPPER, lSeekExistingFile)
{
    QTemporaryFile testFile("Test.txt");
    testFile.open();
    FileWrapper testFileWrapper(testFile.handle());
    EXPECT_TRUE(testFileWrapper.lSeek(0));
}

