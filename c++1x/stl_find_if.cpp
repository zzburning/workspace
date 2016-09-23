/*
   有时我们要在map、vector容器中查找符合条件的记录，map提供一个find的成员函数，但也仅限于查找关键字满足条件的记录，
   不支持值域的比较。如果我们要在值域中查找记录，该函数就无能无力了。而vector甚至连这样的成员函数都没有提供。
   所以一般情况下进行值域的查找，要么自己遍历数据，要么求助于STL的find_if函数。
   而且find()函数只能处理简单类型的内容，也就是缺省类型，如果你想用一个自定义类型的数据作为查找依据则会出错！
   这里将讲述另外一个函数find_if()的用法。 这是find()的一个更强大的版本。这个例子演示了find_if()，
   它接收一个函数对象的参数作为参数， 并使用它来做更复杂的评价对象是否和给出的查找条件相付。
   假设我们的list中有一些按年代排列的包含了事件和日期的记录。我们希望找出发生在1997年的事件。
 *
 *
 find_if的STL定义
 template <class InputIterator, class Predicate>
 InputIterator find_if(InputIterator first, InputIterator last,Predicate pred)
 {
 while (first != last && !pred(*first)) ++first;
 return first;
 }

 find_if是一个模板函数，接受两个数据类型：InputItearator迭代器，Predicate用于比较数值的函数或者函数对象（仿函数）。
 find_if对迭代器要求很低，只需要它支持自增操作即可。当前遍历到的记录符合条件与否，判断标准就是使得pred()为真。
 至此可能还有些不是很明了，下面举几个例子实际操练下的它的用法
 */
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

//find_if()的第三个参数是EventIsIn1997()，它是个仿函数，接收一个string对象，在运算符()的内部定义我所要的查找条件，
//本例的查找条件是：EventRecord.substr(11,4)=="1997"，注意，这里的仿函数返回类型必须是bool类型，
//这客观反应在find_if()函数查找过程中的是否匹配！
class EventIsIn1997 {
  public: 
	bool operator () (string& EventRecord) {
	  // year field is at position 12 for 4 characters in EventRecord
	  return EventRecord.substr(11,4)=="1997";
	  //return this->substr(11,4)=="1997"
	}
};

int find_if_basic (void) 
{
  list<string> Events;

  // string positions 0123456789012345678901234567890123456789012345
  Events.push_back("07 January 1995 Draft plan of house prepared");
  Events.push_back("07 February 1996 Detailed plan of house prepared");
  Events.push_back("10 January 1997 Client agrees to job");
  Events.push_back("15 January 1997 Builder starts work on bedroom");
  Events.push_back("30 April 1997 Builder finishes work");

  list<string>::iterator EventIterator = find_if (Events.begin(), Events.end(), EventIsIn1997());

  // find_if completes the first time EventIsIn1997()() returns true
  // for any object. It returns an iterator to that object which we
  // can dereference to get the object, or if EventIsIn1997()() never
  // returned true, find_if returns end()
  if (EventIterator==Events.end()) {
	cout << "Event not found in list" << endl;
  }
  else {
	cout << *EventIterator << endl;
  }
  return 0;
}
//自定义结构体查找过程
//在这里，我们同样构造了一个仿函数，也就是class vector_finder，也就是vector_finder()函数，
//注意它的结构与我们要查找的结构体之间的关系，我们发现，它们是非常相象的。 这里的重点就在于class vector_finder的构造！
struct value_t
{
  int a;
  int b;
};

class vector_finder
{
  public:
	vector_finder( const int a, const int b ) :m_v_a(a),m_v_b(b){}
	bool operator ()( vector<struct value_t>::value_type &value)
	{
	  return (value.a==m_v_a)&&(value.b = m_v_b);
	}
  private:
	int m_v_a;
	int m_v_b;
};

int find_if_vector()
{
  vector<value_t> my_vector;
  value_t my_value;

  my_value.a = 11; my_value.b = 1001;
  my_vector.push_back(my_value);

  my_value.a = 12; my_value.b = 1002;
  my_vector.push_back(my_value);

  my_value.a = 13; my_value.b = 1003;
  my_vector.push_back(my_value);

  my_value.a = 14; my_value.b = 1004;
  my_vector.push_back(my_value);

  vector<value_t>::iterator it = find_if( my_vector.begin(), my_vector.end(), vector_finder(13,1003));
  if( it == my_vector.end() )
	cout<<"not found!"<<endl;
  else
	cout<<"found value a:"<<(*it).a <<", b:"<<(*it).b<<endl;
  return 0;
}

//在map容器中的应用：
//class map_finder即用于比较的函数对象，它的核心就是重载的()运算符。因为每个容器迭代器的*运算符得到的结果
//都是该容器的value_type值，所以该运算符的形参就是map迭代器指向的value_type类型的引用。
//而map的value_type到底是什么类型，就得看下STL的源代码是如何定义
class map_finder
{
  public:
	map_finder( string cmp_string ) : m_string(cmp_string) {}
	bool operator () (const map<int,string>::value_type pair)
	{
	  return pair.second == m_string;
	}
  private:
	string m_string;
};

int find_if_map()
{
  map<int ,string> my_map;
  my_map.insert( make_pair(10,"china"));
  my_map.insert( make_pair(20,"usa"));
  my_map.insert( make_pair(30,"english"));
  my_map.insert( make_pair(40,"hongkong"));

  map<int,string>::iterator it = find_if(my_map.begin(),my_map.end(),map_finder("english"));
  if( it == my_map.end() )
	cout<<"not found!"<<endl;
  else
	cout<<"found key:"<<(*it).first<<", value:"<<(*it).second<<endl;
  return 0;
}

int main()
{
  find_if_basic();
  find_if_map();
  find_if_vector();
}

