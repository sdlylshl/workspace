using System;

using System.Text;

using System.IO;



namespace HelloCsharp.Utilities

{

    /// <summary>

    /// �ļ�������

    /// </summary>

    public static class DirFile

    {

        #region ���ָ��Ŀ¼�Ƿ����

        /// <summary>

        /// ���ָ��Ŀ¼�Ƿ����

        /// </summary>

        /// <param name="directoryPath">Ŀ¼�ľ���·��</param>

        /// <returns></returns>

        public static bool IsExistDirectory(string directoryPath)

        {

            return Directory.Exists(directoryPath);

        }

        #endregion



        #region ���ָ���ļ��Ƿ����,������ڷ���true

        /// <summary>

        /// ���ָ���ļ��Ƿ����,��������򷵻�true��

        /// </summary>

        /// <param name="filePath">�ļ��ľ���·��</param>        

        public static bool IsExistFile(string filePath)

        {

            return File.Exists(filePath);

        }

        #endregion



        #region ��ȡָ��Ŀ¼�е��ļ��б�

        /// <summary>

        /// ��ȡָ��Ŀ¼�������ļ��б�

        /// </summary>

        /// <param name="directoryPath">ָ��Ŀ¼�ľ���·��</param>        

        public static string[] GetFileNames(string directoryPath)

        {

            //���Ŀ¼�����ڣ����׳��쳣

            if (!IsExistDirectory(directoryPath))

            {

                throw new FileNotFoundException();

            }



            //��ȡ�ļ��б�

            return Directory.GetFiles(directoryPath);

        }

        #endregion



        #region ��ȡָ��Ŀ¼��������Ŀ¼�б�,��Ҫ����Ƕ�׵���Ŀ¼�б�,��ʹ�����ط���.

        /// <summary>

        /// ��ȡָ��Ŀ¼��������Ŀ¼�б�,��Ҫ����Ƕ�׵���Ŀ¼�б�,��ʹ�����ط���.

        /// </summary>

        /// <param name="directoryPath">ָ��Ŀ¼�ľ���·��</param>        

        public static string[] GetDirectories(string directoryPath)

        {

            try

            {

                return Directory.GetDirectories(directoryPath);

            }

            catch (IOException ex)

            {

                throw ex;

            }

        }

        #endregion



        #region ��ȡָ��Ŀ¼����Ŀ¼�������ļ��б�

        /// <summary>

        /// ��ȡָ��Ŀ¼����Ŀ¼�������ļ��б�

        /// </summary>

        /// <param name="directoryPath">ָ��Ŀ¼�ľ���·��</param>

        /// <param name="searchPattern">ģʽ�ַ�����"*"����0��N���ַ���"?"����1���ַ���

        /// ������"Log*.xml"��ʾ����������Log��ͷ��Xml�ļ���</param>

        /// <param name="isSearchChild">�Ƿ�������Ŀ¼</param>

        public static string[] GetFileNames(string directoryPath, string searchPattern, bool isSearchChild)

        {

            //���Ŀ¼�����ڣ����׳��쳣

            if (!IsExistDirectory(directoryPath))

            {

                throw new FileNotFoundException();

            }



            try

            {

                if (isSearchChild)

                {

                    return Directory.GetFiles(directoryPath, searchPattern, SearchOption.AllDirectories);

                }

                else

                {

                    return Directory.GetFiles(directoryPath, searchPattern, SearchOption.TopDirectoryOnly);

                }

            }

            catch (IOException ex)

            {

                throw ex;

            }

        }

        #endregion



        #region ���ָ��Ŀ¼�Ƿ�Ϊ��

        /// <summary>

        /// ���ָ��Ŀ¼�Ƿ�Ϊ��

        /// </summary>

        /// <param name="directoryPath">ָ��Ŀ¼�ľ���·��</param>        

        public static bool IsEmptyDirectory(string directoryPath)

