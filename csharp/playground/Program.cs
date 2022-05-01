using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace playground
{
    class Program
    {
        public static void TestFunction(Object o)
        {
            if (o.GetType() == typeof(string))
            {
                Console.Write($"String: {(string) o}\n");
            }
            else if (o is int i)
            {
                Console.Write($"Int: {i}\n");
            }
        }
        public static void Main(string[] args)
        {
            TestFunction(12);
            TestFunction("asdf");
        }
    }
}
