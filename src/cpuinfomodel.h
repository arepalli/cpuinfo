/****************************************************************************
**
**
** This file is a part of the Qt Cpu Info project
**
**
****************************************************************************/

#ifndef CPUINFOMODEL_H
#define CPUINFOMODEL_H

#include <QAbstractListModel>
#include <QFileSystemWatcher>

class CpuInfoModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum CpuInfoRole {
        KeyRole = Qt::DisplayRole,
        ValueRole = Qt::UserRole,
        ProcessorRole
    };
    Q_ENUM(CpuInfoRole)

    CpuInfoModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE QVariantMap get(int row) const;
    Q_INVOKABLE void append(const QString &processor, const QString &key, const QString  &value);
    Q_INVOKABLE void set(int row, const QString &processor, const QString &key, const QString  &value);
    Q_INVOKABLE void remove(int row);

public slots:
    void updateCPUInfo();

private:
    struct CpuInfo {
        QString processor;
        QString key;
        QString value;
    };

    QFileSystemWatcher m_fileWatcher;
    QList<CpuInfo> m_cpuInfoList;

};

#endif // CPUINFOMODEL_H