        {

            try

            {

                //�ж��Ƿ�����ļ�

                string[] fileNames = GetFileNames(directoryPath);

                if (fileNames.Length > 0)

                {

                    return false;

                }



                //�ж��Ƿ�����ļ���

                string[] directoryNames = GetDirectories(directoryPath);

                if (directoryNames.Length > 0)

                {

                    return false;

                }



                return true;

            }

            catch

            {

                //�����¼��־

                //LogHelper.WriteTraceLog(TraceLogLevel.Error, ex.Message);

                return true;

            }

        }

        #endregion



        #region ���ָ��Ŀ¼���Ƿ����ָ�����ļ�

        /// <summary>

        /// ���ָ��Ŀ¼���Ƿ����ָ�����ļ�,��Ҫ������Ŀ¼��ʹ�����ط���.

        /// </summary>

        /// <param name="directoryPath">ָ��Ŀ¼�ľ���·��</param>

        /// <param name="searchPattern">ģʽ�ַ�����"*"����0��N���ַ���"?"����1���ַ���

        /// ������"Log*.xml"��ʾ����������Log��ͷ��Xml�ļ���</param>        

        public static bool Contains(string directoryPath, string searchPattern)

        {

            try

            {

                //��ȡָ�����ļ��б�

                string[] fileNames = GetFileNames(directoryPath, searchPattern, false);



                //�ж�ָ���ļ��Ƿ����

                if (fileNames.Length == 0)

                {

                    return false;

                }

                else

                {

                    return true;

                }

            }

            catch (Exception ex)

            {

                throw new Exception(ex.Message);

                //LogHelper.WriteTraceLog(TraceLogLevel.Error, ex.Message);

            }

        }



        /// <summary>

        /// ���ָ��Ŀ¼���Ƿ����ָ�����ļ�

        /// </summary>

        /// <param name="directoryPath">ָ��Ŀ¼�ľ���·��</param>

        /// <param name="searchPattern">ģʽ�ַ�����"*"����0��N���ַ���"?"����1���ַ���

        /// ������"Log*.xml"��ʾ����������Log��ͷ��Xml�ļ���</param> 

        /// <param name="isSearchChild">�Ƿ�������Ŀ¼</param>

        public static bool Contains(string directoryPath, string searchPattern, bool isSearchChild)

        {

            try

            {

                //��ȡָ�����ļ��б�

                string[] fileNames = GetFileNames(directoryPath, searchPattern, true);



                //�ж�ָ���ļ��Ƿ����

                if (fileNames.Length == 0)

                {

                    return false;

                }

                else

                {

                    return true;

                }

            }

            catch (Exception ex)

            {

                throw new Exception(ex.Message);

                //LogHelper.WriteTraceLog(TraceLogLevel.Error, ex.Message);

            }

        }

        #endregion



        #region ����Ŀ¼

        /// <summary>

        /// ����Ŀ¼

        /// </summary>

        /// <param name="dir">Ҫ������Ŀ¼·������Ŀ¼��</param>

        public static void CreateDir(string dir)

        {

            if (dir.Length == 0) return;

            if (!Directory.Exists(System.Web.HttpContext.Current.Request.PhysicalApplicationPath + "\\" + dir))

                Directory.CreateDirectory(System.Web.HttpContext.Current.Request.PhysicalApplicationPath + "\\" + dir);

        }

        #endregion



        #region ɾ��Ŀ¼

        /// <summary>

        /// ɾ��Ŀ¼

        /// </summary>

        /// <param name="dir">Ҫɾ����Ŀ¼·��������</param>

        public static void DeleteDir(string dir)

        {

            if (dir.Length == 0) return;

            if (Directory.Exists(System.Web.HttpContext.Current.Request.PhysicalApplicationPath + "\\" + dir))

                Directory.Delete(System.Web.HttpContext.Current.Request.PhysicalApplicationPath + "\\" + dir);

        }

        #endregion



        #region ɾ���ļ�

        /// <summary>

        /// ɾ���ļ�

        /// </summary>

        /// <param name="file">Ҫɾ�����ļ�·��������</param>

        public static void DeleteFile(string file)

