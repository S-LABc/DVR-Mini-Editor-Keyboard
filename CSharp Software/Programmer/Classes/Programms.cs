using Programmer.Properties;
using System;
using System.Diagnostics;
using System.IO;

namespace Programmer
{
    /// <summary>
    /// Запуск консольных приложений ST-LINK_CLI и dfu-util с аргументами.
    /// Чтение и запись бинарных файлов в память микроконтроллера.
    /// Проверка наличия соединения с микрокотроллером в SWD и DFU режимах.
    /// </summary>
    class Programms
    {
        #region PREPARE
        /// <summary>
        /// Шаблон запуска приложения командной строки
        /// </summary>
        /// <param name="path">
        /// Полный путь к исполняемому файлу
        /// </param>
        /// <param name="args">
        /// Агрументы заупска исполняемого файла
        /// </param>
        /// <returns>
        /// Строка с ответом от командной строки
        /// </returns>
        private string StartProcessAndGetOutput(string path, string args)
        {
            using (Process process = new Process())
            {
                process.StartInfo.UseShellExecute = false;
                process.StartInfo.Verb = "runas";
                process.StartInfo.RedirectStandardOutput = true;
                process.StartInfo.RedirectStandardError = true;
                process.StartInfo.CreateNoWindow = true;
                process.StartInfo.FileName = path;
                process.StartInfo.Arguments = args;
                process.Start();
                process.WaitForExit();

                return process.StandardOutput.ReadToEnd() + process.StandardError.ReadToEnd();
            }
        }
        /// <summary>
        /// Удаление файла
        /// </summary>
        /// <param name="path">
        /// Полный путь к файлу
        /// </param>
        private void DeleteFile(string path)
        {
            if (File.Exists(path))
            {
                File.Delete(path);
            }
        }
        /// <summary>
        /// Замена одного файла другим файлом
        /// </summary>
        /// <param name="buffer">
        /// Полный путь к промежуточному файлу
        /// </param>
        /// <param name="target">
        /// Полный путь к целевому файлу
        /// </param>
        private void UpdateFile(string buffer, string target)
        {
            if (File.Exists(buffer))
            {
                DeleteFile(target);
                File.Copy(buffer, target);
                DeleteFile(buffer);
            }
        }
        #endregion

        #region WRITE
        /// <summary>
        /// Запись номеров инструментов через DFU в эмулированную EEPROM.
        /// VID=1EAF PID=0003 Alt=1.
        /// </summary>
        /// <returns>
        /// Содержимое окна консоли
        /// </returns>
        public string WriteToolsDFU()
        {
            string file_path = Resources.PATH_BINARY + Resources.EEPROM_NAME + Resources.BINARY_FILE_EXTENSION;
            string arguments = "-d 1EAF:0003 -a 1 -D " + file_path;
            string result = StartProcessAndGetOutput(Resources.PATH_DFU_UTIL, arguments);

            return result;
        }
        /// <summary>
        /// Запись прошивки клавиатуры через DFU.
        /// VID=1EAF PID=0003 Alt=0.
        /// </summary>
        /// <returns>
        /// Содержимое окна консоли
        /// </returns>
        public string WriteFirmwareDFU()
        {
            string file_path = Resources.PATH_BINARY + Resources.FIRMWARE_NAME + Resources.BINARY_FILE_EXTENSION;
            string arguments = "-d 1EAF:0003 -a 0 -D " + file_path;
            string result = StartProcessAndGetOutput(Resources.PATH_DFU_UTIL, arguments);

            return result;
        }
        /// <summary>
        /// Запись загрузчика через SWD по адресу 0x8000000.
        /// Память полностью очищается.
        /// </summary>
        /// <returns>
        /// Содержимое окна консоли
        /// </returns>
        public string WriteBootloaderSWD()
        {
            string file_path = Resources.PATH_BINARY + Resources.BOOTLOADER_NAME + Resources.BINARY_FILE_EXTENSION;
            string arguments = "-c SWD -ME -P " + file_path + " 0x8000000 -Rst -Run -NoPrompt -Q";
            string result = StartProcessAndGetOutput(Resources.PATH_ST_LINK, arguments);

            return result;
        }
        /// <summary>
        /// Запись всей памяти контроллера через SWD по адресу 0x8000000 размером 0x20000 (128K).
        /// Память полностью очищается.
        /// </summary>
        /// <returns>
        /// Содержимое окна консоли
        /// </returns>
        public string WriteAllFlashSWD()
        {
            string file_path = Resources.PATH_BINARY + Resources.FLASH_NAME + Resources.BINARY_FILE_EXTENSION;
            string arguments = "-c SWD -ME -P " + file_path + " 0x8000000 -Rst -Run -NoPrompt -Q";
            string result = StartProcessAndGetOutput(Resources.PATH_ST_LINK, arguments);

            return result;
        }
        #endregion

