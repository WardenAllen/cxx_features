
/*
 * @author WardenAllen
 * @date   2020/09/10 14:53:44
 * @brief  
 */

#ifdef __cplusplus 
#undef __cplusplus 
#define __cplusplus 202002
#endif // __cplusplus 

#include <iostream>
#include <gtest/gtest.h>

using namespace std;


int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);

	int ret = RUN_ALL_TESTS();

	getchar();

	return ret;
}