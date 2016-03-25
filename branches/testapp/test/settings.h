#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

class Settings
{
private:
    Settings() {}
    Settings(const Settings &) {}
    Settings& operator=(Settings&) {}

public:
    static QString getSetting(const QString &name, const QString &defaultValue = QString());
    static bool setSetting(const QString &name, const QString &value);
};

#endif // SETTINGS_H
