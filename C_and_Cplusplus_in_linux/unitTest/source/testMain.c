/*************************************************************************
    > File Name: testmain.c
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: Sun 23 Mar 2014 10:03:18 PM CST
 ************************************************************************/


#include "test.h"
#include <CUnit/Console.h>
#include <stdio.h>
#include <assert.h>

int InitSuite()
{
    return 0;
}

int EndSuite()
{
    return 0;
}

int Test_Is_Equal(int a,int b,int real)
{
    int result;
    result = sum(a,b);
    if(result == real){
        return 1;
    }
    return 0;
}

int Test_Is_Not_Equal(int a,int b,int real)
{
    int result;
    result = sum(a,b);
    if(result != real){
        return 1;
    }
    return 0;
}

void Test1()
{
    CU_ASSERT(Test_Is_Equal(3,4,7));
}

void Test2()
{
    CU_ASSERT(Test_Is_Not_Equal(4,5,10));
}

/*0:sucessful;1:failed */
int AddTestMain()
{
#if 1
    CU_pSuite pSuite = NULL;

    /*****************
     * 1.CU_add_suite 增加一个Suite
     * 2.Suite名字：testSuite
     * 3.InitSuite EndSuite 分别是测试单元初始和释放函数，如不需要传NULL
     */

    pSuite = CU_add_suite("testSuite",InitSuite,EndSuite);

    //if(NULL != pSuite){
        if(NULL == CU_add_test(pSuite,"Test1",Test1) ||
            NULL == CU_add_test(pSuite,"Test2",Test2)){
            return 1;
        }
   // }

    /**********另一种测试方法**********/

#else
    CU_TestInfo testcases[] = {
        {"Test1",Test1},
        {"Test2",Test2},
        CU_TEST_INFO_NULL
    };

    CU_SuiteIndo Suites[] = {
        {"Test the functon sum:",InitSuite,EndSuite,testcases},
        CU_TEST_INFO_NULL
    };

    if(CUE_SUCCESS != CU_register_suites(Suites)){
        return 1;
    }
    /******************************/

#endif

    return 0;

}


