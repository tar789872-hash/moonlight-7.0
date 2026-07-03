#pragma once

#include <QObject>
#include <QStringList>

class MicManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList availableMics READ availableMics NOTIFY availableMicsChanged)
    Q_PROPERTY(int currentMicIndex READ currentMicIndex WRITE setCurrentMicIndex NOTIFY currentMicIndexChanged)
    Q_PROPERTY(int boostLevel READ boostLevel WRITE setBoostLevel NOTIFY boostLevelChanged)
    Q_PROPERTY(int shortcutKeys READ shortcutKeys WRITE setShortcutKeys NOTIFY shortcutKeysChanged)

public:
    static MicManager* instance();
    
    QStringList availableMics() const;
    
    int currentMicIndex() const;
    void setCurrentMicIndex(int index);
    
    int boostLevel() const;
    void setBoostLevel(int level);
    
    // Number of keys (1-4) for the shortcut combination
    int shortcutKeys() const;
    void setShortcutKeys(int numKeys);

signals:
    void availableMicsChanged();
    void currentMicIndexChanged();
    void boostLevelChanged();
    void shortcutKeysChanged();

private:
    explicit MicManager(QObject* parent = nullptr);
    
    QStringList m_availableMics;
    int m_currentMicIndex;
    int m_boostLevel;
    int m_shortcutKeys;
};
