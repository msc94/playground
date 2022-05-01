using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace playground
{
    class MyClipboard
    {
        public List<List<string>> GetTableFromClipboard()
        {
            if (!Clipboard.ContainsData("HTML Format"))
            {
                Console.WriteLine("Clipboard does not contain HTML data.");
                return new List<List<string>>();
            }

            var clipboardHtmlData = Clipboard.GetData("HTML Format");
            if (clipboardHtmlData == null)
            {
                Console.WriteLine("Clipboard html data was null.");
                return new List<List<string>>();
            }

            var clipboardHtml = clipboardHtmlData.ToString();
            var htmlDocument = new HtmlAgilityPack.HtmlDocument();
            htmlDocument.LoadHtml(clipboardHtml);

            var rows = new List<List<string>>();

            var root = htmlDocument.DocumentNode;
            foreach (var row in root.Descendants("tr"))
            {
                var columns = new List<string>();
                foreach (var column in row.Descendants("td"))
                {
                    var columnText = column.InnerText;
                    columnText = columnText.Trim();
                    columnText = HtmlAgilityPack.HtmlEntity.DeEntitize(columnText);
                    columns.Add(columnText);
                }
                rows.Add(columns);
            }

            // Make sure we have at least one row
            if (rows.Count == 0)
            {
                return new List<List<string>>();
            }

            // Delete fully empty rows
            rows = rows.Where(r => r.Count > 0).ToList();

            // Make sure the structure is rectangular
            if (rows.Any(r => r.Count != rows[0].Count))
            {
                return new List<List<string>>();
            }

            return rows;
        }

        public void Query()
        {
            var rows = GetTableFromClipboard();
            foreach (var row in rows)
            {
                foreach (var column in row)
                {
                    Console.Write(column);
                    Console.Write("\t");
                }
                Console.WriteLine();
            }
        }
    }
}
