import std.stdio;

void main()
{
  immutable inches_per_foot = 12;
  immutable cm_per_inch = 2.54;
  foreach (feet; 0 .. 9)
  {
    foreach (inches; 0 .. inches_per_foot)
    {
      writeln(feet, "`", inches, "``\t", (feet * inches_per_foot + inches) * cm_per_inch);
    }
  }
}
