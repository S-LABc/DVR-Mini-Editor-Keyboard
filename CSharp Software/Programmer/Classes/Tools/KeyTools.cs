using Programmer.Properties;
using System;
using System.Collections.Generic;
using System.IO;
using System.Resources;

namespace Programmer
{
    /// <summary>
    /// Создает объект инструментов
    /// </summary>
    class KeyTools
    {
        readonly ResourceManager language;

        /// <summary>
        /// Конструктор класса
        /// </summary>
        /// <param name="lang">
        /// Текущий язык в программе
        /// </param>
        public KeyTools(ResourceManager lang)
        {
            language = lang;
        }

        /// <summary>
        /// Создание списка инструментов для всех клвиш через парсинг файла инструментов (.csv)
        /// </summary>
        /// <returns>
        /// List: список всех доступных инструментов с атрибутами
        /// </returns>
        public List<KeyTool> CreateListKeyTools()
        {
            List<KeyTool> listKeyTools = new List<KeyTool>();
            string path = Resources.PATH_CONFIG_TOOLS + language.GetString("tools_list_name") + Resources.CSV_FILE_EXTANSION;

            using (StreamReader streamReader = new StreamReader(path))
            {
                string line;

                while ((line = streamReader.ReadLine()) != null)
                {
                    /*
                     * Id = parts[0]   Номер инструмента
                     * Name = parts[1] Имя инструмента
                     * Desc = parts[2] Описание инструмента
                     * Note = parts[3] Примечание к инструменту
                     * Keys = parts[4] Сочетание клавиш обычной клавиатуры
                     */
                    string[] parts = line.Split(Convert.ToChar(Resources.CSV_SEPARATOR));

                    KeyTool key_tool = new KeyTool { 
                        Id = ushort.Parse(parts[0]),
                        Name = parts[1],
                        Desc = parts[2],
                        Note = parts[3],
                        Keys = parts[4] };

                    listKeyTools.Add(key_tool); // Добавить инструмент в список
                }

                return listKeyTools;
            } 
        }
    }
}
