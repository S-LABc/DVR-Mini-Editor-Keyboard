using Programmer.Properties;
using System.IO;
using System.Windows.Forms;
using System.Linq;
using System.Text;
using System;
using System.Resources;

namespace Programmer
{
    /// <summary>
    /// Вызов диалоговых окон.
    /// Обработка файлов раскладки.
    /// Обработка двоичных файлов.
    /// </summary>
    class Data
    {
        readonly MainForm frmChild;
        readonly ResourceManager language;
        readonly KeyTools tools;
        readonly KeyColors colors;

        /// <summary>
        /// Конструктор класса
        /// </summary>
        /// <param name="frm_main">
        /// Ссылка на главную форму для доступа к ее элементам
        /// </param>
        /// <param name="lang">
        /// Текущий язык в программе
        /// </param>
        public Data(MainForm frm_main, ResourceManager lang)
        {
            frmChild = frm_main;
            language = lang;
            tools = new KeyTools(lang);
            colors = new KeyColors(lang);
        }

        

        #region FILE DIALOG
        /// <summary>
        /// Общая настройка окна открытия файла
        /// </summary>
        OpenFileDialog openFD = new OpenFileDialog
        {
            AddExtension = true,
            SupportMultiDottedExtensions = false,
            Multiselect = false,
            RestoreDirectory = false,
        };
        /// <summary>
        /// Общая настройка окна сохранения файла
        /// </summary>
        SaveFileDialog saveFD = new SaveFileDialog
        {
            AddExtension = true,
            SupportMultiDottedExtensions = false,
            RestoreDirectory = false,
        };
        #endregion

