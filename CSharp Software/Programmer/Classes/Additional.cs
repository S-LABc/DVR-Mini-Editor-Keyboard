using System;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

namespace Programmer
{
    /// <summary>
    /// Вспомогальный класс для отрисовки графики
    /// </summary>
    class Additional
    {
        readonly MainForm frmChild;

        /// <summary>
        /// Конструктор класса
        /// </summary>
        /// <param name="frm_main">
        /// Ссылка на главную форму для доступа к ее элементам
        /// </param>
        public Additional(MainForm frm_main)
        {
            frmChild = frm_main;
        }

        /// <summary>
        /// Отрисовка светодиодов и ручки поиска на форме
        /// </summary>
        /// <param name="paint">
        /// Событие отрисовки
        /// </param>
        /// <param name="color">
        /// Цвет ручки поиска
        /// </param>
        public void DrawWheelAndLEDs(PaintEventArgs paint, Color color)
        {
            int led_d = 10;
            int led_x, led_y;
            int wheel_d = 160;
            int wheel_x = frmChild.cmbKey25.Location.X + frmChild.cmbKey25.Size.Width / 2 - wheel_d / 2;
            int wheel_y = frmChild.cmbKey25.Location.Y + frmChild.cmbKey25.Size.Height / 2 - wheel_d / 2;
            /* Ручка поиска */
            paint.Graphics.FillEllipse(new SolidBrush(color), wheel_x, wheel_y, wheel_d, wheel_d);
            /* Светодиоды */
            foreach (var cmb in frmChild.Controls.OfType<ComboBox>().Where(cbox => string.Equals("key_tool", cbox.Tag as String)))
            {
                if (cmb.TabIndex == 43 || cmb.TabIndex == 45 || cmb.TabIndex == 47)
                {
                    led_x = cmb.Location.X + cmb.Size.Width / 2 - led_d / 2;
                    led_y = cmb.Location.Y + cmb.Size.Height + led_d / 4;
                    paint.Graphics.FillEllipse(new SolidBrush(Color.Orange), led_x, led_y, led_d, led_d);
                }
            }
            paint.Graphics.Dispose();
        }
        /// <summary>
        /// Отрисовка цветных прямоугольников в списках цветов колпачков клавиш
        /// </summary>
        /// <param name="combobox">
        /// Выпадающий список с цветом колпачка на форме
        /// </param>
        /// <param name="e">
        /// Событие отрисовки элемента списка
        /// </param>
        public void DrawColorItem(object combobox, DrawItemEventArgs e)
        {
            var cmb = (ComboBox)combobox;
            KeyColor keyColor = (KeyColor)cmb.Items[e.Index];

            Color rectColor = Color.FromArgb(keyColor.RedCh, keyColor.GreenCh, keyColor.BlueCh);
            var rectangle = new Rectangle(e.Bounds.Left, e.Bounds.Top, e.Bounds.Width - 1, e.Bounds.Height - 1);

            using (var solidBrush = new SolidBrush(rectColor))
            {
                e.Graphics.FillRectangle(solidBrush, rectangle);
            }
        }
        /// <summary>
        /// Получение выбранного цвета в списке для ручки поиска
        /// </summary>
        /// <returns>
        /// Color Цвет который выбран в списке
        /// </returns>
        public Color GetColorWheel()
        {
            var cmb = frmChild.cmbColor24;
            KeyColor colorSel = (KeyColor)cmb.SelectedItem;

            return Color.FromArgb(colorSel.RedCh, colorSel.GreenCh, colorSel.BlueCh);
        }
    }
}