        {

            if (File.Exists(System.Web.HttpContext.Current.Request.PhysicalApplicationPath + file))

                File.Delete(System.Web.HttpContext.Current.Request.PhysicalApplicationPath + file);

        }

        #endregion



        #region �����ļ�

        /// <summary>

        /// �����ļ�

        /// </summary>

        /// <param name="dir">����׺���ļ���</param>

        /// <param name="pagestr">�ļ�����</param>

        public static void CreateFile(string dir, string pagestr)

        {

            dir = dir.Replace("/", "\\");

            if (dir.IndexOf("\\") > -1)

                CreateDir(dir.Substring(0, dir.LastIndexOf("\\")));

            System.IO.StreamWriter sw = new System.IO.StreamWriter(System.Web.HttpContext.Current.Request.PhysicalApplicationPath + "\\" + dir, false, System.Text.Encoding.GetEncoding("GB2312"));

            sw.Write(pagestr);

            sw.Close();

        }

        #endregion



        #region �ƶ��ļ�(����--ճ��)

        /// <summary>

        /// �ƶ��ļ�(����--ճ��)

        /// </summary>

        /// <param name="dir1">Ҫ�ƶ����ļ���·����ȫ��(������׺)</param>

        /// <param name="dir2">�ļ��ƶ����µ�λ��,��ָ���µ��ļ���</param>

        public static void MoveFile(string dir1, string dir2)

        {

            dir1 = dir1.Replace("/", "\\");

            dir2 = dir2.Replace("/", "\\");

            if (File.Exists(System.Web.HttpContext.Current.Request.PhysicalApplicationPath + "\\" + dir1))

                File.Move(System.Web.HttpContext.Current.Request.PhysicalApplicationPath + "\\" + dir1, System.Web.HttpContext.Current.Request.PhysicalApplicationPath + "\\" + dir2);

        }

        #endregion



        #region �����ļ�

        /// <summary>

        /// �����ļ�

        /// </summary>

        /// <param name="dir1">Ҫ���Ƶ��ļ���·���Ѿ�ȫ��(������׺)</param>

        /// <param name="dir2">Ŀ��λ��,��ָ���µ��ļ���</param>

        public static void CopyFile(string dir1, string dir2)

        {

            dir1 = dir1.Replace("/", "\\");

            dir2 = dir2.Replace("/", "\\");

            if (File.Exists(System.Web.HttpContext.Current.Request.PhysicalApplicationPath + "\\" + dir1))

            {

                File.Copy(System.Web.HttpContext.Current.Request.PhysicalApplicationPath + "\\" + dir1, System.Web.HttpContext.Current.Request.PhysicalApplicationPath + "\\" + dir2, true);

            }

        }

        #endregion



        #region ����ʱ��õ�Ŀ¼�� / ��ʽ:yyyyMMdd ���� HHmmssff

        /// <summary>

        /// ����ʱ��õ�Ŀ¼��yyyyMMdd

        /// </summary>

        /// <returns></returns>

        public static string GetDateDir()

        {

            return DateTime.Now.ToString("yyyyMMdd");

        }

        /// <summary>

        /// ����ʱ��õ��ļ���HHmmssff

        /// </summary>

        /// <returns></returns>

        public static string GetDateFile()

        {

            return DateTime.Now.ToString("HHmmssff");

        }

        #endregion



        #region �����ļ���

        /// <summary>

        /// �����ļ���(�ݹ�)

        /// </summary>

        /// <param name="varFromDirectory">Դ�ļ���·��</param>

        /// <param name="varToDirectory">Ŀ���ļ���·��</param>

        public static void CopyFolder(string varFromDirectory, string varToDirectory)

        {

            Directory.CreateDirectory(varToDirectory);



            if (!Directory.Exists(varFromDirectory)) return;



            string[] directories = Directory.GetDirectories(varFromDirectory);



            if (directories.Length > 0)

            {

                foreach (string d in directories)

                {

                    CopyFolder(d, varToDirectory + d.Substring(d.LastIndexOf("\\")));

                }

            }

            string[] files = Directory.GetFiles(varFromDirectory);

            if (files.Length > 0)

            {

                foreach (string s in files)

                {

                    File.Copy(s, varToDirectory + s.Substring(s.LastIndexOf("\\")), true);

                }

            }

        }

