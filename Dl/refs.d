import std.stdio;

void fun(ref uint x, double y)
{
  x = 52;
  y = 3.14;
}

void main()
{
  uint a = 1;
  double b = 4.13;
  fun(a, b);
  writeln(a, b);
}
