#include "pch.h"

#include "..\RomanDecimalConsoleApp\RomanNumeralData.h"

    struct RomanInputTestData
    {
        std::string romanNumber;
        bool expectedSuccess;
        int expectedValue;
        eStatusCode statusCode;

        friend std::ostream& operator<<(std::ostream& os, const RomanInputTestData& obj)
        {
            return os
                << "Roman Number " << obj.romanNumber
                << " value" << obj.expectedValue
                << " success/fail expected" << obj.expectedSuccess
                << " status Code"  << obj.statusCode;
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
            RomanInputTestData{ "VI", true, 6 , eStatusCode::eSUCCESS},
            RomanInputTestData{ "EVI", false, -1, eStatusCode::eFAIL_INVALID_DATA_VALUE },
            RomanInputTestData{ "I", true, 1 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "II", true, 2 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "III", true, 3 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "IIII", false, -1 , eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES },
            RomanInputTestData{ "IV", true, 4, eStatusCode::eSUCCESS },
            RomanInputTestData{  "VV", false, -1,  eStatusCode::eFAIL_TOO_MANT_HALF_TEN_VALUES }
            

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

    TEST_P(RomanDataTests, statusCodeTest)
    {
        auto as = GetParam();

        EXPECT_EQ(romanNumeralData->getStatusCode(), as.statusCode);
    }


    

    