        #endregion



        #region ����ļ�,����ļ��������򴴽�

        /// <summary>

        /// ����ļ�,����ļ��������򴴽�  

        /// </summary>

        /// <param name="FilePath">·��,�����ļ���</param>

        public static void ExistsFile(string FilePath)

        {

            //if(!File.Exists(FilePath))    

            //File.Create(FilePath);    

            //����д���ᱨ��,��ϸ�����뿴����.........   

            if (!File.Exists(FilePath))

            {

                FileStream fs = File.Create(FilePath);

                fs.Close();

            }

        }

        #endregion



        #region ɾ��ָ���ļ��ж�Ӧ�����ļ�������ļ�

        /// <summary>

        /// ɾ��ָ���ļ��ж�Ӧ�����ļ�������ļ�

        /// </summary>

        /// <param name="varFromDirectory">ָ���ļ���·��</param>

        /// <param name="varToDirectory">��Ӧ�����ļ���·��</param>

        public static void DeleteFolderFiles(string varFromDirectory, string varToDirectory)

        {

            Directory.CreateDirectory(varToDirectory);



            if (!Directory.Exists(varFromDirectory)) return;



            string[] directories = Directory.GetDirectories(varFromDirectory);



            if (directories.Length > 0)

            {

                foreach (string d in directories)

                {

                    DeleteFolderFiles(d, varToDirectory + d.Substring(d.LastIndexOf("\\")));

                }

            }





            string[] files = Directory.GetFiles(varFromDirectory);



            if (files.Length > 0)

            {

                foreach (string s in files)

                {

                    File.Delete(varToDirectory + s.Substring(s.LastIndexOf("\\")));

                }

            }

        }

        #endregion



        #region ���ļ��ľ���·���л�ȡ�ļ���( ������չ�� )

        /// <summary>

        /// ���ļ��ľ���·���л�ȡ�ļ���( ������չ�� )

        /// </summary>

        /// <param name="filePath">�ļ��ľ���·��</param>        

        public static string GetFileName(string filePath)

        {

            //��ȡ�ļ�������

            FileInfo fi = new FileInfo(filePath);

            return fi.Name;

        }

        #endregion



        /// <summary>

        /// �����ļ��ο�����,ҳ��������

        /// </summary>

        /// <param name="cDir">��·��</param>

        /// <param name="TempId">ģ�������滻���</param>

        public static void CopyFiles(string cDir, string TempId)

