
namespace Programmer
{
    /// <summary>
    /// Класс для создания объектов инструментов
    /// Id - номер инструмента. Записывается в EEPROM (0 - 65535)
    /// Name - Название инструмента. Задано в программе DaVinci Resolve
    /// Desc - Описание инструмента. Вольный формат. Для удобства работы
    /// Note - Примечание инструмента. Вольный формат. Используется при необходимости
    /// Keys - Сочетание клавиш инструмента. Задано в программе для монтажа
    /// </summary>
    class KeyTool
    {
        public ushort Id { get; set; }
        public string Name { get; set; }
        public string Desc { get; set; }
        public string Note { get; set; }
        public string Keys { get; set; }
    }
}
