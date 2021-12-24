//#include <fmt/format.h>
#include <type_traits>
#include <array>
#include <cassert>
#include <cstdint> // za (u)intptr_t

// Vaš kod dolazi ovdje.

template <typename T>
struct TypeIdentity{
    using type = T;
};
///za uklanjanje reference
template <typename T>
using TypeIdentity_t = typename TypeIdentity<T>::type;


template< typename T > 
struct RemoveReference : TypeIdentity<T> { };

template< typename T > 
struct RemoveReference<T&>   : TypeIdentity<T> { };

template< typename T > 
struct RemoveReference<T&&>  : TypeIdentity<T> { };

template <typename T>
using RemoveReference_t = typename RemoveReference<T>::type;


//dodavanje lijeve reference
template<typename T>
struct AddLValueReference: TypeIdentity<T&> {};

template<typename T>
struct AddLValueReference<T&>: TypeIdentity<T&> {};

template<typename T>
struct AddLValueReference<T&&>: TypeIdentity<T&> {};

template<>
struct AddLValueReference<void>: TypeIdentity<void> {};

template<typename T>
using AddLValueReference_t = typename AddLValueReference<T>::type;


///provjera jeli niz
template<typename T >
struct IsArray : std::false_type{};

template<typename T>
struct IsArray<T[]> : std::true_type{};

template<typename T, std::size_t N>
struct IsArray<T[N]> : std::true_type{};

template<typename T>
inline constexpr bool IsArray_v = IsArray<T>::value;


//operator zbrajanja
template <typename T, typename S, std::size_t N>
auto operator +(const std::array<T, N>& a,  const std::array<S, N>& b)
{ 
   std::array<decltype(std::declval<T&>() + std::declval<S&>()), N> res;
   for (int i = 0; i < N; ++i){
      res[i] = a[i] +b[i];
    }
   return res;
}

//za baze
class B {};
class D : public B {};
class C{};

class E : public B, public C {};



class Base{
    public:
    virtual ~Base() = default;
};
class Derived : public Base {};


template <typename B>
std::true_type convert(const volatile B*);//u baznu klasu

template <typename>
std::false_type convert(const volatile void*); //u void

template <typename B, typename D>
auto test_if_base() -> decltype(convert<B>(static_cast<D*>(nullptr)));

template <typename Base,typename Derived>
struct IsBaseOf{
    constexpr static bool value = std::is_class<Base>::value && 
                                  std::is_class<Derived>::value  &&
                                  decltype(test_if_base<Base,Derived>())::value;
              };

int main(){
    // 1. 
    static_assert(std::is_same_v<RemoveReference_t<int &>, int>);
    static_assert(std::is_same_v<RemoveReference_t<int &&>, int>);
    static_assert(std::is_same_v<RemoveReference_t<int const &>, int const>);
    
    // 2.
    static_assert(std::is_same_v<AddLValueReference_t<int>, int&>);
    static_assert(std::is_same_v<AddLValueReference_t<int&>, int&>);
    static_assert(std::is_same_v<AddLValueReference_t<int&&>, int&>);
    static_assert(std::is_same_v<AddLValueReference_t<void>, void>);
    
    // 3. 
    static_assert(IsArray_v<int> == false);
    static_assert(IsArray_v<int[]> == true);
    static_assert(IsArray_v<int[3]> == true);
    
    // 4. Operator zbrajanja
    std::array<int,3> a{1,2,3};
    std::array<float,3> b{1.0f, 2.0f, 3.0f};
    auto c = a+b;
    assert(c[0] == 2);
    assert(c[1] == 4);
    assert(c[2] == 6);
    static_assert(std::is_same_v<std::decay_t<decltype(c[0])>, float>); 
    
    // 5. IsBaseOf
    static_assert( IsBaseOf<B,D>::value );
    static_assert( !IsBaseOf<B,C>::value );
    static_assert( IsBaseOf<B,B>::value );
    static_assert( !IsBaseOf<int,long>::value );
    static_assert( !IsBaseOf<void,void>::value );
    static_assert( !IsBaseOf<void,B>::value );

    static_assert( IsBaseOf<const B,D>::value );
    static_assert( IsBaseOf<B, volatile D>::value );
    
    static_assert( IsBaseOf<B,E>::value );
    static_assert( IsBaseOf<C,E>::value );

    // 6. safe_cast().
    /*
    auto x1 = safe_cast<int>(42.0f);  // float -> int 
    assert(x1 == 42);
    fmt::print("x1 = {}\n", x1);
    bool same = std::is_same_v< decltype(x1), int >;
    assert(same == true); 

//    auto x1a = safe_cast<int>(42.1); // assertion in safe_cast<> must fail

//    double x3 = 100*std::numeric_limits<float>::max() + 1.0;
//    float x4 = safe_cast<float>(x3);  // failed inside safe_cast<>.
//    fmt::print("x3 = {}, x4 = {}\n", x3, x4);

    long double xld1 = 32.1;
    float xld2 = safe_cast<float>(xld1);
    fmt::print("xld2 = {}\n", xld2);

    std::string y2{"noName"};
    auto x2 = safe_cast<std::string>(y2);
    assert(x2 == y2);

    // Pokazivači
    Derived * pd = new Derived;
    Base * pb = safe_cast<Base*>(pd);
    Derived * pd1 = safe_cast<Derived*>(pb);

    // Ovo ne dozvoljavamo sa safe_cast!
//    void * pv = new int{7};
//    int * pi = static_cast<int*>(pv);
//    double * pdub = static_cast<double*>(pv);
//    fmt::print("*pi = {}\n", *pi);
//    fmt::print("*pdub = {}\n", *pdub); // nema greške, samo smeće na izlazu
//    delete pi;
    
    intptr_t intptr = safe_cast<intptr_t>(new double{3.14});
    fmt::print("intptr = {:#x}\n", intptr);
    double * dptr = safe_cast<double *>(intptr);
    fmt::print("dptr   = {}\n", static_cast<void*>(dptr));

    uintptr_t uintptr = safe_cast<uintptr_t>(new double{3.14});
    fmt::print("uintptr = {:#x}\n", uintptr);
    double * dptr1 = safe_cast<double *>(uintptr);
    fmt::print("dptr1   = {}\n", static_cast<void*>(dptr1));

    return 0;*/
}
