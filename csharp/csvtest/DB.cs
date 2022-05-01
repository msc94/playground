using System;
using System.Collections.Generic;
using System.Data;
using System.Diagnostics;
using Microsoft.Data.Sqlite;
using CsvHelper;
using System.IO;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

class DB
{
    private static string GetConnectionString()
    {
        return "Data Source=./data/hello.db";
    }

    private static SqliteConnection GetConnection()
    {
        return new SqliteConnection(GetConnectionString());
    }

    public static void CreateTable()
    {
        using (var conn = GetConnection())
        {
            conn.Open();
            using (var comm = conn.CreateCommand())
            {
                // Drop Table if present
                comm.CommandText = "DROP TABLE IF EXISTS CsvImport;";
                comm.ExecuteNonQuery();

                comm.CommandText = @"
                    CREATE TABLE 'CsvImport' (
                        'LINECNT'	TEXT,
                        'DUMMY_AEND'	TEXT,
                        'CHANGE'	TEXT,
                        'CLASS'	TEXT,
                        'MODUL4'	TEXT,
                        'MODUL4_T'	TEXT,
                        'KO_BEREICH'	TEXT,
                        'MODUL1'	TEXT,
                        'PPG1'	TEXT,
                        'HIERST_BAU'	TEXT,
                        'MATERIAL'	TEXT,
                        '/BMW/PEPK_BKPROD'	TEXT,
                        '/BMW/PEPK_BKPROD_BEZ'	TEXT,
                        '/BMW/PEP_DMU'	TEXT,
                        '/BMW/PEPZHIN'	TEXT,
                        '/BMW/PEPETYP'	TEXT,
                        '/BMW/PEPZF'	TEXT,
                        '/BMW/PEPSDKZ'	TEXT,
                        '/BMW/PEP_ESDKZ'	TEXT,
                        '/BMW/PEPGEFAHRKZ'	TEXT,
                        '/BMW/PEPBA'	TEXT,
                        '/BMW/PEPTA'	TEXT,
                        '/BMW/PEPCH'	TEXT,
                        '/BMW/PEPCODKZ'	TEXT,
                        '/BMW/PEPLIRE'	TEXT,
                        '/BMW/PEPFKZ'	TEXT,
                        '/BMW/PEP_EXC'	TEXT,
                        '/BMW/PEP_EXC_BEZ'	TEXT,
                        '/BMW/PEP_VCR'	TEXT,
                        '/BMW/PEPAI'	TEXT,
                        '/BMW/PEPZI'	TEXT,
                        '/BMW/PEP_VZK'	TEXT,
                        '/BMW/PEP_ITMSKZ'	TEXT,
                        'VORKOMM_ALT'	TEXT,
                        'PNAME_00'	TEXT,
                        'PNAME_01'	TEXT,
                        'PNAME_02'	TEXT,
                        'PNAME_03'	TEXT,
                        'PNAME_04'	TEXT,
                        'PNAME_05'	TEXT,
                        'PNAME_06'	TEXT,
                        'PNAME_07'	TEXT,
                        'PNAME_08'	TEXT,
                        'PNAME_09'	TEXT,
                        'PNAME_10'	TEXT,
                        'PNAME_11'	TEXT,
                        'PNAME_12'	TEXT,
                        'PNAME_13'	TEXT,
                        'NACHKOMM_ALT'	TEXT,
                        'KNOWLEDGE'	TEXT,
                        'QUANT'	TEXT,
                        'QUNIT'	TEXT,
                        'FREIGABEHW'	TEXT,
                        'OBJNAME'	TEXT,
                        'AENR_ISTUFE_ALL'	TEXT,
                        'DUMMY_GEW_AENR'	TEXT,
                        'TAIS_GESCH'	TEXT,
                        'MSTAE'	TEXT,
                        'AENNR'	TEXT,
                        'AENST'	TEXT,
                        'DUMMY_SF'	TEXT,
                        'SFDB_PEP_KEY'	TEXT,
                        'SFDB_KEY'	TEXT,
                        'SFDB_BEM_NAME'	TEXT,
                        'SF_DIS'	TEXT,
                        'SFDB_TIGHTENED'	TEXT,
                        'SFDB_RIVET'	TEXT,
                        'SFDB_SETTING_FORCE'	TEXT,
                        'SFDB_SET_FORCE_DEV'	TEXT,
                        'SFDB_REUSE'	TEXT,
                        'SFDB_RSKL'	TEXT,
                        'SFDB_SELF_TAPPING'	TEXT,
                        'SFDB_SCREW_PROTECTION'	TEXT,
                        'SFDB_VSKL'	TEXT,
                        'SFDB_ANZVER_TXT'	TEXT,
                        'SFDB_ANZMNT'	TEXT,
                        'SFDB_ANZWKL'	TEXT,
                        'SFDB_WKLTOL'	TEXT,
                        'SFDB_ANZMNT_MAX_GES'	TEXT,
                        'SFDB_ELONG_MIN'	TEXT,
                        'SFDB_ELONG_MAX'	TEXT,
                        'SFDB_GRAD_SHUT_DOWN'	TEXT,
                        'SFDB_BEMERK'	TEXT,
                        'SFDB_SPEC_REWORK'	TEXT,
                        'SFDB_ZUL_SETZVER'	TEXT,
                        'SFDB_SPEC_SERVICE'	TEXT,
                        'SFDB_BEMERK_SERV'	TEXT,
                        'SFDB_KONST'	TEXT,
                        'SFDB_KONST_ABT'	TEXT,
                        'SFDB_DB_MOTORBIKE'	TEXT,
                        'DUMMY_PTEINFO_REL'	TEXT,
                        'DUMMY_PTEINFO_USA'	TEXT,
                        'DUMMY_PTEINFO_MEX'	TEXT,
                        'DUMMY_PTEINFO_ZAF'	TEXT,
                        'DUMMY_PTEINFO_CHN'	TEXT,
                        'DUMMY_PTE'	TEXT,
                        'PTE_ART'	TEXT,
                        'PTE_BAUORT_KZ'	TEXT,
                        'PTE_MO'	TEXT,
                        'PTE_LOCAL_CONT'	TEXT,
                        'PTE_DSNR'	TEXT,
                        'PTE_BEZUG'	TEXT,
                        'PTE_BEZ_ART'	TEXT,
                        'PTE_ABW_MENG'	TEXT,
                        'PTE_ABW_UNIT'	TEXT,
                        'PTE_TF_CODE'	TEXT,
                        'PTE_TF_MENGE'	TEXT,
                        'PTE_TF_UNIT'	TEXT,
                        'PTE_WB_MO'	TEXT,
                        'PTE_AENNR'	TEXT,
                        'DUMMY_HWS'	TEXT,
                        'HWS_ANORT'	TEXT,
                        'HWS_ANFORDERER'	TEXT,
                        'HWS_FREIGABE'	TEXT,
                        'HWS_KONSTRUKTION'	TEXT,
                        'HWS_SGEVOR'	TEXT,
                        'HWS_VBORT'	TEXT,
                        'HWS_AOGEVOR'	TEXT,
                        'DUMMY_QSERV'	TEXT,
                        'KLAMM_AUS'	TEXT,
                        'SB_T_BEZ'	TEXT,
                        'GEN_TEIL_SB_T_BEZ'	TEXT,
                        'GEN_TEIL'	TEXT,
                        'GEN_TEIL_ID'	TEXT,
                        'GEN_SB_TEXT'	TEXT,
                        'GEN_TEIL_BEZEI'	TEXT,
                        'GEN_TEIL_NR'	TEXT,
                        'KL_BEZWI'	TEXT,
                        'KLAMM_BEZEI'	TEXT,
                        'LI_RE_KENNZ'	TEXT,
                        'UNTERBEZ'	TEXT,
                        'BEZEI'	TEXT,
                        'KLGR_BEZWI'	TEXT,
                        'KGA_BEZEI'	TEXT,
                        'KGA_BEZWI'	TEXT,
                        'KLGR_NR'	TEXT,
                        'DUMMY_BEMERKUNG'	TEXT,
                        'DUMMY_VERFUEG_SERIE'	TEXT,
                        'DUMMY_VERFUEG_ERSATZ'	TEXT,
                        'DUMMY_DH'	TEXT,
                        'DUMMY_LIEF'	TEXT,
                        'SNR_EXT'	TEXT,
                        'TEIL_BEN_EXT'	TEXT,
                        'LIEF_NAM'	TEXT,
                        'DUMMY_MMG_REVIEW'	TEXT,
                        'DUMMY_MMG_REV_BEFUND'	TEXT,
                        'DUMMY_MMG_REV_MASSN'	TEXT,
                        'DUMMY_MMG_REV_NAEL'	TEXT,
                        'DUMMY_MMG_REV_VERANTW'	TEXT,
                        'DUMMY_MMG_REV_ZIELT'	TEXT,
                        'DUMMY_MMG_REV_STATUS'	TEXT
                    );";
                comm.ExecuteNonQuery();
            }
        }

    }

