#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

////////////////////////////////////////////////
// C++14 "Generic Lambdas" demo code    
int GenericLambdas()
{
  auto func = [](int input){return input * input;};
  std::cout << func(10) << std::endl;

  std::vector<int> ivec = { 1, 2, 3, 4};
  std::vector<std::string> svec = { "red", "green", "blue" };

  auto adder  = [](auto op1, auto op2){ return op1 + op2; };

  std::cout << "int result : "
	<< std::accumulate(ivec.begin(), ivec.end(), 0, adder )
	<< "\n";
  std::cout << "string result : "
	<< std::accumulate(svec.begin(), svec.end(), std::string(""), adder )
	<< "\n";
  return 0;
}

// 真正泛型lambda的发光点是和STL结合使用的时候，如果你想以递减的顺序对一个vector排序，使用泛型lambda，我们可以这样写：
// std::sort(V.begin(), V.end(), [](auto i, auto j) { return (i > j); });
int ReverseVector() {
  std::vector<int> V(10);

  // Use std::iota to create a sequence of integers 0, 1, ...
  std::iota(V.begin(), V.end(), 1);

  // Print the unsorted data using std::for_each and a lambda
  std::cout << "Original data" << std::endl;
  std::for_each(V.begin(), V.end(), [](auto i) { std::cout << i << " "; });
  std::cout << std::endl;

  // Sort the data using std::sort and a lambda
  std::sort(V.begin(), V.end(), [](auto i, auto j) { return (i > j); });

  // Print the sorted data using std::for_each and a lambda
  std::cout << "Sorted data" << std::endl;
  std::for_each(V.begin(), V.end(), [](auto i) { std::cout << i << " "; });
  std::cout << std::endl;

  return 0;
}

////////////////////////////////////////////////
// C++14 "TypeInference" demo code    
struct record {
  std::string name;
  int id;
};

auto find_id(const std::vector<record> &people,
	const std::string &name)
{
  auto match_name = [&name](const record& r) -> bool {
	return r.name == name;
  };
  auto ii = find_if(people.begin(), people.end(), match_name );
  if (ii == people.end())
	return -1;
  else
	return ii->id;
}

int TypeInference()
{
  std::vector<record> roster = { {"mark",1},
	{"bill",2},
	{"ted",3}};
  std::cout << find_id(roster,"bill") << "\n";
  std::cout << find_id(roster,"ron") << "\n";
  return 0;
}

////////////////////////////////////////////////
// C++14 "auto" demo code    

auto& add_one(std::vector<int>& v) {
  for(auto& it : v) {
	it += 1;
  }
  return v;
}

void multiply_by_two(std::vector<int>& v) {
  for(auto& it : v) {
	it *= 2;
  }    
}

void print_vec(const std::vector<int>& v) {
  for(const auto& e: v) {
	std::cout << e << std::endl;
  }   
  std::cout << std::endl;     
}

int TestAuto() {

  // Add one and multiply by two a vector of integers
  std::vector<int> my_vector{-1, 2, 3, 5};
  multiply_by_two(add_one(my_vector));    
  print_vec(my_vector);

  return 0;
}

////////////////////////////////////////////////
int main()
{
//   GenericLambdas();
//   ReverseVector();
  TestAuto();
}

