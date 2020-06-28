#ifndef PLISTREADER_H
#define PLISTREADER_H

#include <QXmlStreamReader>

class PListReader
{
public:
    PListReader();
    QString errorString() const;
    bool read(QIODevice *device);
    const QList<QVariant> data() const;
private:
    void readPList();
    void readDict(QList<QVariant> &array);
    void readArray(QList<QVariant> &array);
    void readKey(QMap<QString, QVariant> &dict);
private:
    QXmlStreamReader	m_xmlReader;
    QList<QVariant>		m_data;
};

#endif // PLISTREADER_H