    public static List<List<string>> ParseCsv()
    {
        var tr = File.OpenText("./data/Mappe3.csv");

        var parser = new CsvHelper.CsvParser(tr, CultureInfo.InvariantCulture);
        parser.Configuration.Delimiter = ";";

        var ret = new List<List<string>>();
        while (true)
        {
            var fields = parser.Read();
            if (fields == null)
            {
                break;
            }

            ret.Add(new List<string>(fields));
        }

        return ret;
    }

    public static void ImportCsv()
    {
        CreateTable();

        var csvData = ParseCsv();

        var columnCount = csvData[0].Count;
        if (csvData.Any(x => x.Count != columnCount))
        {
            throw new InvalidOperationException();
        }

        using (var conn = GetConnection())
        {
            Parallel.ForEach(csvData, x =>
            {
                using (var insertCommand = GetCommandString(conn, columnCount))
                {

                }
            });
            conn.Open();
            {
                var sw = new Stopwatch();
                insertCommand.Prepare();
                sw.Start();
                var transaction = conn.BeginTransaction();
                insertCommand.Transaction = transaction;
                foreach (var entry in csvData)
                {
                    for (int i = 0; i < columnCount; i++)
                    {
                        insertCommand.Parameters[i].Value = entry[i];
                    }
                    insertCommand.ExecuteNonQuery();
                }
                transaction.Commit();
                sw.Stop();
                Console.WriteLine($"Took {sw.Elapsed.TotalSeconds} s");
            }
        }
    }

    public static SqliteCommand GetCommandString(SqliteConnection conn, int parameterCount)
    {
        var comm = conn.CreateCommand();

        var sb = new StringBuilder();
        sb.Append("INSERT INTO 'CsvImport' VALUES (");
        for (int i = 0; i < parameterCount; i++)
        {
            sb.Append($"@{i}, ");
            comm.Parameters.Add($"{i}", SqliteType.Text);
        }
        sb.Remove(sb.Length - 2, 2);
        sb.Append(");");

        comm.CommandText = sb.ToString();
        return comm;
    }
}