#pragma once

#include <iostream>

#define LOG_DEBUG(x) (std::cout << __FILE__ << ":" << __LINE__ << " [.] " << x << std::endl)
#define LOG_INFO(x)  (std::cout << __FILE__ << ":" << __LINE__ << " [-] " << x << std::endl)
#define LOG_WARN(x)  (std::cerr << __FILE__ << ":" << __LINE__ << " [!] " << x << std::endl)
#define LOG_ERROR(x) (std::cerr << __FILE__ << ":" << __LINE__ << " [#] " << x << std::endl)