        {

            //if (Directory.Exists(Request.PhysicalApplicationPath + "\\Controls"))

            //{

            //    string TempStr = string.Empty;

            //    StreamWriter sw;

            //    if (File.Exists(Request.PhysicalApplicationPath + "\\Controls\\Default.aspx"))

            //    {

            //        TempStr = File.ReadAllText(Request.PhysicalApplicationPath + "\\Controls\\Default.aspx");

            //        TempStr = TempStr.Replace("{$ChannelId$}", TempId);



            //        sw = new StreamWriter(Request.PhysicalApplicationPath + "\\" + cDir + "\\Default.aspx", false, System.Text.Encoding.GetEncoding("GB2312"));

            //        sw.Write(TempStr);

            //        sw.Close();

            //    }

            //    if (File.Exists(Request.PhysicalApplicationPath + "\\Controls\\Column.aspx"))

            //    {

            //        TempStr = File.ReadAllText(Request.PhysicalApplicationPath + "\\Controls\\Column.aspx");

            //        TempStr = TempStr.Replace("{$ChannelId$}", TempId);



            //        sw = new StreamWriter(Request.PhysicalApplicationPath + "\\" + cDir + "\\List.aspx", false, System.Text.Encoding.GetEncoding("GB2312"));

            //        sw.Write(TempStr);

            //        sw.Close();

            //    }

            //    if (File.Exists(Request.PhysicalApplicationPath + "\\Controls\\Content.aspx"))

            //    {

            //        TempStr = File.ReadAllText(Request.PhysicalApplicationPath + "\\Controls\\Content.aspx");

            //        TempStr = TempStr.Replace("{$ChannelId$}", TempId);



            //        sw = new StreamWriter(Request.PhysicalApplicationPath + "\\" + cDir + "\\View.aspx", false, System.Text.Encoding.GetEncoding("GB2312"));

            //        sw.Write(TempStr);

            //        sw.Close();

            //    }

            //    if (File.Exists(Request.PhysicalApplicationPath + "\\Controls\\MoreDiss.aspx"))

            //    {

            //        TempStr = File.ReadAllText(Request.PhysicalApplicationPath + "\\Controls\\MoreDiss.aspx");

            //        TempStr = TempStr.Replace("{$ChannelId$}", TempId);



            //        sw = new StreamWriter(Request.PhysicalApplicationPath + "\\" + cDir + "\\DissList.aspx", false, System.Text.Encoding.GetEncoding("GB2312"));

            //        sw.Write(TempStr);

            //        sw.Close();

            //    }

            //    if (File.Exists(Request.PhysicalApplicationPath + "\\Controls\\ShowDiss.aspx"))

            //    {

            //        TempStr = File.ReadAllText(Request.PhysicalApplicationPath + "\\Controls\\ShowDiss.aspx");

            //        TempStr = TempStr.Replace("{$ChannelId$}", TempId);



            //        sw = new StreamWriter(Request.PhysicalApplicationPath + "\\" + cDir + "\\Diss.aspx", false, System.Text.Encoding.GetEncoding("GB2312"));

            //        sw.Write(TempStr);

            //        sw.Close();

            //    }

            //    if (File.Exists(Request.PhysicalApplicationPath + "\\Controls\\Review.aspx"))

            //    {

            //        TempStr = File.ReadAllText(Request.PhysicalApplicationPath + "\\Controls\\Review.aspx");

            //        TempStr = TempStr.Replace("{$ChannelId$}", TempId);



            //        sw = new StreamWriter(Request.PhysicalApplicationPath + "\\" + cDir + "\\Review.aspx", false, System.Text.Encoding.GetEncoding("GB2312"));

            //        sw.Write(TempStr);

            //        sw.Close();

            //    }

            //    if (File.Exists(Request.PhysicalApplicationPath + "\\Controls\\Search.aspx"))

            //    {

            //        TempStr = File.ReadAllText(Request.PhysicalApplicationPath + "\\Controls\\Search.aspx");

            //        TempStr = TempStr.Replace("{$ChannelId$}", TempId);



            //        sw = new StreamWriter(Request.PhysicalApplicationPath + "\\" + cDir + "\\Search.aspx", false, System.Text.Encoding.GetEncoding("GB2312"));

            //        sw.Write(TempStr);

            //        sw.Close();

            //    }

            //}

        }





        #region ����һ��Ŀ¼

        /// <summary>

        /// ����һ��Ŀ¼

        /// </summary>

        /// <param name="directoryPath">Ŀ¼�ľ���·��</param>

        public static void CreateDirectory(string directoryPath)

        {

            //���Ŀ¼�������򴴽���Ŀ¼

            if (!IsExistDirectory(directoryPath))

            {

                Directory.CreateDirectory(directoryPath);

            }

        }

        #endregion



        #region ����һ���ļ�

        /// <summary>

        /// ����һ���ļ���

        /// </summary>

        /// <param name="filePath">�ļ��ľ���·��</param>

        public static void CreateFile(string filePath)

        {

            try

            {

                //����ļ��������򴴽����ļ�

                if (!IsExistFile(filePath))

                {

                    //����һ��FileInfo����

                    FileInfo file = new FileInfo(filePath);



                    //�����ļ�

                    FileStream fs = file.Create();



                    //�ر��ļ���

                    fs.Close();

                }

            }

            catch (Exception ex)

            {

                //LogHelper.WriteTraceLog(TraceLogLevel.Error, ex.Message);

                throw ex;

            }

        }



