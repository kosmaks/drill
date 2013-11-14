#pragma once

#include <iostream>

#define LOG_DEBUG(x) (std::cout << " [.] " << x << std::endl)
#define LOG_INFO(x)  (std::cout << " [-] " << x << std::endl)
#define LOG_WARN(x)  (std::cerr << " [!] " << x << std::endl)
#define LOG_ERROR(x) (std::cerr << " [#] " << x << std::endl)
