using Programmer.Properties;
using System;
using System.Collections.Generic;
using System.IO;
using System.Resources;

namespace Programmer
{
    /// <summary>
    /// Создает объект цветов колпачков клавиш
    /// </summary>
    class KeyColors
    {
        readonly ResourceManager language;

        /// <summary>
        /// Конструктор класса
        /// </summary>
        /// <param name="lang">
        /// Текущий язык в программе
        /// </param>
        public KeyColors(ResourceManager lang)
        {
            language = lang;
        }

        /// <summary>
        /// Создание списка цветов колпачков клвиш через парсинг файла с цветами (.csv)
        /// </summary>
        /// <returns>
        /// List: список всех доступных цветов с атрибутами
        /// </returns>
        public List<KeyColor> CreateListKeyColors()
        {
            List<KeyColor> listKeyColors = new List<KeyColor>();
            string path = Resources.PATH_CONFIG_COLORS + language.GetString("key_colors_list_name") + Resources.CSV_FILE_EXTANSION;

            using (StreamReader streamReader = new StreamReader(path))
            {
                string line;

                while ((line = streamReader.ReadLine()) != null)
                {
                    /*
                     * Id = parts[0] Номер цвета
                     * Name = parts[1] Название цвета
                     * RedCh = parts[2] Красный канал цвета
                     * GreenCh = parts[3] Зеленый канал цвета
                     * BlueCh = parts[4] Синий канал цвета
                     */
                    string[] parts = line.Split(Convert.ToChar(Resources.CSV_SEPARATOR));

                    KeyColor key_color = new KeyColor { 
                        Id = ushort.Parse(parts[0]),
                        Name = parts[1],
                        RedCh = int.Parse(parts[2]),
                        GreenCh = int.Parse(parts[3]),
                        BlueCh = int.Parse(parts[4]) };

                    listKeyColors.Add(key_color); // Добавить цвет в список
                }

                return listKeyColors;
            }
        }
    }
}