        /// <summary>

        /// ����һ���ļ�,�����ֽ���д���ļ���

        /// </summary>

        /// <param name="filePath">�ļ��ľ���·��</param>

        /// <param name="buffer">������������</param>

        public static void CreateFile(string filePath, byte[] buffer)

        {

            try

            {

                //����ļ��������򴴽����ļ�

                if (!IsExistFile(filePath))

                {

                    //����һ��FileInfo����

                    FileInfo file = new FileInfo(filePath);



                    //�����ļ�

                    FileStream fs = file.Create();



                    //д���������

                    fs.Write(buffer, 0, buffer.Length);



                    //�ر��ļ���

                    fs.Close();

                }

            }

            catch (Exception ex)

            {

                //LogHelper.WriteTraceLog(TraceLogLevel.Error, ex.Message);

                throw ex;

            }

        }

        #endregion



        #region ��ȡ�ı��ļ�������

        /// <summary>

        /// ��ȡ�ı��ļ�������

        /// </summary>

        /// <param name="filePath">�ļ��ľ���·��</param>        

        public static int GetLineCount(string filePath)

        {

            //���ı��ļ��ĸ��ж���һ���ַ���������

            string[] rows = File.ReadAllLines(filePath);



            //��������

            return rows.Length;

        }

        #endregion



        #region ��ȡһ���ļ��ĳ���

        /// <summary>

        /// ��ȡһ���ļ��ĳ���,��λΪByte

        /// </summary>

        /// <param name="filePath">�ļ��ľ���·��</param>        

        public static int GetFileSize(string filePath)

        {

            //����һ���ļ�����

            FileInfo fi = new FileInfo(filePath);



            //��ȡ�ļ��Ĵ�С

            return (int)fi.Length;

        }

        #endregion



        #region ��ȡָ��Ŀ¼�е���Ŀ¼�б�

        /// <summary>

        /// ��ȡָ��Ŀ¼����Ŀ¼��������Ŀ¼�б�

        /// </summary>

        /// <param name="directoryPath">ָ��Ŀ¼�ľ���·��</param>

        /// <param name="searchPattern">ģʽ�ַ�����"*"����0��N���ַ���"?"����1���ַ���

        /// ������"Log*.xml"��ʾ����������Log��ͷ��Xml�ļ���</param>

        /// <param name="isSearchChild">�Ƿ�������Ŀ¼</param>

        public static string[] GetDirectories(string directoryPath, string searchPattern, bool isSearchChild)

        {

            try

            {

                if (isSearchChild)

                {

                    return Directory.GetDirectories(directoryPath, searchPattern, SearchOption.AllDirectories);

                }

                else

                {

                    return Directory.GetDirectories(directoryPath, searchPattern, SearchOption.TopDirectoryOnly);

                }

            }

            catch (IOException ex)

            {

                throw ex;

            }

        }

        #endregion



        #region ���ı��ļ�д������



        /// <summary>

        /// ���ı��ļ���д������

        /// </summary>

        /// <param name="filePath">�ļ��ľ���·��</param>

        /// <param name="text">д�������</param>

        /// <param name="encoding">����</param>

        public static void WriteText(string filePath, string text, Encoding encoding)

        {

            //���ļ�д������

            File.WriteAllText(filePath, text, encoding);

        }

        #endregion



        #region ���ı��ļ���β��׷������

        /// <summary>

        /// ���ı��ļ���β��׷������

        /// </summary>

        /// <param name="filePath">�ļ��ľ���·��</param>

        /// <param name="content">д�������</param>

        public static void AppendText(string filePath, string content)

        {

            File.AppendAllText(filePath, content);

        }

        #endregion



        #region �������ļ������ݸ��Ƶ����ļ���

        /// <summary>

        /// ��Դ�ļ������ݸ��Ƶ�Ŀ���ļ���

        /// </summary>

