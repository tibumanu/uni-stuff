using System;
using System.Net.Security;
using System.Net.Sockets;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

class AsyncAwaitDownloader  // TcpClient
{
    public async Task DownloadAsync(string url, int port, int maxRedirects = 5)
    {
        if (maxRedirects <= 0)
        {
            Console.WriteLine("Too many redirects. Aborting.");
            return;
        }

        // Parse the URL to extract components like host and path.
        var uri = new Uri(url); 

        using var client = new TcpClient();
        await client.ConnectAsync(uri.Host, port);

        // NetworkStream for reading and writing data.
        using NetworkStream networkStream = client.GetStream();
        Stream stream = networkStream;

        // Use SslStream for HTTPS connections
        if (uri.Scheme == Uri.UriSchemeHttps)
        {
            var sslStream = new SslStream(networkStream, false, new RemoteCertificateValidationCallback(ValidateServerCertificate), null);
            await sslStream.AuthenticateAsClientAsync(uri.Host);
            stream = sslStream;
        }

        string request = $"GET {uri.PathAndQuery} HTTP/1.1\r\n" +
                         $"Host: {uri.Host}\r\n" +
                         "Connection: close\r\n\r\n"; // Indicates to close the connection after the response.
        byte[] requestBytes = Encoding.ASCII.GetBytes(request); // Convert the request string into a byte array.

        await stream.WriteAsync(requestBytes, 0, requestBytes.Length); // Send the HTTP request to the server.

        byte[] buffer = new byte[8192]; // Allocate a buffer to store the server's response.
        int bytesRead = await stream.ReadAsync(buffer, 0, buffer.Length); // Receive the response into the buffer.

        if (bytesRead > 0) // If data was successfully received.
        {
            string response = Encoding.ASCII.GetString(buffer, 0, bytesRead); // Decode the received bytes into a string.
            Console.WriteLine("Response:");
            Console.WriteLine(response); // Print the entire HTTP response (headers + body).

            // Parse the HTTP response into headers and body.
            string[] headerParts = response.Split(new[] { "\r\n\r\n" }, 2, StringSplitOptions.None);
            string headers = headerParts[0]; // Everything before \r\n\r\n is the headers.
            string body = headerParts.Length > 1 ? headerParts[1] : ""; // The rest is the body (if present).

            Console.WriteLine("Headers:");
            Console.WriteLine(headers); // Print the headers.

            // Check for the HTTP status code.
            string[] statusLine = headers.Split("\r\n")[0].Split(" ");
            int statusCode = int.Parse(statusLine[1]);

            if (statusCode == 301 || statusCode == 302) // Handle redirect status codes.
            {
                string locationHeader = Array.Find(headers.Split("\r\n"), line => line.StartsWith("Location:"));
                if (!string.IsNullOrEmpty(locationHeader))
                {
                    string newUrl = locationHeader.Split(": ")[1];
                    Console.WriteLine($"Redirecting to {newUrl}");
                    var newUri = new Uri(newUrl);
                    int newPort = newUri.Scheme == "https" ? 443 : 80; // Determine the new port based on the scheme.
                    await DownloadAsync(newUrl, newPort, maxRedirects - 1); // Recursively call DownloadAsync with the new URL.
                }
            }
            else
            {
                // Check for the Content-Length header and parse its value.
                if (headers.Contains("Content-Length:"))
                {
                    string contentLengthLine = Array.Find(headers.Split("\r\n"), line => line.StartsWith("Content-Length:"));
                    int contentLength = int.Parse(contentLengthLine.Split(":")[1].Trim()); // Extract the content length value.
                    Console.WriteLine($"Content-Length: {contentLength}"); // Print the content length.
                }

                // Optionally, handle and display the response body here.
                Console.WriteLine("Body:");
                Console.WriteLine(body);
            }
        }
    }

    // Validate the server certificate (for demo purposes, always return true)
    private static bool ValidateServerCertificate(object sender, X509Certificate certificate, X509Chain chain, SslPolicyErrors sslPolicyErrors)
    {
        return true;
    }

    public static async Task RunSol()
    {
        Console.WriteLine("third task: async await");
        var downloader = new AsyncAwaitDownloader();
        await downloader.DownloadAsync("http://www.cnatdcu.ro", 80); // Start downloading a file from the specified URL.
    }
}
