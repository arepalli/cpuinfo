/****************************************************************************
**
**
** This file is a part of the Qt Cpu Info project
**
**
****************************************************************************/

#include "cpuinfomodel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QGuiApplication>

namespace  {
    const QString CPU_INFO_FILE_PATH    = "/proc/cpuinfo";
}

CpuInfoModel::CpuInfoModel(QObject *parent ) : QAbstractListModel(parent)
  , m_processorCount(0)
{
    updateCPUInfo();
    connect(&m_fileWatcher, SIGNAL(fileChanged(const QString &)), this, SLOT(updateCPUInfo()));
    m_fileWatcher.addPath(CPU_INFO_FILE_PATH);
}

int CpuInfoModel::rowCount(const QModelIndex &) const
{
    return m_cpuInfoList.count();
}

QVariant CpuInfoModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < rowCount())
        switch (role) {
        case ProcessorRole: return m_cpuInfoList.at(index.row()).processor;
        case KeyRole: return m_cpuInfoList.at(index.row()).key;
        case ValueRole: return m_cpuInfoList.at(index.row()).value;
        default: return QVariant();
    }
    return QVariant();
}

QHash<int, QByteArray> CpuInfoModel::roleNames() const
{
    static const QHash<int, QByteArray> roles {
        { ProcessorRole, "processor" },
        { KeyRole, "key" },
        { ValueRole, "value" }
    };
    return roles;
}

QVariantMap CpuInfoModel::get(int row) const
{
    const CpuInfo cpuInfo = m_cpuInfoList.value(row);
    return { {"processor", cpuInfo.processor}, {"key", cpuInfo.key}, {"value", cpuInfo.value} };
}

void CpuInfoModel::append(const QString &processor, const QString &key, const QString &value)
{
    int row = 0;
    while (row < m_cpuInfoList.count() && processor > m_cpuInfoList.at(row).processor)
        ++row;
    beginInsertRows(QModelIndex(), row, row);
    m_cpuInfoList.insert(row, {processor, key, value});
    endInsertRows();
}

void CpuInfoModel::set(int row, const QString &processor, const QString &key, const QString &value)
{
    if (row < 0 || row >= m_cpuInfoList.count())
        return;

    m_cpuInfoList.replace(row, { processor, key, value });
    dataChanged(index(row, 0), index(row, 0), { ProcessorRole, KeyRole, ValueRole });
}

QStringList CpuInfoModel::keys() const
{
    //qDebug() << m_keys;
    return m_keys;
}

quint32 CpuInfoModel::processorCount() const
{
    return m_processorCount;
}

void CpuInfoModel::setProcessorCount(quint32 processorCount)
{
    if (processorCount != m_processorCount) {
        m_processorCount = processorCount;
        emit processorCountChanged();
    }
}

/**
 * @brief updateCPUInfo
 * This function gets the cpuinfo located in /proc/cpuInfo file and format the each entry found in the file
 * @return
 * Returns list of QStrings. Each item in the list represent one entry from cpuInfo file
 */
void CpuInfoModel::updateCPUInfo()
{
    QFile cpuInfoFile(CPU_INFO_FILE_PATH);
    quint32 processorCount = 0;
    quint32 rowCount = 0;

    bool canReadFile = cpuInfoFile.open(QIODevice::ReadOnly);
    if(canReadFile) {
        QTextStream fileStream(&cpuInfoFile);

        QString lineData;
        //Read file content and format it
        do {
            lineData = fileStream.readLine();

            //Each entry in cpuInfo file is ":" separated <key,Val> pair
            QStringList lineSplitData = lineData.split(":");
            QString keyPart;
            QString valuePart;
            if(lineSplitData.length() == 2) {
                keyPart = lineSplitData.at(0).trimmed();//Trim extra spaces
                valuePart = lineSplitData.at(1).trimmed();//Trim extra spaces
            } else if(lineSplitData.length() == 1) {
                keyPart = lineSplitData.at(0).trimmed();//Trim extra spaces
            }

            if (keyPart == "processor")
                processorCount++;

            if (!keyPart.isEmpty()) {
                if (m_cpuInfoList.count() == rowCount) {
                    m_cpuInfoList.append({ QString::number(processorCount-1), keyPart, valuePart});
                    if (processorCount == 1) {
                        m_keys.append(keyPart);
                    }
                } else {
                    set(rowCount+1, QString::number(processorCount-1), keyPart, valuePart);
                }

                rowCount++;
            }

        } while(!lineData.isNull());

        cpuInfoFile.close();
    } else {
        qDebug()<<"FileOpenError: " << cpuInfoFile.errorString();
    }

    setProcessorCount(processorCount);
    //qDebug() << "updateCPUInfo, processorCount: " << processorCount;
}
