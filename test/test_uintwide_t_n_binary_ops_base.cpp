///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif

#include <test/test_uintwide_t_n_binary_ops_base.h>

std::random_device test_uintwide_t_n_binary_ops_base::my_rnd;

test_uintwide_t_n_binary_ops_base::random_generator_type test_uintwide_t_n_binary_ops_base::my_gen(my_rnd());

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
