namespace Data_Compression_Module
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Text;

    public class HuffmanNode
    {
        public char Symbol { get; set; }
        public int Frequency { get; set; }
        public HuffmanNode? Left { get; set; }
        public HuffmanNode? Right { get; set; }


        private static HuffmanNode BuildHuffmanTree(string inputText){
            // Count the frequency of each character in the input text
            Dictionary<char, int> charFrequencies = new Dictionary<char, int>();
            foreach (char c in inputText){
                if (charFrequencies.ContainsKey(c)){
                    charFrequencies[c]++;
                }
                else{
                    charFrequencies[c] = 1;
                }
            }

            // create a priority queue (min heap) to store Huffman tree nodes
            PriorityQueue<HuffmanNode, int> priorityQueue = new PriorityQueue<HuffmanNode, int>();

            // create a leaf node for each character and add it to the priority queue
            foreach (var entry in charFrequencies){
                priorityQueue.Enqueue(new HuffmanNode { Symbol = entry.Key, Frequency = entry.Value }, entry.Value);
            }

            // Build the Huffman tree by combining the two nodes with the lowest frequencies
            while (priorityQueue.Count > 1){
                HuffmanNode left = priorityQueue.Dequeue();
                HuffmanNode right = priorityQueue.Dequeue();

                HuffmanNode parent = new HuffmanNode{
                    Symbol = '\0', // internal node doesn't contain actual data
                    Frequency = left.Frequency + right.Frequency,
                    Left = left,
                    Right = right
                };

                priorityQueue.Enqueue(parent, parent.Frequency);
            }

            // remaining node in the priority queue is the root of the Huffman tree
            return priorityQueue.Dequeue();
        }

        public static void Compress(string inputFilePath, string outputFilePath)
        {
            // read input text from file
            string inputText = File.ReadAllText(inputFilePath);

            // build Huffman tree
            HuffmanNode root = BuildHuffmanTree(inputText);

            // generate Huffman codes
            Dictionary<char, string> encodingMap = GenerateHuffmanCodes(root);

            // encode input text
            string encodedData = Encode(inputText, encodingMap);

            // write Huffman tree structure and compressed data to output file
            using (FileStream fs = new FileStream(outputFilePath, FileMode.Create))
            using (BinaryWriter writer = new BinaryWriter(fs)){
                // serialize Huffman tree structure
                SerializeHuffmanTree(root, writer);

                // write length of encoded data
                writer.Write(encodedData.Length);

                // write encoded data
                writer.Write(encodedData);
            }
        }

        public static void Decompress(string inputFilePath, string outputFilePath){
            using FileStream fs = new FileStream(inputFilePath, FileMode.Open);
            using BinaryReader reader = new BinaryReader(fs);
            // deserialize Huffman tree structure
            HuffmanNode root = DeserializeHuffmanTree(reader);

            // read length of encoded data
            int encodedDataLength = reader.ReadInt32();

            // read encoded data
            byte[] encodedDataBytes = reader.ReadBytes(encodedDataLength + 1);
            string encodedData = Encoding.UTF8.GetString(encodedDataBytes);

            // decode the compressed data using the Huffman tree
            string decodedData = Decode(encodedData, root);
            //Console.WriteLine(decodedData);

            // write the decompressed data to the output file
            File.WriteAllText(outputFilePath, decodedData);
        }

        private static void SerializeHuffmanTree(HuffmanNode root, BinaryWriter writer){
            if (root == null)
            {
                writer.Write(false); // Node is null
                return;
            }

            writer.Write(true); // Node is not null
            writer.Write(root.Symbol);
            writer.Write(root.Frequency);

            SerializeHuffmanTree(root.Left, writer);
            SerializeHuffmanTree(root.Right, writer);
        }

        private static HuffmanNode DeserializeHuffmanTree(BinaryReader reader)
        {
            if (!reader.ReadBoolean()) // Node is null
                return null;

            char symbol = reader.ReadChar();
            int frequency = reader.ReadInt32();

            HuffmanNode node = new HuffmanNode
            {
                Symbol = symbol,
                Frequency = frequency,
                Left = DeserializeHuffmanTree(reader),
                Right = DeserializeHuffmanTree(reader)
            };

            return node;
        }

        private static Dictionary<char, string> GenerateHuffmanCodes(HuffmanNode root){
            Dictionary<char, string> huffmanCodes = new Dictionary<char, string>();
            GenerateHuffmanCodesRecursive(root, "", huffmanCodes);
            //Console.WriteLine(huffmanCodes.ToArray().ToString());
            return huffmanCodes;
        }

        private static void GenerateHuffmanCodesRecursive(HuffmanNode node, string code, Dictionary<char, string> huffmanCodes){
            if (node == null)
                return;

            // if the node is a leaf, it represents a character with its Huffman code
            if (node.Left == null && node.Right == null)
            {
                huffmanCodes[node.Symbol] = code;
            }

            // traverse left subtree with code '0' appended
            GenerateHuffmanCodesRecursive(node.Left, code + "0", huffmanCodes);
            // traverse right subtree with code '1' appended
            GenerateHuffmanCodesRecursive(node.Right, code + "1", huffmanCodes);
        }

        private static string Encode(string inputText, Dictionary<char, string> encodingMap){
            StringBuilder encodedData = new StringBuilder();
            foreach (char character in inputText){
                if (encodingMap.ContainsKey(character)){
                    encodedData.Append(encodingMap[character]);
                    //Console.WriteLine(encodedData.ToString());
                }
                else{
                    // character is not found in encoding map
                    // this could occur if the character was not present in the input text used to build the Huffman tree
                    throw new ArgumentException($"Character '{character}' not found in Huffman encoding map.");
                }
            }
            //// add end-of-data marker (for example, adding '1' until the length is a multiple of 8)
            //int paddingLength = (8 - encodedData.Length % 8) % 8;
            //encodedData.Append('0', paddingLength);
            return (encodedData.ToString() + '\0');
        }

        private static string Decode(string encodedData, HuffmanNode root){
            StringBuilder decodedText = new StringBuilder();
            HuffmanNode current = root;

            int currentIndex = 0;
            while (currentIndex < encodedData.Length){
                char bit = encodedData[currentIndex];
                if (bit == '0'){
                    current = current.Left;
                }
                else if (bit == '1'){
                    current = current.Right;
                }

                // check if we have reached a leaf node
                if (current.Left == null && current.Right == null){
                    // Found a character, append it to the decoded text
                    decodedText.Append(current.Symbol);
                    // Reset to the root for the next character
                    current = root;
                }
                //else if (bit == '0' && current.Left == null && current.Right == null){
                //    break; // stop decoding, reached end marker
                //}
                currentIndex++;
            }

            return decodedText.ToString();
        }



    }
    internal class Program
    {
        static void Main(string[] args)
        {
            string inputFilePath = "C:\\sem4\\ISS\\DCmodule\\Data Compression Module\\Data Compression Module\\input.txt";
            string compressedFilePath = "compressed.bin";
            string decompressedFilePath = "decompressed.txt";

            // compress the input text
            HuffmanNode.Compress(inputFilePath, compressedFilePath);
            Console.WriteLine("Compression completed.");

            // decompress the compressed file
            HuffmanNode.Decompress(compressedFilePath, decompressedFilePath);
            Console.WriteLine("Decompression completed.");

            // read original input text
            string originalInputText = File.ReadAllText(inputFilePath);

            // read decompressed text
            string decompressedText = File.ReadAllText(decompressedFilePath);

            Console.WriteLine($"\nORIGINAL BODY\n{originalInputText} \n\n\nDECOMPRESSED BODY\n{decompressedText}\n");


            Console.WriteLine("RESULT: ");
            if (originalInputText == decompressedText)
            {
                Console.WriteLine("Decompressed text matches original input text.");
            }
            else
            {
                Console.WriteLine("Decompressed text does not match original input text.");
            }
        }
    }
}
