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
            RomanInputTestData{  "VV", false, -1,  eStatusCode::eFAIL_TOO_MANT_HALF_TEN_VALUES },
            RomanInputTestData{ "VII", true, 7, eStatusCode::eSUCCESS },
            RomanInputTestData{ "VIII", true, 8, eStatusCode::eSUCCESS },
            RomanInputTestData{ "VIIII", false, -1 , eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES },
            RomanInputTestData{ "IX", true, 9 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "IIX", false, -1 , eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES },
            RomanInputTestData{ "X", true, 10 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "XI", true, 11 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "XII", true, 12 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "XIII", true, 13 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "XIIV", false, -1 , eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES },
            RomanInputTestData{ "XIV", true, 14 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "XV", true, 15 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "XVI", true, 16 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "XVII", true, 17 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "XVIII", true, 18 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "XVIIII", false, -1 , eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES },
            RomanInputTestData{ "XIX", true, 19 , eStatusCode::eSUCCESS },  
            RomanInputTestData{ "XIIX", false, -1 , eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES },
            RomanInputTestData{ "XVV", false, -1,  eStatusCode::eFAIL_TOO_MANT_HALF_TEN_VALUES },
            RomanInputTestData{ "VX", false, -1,  eStatusCode::eFAIL_HALF_VALUES_NOT_ALLOWED_PRE },
            RomanInputTestData{ "XX", true, 20 , eStatusCode::eSUCCESS }, 
            RomanInputTestData{ "vi", true, 6 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "evi", false, -1, eStatusCode::eFAIL_INVALID_DATA_VALUE },
            RomanInputTestData{ "i", true, 1 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "ii", true, 2 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "iii", true, 3 , eStatusCode::eSUCCESS },
              RomanInputTestData{ "iiii", false, -1 , eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES },
                RomanInputTestData{ "iv", true, 4, eStatusCode::eSUCCESS },
                RomanInputTestData{ "vv", false, -1,  eStatusCode::eFAIL_TOO_MANT_HALF_TEN_VALUES },
                RomanInputTestData{ "vii", true, 7, eStatusCode::eSUCCESS },
                RomanInputTestData{ "viii", true, 8, eStatusCode::eSUCCESS },
                RomanInputTestData{ "viiii", false, -1 , eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES },
                RomanInputTestData{ "ix", true, 9 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "iix", false, -1 , eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES },
                RomanInputTestData{ "x", true, 10 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "xi", true, 11 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "xii", true, 12 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "xiii", true, 13 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "xiiv", false, -1 , eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES },
                RomanInputTestData{ "xiv", true, 14 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "xvi", true, 16 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "xv", true, 15 , eStatusCode::eSUCCESS }
      
        ));

    INSTANTIATE_TEST_CASE_P(roman_data_tests2, RomanDataTests, testing::Values(
        RomanInputTestData{ "xvii", true, 17 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "xviii", true, 18 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "xviiii", false, -1 , eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES },
        RomanInputTestData{ "xix", true, 19 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "xiix", false, -1 , eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES },
        RomanInputTestData{ "xvv", false, -1,  eStatusCode::eFAIL_TOO_MANT_HALF_TEN_VALUES },
        RomanInputTestData{ "vx", false, -1,  eStatusCode::eFAIL_HALF_VALUES_NOT_ALLOWED_PRE },
        RomanInputTestData{ "xx", true, 20 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "XXVV", false, -1,  eStatusCode::eFAIL_TOO_MANT_HALF_TEN_VALUES },
        RomanInputTestData{ "XVX", false, -1,  eStatusCode::eFAIL_HALF_VALUES_NOT_ALLOWED_PRE},
        RomanInputTestData{ "XXI", true, 21 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "XXIV", true, 24 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "XXVIII", true, 28 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "XXIX", true, 29 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "XXX", true, 30 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "XXXI", true, 31 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "XXXVII", true, 37 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "XXXIX", true, 39 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "XXXX", false, -1 , eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES },
        RomanInputTestData{ "XXXIXIX", false, -1 , eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES },

        RomanInputTestData{ "XL", true, 40 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "XLI", true, 41 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "XLII", true, 42 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "XLIII", true, 43 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "XLIV", true, 44 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "XLV", true, 45 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "XLVI", true, 46 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "XLVII", true, 47 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "XLVIII", true, 48 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "XLIX", true, 49 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "L", true, 50 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "LI", true, 51 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "IL", false, -1 , eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER }

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


    

    