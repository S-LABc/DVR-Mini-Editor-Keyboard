using System;
using System.Diagnostics;
using System.Windows.Forms;
using Programmer.Properties;

namespace Programmer
{
    public partial class MainForm : Form
    {
        readonly Language language;
        readonly Data data;
        readonly Messages messages;
        readonly Additional additional;
        readonly Programms programms = new Programms();

        public MainForm()
        {
            InitializeComponent();

            language = new Language(this);
            data = new Data(this, language.GetCurrentLanguage());
            messages = new Messages(language.GetCurrentLanguage());
            additional = new Additional(this);

            language.SetLanguageText();
            data.LoadingTools();
            data.LoadingColors();
        }

        #region Menu LAYOUT
        private void MenuLayoutOpen_Click(object sender, EventArgs e)
        {
            if (!data.OpenLayout())
            {
                messages.ShowMessageLayout();
            }
        }
        private void MenuLayoutSave_Click(object sender, EventArgs e)
        {
            data.SaveLayout();
        }

        private void MenuLayoutRestore_Click(object sender, EventArgs e)
        {
            if (!data.OpenDefaultLayout())
            {
                messages.ShowMessageLayout();
            }
        }
        #endregion

        #region Menu WRITE
        private void MenuWriteTools_Click(object sender, EventArgs e)
        {
            data.UpdateToolsBinary();
            string text = programms.WriteToolsDFU();
            messages.ShowMessageDFUUTIL(text);
        }
        private void MenuWriteFirmware_Click(object sender, EventArgs e)
        {
            string text = programms.WriteFirmwareDFU();
            messages.ShowMessageDFUUTIL(text);
        }
        private void MenuWriteBootloader_Click(object sender, EventArgs e)
        {
            string text = programms.WriteBootloaderSWD();
            messages.ShowMessageSTLINK(text);
        }
        private void MenuWriteAllFlash_Click(object sender, EventArgs e)
        {
            string text = programms.WriteAllFlashSWD();
            messages.ShowMessageSTLINK(text);
        }
        #endregion

        #region Menu READ
        private void MenuReadTools_Click(object sender, EventArgs e)
        {
            string text = programms.ReadToolsDFU();
            messages.ShowMessageDFUUTIL(text);
            data.UpdateToolsForm();
        }
        private void MenuReadFirmware_Click(object sender, EventArgs e)
        {
            string text = programms.ReadFirmwareDFU();
            messages.ShowMessageDFUUTIL(text);
        }
        private void MenuReadBootloader_Click(object sender, EventArgs e)
        {
            string text = programms.ReadBootloaderSWD();
            messages.ShowMessageSTLINK(text);
        }
        private void MenuReadAllFlash_Click(object sender, EventArgs e)
        {
            string text = programms.ReadAllFlash();
            messages.ShowMessageSTLINK(text);
        }
        #endregion

        #region Menu IMPORT
        /// <summary>
        /// Импорт двоичного файла (.bin) ИНСТРУМЕНТОВ EEPROM в рабочую папку программы
        /// Старый файл будет удалён
        /// Выбранные инструменты в окне формы будут заменены на новые из файла
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MenuImportTools_Click(object sender, EventArgs e)
        {
            if (data.ImportBin(Resources.EEPROM_NAME))
            {
                messages.ShowMessageImport(Resources.EEPROM_NAME);
            }
            else
            {
                messages.ShowMessageImport("error");
            }
        }

        /// <summary>
        /// Импорт двоичного файла (.bin) ПРОШИВКИ написанной в Arduino IDE в рабочую папку программы
        /// Старый файл будет удалён
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MenuImportFirmware_Click(object sender, EventArgs e)
        {
            if (data.ImportBin(Resources.FIRMWARE_NAME))
            {
                messages.ShowMessageImport(Resources.FIRMWARE_NAME);
            }
            else
            {
                messages.ShowMessageImport("error");
            }
        }

        /// <summary>
        /// Импорт двоичного файла (.bin) ЗАГРУЗЧИКА DFU в рабочую папку программы
        /// Старый файл будет удалён
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MenuImportBootloader_Click(object sender, EventArgs e)
        {
            if (data.ImportBin(Resources.BOOTLOADER_NAME))
            {
                messages.ShowMessageImport(Resources.BOOTLOADER_NAME);
            }
            else
            {
                messages.ShowMessageImport("error");
            }
        }

        /// <summary>
        /// Импорт двоичного файла (.bin) ВСЕЙ ПАМЯТИ (FLASH) в рабочую папку программы
        /// Старый файл будет удалён
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MenuImportAllFlash_Click(object sender, EventArgs e)
        {
            if (data.ImportBin(Resources.FLASH_NAME))
            {
                messages.ShowMessageImport(Resources.FLASH_NAME);
            }
            else
            {
                messages.ShowMessageImport("error");
            }
        }
        #endregion

