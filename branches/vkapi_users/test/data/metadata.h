/*!
 * \file
 * \brief Заголовочный файл с описанием функций преобразования типов данных
 */

#ifndef METADATA_H
#define METADATA_H

#include <QString>
#include <QDateTime>

/*!
 * \brief Класс для преобразования типов данных
 */
class Metadata
{
private:
    Metadata() {}

public:

    enum TimeUnit
    {
        TU_SECONDS,
        TU_MINUTES,
        TU_HOURS
    };

    /*!
     * \brief Получение окончания единицы измерения времени
     * \param[in] value Количество времени
     * \param[in] timeUnit Единицы измерения времени
     * \return Окончание единицы измерения времени
     */
    static QString getSuffix(qint64 value, TimeUnit timeUnit = TU_MINUTES);

    /*!
     * \brief Преобразование разницы между подаваемым и текущим временем в строку в читаемом человеком формате
     * \param[in] dateTime Дата/время
     * \return Разница между подаваемым и текущим временем в читаемом человеком формате
     */
    static QString timeDiffStr(const QDateTime &dateTime);

    /*!
     * \brief Преобразование разницы между подаваемой и текущей датой в строку в читаемом человеком формате
     * \param dateTime Дата
     * \return Разница между подаваемой и текущей датой в читаемом человеком формате
     */
    static QString dateDiffStr(const QDateTime &dateTime);
};

#endif // METADATA_H