        /// <param name="sourceFilePath">Դ�ļ��ľ���·��</param>

        /// <param name="destFilePath">Ŀ���ļ��ľ���·��</param>

        public static void Copy(string sourceFilePath, string destFilePath)

        {

            File.Copy(sourceFilePath, destFilePath, true);

        }

        #endregion



        #region ���ļ��ƶ���ָ��Ŀ¼

        /// <summary>

        /// ���ļ��ƶ���ָ��Ŀ¼

        /// </summary>

        /// <param name="sourceFilePath">��Ҫ�ƶ���Դ�ļ��ľ���·��</param>

        /// <param name="descDirectoryPath">�ƶ�����Ŀ¼�ľ���·��</param>

        public static void Move(string sourceFilePath, string descDirectoryPath)

        {

            //��ȡԴ�ļ�������

            string sourceFileName = GetFileName(sourceFilePath);



            if (IsExistDirectory(descDirectoryPath))

            {

                //���Ŀ���д���ͬ���ļ�,��ɾ��

                if (IsExistFile(descDirectoryPath + "\\" + sourceFileName))

                {

                    DeleteFile(descDirectoryPath + "\\" + sourceFileName);

                }

                //���ļ��ƶ���ָ��Ŀ¼

                File.Move(sourceFilePath, descDirectoryPath + "\\" + sourceFileName);

            }

        }

        #endregion





        #region ���ļ��ľ���·���л�ȡ�ļ���( ��������չ�� )

        /// <summary>

        /// ���ļ��ľ���·���л�ȡ�ļ���( ��������չ�� )

        /// </summary>

        /// <param name="filePath">�ļ��ľ���·��</param>        

        public static string GetFileNameNoExtension(string filePath)

        {

            //��ȡ�ļ�������

            FileInfo fi = new FileInfo(filePath);

            return fi.Name.Split('.')[0];

        }

        #endregion



        #region ���ļ��ľ���·���л�ȡ��չ��

        /// <summary>

        /// ���ļ��ľ���·���л�ȡ��չ��

        /// </summary>

        /// <param name="filePath">�ļ��ľ���·��</param>        

        public static string GetExtension(string filePath)

        {

            //��ȡ�ļ�������

            FileInfo fi = new FileInfo(filePath);

            return fi.Extension;

        }

        #endregion



        #region ���ָ��Ŀ¼

        /// <summary>

        /// ���ָ��Ŀ¼�������ļ�����Ŀ¼,����Ŀ¼��Ȼ����.

        /// </summary>

        /// <param name="directoryPath">ָ��Ŀ¼�ľ���·��</param>

        public static void ClearDirectory(string directoryPath)

        {

            if (IsExistDirectory(directoryPath))

            {

                //ɾ��Ŀ¼�����е��ļ�

                string[] fileNames = GetFileNames(directoryPath);

                for (int i = 0; i < fileNames.Length; i++)

                {

                    DeleteFile(fileNames);

                }



                //ɾ��Ŀ¼�����е���Ŀ¼

                string[] directoryNames = GetDirectories(directoryPath);

                for (int i = 0; i < directoryNames.Length; i++)

                {

                    DeleteDirectory(directoryNames);

                }

            }

        }

        #endregion



        #region ����ļ�����

        /// <summary>

        /// ����ļ�����

        /// </summary>

        /// <param name="filePath">�ļ��ľ���·��</param>

        public static void ClearFile(string filePath)

        {

            //ɾ���ļ�

            File.Delete(filePath);



            //���´������ļ�

            CreateFile(filePath);

        }

        #endregion



        #region ɾ��ָ��Ŀ¼

        /// <summary>

        /// ɾ��ָ��Ŀ¼����������Ŀ¼

        /// </summary>

        /// <param name="directoryPath">ָ��Ŀ¼�ľ���·��</param>

        public static void DeleteDirectory(string directoryPath)

        {

            if (IsExistDirectory(directoryPath))

            {

                Directory.Delete(directoryPath, true);

            }

        }

        #endregion

    }

}