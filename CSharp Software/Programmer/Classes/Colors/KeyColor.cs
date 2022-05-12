
namespace Programmer
{
    /// <summary>
    /// Класс для создания объектов цветов колпачков клавиш
    /// Id - номер цвета. Записывается в EEPROM (0 - 65535)
    /// Name - Название цвета. Общепринятое название
    /// RedCh - Красный канал цвета в формате RGB
    /// GreenCh - Зеленый канал цвета в формате RGB
    /// BlueCh - Синий канал цвета в формате RGB
    /// </summary>
    class KeyColor
    {
        public ushort Id { get; set; }
        public string Name { get; set; }
        public int RedCh { get; set; }
        public int GreenCh { get; set; }
        public int BlueCh { get; set; }
    }
}
