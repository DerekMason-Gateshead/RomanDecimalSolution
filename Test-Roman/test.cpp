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
        RomanInputTestData{ "IL", false, -1 , eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER },
        RomanInputTestData{ "LIII", true, 53 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "LIV", true, 54 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "LIIV", false, -1 , eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES },
        RomanInputTestData{ "LVIII", true, 58 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "LVX", false, -1 , eStatusCode::eFAIL_HALF_VALUES_NOT_ALLOWED_PRE },
        RomanInputTestData{ "LIX", true, 59 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "LXIII", true, 63 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "LXIV", true, 64 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "LXIIII", false, -1 , eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES },
        RomanInputTestData{ "LXVIII", true, 68 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "LXIX", true, 69 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "LXXIII", true, 73 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "LXXVIII", true, 78 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "LXXXVIII", true, 88 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "LXXXIX", true, 89 , eStatusCode::eSUCCESS },
        RomanInputTestData{ "VL", false, -1 , eStatusCode::eFAIL_HALF_VALUES_NOT_ALLOWED_PRE },
        RomanInputTestData{ "XC", true, 90 , eStatusCode::eSUCCESS }
        ));


        INSTANTIATE_TEST_CASE_P(roman_data_tests3, RomanDataTests, testing::Values(
            RomanInputTestData{ "VC", false, -1 , eStatusCode::eFAIL_HALF_VALUES_NOT_ALLOWED_PRE },
            RomanInputTestData{ "XCI", true, 91 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "XCIIII", false, -1 , eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES },
            RomanInputTestData{ "XCIV", true, 94 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "xcviiii", false, -1 , eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES },
            RomanInputTestData{ "xcvv", false, -1,  eStatusCode::eFAIL_TOO_MANT_HALF_TEN_VALUES },
            RomanInputTestData{ "CVX", false, -1,  eStatusCode::eFAIL_HALF_VALUES_NOT_ALLOWED_PRE },
            RomanInputTestData{ "XCIX", true, 99 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CXXVV", false, -1,  eStatusCode::eFAIL_TOO_MANT_HALF_TEN_VALUES },
            RomanInputTestData{ "XVX", false, -1,  eStatusCode::eFAIL_HALF_VALUES_NOT_ALLOWED_PRE },
            RomanInputTestData{ "CI", true, 101 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CIV", true, 104 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CXXVIII", true, 128 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CXXIX", true, 129 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CXXX", true, 130 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CXXXIX", true, 139 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CXXVII", true, 127 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CXIX", true, 119 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "XXXX", false, -1 , eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES },
            RomanInputTestData{ "CXIXIX", false, -1 , eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES },

            RomanInputTestData{ "CXL", true, 140 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CXLI", true, 141 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CCXLII", true, 242 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CCXLIII", true, 243 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CCCXLIV", true, 344 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CCCXLV", true, 345 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CCCXLVI", true, 346 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CCCXLVII", true, 347 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CCCXLVIII", true, 348 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CXLIX", true, 149 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CL", true, 150 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CCLI", true, 251 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CIL", false, -1 , eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER },
            RomanInputTestData{ "CCLIII", true, 253 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CCCLIV", true, 354 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CCLIIV", false, -1 , eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES },
            RomanInputTestData{ "CCCLVIII", true, 358 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "LCCL", false, -1 , eStatusCode::eFAIL_HALF_VALUES_NOT_ALLOWED_PRE },
            RomanInputTestData{ "CCCLIX", true, 359 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CCCLXIII", true, 363 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CCCLXIV", true, 364 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CCCLXIIII", false, -1 , eStatusCode::eFAIL_TOO_MANY_BASE10_VALUES },
            RomanInputTestData{ "CCCLXVIII", true, 368 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CLXIX", true, 169 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CCCLXXIII", true, 373 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CCCLXXVIII", true, 378 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CCCLXXXVIII", true, 388 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "CCCLXXXIX", true, 389 , eStatusCode::eSUCCESS },
            RomanInputTestData{ "VCCC", false, -1 , eStatusCode::eFAIL_HALF_VALUES_NOT_ALLOWED_PRE },
            RomanInputTestData{ "CCCXC", true, 390 , eStatusCode::eSUCCESS }
        ));
        
            INSTANTIATE_TEST_CASE_P(roman_data_tests4, RomanDataTests, testing::Values(
                RomanInputTestData{ "CCCXCVIII", true, 398 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "CCCXCIX", true, 399 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "CD", true, 400 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "CDIII", true, 403 , eStatusCode::eSUCCESS }, 
                RomanInputTestData{ "CDIV", true, 404 , eStatusCode::eSUCCESS }, 
                RomanInputTestData{ "CDVIII", true, 408 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "CDIX", true, 409 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "CDXXXIX", true, 439 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "CDXL", true, 440 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "CDXLIX", true, 449 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "CDL", true, 450 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "CDLXXXIV", true, 484 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "CDLXXXIX", true, 489 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "CDXC", true, 490 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "CDXCIX", true, 499 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "D", true, 500 , eStatusCode::eSUCCESS },
                RomanInputTestData{ "VD", false, -1 , eStatusCode::eFAIL_HALF_VALUES_NOT_ALLOWED_PRE },
                RomanInputTestData{ "LD", false, -1 , eStatusCode::eFAIL_HALF_VALUES_NOT_ALLOWED_PRE },
                RomanInputTestData{ "XD", false, -1 , eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER },
                RomanInputTestData{ "ID", false, -1 , eStatusCode::eFAIL_INVALID_PRE_VALUE_FOR_NUMBER },
                RomanInputTestData{ "CCD", false, -1 , eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES },
                RomanInputTestData{ "CXCD", false, -1 , eStatusCode::eFAIL_TOO_MANY_PRE_BASE_10_VALUES },
                RomanInputTestData{ "LL", false, -1,  eStatusCode::eFAIL_TOO_MANT_HALF_TEN_VALUES },
                RomanInputTestData{ "DD", false, -1,  eStatusCode::eFAIL_TOO_MANT_HALF_TEN_VALUES }

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


    

    