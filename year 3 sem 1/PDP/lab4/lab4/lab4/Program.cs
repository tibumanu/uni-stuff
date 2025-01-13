using System;
using lab4.socket;
using lab4.parser;
using System.Collections.Generic;

namespace lab4
{
    internal class Program
    {
        private static readonly List<string> Urls = new()
        {
            "http://www.cnatdcu.ro",

        };

        static void Main()
        {
            Console.WriteLine("1. Callback Parser");
            Console.WriteLine("2. Task Parser");
            Console.WriteLine("3. Async Await Parser");
            string choice = Console.ReadLine();
            switch (choice)
            {
                case "1":
                    try { new CallbackSolution(Urls); }
                    catch (Exception e) { Console.WriteLine(e.Message); }
                    break;
                case "2":
                    //new TaskSolution(Urls);
                    break;
                case "3":
                    //new AsyncAwaitSolution(Urls);
                    break;
                default:
                    Console.WriteLine("Invalid choice");
                    break;
            }
        }
    }
}
