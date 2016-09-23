
#include <iostream>

using namespace std;

int g_cnt = 0;

class A 
{
public:
  A()
  {
	cout << "construct:" << g_cnt <<  endl;
  }
  ~A()
  {
	cout << "distruct:" <<  g_cnt <<  endl;
  }
};


int main()
{
  for (int i=0; i < 10; i++)
  {
  	A a;
	g_cnt++;
  }

  return 0;
}
