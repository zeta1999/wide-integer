///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2021.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#include <cstdint>
#include <random>
#include <string>

#include <math/wide_integer/uintwide_t.h>
#include <math/wide_integer/uintwide_t_examples.h>

namespace
{
  template<typename LimbType, typename AllocatorType = void>
  bool generate()
  {
    using random_engine_type = std::mersenne_twister_engine<std::uint64_t,
                                                            64,
                                                            312,
                                                            156,
                                                            31,
                                                            UINT64_C(0xB5026F5AA96619E9),
                                                            29,
                                                            UINT64_C(0x5555555555555555),
                                                            17,
                                                            UINT64_C(0x71D67FFFEDA60000),
                                                            37,
                                                            UINT64_C(0xFFF7EEE000000000),
                                                            43,
                                                            UINT64_C(6364136223846793005)>;

    using wide_integer_type  = math::wide_integer::uintwide_t<256U, std::uint32_t, AllocatorType>;
    using distribution_type  = math::wide_integer::uniform_int_distribution<wide_integer_type::my_digits, typename wide_integer_type::limb_type>;

    // Generate a random number with wide_integer_type having limbs of type LimbType.
    random_engine_type generator;

    distribution_type distribution;

    const wide_integer_type n = distribution(generator);

    const bool result_is_ok =
      (n == wide_integer_type("0xF258D22D4DB91392B5EE8CB6ABE457F8401F7AC78BC80F1CC96D191CF6F6AEA6"));

    return result_is_ok;
  }
}

bool math::wide_integer::example007_random_generator()
{
  const bool result_08_is_ok = generate<std::uint8_t> ();
  const bool result_16_is_ok = generate<std::uint16_t>();
  const bool result_32_is_ok = generate<std::uint32_t>();

  const bool result_is_ok = (   result_08_is_ok
                             && result_16_is_ok
                             && result_32_is_ok);

  return result_is_ok;
}

// Enable this if you would like to activate this main() as a standalone example.
#if 0

#include <iomanip>
#include <iostream>

int main()
{
  const bool result_is_ok = wide_integer::example007_random_generator();

  std::cout << "result_is_ok: " << std::boolalpha << result_is_ok << std::endl;
}

#endif
