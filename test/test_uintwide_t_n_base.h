#ifndef TEST_UINTWIDE_T_N_BASE_2019_12_29_H_
  #define TEST_UINTWIDE_T_N_BASE_2019_12_29_H_

  #include <atomic>
  #include <random>
  #include <sstream>

  #include <boost/multiprecision/cpp_int.hpp>
  #include <boost/noncopyable.hpp>

  #include <test/parallel_for.h>
  #include <wide_integer/generic_template_uintwide_t.h>

  class test_uintwide_t_n_base : private boost::noncopyable
  {
  public:
    virtual ~test_uintwide_t_n_base() = default;

    virtual std::size_t get_digits2() const = 0;

    std::size_t size() const { return number_of_cases; }

    virtual void initialize() = 0;

  protected:
    test_uintwide_t_n_base(const std::size_t count)
      : number_of_cases(count) { }

    template<typename UnsignedIntegralType>
    static std::string hexlexical_cast(const UnsignedIntegralType& u)
    {
      std::stringstream ss;

      ss << std::hex << u;

      return ss.str();
    }

    template<typename OtherLocalUintType,
             typename OtherBoostUintType>
    static void get_equal_random_test_values_boost_and_local_n(OtherLocalUintType* u_local,
                                                               OtherBoostUintType* u_boost,
                                                               const std::size_t count)
    {
      using other_local_uint_type = OtherLocalUintType;
      using other_boost_uint_type = OtherBoostUintType;

      my_random_generator.seed(std::clock());

      std::atomic_flag rnd_lock = ATOMIC_FLAG_INIT;

      my_concurrency::parallel_for
      (
        std::size_t(0U),
        count,
        [&u_local, &u_boost, &rnd_lock](std::size_t i)
        {
          while(rnd_lock.test_and_set()) { ; }
          const other_local_uint_type a = my_random_generator();
          rnd_lock.clear();

          u_local[i] = a;
          u_boost[i] = other_boost_uint_type("0x" + hexlexical_cast(a));
        }
      );
    }

  private:
    static std::linear_congruential_engine<std::uint32_t, 48271, 0, 2147483647> my_random_generator;
    const std::size_t number_of_cases;

    test_uintwide_t_n_base() = delete;
  };

#endif // TEST_UINTWIDE_T_N_BASE_2019_12_29_H_
