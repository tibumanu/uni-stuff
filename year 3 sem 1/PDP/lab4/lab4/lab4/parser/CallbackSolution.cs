using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using lab4.socket;

namespace lab4.parser
{
    internal class CallbackSolution : Common
    {
        protected override string ParserType => "Callback";

        public CallbackSolution(List<string> urls) : base(urls)
        {
        }

        protected override void Run()
        {
            Console.WriteLine("Starting callback solution...");
            ForEach((index, url) =>
            {
                try
                {
                    Uri uri = new Uri(url);  // Use the Uri class to extract host and path
                    var host = uri.Host;
                    var path = uri.AbsolutePath;
                    var ipAddress = Dns.GetHostEntry(host).AddressList[0];

                    var socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                    var endPoint = new IPEndPoint(ipAddress, 80);  // Assume port 80 for HTTP
                    var socketHandler = new SocketHandler(socket, host, path);

                    Console.WriteLine($"Attempting to connect to {host} at {path}...");
                    var connectDone = new ManualResetEvent(false); // Synchronization object
                    socketHandler.BeginConnect(endPoint, ar => HandleConnected(ar, socketHandler, connectDone));
                    connectDone.WaitOne(); // Wait until the connection process completes
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Error while processing URL {url}: {ex.Message}");
                }
            });
        }

        private void HandleConnected(IAsyncResult ar, SocketHandler socketHandler, ManualResetEvent connectDone)
        {
            try
            {
                Console.WriteLine($"Connected to {socketHandler.BaseUrl}...");

                socketHandler.Socket.EndConnect(ar); // Complete connection
                LogConnected(socketHandler);

                string request = $"GET {socketHandler.UrlPath} HTTP/1.1\r\nHost: {socketHandler.BaseUrl}\r\n\r\n";
                byte[] requestData = Encoding.ASCII.GetBytes(request);
                Console.WriteLine($"Sending request: {request}");
                socketHandler.BeginSend(requestData, ar2 => HandleSent(ar2, socketHandler, connectDone));
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error during connection: {ex.Message}");
            }
        }

        private void HandleSent(IAsyncResult ar, SocketHandler socketHandler, ManualResetEvent connectDone)
        {
            try
            {
                int bytesSent = socketHandler.Socket.EndSend(ar);
                LogSent(socketHandler, bytesSent);
                Console.WriteLine($"Sent {bytesSent} bytes. Waiting for response...");
                socketHandler.BeginReceive(ar2 => HandleReceived(ar2, socketHandler, connectDone));
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error during sending: {ex.Message}");
            }
        }

        private void HandleReceived(IAsyncResult ar, SocketHandler socketHandler, ManualResetEvent connectDone)
        {
            try
            {
                int bytesReceived = socketHandler.Socket.EndReceive(ar);

                if (bytesReceived > 0)
                {
                    // Append the received data to the response content
                    socketHandler.ResponseContent.Append(Encoding.ASCII.GetString(socketHandler.Buffer, 0, bytesReceived));
                    Console.WriteLine($"Received {bytesReceived} bytes...");

                    // Continue receiving if more data is available
                    socketHandler.BeginReceive(ar2 => HandleReceived(ar2, socketHandler, connectDone));
                }
                else
                {
                    // No more data to receive, finalize the response
                    Console.WriteLine("No more data received, finalizing response...");
                    LogReceived(socketHandler); // Log full response content
                    Console.WriteLine("Response fully received:");
                    Console.WriteLine(socketHandler.ResponseContent.ToString());

                    // Shutdown and close the connection after receiving all data
                    Console.WriteLine("Closing connection...");
                    socketHandler.ShutdownAndClose();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error during receiving: {ex.Message}");
            }
            finally
            {
                connectDone.Set(); // Signal the operation is complete
            }
        }



    }
}
