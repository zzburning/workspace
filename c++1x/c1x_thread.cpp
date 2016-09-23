int main()
{
  std::thread th([](){std::cout << "I'm a thread." << std::endl;});
  th.join();
}
