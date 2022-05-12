using Programmer.Properties;
using System.Reflection;
using System.Resources;
using System.Windows.Forms;

namespace Programmer
{
    class Language
    {
        readonly MainForm frmChild;
        ResourceManager language;

        /// <summary>
        /// Конструктор класса
        /// </summary>
        /// <param name="frm_main">
        /// Ссылка на главную форму для доступа к ее элементам
        /// </param>
        public Language(MainForm frm_main)
        {
            frmChild = frm_main;
            СhoiceLanguage(Settings.Default.language);
        }

        /// <summary>
        /// Получение текущего языка приложения
        /// </summary>
        /// <returns>
        /// Язык приложения в виде объекта
        /// </returns>
        public ResourceManager GetCurrentLanguage()
        {
            return language;
        }

        /// <summary>
        /// Выбор используемого языка. Значение берется из файла конфигурации
        /// </summary>
        /// <param name="lang">
        /// Язык который нужно выбрать
        /// </param>
        private void СhoiceLanguage(string lang)
        {
            if (lang == "Russian")
            {
                language = new ResourceManager(GetType().Namespace + ".Languages." + Settings.Default.language,
                    Assembly.GetExecutingAssembly());
                frmChild.menuLanguageRussian.Checked = true;
                frmChild.menuLanguageEnglish.Checked = false;
            }
            else if (lang == "English")
            {
                language = new ResourceManager(GetType().Namespace + ".Languages." + Settings.Default.language,
                    Assembly.GetExecutingAssembly());
                frmChild.menuLanguageRussian.Checked = false;
                frmChild.menuLanguageEnglish.Checked = true;
            }
        }

        /// <summary>
        /// Установка текста на форме выбранного языка
        /// </summary>
        public void SetLanguageText()
        {
            frmChild.Text = language.GetString("form_main_text");

            frmChild.menuLayout.Text = language.GetString("menu_layout");
            frmChild.menuLayoutSave.Text = language.GetString("menu_layout_save");
            frmChild.menuLayoutOpen.Text = language.GetString("menu_layout_open");
            frmChild.menuLayoutRestore.Text = language.GetString("menu_layout_restore");
            frmChild.menuWrite.Text = language.GetString("menu_write");
            frmChild.menuWriteTools.Text = language.GetString("menu_write_tools");
            frmChild.menuWriteFirmware.Text = language.GetString("menu_write_firmware");
            frmChild.menuWriteBootloader.Text = language.GetString("menu_write_bootloader");
            frmChild.menuWriteAllFlash.Text = language.GetString("menu_write_all_flash");
            frmChild.menuRead.Text = language.GetString("menu_read");
            frmChild.menuReadTools.Text = language.GetString("menu_read_tools");
            frmChild.menuReadFirmware.Text = language.GetString("menu_read_firmware");
            frmChild.menuReadBootloader.Text = language.GetString("menu_read_bootloader");
            frmChild.menuReadAllFlash.Text = language.GetString("menu_read_all_flash");
            frmChild.menuImport.Text = language.GetString("menu_import");
            frmChild.menuImportTools.Text = language.GetString("menu_import_tools");
            frmChild.menuImportFirmware.Text = language.GetString("menu_import_firmware");
            frmChild.menuImportBootloader.Text = language.GetString("menu_import_bootloader");
            frmChild.menuImportAllFlash.Text = language.GetString("menu_import_all_flash");
            frmChild.menuExport.Text = language.GetString("menu_export");
            frmChild.menuExportTools.Text = language.GetString("menu_export_tools");
            frmChild.menuExportFirmware.Text = language.GetString("menu_export_firmware");
            frmChild.menuExportBootloader.Text = language.GetString("menu_export_bootloader");
            frmChild.menuExportAllFlash.Text = language.GetString("menu_export_all_flash");
            frmChild.menuCheck.Text = language.GetString("menu_check");
            frmChild.menuCheckDFU.Text = language.GetString("menu_check_dfu");
            frmChild.menuCheckSWD.Text = language.GetString("menu_check_swd");
            frmChild.menuDriver.Text = language.GetString("menu_driver");
            frmChild.menuDriverDFU.Text = language.GetString("menu_driver_dfu");
            frmChild.menuDriverSWD.Text = language.GetString("menu_driver_st_link");
            frmChild.menuLanguage.Text = language.GetString("menu_language");
            frmChild.lblKey1.Text = language.GetString("lable_key_1");
            frmChild.lblKey2.Text = language.GetString("lable_key_2");
            frmChild.lblKey3.Text = language.GetString("lable_key_3");
            frmChild.lblKey4.Text = language.GetString("lable_key_4");
            frmChild.lblKey5.Text = language.GetString("lable_key_5");
            frmChild.lblKey6.Text = language.GetString("lable_key_6");
            frmChild.lblKey7.Text = language.GetString("lable_key_7");
            frmChild.lblKey8.Text = language.GetString("lable_key_8");
            frmChild.lblKey9.Text = language.GetString("lable_key_9");
            frmChild.lblKey10.Text = language.GetString("lable_key_10");
            frmChild.lblKey11.Text = language.GetString("lable_key_11");
            frmChild.lblKey12.Text = language.GetString("lable_key_12");
            frmChild.lblKey13.Text = language.GetString("lable_key_13");
            frmChild.lblKey14.Text = language.GetString("lable_key_14");
            frmChild.lblKey15.Text = language.GetString("lable_key_15");
            frmChild.lblKey16.Text = language.GetString("lable_key_16");
            frmChild.lblKey17.Text = language.GetString("lable_key_17");
            frmChild.lblKey18.Text = language.GetString("lable_key_18");
            frmChild.lblKey19.Text = language.GetString("lable_key_19");
            frmChild.lblKey20.Text = language.GetString("lable_key_20");
            frmChild.lblKey21.Text = language.GetString("lable_key_21");
            frmChild.lblKey22.Text = language.GetString("lable_key_22");
            frmChild.lblKey23.Text = language.GetString("lable_key_23");
            frmChild.lblKey24.Text = language.GetString("lable_key_24");
            frmChild.lblKey25.Text = language.GetString("lable_key_25");
            frmChild.lblDescText.Text = language.GetString("lable_description_text");
            frmChild.lbNoteText.Text = language.GetString("lable_note_text");
            frmChild.lblKeysText.Text = language.GetString("lable_keys_text");
            frmChild.lblColorText.Text = language.GetString("lable_color_text");
            frmChild.lblVersion.Text = Application.ProductVersion.ToString();
        }

        /// <summary>
        /// Переключение языка из меню формы.
        /// Значение сохраняется в файле кофигурации
        /// </summary>
        /// <param name="lang">
        /// Язык на который нужно переключить приложение
        /// </param>
        /// <returns>
        /// Новый выбранный язык
        /// </returns>
        public string SwitchLanguage(object lang)
        {
            if (lang == frmChild.menuLanguageRussian)
            {
                Settings.Default.language = "Russian";
                frmChild.menuLanguageRussian.Checked = true;
                frmChild.menuLanguageEnglish.Checked = false;
            }
            else if (lang == frmChild.menuLanguageEnglish)
            {
                Settings.Default.language = "English";
                frmChild.menuLanguageRussian.Checked = false;
                frmChild.menuLanguageEnglish.Checked = true;
            }

            return Settings.Default.language;
        }
    }
}
