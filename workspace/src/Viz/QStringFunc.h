#ifdef QT_CORE_LIB
#ifndef LIB_VIZ_QSTRING_FUNC_H
#define LIB_VIZ_QSTRING_FUNC_H

#include <string>
#include <QString>
#include <QFileInfo>
#include <QObject>

/* *****************************************************************************
 *
 *                              All kinds of QSTR(...)
 *
 *            VizSTR(...) looks Stupid, so we use QSTR(...), but be
 *              careful the same name may be used by other library
 *
 * ****************************************************************************/

inline std::string STR(const QString& qstr)       { return qstr.toStdString(); }
inline QString QSTR(const char* char_ptr)         { return QObject::tr(char_ptr); }
inline QString QSTR(const std::string stdstr)     { return QObject::tr(stdstr.c_str()); }

inline QString QSTR(long n, int base=10)          { return QString::number(n, base); }
inline QString QSTR(ulong n, int base=10)         { return QString::number(n, base); }
inline QString QSTR(int n, int base=10)           { return QString::number(n, base); }
inline QString QSTR(uint n, int base=10)          { return QString::number(n, base); }
inline QString QSTR(qlonglong n, int base=10)     { return QString::number(n, base); }
inline QString QSTR(qulonglong n, int base=10)    { return QString::number(n, base); }

enum VizFloatStrFormatEnum {
    VizUpperSci    = 'E',   // use scientific notation and uppercase E`
    VizLowerSci    = 'e',   // use scientific notation and lowercase `e`
    VizNonSci      = 'f',   // do not use scientific notation
    VizUpperAdp    = 'G',   // use scientific notation or not base on the value and uppercase `E`
    VizLowerAdp    = 'g'    // use scientific notation or not base on the value and lowercase `e`
};//enum VizFloatStrFormatEnum

inline QString QSTR(double val, char fmt='g', int prc=6)      { return QString::number(val, fmt, prc); }
inline QString QSTR(float val, char fmt='g', int prc=6)       { return QString::number(val, fmt, prc); }

inline QString QSTR(bool bool_val,
                    const QString& yes=QSTR("true"),
                    const QString& no =QSTR("false")) {
    return bool_val ? yes : no;
}

inline bool VizToBool(const QString& str, const QString& yes=QSTR("true")) {
    return str==yes ? true : false;
}


/* *****************************************************************************
 *
 *                      std::string-like find API
 *
 * ****************************************************************************/

#ifndef VIZ_QSTR_NPOS
#define VIZ_QSTR_NPOS -1
#endif

const QString VIZ_EMPTY_QSTR = QString();

int VizFind(const QString& str, const QString& sub, int from=0);
int VizRFind(const QString& str, const QString& sub, int from=VIZ_QSTR_NPOS);
int VizFindFirstOf(const QString& str, const QString& sub, int from=0);
int VizFindFirstNotOf(const QString& str, const QString& sub, int from=0);
int VizFindLastOf(const QString& str, const QString& sub, int from=VIZ_QSTR_NPOS);
int VizFindLastNotOf(const QString& str, const QString& sub, int from=VIZ_QSTR_NPOS);

/* *****************************************************************************
 *
 *                           Sub String Operation
 *
 * ****************************************************************************/

QString VizSubStr(const QString& str, int bgn, int length=VIZ_QSTR_NPOS);
int VizSubCount(const QString& str, const QString& sub);
QString VizSubBetween(const QString& str,
                      const QString& head, const QString& tail,
                      int from=0);
QString VizSubBehind(const QString& str, const QString& flags,
                     int from=0);
QString VizSubBefore(const QString& str, const QString& flags,
                     int from=0);

/* *****************************************************************************
 *
 *                              String Edit
 *
 * ****************************************************************************/

void VizRemoveAll(QString* io_str_ptr, const QString& sub, int from=0);
void VizReplaceAll(QString* io_str_ptr,
                   const QString& oldsub, const QString& newsub,
                   int from=0);

/* *****************************************************************************
 *
 *                             VizStringTokenizer
 *
 * ****************************************************************************/

class VizStringTokenizer
{
private:
    VizStringTokenizer(const VizStringTokenizer&);
    VizStringTokenizer& operator=(const VizStringTokenizer&);

public:
    static QString Space() { return QString("\f\n\r\t\v "); }

public:
    VizStringTokenizer(const QString& space=Space());
    void operate(const QString& str);
    bool hasMore() const;
    QString next();
    QStringList getAll() const;

private:
    const QString* _str_ptr;
    QString _space;
    int _bgn, _end;

};//class VizStringTokenizer


/* *****************************************************************************
 *
 *                         File Path QString Operation
 *
 * ****************************************************************************/

inline QString VizFileName(const QString& file_path) {
    QFileInfo info(file_path); return info.fileName();
}

inline QString VizFileDir(const QString& file_path) {
    QFileInfo info(file_path); return info.path();
}

inline QString VizAbsolutePath(const QString& file_path) {
    QFileInfo info(file_path); return info.absoluteFilePath();
}

inline QString VizAbsoluteDir(const QString& file_path) {
    QFileInfo info(file_path); return info.absolutePath();
}

inline QString VizSuffix(const QString& file_path) {
    QFileInfo info(file_path); return info.suffix();
}

inline QString VizLongSuffix(const QString& file_path) {
    QFileInfo info(file_path); return info.completeSuffix();
}

inline QString VizBaseName(const QString& file_path) {
    QFileInfo info(file_path); return info.baseName();
}

inline QString VizLongBaseName(const QString& file_path) {
    QFileInfo info(file_path); return info.completeBaseName();
}

#endif // LIB_VIZ_QSTRING_FUNC_H
#endif // QT_CORE_LIB
