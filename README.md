# LowinPG

*Local Windowed Password Generator*. Программное обеспечение для генерации паролей, написанное на C++14 (Qt v5.11.0).    

* Алгоритм ГПСЧ: **Вихрь Мерсенна**

* Язык интерфейса: **Русский**

* Целевые устройства: **Настольные компьютеры**

## Основные возможности

Параметры генерируемых паролей:

* Качественные характеристики:
  
  * Наличие букв
  
  * Наличие цифр
  
  * Наличие специальных символов

* Количественные характеристики:
  
  * Длина пароля
  
  * Количество паролей (сгенерированных за раз)

Дополнительные функции:

* Экспорт паролей в текстовый документ по выбранному пути

* Копирование паролей в буфер обмена системы

## Отчеты по сборке

Программное обеспечение было запущено и проверено на следующих системах:

| Наименование системы                 | Семейство систем | Версия приложения | Дата       |
| ------------------------------------ | ---------------- | ----------------- | ---------- |
| Windows 10 Pro 22H2 64-bit           | Windows          | 1.3.2             | 27.01.2024 |
| Astra Linux CE 2.12.46 (Orel) x86_64 | Debian Linux     | 1.3.0             | 07.12.2023 |
| Windows 10 Pro 22H2 64-bit           | Windows          | 1.3.0             | 07.12.2023 |
| Astra Linux CE 2.12.46 (Orel) x86_64 | Debian Linux     | 1.2.+             | 03.12.2023 |
| Windows 10 Pro 22H2 64-bit           | Windows          | 1.2.+             | 03.12.2023 |
| Windows 10 Pro 22H2 64-bit           | Windows          | 1.1.+             | 25.11.2023 |
| Astra Linux CE 2.12.46 (Orel) x86_64 | Debian Linux     | 1.1.+             | 25.11.2023 |
| Astra Linux CE 2.12.46 (Orel) x86_64 | Debian Linux     | 1.0.0             | 06.11.2023 |

## Документация

Документация к данному программному обеспечению оформляется с помощью Doxygen в формате HTML. Архив с документацией прикрепляется к выпуску версии проекта.

## Тестирование

Unit-тестирование с помощью QTest проводится по следующим классам:
* RandomGenerator

## Интерфейс

![LowinPG в системе Astra Linux](img/lowinpg_astra_linux.png)
