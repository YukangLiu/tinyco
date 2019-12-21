//@author Liu Yukang
#include <iostream>
#include "schedule.h"

int main()
{
	co_go(
		[]
		{
			std::cout << "111" << std::endl;
			co_go(
				[]
				{
					std::cout << "222" << std::endl;
					co_yield();
					std::cout << "222222" << std::endl;
				}
				);
			std::cout << "111111" << std::endl;
		}
	);

	co_go(
		[]
		{
			std::cout << "333" << std::endl;
			co_go(
				[]
				{
					std::cout << "444" << std::endl;
					co_yield();
					std::cout << "444444" << std::endl;
				}
				);
			std::cout << "333333" << std::endl;
		}
		);
	std::cout << "end" << std::endl;
}