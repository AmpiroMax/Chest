#ifndef SYSTEM_SIGNAL_H
#define SYSTEM_SIGNAL_H

enum class SystemSignal {
    None,
    Quit,   // Система просит завершить игру
    Restart // Можно легко добавить другие сигналы (перезапуск, загрузка меню и т.д.)
};

#endif // SYSTEM_SIGNAL_H
