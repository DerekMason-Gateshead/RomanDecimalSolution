#include "pch.h"
#include "..\RomanDecimalConsoleApp\RomanNumeralData.h"

struct ValidTestData
{
    std::string romanNumber;
    bool expectedSuccess;
    int expectedValue;


    friend std::ostream& operator<<(std::ostream& os, const ValidTestData& obj)
    {
        return os
            << "Roman Number " << obj.romanNumber
            << "expected Success" << obj.expectedSuccess
            << " value" << obj.expectedValue;
    }
};

struct RomanInputDataTest : testing::Test
{
    RomanNumeralData* romanNumeralData;
    RomanInputDataTest()
    {
        romanNumeralData = new RomanNumeralData();
    }

    virtual ~RomanInputDataTest() { delete romanNumeralData; }
};

struct DataValidTests : RomanInputDataTest, testing::WithParamInterface<ValidTestData>
{
    DataValidTests()
    {
        romanNumeralData->setRomanNumeralData(GetParam().romanNumber);
    }
};

INSTANTIATE_TEST_CASE_P(successTests, DataValidTests, testing::Values(
    ValidTestData{ "VI", true, 6 }
));

TEST_P(DataValidTests, dataValidTest)
{
    auto as = GetParam();

  
    EXPECT_TRUE( romanNumeralData->IsDataValid());

}


