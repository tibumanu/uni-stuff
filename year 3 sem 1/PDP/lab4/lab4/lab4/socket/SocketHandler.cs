using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace lab4.socket
{
    public class SocketHandler
    {
        public string Id { get; }
        public string BaseUrl { get; }
        public string UrlPath { get; }
        public Socket Socket { get; }
        public byte[] Buffer { get; }
        public StringBuilder ResponseContent { get; }

        // Constructor for SocketHandler
        public SocketHandler(Socket socket, string baseUrl, string urlPath)
        {
            Socket = socket;
            Id = Guid.NewGuid().ToString(); // Unique identifier for each connection
            BaseUrl = baseUrl;
            UrlPath = urlPath;
            Buffer = new byte[1024]; // Buffer for receiving data
            ResponseContent = new StringBuilder();
        }

        public void BeginConnect(IPEndPoint endPoint, AsyncCallback callback)
        {
            Socket.BeginConnect(endPoint, callback, this);  // Begin the connection
        }

        public void BeginSend(byte[] data, AsyncCallback callback)
        {
            Socket.BeginSend(data, 0, data.Length, SocketFlags.None, callback, this); // Begin sending data
        }

        public void BeginReceive(AsyncCallback callback)
        {
            Socket.BeginReceive(Buffer, 0, Buffer.Length, SocketFlags.None, callback, this); // Begin receiving data
        }

        public void ShutdownAndClose()
        {
            Socket.Shutdown(SocketShutdown.Both);
            Socket.Close(); // Shutdown and close the socket
        }
    }
}
