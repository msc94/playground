using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;
using System.Text;

namespace csvtest
{
    class StringStreamReader
    {
        private string _data;
        private int _pos = 0;

        public StringStreamReader(string data)
        {
            _data = data;
        }

        public int Peek()
        {
            if (_pos >= _data.Length)
            {
                return -1;
            }

            return _data[_pos];
        }

        public int Read()
        {
            if (_pos >= _data.Length)
            {
                return -1;
            }
            
            return _data[_pos++];
        }
    }

    class CsvParser
    {
        private string _path;

        class ConfigurationProperties
        {
            public char Delimiter { get; } = ';';
            public char Quote { get; } = '"';
        }
        ConfigurationProperties Configuration { get; } = new ConfigurationProperties();

        public CsvParser()
        {
        }

        public List<List<string>> GetDataFromString(string data)
        {
            return GetData(new StringStreamReader(data));
        }

        public List<List<string>> GetData(StringStreamReader reader)
        {
            var rows = new List<List<string>>();
            while (true)
            {
                var row = ReadLine(reader);
                rows.Add(row);

                if (reader.Peek() == -1)
                {
                    break;
                }
            }
            return rows;
        }

        public List<string> ReadLine(StringStreamReader reader)
        {
            var row = new List<string>();

            while (true)
            {
                string field = ReadField(reader);
                row.Add(field);

                var c = reader.Peek();
                if (c == '\r' || c == '\n')
                {
                    break;
                }
            }

            ConsumeNewLine(reader);
            return row;
        }

        public string ReadField(StringStreamReader reader)
        {
            var c = reader.Peek();

            if (c == Configuration.Quote)
            {
                return ReadFieldQuoted(reader);
            }

            return ReadFieldUnquoted(reader);
        }

        public string ReadFieldQuoted(StringStreamReader reader)
        {
            var sb = new StringBuilder();

            var c = reader.Read();
            Debug.Assert(c == Configuration.Quote);

            while (true)
            {
                c = reader.Peek();

                if (c == Configuration.Quote)
                {
                    // Consume quote
                    reader.Read();

                    var next = reader.Peek();
                    if (next == Configuration.Quote)
                    {
                        // Double Quote. Add one to string, ignore the other
                    }
                    else if (next == Configuration.Delimiter)
                    {
                        // Consume Delimiter before returning
                        reader.Read();
                        break;
                    }
                    else
                    {
                        Debug.Assert(false);
                    }
                }

                if (c == '\r' || c == '\n')
                {
                    // Newline is just a normal character in a quote. Add to sb.
                }

                sb.Append((char)c);
                reader.Read();
            }
            return sb.ToString();
        }

        public string ReadFieldUnquoted(StringStreamReader reader)
        {
            var sb = new StringBuilder();
            while (true)
            {
                var c = reader.Peek();

                if (c == '\r' || c == '\n')
                {
                    break;
                }

                if (c == Configuration.Delimiter)
                {
                    // Consume Delimiter
                    reader.Read();
                    break;
                }

                sb.Append((char)c);
                reader.Read();
            }
            return sb.ToString();
        }

        private void ConsumeNewLine(StringStreamReader reader)
        {
            if (reader.Peek() == '\r')
            {
                reader.Read();
            }

            bool consumed = false;
            if (reader.Peek() == '\n')
            {
                consumed = true;
                reader.Read();
            }

            Debug.Assert(consumed);
            return;
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            DB.ImportCsv();
            return;

            var sw = new Stopwatch();

            var path = @"E:\Windows10_Arbeit\share\ms\projects\SLR_Analyse\in\Strukturbericht_PLM_R_LKS_20180313_ungefiltert.csv";
            var data = File.ReadAllText(path);

            sw.Start();
            var csvParser = new CsvParser();
            var rows = csvParser.GetDataFromString(data);
            sw.Stop();

            Console.WriteLine($"Took {sw.Elapsed.TotalSeconds} s");

            foreach (var row in rows)
            {
                foreach (var column in row)
                {
                    // if (column == "Hello")
                    // {
                    //     Console.WriteLine("Hello World");
                    // }
                    Console.WriteLine(column);
                }
            }
        }
    }
}
