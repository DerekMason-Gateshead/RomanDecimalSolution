#include "pch.h"

#include "..\RomanDecimalConsoleApp\RomanNumeralData.h"

    struct RomanInputTestData
    {
        std::string romanNumber;
        bool expectedSuccess;
        int expectedValue;


        friend std::ostream& operator<<(std::ostream& os, const RomanInputTestData& obj)
        {
            return os
                << "Roman Number " << obj.romanNumber
                << " expected Success" << obj.expectedSuccess
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

    struct RomanDataTests : RomanInputDataTest, testing::WithParamInterface<RomanInputTestData>
    {
        RomanDataTests()
        {
            romanNumeralData->setRomanNumeralData(GetParam().romanNumber);
        }
    };

    
    INSTANTIATE_TEST_CASE_P(roman_data_tests, RomanDataTests, testing::Values(
            RomanInputTestData{ "VI", true, 6 }
        ));

    TEST_P(RomanDataTests, dataValidTest)
    {
            auto as = GetParam();
            
            EXPECT_EQ(romanNumeralData->IsDataValid(),as.expectedSuccess);
    }

    TEST_P(RomanDataTests, dataValueTest)
    {
        auto as = GetParam();

        EXPECT_EQ(romanNumeralData->romanDecimalValue(), as.expectedValue);
    }
    

    