        #region READ
        /// <summary>
        /// Чтение номеров инструментов через DFU из эмулированной EEPROM.
        /// VID=1EAF PID=0003 Alt=1.
        /// </summary>
        /// <returns>
        /// Содержимое окна консоли
        /// </returns>
        public string ReadToolsDFU()
        {
            /* dfu-util-0.9 почему-то не хочет перезаписывать существующий файл */

            string buffer_path = Resources.PATH_BINARY + Resources.BINARY_BUFFER_NAME + Resources.BINARY_FILE_EXTENSION;
            string eeprom_path = Resources.PATH_BINARY + Resources.EEPROM_NAME + Resources.BINARY_FILE_EXTENSION;

            DeleteFile(buffer_path); // Удалить промежуточный файл (буфер), если он не был удалён ранее

            string arguments = "-d 1EAF:0003 -a 1 -U " + buffer_path;
            string result = StartProcessAndGetOutput(Resources.PATH_DFU_UTIL, arguments); // Считать данные в буфер

            UpdateFile(buffer_path, eeprom_path); // Обновить целевой файл данными из буферного файла

            return result;
        }
        /// <summary>
        /// Чтение прошивки клавиатуры через DFU.
        /// VID=1EAF PID=0003 Alt=0.
        /// </summary>
        /// <returns>
        /// Содержимое окна консоли
        /// </returns>
        public string ReadFirmwareDFU()
        {
            /* dfu-util-0.9 почему-то не хочет перезаписывать существующий файл */

            string buffer_path = Resources.PATH_BINARY + Resources.BINARY_BUFFER_NAME + Resources.BINARY_FILE_EXTENSION;
            string firmware_path = Resources.PATH_BINARY + Resources.FIRMWARE_NAME + Resources.BINARY_FILE_EXTENSION;

            DeleteFile(buffer_path); // Удалить промежуточный файл (буфер), если он не был удалён ранее

            string arguments = "-d 1EAF:0003 -a 0 -U " + buffer_path;
            string result = StartProcessAndGetOutput(Resources.PATH_DFU_UTIL, arguments);

            UpdateFile(buffer_path, firmware_path); // Обновить целевой файл данными из буферного файла

            return result;
        }
        /// <summary>
        /// Считывание загрузчика через SWD с адреса 0x8000000 размером 0x2000 (8K).
        /// </summary>
        /// <returns>
        /// Содержимое окна консоли
        /// </returns>
        public string ReadBootloaderSWD()
        {
            string file_path = Resources.PATH_BINARY + Resources.BOOTLOADER_NAME + Resources.BINARY_FILE_EXTENSION;
            string arguments = "-c SWD -Dump 0x8000000 0x2000 " + file_path + " -Rst -NoPrompt -Q";
            string result = StartProcessAndGetOutput(Resources.PATH_ST_LINK, arguments);

            return result;
        }
        /// <summary>
        /// Считывание всей памяти контроллера через SWD с адреса 0x8000000 размером 0x20000 (128K).
        /// </summary>
        /// <returns>
        /// Содержимое окна консоли
        /// </returns>
        public string ReadAllFlash()
        {
            string file_path = Resources.PATH_BINARY + Resources.FLASH_NAME + Resources.BINARY_FILE_EXTENSION;
            string arguments = "-c SWD -Dump 0x8000000 0x20000 " + file_path + " -Rst -NoPrompt -Q";
            string result = StartProcessAndGetOutput(Resources.PATH_ST_LINK, arguments);

            return result;
        }
        #endregion

        #region CHECK
        /// <summary>
        /// Запрос списка устройств в режиме DFU
        /// </summary>
        /// <returns>
        /// Содержимое окна консоли
        /// </returns>
        public string ListDFU()
        {
            string result = StartProcessAndGetOutput(Resources.PATH_DFU_UTIL, "-l");

            return result;
        }
        /// <summary>
        /// Соединение с контроллером по интерфейсу SWD.
        /// </summary>
        /// <returns>
        /// Содержимое окна консоли
        /// </returns>
        public string ListSWD()
        {
            string result = StartProcessAndGetOutput(Resources.PATH_ST_LINK, "-c SWD");

            return result;
        }
        #endregion

        #region DRIVERS
        /// <summary>
        /// Установка драйвера для клавиатуры в режиме DFU
        /// </summary>
        /// <returns>
        /// Логическое значение: выполнено или не выполнено
        /// </returns>
        public bool InstallDriverDFU()
        {
            try
            {
                string arguments = "--vid 0x1EAF --pid 0x0003 --type 1 --name " + Resources.NAME_DFU_MODE + " --dest " + Resources.PATH_DRIVER_DFU;

                using (Process installingDFU = new Process())
                {
                    installingDFU.StartInfo.FileName = Resources.PATH_WDI;
                    installingDFU.StartInfo.Arguments = arguments;
                    installingDFU.Start();
                }

                return true;
            }
            catch
            {
                return false;
            }
        }
        /// <summary>
        /// Установка драйвера для программатора ST-Link
        /// </summary>
        /// <returns>
        /// Логическое значение: выполнено или не выполнено
        /// </returns>
        public bool InstallDriverSWD()
        {
            try
            {
                using (Process installingSWD = new Process())
                {
                    if (Environment.GetEnvironmentVariable("PROCESSOR_ARCHITECTURE", EnvironmentVariableTarget.Machine) == "AMD64" ||
                        Environment.GetEnvironmentVariable("PROCESSOR_ARCHITECTURE6432", EnvironmentVariableTarget.Machine) == "AMD64")
                    {
                        installingSWD.StartInfo.FileName = Resources.PATH_DRIVER_ST_LINK_64;
                    }
                    else
                    {
                        installingSWD.StartInfo.FileName = Resources.PATH_DRIVER_ST_LINK_86;
                    }

                    installingSWD.Start();
                }

                return true;
            }
            catch
            {
                return false;
            }
        }
        #endregion
    }
}
