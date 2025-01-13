namespace try2
{
    internal class Program
    {
        static async Task Main(string[] args)
        {
            Console.WriteLine("1. callback");
            Console.WriteLine("2. tasks");
            Console.WriteLine("3. async await");
            
            string choice = Console.ReadLine();
            switch (choice)
            {
                case "1":
                    PPDLab4.Program.RunSol();
                    break;
                case "2":
                    await TaskBasedDownloader.RunSol();
                    break;
                case "3":
                    await AsyncAwaitDownloader.RunSol();
                    break;
                default:
                    Console.WriteLine("invalid choice;");
                    break;
            }
        }
    }
}