        #region LAYOUT
        /// <summary>
        /// Загрузисть в программу файл раскладки
        /// </summary>
        /// <returns>
        /// Логическое значение: выполнено или не выполнено
        /// </returns>
        public bool OpenLayout()
        {
            openFD.Title = language.GetString("ofd_open");
            openFD.Filter = language.GetString("fd_layout_filter");
            openFD.DefaultExt = Resources.LAYOUT_FILE_EXTENSION;

            if (openFD.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    string[] tools = new string[25];
                    ushort[] colors = new ushort[25];

                    using (StreamReader streamReader = new StreamReader(openFD.FileName))
                    {
                        string line;
                        int i = 0;

                        while ((line = streamReader.ReadLine()) != null)
                        {
                            /*
                             * parts[0] Название инструмента (Name)
                             * parts[1] Номер цвета (Id)
                             */
                            string[] parts = line.Split(Convert.ToChar(Resources.LAYOUT_SEPARATOR));
                            tools[i] = parts[0];
                            colors[i] = ushort.Parse(parts[1]);
                            i++;
                        }
                    }

                    if (tools.Length == 25)
                    {
                        UpdateToolsComboBox(tools);
                        UpdateColorsComboBox(colors);

                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                catch
                {
                    return false;
                }
            }

            return false;
        }
        /// <summary>
        /// Выгрузить из программы файл раскладки
        /// </summary>
        /// <returns>
        /// Логическое значение: выполнено или не выполнено
        /// </returns>
        public bool SaveLayout()
        {
            saveFD.Title = language.GetString("ofd_save");
            saveFD.Filter = language.GetString("fd_layout_filter");
            saveFD.DefaultExt = Resources.LAYOUT_FILE_EXTENSION;

            string[] line = new string[25];
            int i = 0;

            if (saveFD.ShowDialog() == DialogResult.OK)
            {
                /* Сбор выбранных инструментов */
                foreach (var cmb in frmChild.Controls.OfType<ComboBox>().Where(cbox => string.Equals("key_tool", cbox.Tag as String)))
                {
                    KeyTool toolSel = (KeyTool)cmb.SelectedItem;
                    line[i] = toolSel.Name + Resources.LAYOUT_SEPARATOR;
                    i++;
                }
                i = 0;
                /* Сбор выбранных цветов колпачков клавиш */
                foreach (var cmb in frmChild.Controls.OfType<ComboBox>().Where(cbox => string.Equals("color_tool", cbox.Tag as String)))
                {
                    KeyColor toolSel = (KeyColor)cmb.SelectedItem;
                    line[i] += toolSel.Id;
                    i++;
                }
                /* Запись в файл подготовленного массива данных */
                using (StreamWriter streamWriter = new StreamWriter(saveFD.FileName))
                {
                    for (int j = 0; j < line.Length; j++)
                    {
                        streamWriter.WriteLine(line[j]);
                    }
                    
                    return true;
                }
            }

            return false;
        }
        /// <summary>
        /// Загрузка списка раскладки при перетаскивании его на форму
        /// </summary>
        /// <param name="e">
        /// Событие перетаскивания
        /// </param>
        /// <returns>
        /// Логическое значение: выполнено или не выполнено
        /// </returns>
        public bool OpenLayoutDragDrop(DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop) &&
                e.Effect == DragDropEffects.Move)
            {
                try
                {
                    string[] path = (string[])e.Data.GetData(DataFormats.FileDrop); // Получение полного пути к файлу

                    if (string.Equals(Path.GetExtension(path[0]),
                        Resources.LAYOUT_FILE_EXTENSION,
                        StringComparison.InvariantCultureIgnoreCase)) // Проверка файла на правильное расширение
                    {
                        string[] tools = new string[25];
                        ushort[] colors = new ushort[25];

                        using (StreamReader streamReader = new StreamReader(path[0]))
                        {
                            string line;
                            int i = 0;

                            while ((line = streamReader.ReadLine()) != null)
                            {
                                /*
                                 * parts[0] Название инструмента (Name)
                                 * parts[1] Номер цвета (Id)
                                 */
                                string[] parts = line.Split(Convert.ToChar(Resources.LAYOUT_SEPARATOR));

                                tools[i] = parts[0];
                                colors[i] = ushort.Parse(parts[1]);

                                i++;
                            }
                        }

                        if (tools.Length == 25)
                        {
                            UpdateToolsComboBox(tools);
                            UpdateColorsComboBox(colors);

                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                }
                catch
                {
                    return false;
                }
            }

            return false;
        }
        /// <summary>
        /// Загрузка списка раскладки по умолчанию
        /// </summary>
        /// <returns>
        /// Логическое значение: выполнено или не выполнено
        /// </returns>
        public bool OpenDefaultLayout()
        {
            try
            {
                string path = Resources.PATH_CONFIG + Resources.DEFAULT_LAYOUT_FILE_NAME + Resources.LAYOUT_FILE_EXTENSION;
                string[] tools = new string[25];
                ushort[] colors = new ushort[25];

                using (StreamReader streamReader = new StreamReader(path))
                {
                    string line;
                    int i = 0;

                    while ((line = streamReader.ReadLine()) != null)
                    {
                        /*
                         * parts[0] Название инструмента (Name)
                         * parts[1] Номер (Id) цвета
                         */
                        string[] parts = line.Split(Convert.ToChar(Resources.LAYOUT_SEPARATOR));

                        tools[i] = parts[0];
                        colors[i] = ushort.Parse(parts[1]);

                        i++;
                    }
                }

                if (tools.Length == 25)
                {
                    UpdateToolsComboBox(tools);
                    UpdateColorsComboBox(colors);

                    return true;
                }
                else
                {
                    return false;
                }
            }
            catch
            {
                return false;
            }
        }
        #endregion

        #region BINARY
        /// <summary>
        /// Импорт двоичного файла из каталога пользователя в каталог приложения
        /// </summary>
        /// <param name="file_name">
        /// Имя двоичного файла - EEPROM, BOOTLOADER, FIRMWARE, FLASH
        /// </param>
        /// <returns>
        /// Логическое значение: выполнено или не выполнено
        /// </returns>
        public bool ImportBin(string file_name)
        {
            openFD.Title = language.GetString("ofd_import");
            openFD.Filter = language.GetString("fd_binary_filter");
            openFD.DefaultExt = Resources.BINARY_FILE_EXTENSION;

            if (openFD.ShowDialog() == DialogResult.OK)
            {
                string old_file_path = Resources.PATH_BINARY + file_name + Resources.BINARY_FILE_EXTENSION;
                try
                {
                    byte[] new_file = File.ReadAllBytes(openFD.FileName);

                    if (new_file.Length > 0)
                    {
                        FileStream old_file = File.Open(old_file_path, FileMode.Open);

                        if (new_file.Length <= old_file.Length)
                        {
                            using (BinaryWriter binaryWriter = new BinaryWriter(old_file))
                            {
                                binaryWriter.Write(new_file);
                            }

                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
                catch
                {
                    return false;
                }
            }

            return false;
        }
        /// <summary>
        /// Экспорт двоичного файла из каталога приложения в каталог пользователя
        /// </summary>
        /// <param name="file_name">
        /// Имя двоичного файла - EEPROM, BOOTLOADER, FIRMWARE, FLASH
        /// </param>
        /// <returns>
        /// Логическое значение: выполнено или не выполнено
        /// </returns>
        public bool ExportBin(string file_name)
        {
            saveFD.Title = language.GetString("sfd_export");
            saveFD.Filter = language.GetString("fd_binary_filter");
            saveFD.DefaultExt = Resources.BINARY_FILE_EXTENSION; 

            if (saveFD.ShowDialog() == DialogResult.OK)
            {
                string file_path = Resources.PATH_BINARY + file_name + Resources.BINARY_FILE_EXTENSION;
                try
                {
                    // Скопировать выбранный по имени файл в новое место с новым именем
                    File.Copy(file_path, saveFD.FileName);
                    // Проверка удачного/неудачного копирования
                    if (File.Exists(saveFD.FileName))
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                catch
                {
                    return false;
                }
            }

            return false;
        }
        #endregion

        #region UPDATE
        /*
         * ***** all_byte *****
         * Кол-во байт на номер страницы (4) +
         * + Кол-во клавиш (25) x
         * x Кол-во байт на клавишу (2) x
         * x Кол-во байт на виртуальный номер (2)
         * 
         * ********************
         * При размере страницы 1k (0x400) доступно микусимум 256 ячеек под данные
         * 2 байта отводится данным (номеру инструмента под клавишу 0 - 65535)
         * 2 байта под виртуальный номер ячеки 0 - 65535
         */

        /// <summary>
        /// Чтение номеров инструементов из бинарного файла 
        /// </summary>
        public void UpdateToolsForm()
        {
            byte all_byte = 4 + 25 * 2 * 2;
            byte[] tools_id = new byte[all_byte];

            /* Чтение из файла в массив */
            using (FileStream readEEPROM = new FileStream(Resources.PATH_BINARY + Resources.EEPROM_NAME + Resources.BINARY_FILE_EXTENSION,
                FileMode.Open))
            {
                using (BinaryReader readTools = new BinaryReader(readEEPROM))
                {
                    tools_id = readTools.ReadBytes(all_byte);
                }
            }

            /* Выбор инструментов по номеру в списках на форме */
            foreach (var cmb in frmChild.Controls.OfType<ComboBox>().Where(cbox => string.Equals("key_tool", cbox.Tag as String)))
            {
                int id = (tools_id[all_byte - 3] << 8) | tools_id[all_byte - 4];
                cmb.SelectedValue = Convert.ToUInt16(id);
                all_byte -= 4;
            }
        }
        /// <summary>
        /// Запись номеров инструментов в бинарный файл
        /// </summary>
        public void UpdateToolsBinary()
        {
            byte all_byte = 4 + 25 * 2 * 2;
            byte[] eeprom = new byte[all_byte];

            /* Первые 2 байта (так сделано в EEPROM.h) номер страницы (PageBase) */
            eeprom[0] = 0x00;
            eeprom[1] = 0x00;
            /* Следующие 2 байта флаг состояния страницы */
            eeprom[2] = 0xFF;
            eeprom[3] = 0xFF;

            /* Сбор номеров инструментов из списков на форме */
            foreach (var cmb in frmChild.Controls.OfType<ComboBox>().Where(cbox => string.Equals("key_tool", cbox.Tag as String)))
            {
                eeprom[all_byte - 4] = (byte)(((ushort)cmb.SelectedValue) & 0xFF); // Младший байт элемента
                eeprom[all_byte - 3] = (byte)(((ushort)cmb.SelectedValue) >> 8); // Старший байт элемента
                eeprom[all_byte - 2] = (byte)((((all_byte - 4) / 4) - 1) & 0xFF); // Младший байт порядкового номера ячейки
                eeprom[all_byte - 1] = (byte)((((all_byte - 4) / 4) - 1) >> 8); // Старший байт порядкового номера ячейки
                all_byte -= 4;
            }

            /* Запись массива в файл */
            using (FileStream writeEEPROM = new FileStream(Resources.PATH_BINARY + Resources.EEPROM_NAME + Resources.BINARY_FILE_EXTENSION,
            FileMode.Open))
            {
                using (BinaryWriter writeTools = new BinaryWriter(writeEEPROM, Encoding.Default))
                {
                    for (int i = 0; i < eeprom.Length; i++)
                    {
                        writeTools.Write(eeprom[i]);
                    }
                }
            }
        }
        /// <summary>
        /// Обновление инструментов в выпадающих списках
        /// </summary>
        /// <param name="tools">
        /// Массив с названиями доступных инструментов
        /// </param>
        private void UpdateToolsComboBox(string[] tools)
        {
            int i = 0;

            foreach (var cmb in frmChild.Controls.OfType<ComboBox>().Where(cbox => string.Equals("key_tool", cbox.Tag as String)))
            {
                cmb.Text = tools[i];
                i++;
            }
        }
        /// <summary>
        /// Обновление цветов колпачков клавиш в выпадающих списках
        /// </summary>
        /// <param name="keys">
        /// Массив с номерами доступных цветов колпачков клавиш
        /// </param>
        private void UpdateColorsComboBox(ushort[] keys)
        {
            int i = 0;

            foreach (var cmb in frmChild.Controls.OfType<ComboBox>().Where(cbox => string.Equals("color_tool", cbox.Tag as String)))
            {
                cmb.SelectedIndex = keys[i];
                i++;
            }
        }
        #endregion

        #region OTHER
        /// <summary>
        /// Загрузка инструментов в выпадающие списки
        /// </summary>
        public void LoadingTools()
        {
            foreach (var cmb in frmChild.Controls.OfType<ComboBox>().Where(cbox => string.Equals("key_tool", cbox.Tag as String)))
            {
                cmb.DataSource = tools.CreateListKeyTools();
                cmb.DisplayMember = "Name";
                cmb.ValueMember = "Id";
                // Установка сохранённых в предыдущий раз инструментов
                cmb.Text = (string)Settings.Default[cmb.Name];
            }
        }
        /// <summary>
        /// Загрузка цветов колпачков клавиш в выпадающие списки
        /// </summary>
        public void LoadingColors()
        {
            foreach (var cmb in frmChild.Controls.OfType<ComboBox>().Where(cbox => string.Equals("color_tool", cbox.Tag as String)))
            {
                cmb.DataSource = colors.CreateListKeyColors();
                cmb.ValueMember = "Id";
                // Установка сохранённых в предыдущий раз цветов колпачков клавиш
                cmb.SelectedIndex = (ushort)Settings.Default[cmb.Name];
            }
        }
        /// <summary>
        /// Сохранение выбранных на форме параметров внутрь приложения перед закрытием
        /// </summary>
        public void SaveUserChenges()
        {
            /* Запись данных из списков инструментов */
            foreach (var cmb in frmChild.Controls.OfType<ComboBox>().Where(cbox => string.Equals("key_tool", cbox.Tag as String)))
            {
                Settings.Default[cmb.Name] = cmb.Text;
            }
            /* Запись данных из списков цветов колпачков клавиш */
            foreach (var cmb in frmChild.Controls.OfType<ComboBox>().Where(cbox => string.Equals("color_tool", cbox.Tag as String)))
            {
                KeyColor colorSel = (KeyColor)cmb.SelectedItem;
                Settings.Default[cmb.Name] = colorSel.Id;
            }
            Settings.Default.Save();
        }
        /// <summary>
        /// Отображение описания, примечания, комбинации клавиш выбранного инструмента
        /// </summary>
        /// <param name="combobox">
        /// Выпадающий список с инструментами клавиши на форме
        /// </param>
        public void ShowToolInfo(object combobox)
        {
            var cmbKey = (ComboBox)combobox;
            KeyTool toolSel = (KeyTool)cmbKey.SelectedItem;
            frmChild.lblDescription.Text = toolSel.Desc;
            frmChild.lblNote.Text = toolSel.Note;
            frmChild.lblKeys.Text = toolSel.Keys;
        }
        /// <summary>
        /// Отображение информации о цвете колпачка выбранной клавиши
        /// </summary>
        /// <param name="combobox">
        /// Выпадающий список с цветом колпачка на форме
        /// </param>
        public void ShowColorInfo(object combobox)
        {
            var cmbColor = (ComboBox)combobox;
            KeyColor colorSel = (KeyColor)cmbColor.SelectedItem;
            frmChild.lblColor.Text = colorSel.Name;
            // Смена цвета ручки поиска на форме при выборе нового цвета
            if (cmbColor.TabIndex == 50)
            {
                frmChild.Invalidate();
            }
        }
        #endregion
    }
}
