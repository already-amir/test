#ifndef SYS_H
#define SYS_H

#include <QObject>

class Sys : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int test READ test WRITE setTest NOTIFY testChanged FINAL)
    Q_PROPERTY(QString usr READ usr WRITE setUsr NOTIFY usrChanged FINAL)
    Q_PROPERTY(int temp READ temp WRITE setTemp NOTIFY tempChanged FINAL)
    Q_PROPERTY(bool lock READ lock WRITE setLock NOTIFY lockChanged FINAL)
public:
    explicit Sys(QObject *parent = nullptr);

    bool lock() const;
    void setlock(bool newLock);

    int temp() const;
    void settemp(int newTemp);

    QString usr() const;
    void setusr(const QString &newUsr);

    int test() const;
    void settest(int newTest);

signals:
    void lockChanged();
    void tempChanged();

    void usrChanged();

    void testChanged();

private:
    bool m_lock;
    int m_temp;
    QString m_usr;
    int m_test;
};

#endif // SYS_H