        #region Menu EXPORT
        /// <summary>
        /// Экспорт двоичного файла (.bin) ИНСТРУМЕНТОВ EEPROM в место указанное пользователем
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MenuExportTools_Click(object sender, EventArgs e)
        {
            if (data.ExportBin(Resources.EEPROM_NAME))
            {
                messages.ShowMessageExport(Resources.EEPROM_NAME);
            }
            else
            {
                messages.ShowMessageExport("error");
            }
        }

        /// <summary>
        /// Экспорт двоичного файла (.bin) ПРОШИВКИ написанной в Arduino IDE в место указанное пользователем
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MenuExportFirmware_Click(object sender, EventArgs e)
        {
            if (data.ExportBin(Resources.FIRMWARE_NAME))
            {
                messages.ShowMessageExport(Resources.FIRMWARE_NAME);
            }
            else
            {
                messages.ShowMessageExport("error");
            }
        }

        /// <summary>
        /// Экспорт двоичного файла (.bin) ЗАГРУЗЧИКА DFU в место указанное пользователем
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MenuExportBootloader_Click(object sender, EventArgs e)
        {
            if (data.ExportBin(Resources.BOOTLOADER_NAME))
            {
                messages.ShowMessageExport(Resources.BOOTLOADER_NAME);
            }
            else
            {
                messages.ShowMessageExport("error");
            }
        }

        /// <summary>
        /// Экспорт двоичного файла (.bin) ВСЕЙ ПАМЯТИ (FLASH) в место указанное пользователем
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MenuExportAllFlash_Click(object sender, EventArgs e)
        {
            if (data.ExportBin(Resources.FLASH_NAME))
            {
                messages.ShowMessageExport(Resources.FLASH_NAME);
            }
            else
            {
                messages.ShowMessageExport("error");
            }
        }
        #endregion

        #region Menu CHECK
        private void MenuCheckDFU_Click(object sender, EventArgs e)
        {
            string text = programms.ListDFU();
            messages.ShowMessageDFUUTIL(text);
        }
        private void MenuCheckSWD_Click(object sender, EventArgs e)
        {
            string text = programms.ListSWD();
            messages.ShowMessageSTLINK(text);

        }
        #endregion

        #region DRIVER
        private void MenuDriverDFU_Click(object sender, EventArgs e)
        {
            if (programms.InstallDriverDFU())
            {
                messages.ShowMessageDriver("dfu ok");
            }
            else
            {
                messages.ShowMessageDriver("dfu error");
            }
        }
        private void MenuDriverSWD_Click(object sender, EventArgs e)
        {
            if (programms.InstallDriverSWD())
            {
                messages.ShowMessageDriver("swd ok");
            }
            else
            {
                messages.ShowMessageDriver("swd error");
            }
        }
        #endregion

        #region Form MAIN
        private void FrmMain_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop) &&
                ((e.AllowedEffect & DragDropEffects.Move) == DragDropEffects.Move))
            {
                e.Effect = DragDropEffects.Move;
            }
        }
        private void FrmMain_DragDrop(object sender, DragEventArgs e)
        {
            if (!data.OpenLayoutDragDrop(e))
            {
                messages.ShowMessageLayout();
            }
        }
        private void FrmMain_FormClosing(object sender, FormClosingEventArgs e) => data.SaveUserChenges();
        private void FrmMain_Paint(object sender, PaintEventArgs e) => additional.DrawWheelAndLEDs(e, additional.GetColorWheel());
        #endregion

        #region OTHER
        private void CmbKeys_SelectedIndexChanged(object sender, EventArgs e) => data.ShowToolInfo(sender);
        private void CmbKeys_Click(object sender, EventArgs e) => data.ShowToolInfo(sender);
        private void CmbColors_DrawItem(object sender, DrawItemEventArgs e) => additional.DrawColorItem(sender, e);
        private void CmbColors_SelectedIndexChanged(object sender, EventArgs e) => data.ShowColorInfo(sender);
        private void CmbColors_Click(object sender, EventArgs e) => data.ShowColorInfo(sender);
        private void MenuLanguageItem_Click(object sender, EventArgs e)
        {
            string new_lang = language.SwitchLanguage(sender);
            messages.ShowMessageChangeLanguage(new_lang);
            Application.Restart();
        }
        private void LblProjectLink_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e) => Process.Start(Resources.PROJECT_WEB_LINK);
        #endregion        
    }
}
