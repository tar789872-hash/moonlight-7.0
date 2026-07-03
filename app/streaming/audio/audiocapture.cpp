#include "audiocapture.h"
#include <QAudioDeviceInfo>
#include <QDebug>

MicManager* MicManager::instance() {
    static MicManager s_instance;
    return &s_instance;
}

MicManager::MicManager(QObject* parent) : QObject(parent), m_currentMicIndex(0), m_boostLevel(100), m_shortcutKeys(2) {
    m_availableMics.append("Default System Microphone");
    const auto deviceInfos = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    for (const QAudioDeviceInfo &deviceInfo : deviceInfos) {
        if (!m_availableMics.contains(deviceInfo.deviceName())) {
            m_availableMics.append(deviceInfo.deviceName());
        }
    }
}

QStringList MicManager::availableMics() const { 
    return m_availableMics; 
}

int MicManager::currentMicIndex() const { 
    return m_currentMicIndex; 
}

void MicManager::setCurrentMicIndex(int index) {
    if (m_currentMicIndex != index && index >= 0 && index < m_availableMics.size()) {
        m_currentMicIndex = index;
        emit currentMicIndexChanged();
        qDebug() << "Selected microphone:" << m_availableMics.at(index);
    }
}

int MicManager::boostLevel() const { 
    return m_boostLevel; 
}

void MicManager::setBoostLevel(int level) {
    if (m_boostLevel != level) {
        m_boostLevel = level;
        emit boostLevelChanged();
        qDebug() << "Microphone boost level set to:" << level << "%";
    }
}

int MicManager::shortcutKeys() const { 
    return m_shortcutKeys; 
}

void MicManager::setShortcutKeys(int numKeys) {
    if (m_shortcutKeys != numKeys && numKeys >= 1 && numKeys <= 4) {
        m_shortcutKeys = numKeys;
        emit shortcutKeysChanged();
        qDebug() << "Microphone shortcut keys set to:" << numKeys;
    }
}
