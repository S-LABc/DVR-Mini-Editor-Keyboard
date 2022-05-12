using Programmer.Properties;
using System.Reflection;
using System.Resources;
using System.Windows.Forms;

namespace Programmer
{
    /// <summary>
    /// Фармирование сообщений пользователю при работе с
    /// консольными приложениями, операциями над файлами, установкой драйверов
    /// </summary>
    class Messages
    {
        ResourceManager language;

        /// <summary>
        /// Конструктор класса
        /// </summary>
        /// <param name="lang">
        /// Текущий язык в программе
        /// </param>
        public Messages(ResourceManager lang)
        {
            language = lang;
        }

        #region ST-LINK
        /// <summary>
        /// Выводит сообщение в соответсвии с ответом st-link_cli
        /// </summary>
        /// <param name="responseCLI">
        /// Ответ командной строки
        /// </param>
        public void ShowMessageSTLINK(string responseCLI)
        {
            if (responseCLI.Contains("Application started") && responseCLI.Contains("bin/bootloader.bin"))
            {
                MessageBox.Show(language.GetString("message_stlink_write_bootloader_done"),
                    language.GetString("message_caption_information"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
            }
            else if (responseCLI.Contains("Application started") && responseCLI.Contains("bin/flash.bin"))
            {
                MessageBox.Show(language.GetString("message_stlink_write_all_flash_done"),
                        language.GetString("message_caption_information"),
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Information);
            }
            else if (responseCLI.Contains("Dumping memory to bin/bootloader.bin succeded"))
            {
                MessageBox.Show(language.GetString("message_stlink_dump_bootloader_success"),
                        language.GetString("message_caption_information"),
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Information);
            }
            else if (responseCLI.Contains("Dumping memory to bin/flash.bin succeded"))
            {
                MessageBox.Show(language.GetString("message_stlink_dump_all_flash_success"),
                        language.GetString("message_caption_information"),
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Information);
            }
            else if (responseCLI.Contains("Device family: STM32F10xx Medium-density") && responseCLI.Contains("Device flash Size: 128 Kbytes"))
            {
                MessageBox.Show(language.GetString("message_stlink_device_found"),
                        language.GetString("message_caption_information"),
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Information);
            }
            else if (responseCLI.Contains("No target connected"))
            {
                MessageBox.Show(language.GetString("message_stlink_device_not_found"),
                    language.GetString("message_caption_error"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
            else if (responseCLI.Contains("No ST-LINK detected"))
            {
                MessageBox.Show(language.GetString("message_stlink_st_link_not_found"),
                    language.GetString("message_caption_error"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
            else
            {
                MessageBox.Show(language.GetString("message_stlink_error"),
                    language.GetString("message_caption_error"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
        }
        #endregion

        #region DFU UTIL
        /// <summary>
        /// Выводит сообщение в соответсвии с ответом dfu-util
        /// </summary>
        /// <param name="responseCLI">
        /// Ответ командной строки
        /// </param>
        public void ShowMessageDFUUTIL(string responseCLI)
        {
            if (responseCLI.Contains("Found DFU: [1eaf:0003]") && responseCLI.Contains("Mini Editor Keyboard"))
            {
                MessageBox.Show(language.GetString("message_dfuutil_device_found"),
                    language.GetString("message_caption_information"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
            }
            else if (responseCLI.Contains("Upload done") && responseCLI.Contains("Setting Alternate Setting #1"))
            {
                MessageBox.Show(language.GetString("message_dfuutil_read_tools_done"),
                    language.GetString("message_caption_information"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
            }
            else if (responseCLI.Contains("Upload done") && responseCLI.Contains("Setting Alternate Setting #0"))
            {
                MessageBox.Show(language.GetString("message_dfuutil_read_firmware_done"),
                    language.GetString("message_caption_information"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
            }
            else if (responseCLI.Contains("Error sending completion packet") && responseCLI.Contains("Setting Alternate Setting #1"))
            {
                MessageBox.Show(language.GetString("message_dfuutil_write_tools_done"),
                    language.GetString("message_caption_information"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
            }
            else if (responseCLI.Contains("Error sending completion packet") && responseCLI.Contains("Setting Alternate Setting #0"))
            {
                MessageBox.Show(language.GetString("message_dfuutil_write_firmware_done"),
                    language.GetString("message_caption_information"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
            }
            else if (responseCLI.Contains("No DFU capable USB device available"))
            {
                MessageBox.Show(language.GetString("message_dfuutil_device_not_found"),
                    language.GetString("message_caption_error"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
            else
            {
                MessageBox.Show(language.GetString("message_dfuutil_device_not_found"),
                    language.GetString("message_caption_error"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
        }
        #endregion

        #region IMPORT
        /// <summary>
        /// Выводит сообщение при импорте файлов
        /// </summary>
        /// <param name="code">
        /// Тип сообщения в ручном режиме
        /// </param>
        public void ShowMessageImport(string code)
        {
            if (code
                == "error")
            {
                MessageBox.Show(language.GetString("message_import_error"),
                    language.GetString("message_caption_error"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
            else if (code
                == Resources.EEPROM_NAME)
            {
                MessageBox.Show(language.GetString("message_import_tools_success"),
                    language.GetString("message_caption_information"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
            }
            else if (code
                == Resources.FIRMWARE_NAME)
            {
                MessageBox.Show(language.GetString("message_import_firmware_success"),
                    language.GetString("message_caption_information"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
            }
            else if (code
                == Resources.BOOTLOADER_NAME)
            {
                MessageBox.Show(language.GetString("message_import_bootloader_success"),
                    language.GetString("message_caption_information"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
            }
            else if (code
                == Resources.FLASH_NAME)
            {
                MessageBox.Show(language.GetString("message_import_all_flash_success"),
                    language.GetString("message_caption_information"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
            }
        }
        #endregion

        #region EXPORT
        /// <summary>
        /// Выводит сообщение при экспорте файлов
        /// </summary>
        /// <param name="code">
        /// Тип сообщения в ручном режиме
        /// </param>
        public void ShowMessageExport(string code)
        {
            if (code
                == "error")
            {
                MessageBox.Show(language.GetString("message_export_error"),
                    language.GetString("message_caption_error"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
            else if (code
                == Resources.EEPROM_NAME)
            {
                MessageBox.Show(language.GetString("message_export_tools_success"),
                    language.GetString("message_caption_information"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
            }
            else if (code
                == Resources.FIRMWARE_NAME)
            {
                MessageBox.Show(language.GetString("message_export_firmware_success"),
                    language.GetString("message_caption_information"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
            }
            else if (code
                == Resources.BOOTLOADER_NAME)
            {
                MessageBox.Show(language.GetString("message_export_bootloader_success"),
                    language.GetString("message_caption_information"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
            }
            else if (code
                == Resources.FLASH_NAME)
            {
                MessageBox.Show(language.GetString("message_export_all_flash_success"),
                    language.GetString("message_caption_information"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
            }
        }
        #endregion

        #region DRIVER
        /// <summary>
        /// Выводит сообщения при установке драйверов
        /// </summary>
        /// <param name="code">
        /// Тип сообщения в ручном режиме
        /// </param>
        public void ShowMessageDriver(string code)
        {
            if (code
                == "dfu ok")
            {
                MessageBox.Show(language.GetString("message_dfu_success"),
                    language.GetString("message_caption_information"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
            }
            else if (code 
                == "dfu error")
            {
                MessageBox.Show(language.GetString("message_dfu_error"),
                    language.GetString("message_caption_error"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
            else if (code 
                == "swd ok")
            {
                MessageBox.Show(language.GetString("message_swd_success"),
                    language.GetString("message_caption_information"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
            }
            else if (code 
                == "swd error")
            {
                MessageBox.Show(language.GetString("message_swd_error"),
                    language.GetString("message_caption_error"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
        }
        #endregion

        #region OTHER
        /// <summary>
        /// Выводит сообщение при работе с файлами раскладки
        /// </summary>
        public void ShowMessageLayout()
        {
            MessageBox.Show(language.GetString("message_layout_error"),
                    language.GetString("message_caption_error"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
        }
        /// <summary>
        /// Сообщение на новом языке при смене текущего языка на новый
        /// </summary>
        /// <param name="lang">
        /// Измененный язык приложения
        /// </param>
        public void ShowMessageChangeLanguage(string lang)
        {
            // Смена языка на новый
            language = new ResourceManager(GetType().Namespace + ".Languages." + lang,
                Assembly.GetExecutingAssembly());
            // Сообщение на новом языке
            MessageBox.Show(language.GetString("message_change_language"),
                    language.GetString("message_caption_information"),
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Information);
        }
        #endregion
    }
}
