/*************************************************************************
    > File Name: CuintRunTest.c
    > Author: tiankonguse
    > Mail: i@tiankonguse.com 
    > Created Time: Sun 23 Mar 2014 10:03:47 PM CST
 ************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <CUnit/Console.h>

extern int AddTestMain();

int main()
{
    //初始化
    if(CUE_SUCCESS != CU_initialize_registry()){
        return CU_get_error();
    }

    //返回注册到用例指针
    assert(NULL != CU_get_registry);

    //检测是否在执行
    assert(!CU_is_test_running());

    //调用那个测试模块完成测试用例
    if(0 != AddTestMain()){

        CU_cleanup_registry();
        return CU_get_error();
    }

    /*使用console控制交互界面的函数入口*/
    CU_console_run_tests();

    /*使用自动产生XML文件的模式*/
    CU_set_output_filename("TestMax");
    CU_list_tests_to_file();
    CU_automated_run_tests();

    /*调用完毕清理注册信息*/
    CU_cleanup_registry();

}
