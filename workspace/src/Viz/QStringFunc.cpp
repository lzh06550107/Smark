#ifdef QT_CORE_LIB
#include <QString>
#include <QStringList>
#include "Viz/QStringFunc.h"

/* *****************************************************************************
 *
 *                      std::string-like find API
 *
 * ****************************************************************************/

int VizFind(const QString& str, const QString& sub, int from) {
    return str.indexOf(sub, from);
}

int VizRFind(const QString& str, const QString& sub, int from) {
    return str.lastIndexOf(sub, from);
}

int VizFindFirstOf(const QString& str, const QString& sub, int from)
{
    if(VIZ_QSTR_NPOS==from) return VIZ_QSTR_NPOS;
    Q_ASSERT(0<=from && from<str.size());
    for(int i=from; i<str.size(); ++i)
        for(int j=0; j<sub.size(); ++j)
            if(str[i] == sub[j]) return i;
    return VIZ_QSTR_NPOS;
}

int VizFindFirstNotOf(const QString& str, const QString& sub, int from)
{
    if(VIZ_QSTR_NPOS==from) return VIZ_QSTR_NPOS;
    Q_ASSERT(0<=from && from<str.size());
    bool has_one;
    for(int i=from; i<str.size(); ++i) {
        has_one = false;
        for(int j=0; j<sub.size(); ++j)
            has_one |= (str[i]==sub[j]);
        if(!has_one) return i;
    }
    return VIZ_QSTR_NPOS;
}

int VizFindLastOf(const QString& str, const QString& sub, int from)
{
    if(VIZ_QSTR_NPOS==from) from = str.size()-1;
    Q_ASSERT(0<=from && from<str.size());
    for(int i=from; i>=0; --i)
        for(int j=0; j<sub.size(); ++j)
            if(str[i] == sub[j]) return i;
    return VIZ_QSTR_NPOS;
}

int VizFindLastNotOf(const QString& str, const QString& sub, int from)
{
    if(VIZ_QSTR_NPOS==from) from = str.size()-1;
    Q_ASSERT(0<=from && from<str.size());
    bool has_one;
    for(int i=from; i>=0; --i) {
        has_one = false;
        for(int j=0; j<sub.size(); ++j)
            has_one |= (str[i]==sub[j]);
        if(!has_one) return i;
    }
    return VIZ_QSTR_NPOS;
}


/* *****************************************************************************
 *
 *                           Sub String Operation
 *
 * ****************************************************************************/

QString VizSubStr(const QString& str, int bgn, int length)
{
    if(VIZ_QSTR_NPOS==bgn) return QString();
    if(VIZ_QSTR_NPOS==length) length = str.size() -bgn;
    Q_ASSERT(0<=bgn && bgn<str.size());
    Q_ASSERT(0<=length && length<str.size()-bgn);
    QString sub(length, QChar('X'));
    for(int i=0; i<length; ++i)
        sub[i] = str[bgn+i];
    return sub;
    return QString();
}

int VizSubCount(const QString& str, const QString& sub) {
    return str.count(sub);
}

QString VizSubBetween(const QString& str,
                       const QString& head, const QString& tail,
                       int from)
{
    if(VIZ_QSTR_NPOS==from) return QString();
    Q_ASSERT(0<=from && from<str.size());
    int bgn = str.indexOf(head, from);
    int end = str.indexOf(tail, bgn+head.size());
    if(VIZ_QSTR_NPOS==bgn || VIZ_QSTR_NPOS==end) {
        return QString();
    } else {
        bgn += head.size();
        return VizSubStr(str, bgn, end-bgn);
    }
}

QString VizSubBehind(const QString& str, const QString& flags, int from)
{
    if(VIZ_QSTR_NPOS==from) return QString();
    Q_ASSERT(0<=from && from<str.size());
    int bgn = str.indexOf(flags, from);
    if(VIZ_QSTR_NPOS==bgn)
        return QString();
    else
        return VizSubStr(str, bgn+flags.size(), VIZ_QSTR_NPOS);
}

QString VizSubBefore(const QString& str, const QString& flags, int from)
{
    if(VIZ_QSTR_NPOS==from) return QString();
    Q_ASSERT(0<=from && from<str.size());
    int end = str.indexOf(flags, from);
    if(VIZ_QSTR_NPOS==end)
        return QString();
    else
        return VizSubStr(str, 0, end);
}

/* *****************************************************************************
 *
 *                              String Edit
 *
 * ****************************************************************************/

void VizRemoveAll(QString* io_str_ptr, const QString& sub, int from)
{
    if(VIZ_QSTR_NPOS==from) return;
    Q_ASSERT(0<=from && from<io_str_ptr->size());
    for(int pos=io_str_ptr->indexOf(sub, from);
        pos!=VIZ_QSTR_NPOS; pos=io_str_ptr->indexOf(sub, pos)) {
        io_str_ptr->remove(pos, sub.size());
    }
}

void VizReplaceAll(QString* io_str_ptr,
                    const QString& oldsub, const QString& newsub,
                    int from)
{
    if(VIZ_QSTR_NPOS==from) return;
    Q_ASSERT(0<=from && from<io_str_ptr->size());
    int pos = io_str_ptr->indexOf(oldsub, from);
    while(VIZ_QSTR_NPOS!=pos) {
        io_str_ptr->replace(pos, oldsub.size(), newsub);
        pos += newsub.size();
        pos = io_str_ptr->indexOf(oldsub, pos);
    }
}

/* *****************************************************************************
 *
 *                         VizStringTokenizer
 *
 * ****************************************************************************/


VizStringTokenizer::VizStringTokenizer(const QString& space)
    :_str_ptr(NULL), _space(space), _bgn(0), _end(0)
    { /*nothing need to do*/ }

void VizStringTokenizer::operate(const QString& str) {
    _str_ptr = &str;
    _bgn = VizFindFirstNotOf(*_str_ptr, _space);
    _end = VizFindFirstOf(*_str_ptr, _space, _bgn);
}

bool VizStringTokenizer::hasMore() const {
    Q_ASSERT(_str_ptr != NULL);
    return (_bgn != _end);
}

QString VizStringTokenizer::next()
{
    Q_ASSERT(_str_ptr != NULL);
    QString token;
    if(VIZ_QSTR_NPOS!=_bgn && VIZ_QSTR_NPOS!=_end) {
        token = VizSubStr(*_str_ptr, _bgn, _end-_bgn);
        _bgn = VizFindFirstNotOf(*_str_ptr, _space, _end);
        _end = VizFindFirstOf(*_str_ptr, _space, _bgn);
    } else if (VIZ_QSTR_NPOS!=_bgn  && VIZ_QSTR_NPOS==_end) {
        token = VizSubStr(*_str_ptr, _bgn, VIZ_QSTR_NPOS);
        _bgn = VizFindFirstNotOf(*_str_ptr, _space, _end);
    }
    return token;
}

QStringList VizStringTokenizer::getAll() const
{
    QStringList list;
    int temp_bgn = VizFindFirstNotOf(*_str_ptr, _space);
    int temp_end = VizFindFirstOf(*_str_ptr, _space, temp_bgn);
    while(temp_bgn!=temp_end)
    {
        if(VIZ_QSTR_NPOS!=temp_bgn && VIZ_QSTR_NPOS!=temp_end) {
            list.push_back(VizSubStr(*_str_ptr, temp_bgn, temp_end-temp_bgn));
            temp_bgn = VizFindFirstNotOf(*_str_ptr, _space, temp_end);
            temp_end = VizFindFirstOf(*_str_ptr, _space, temp_bgn);
        } else if (VIZ_QSTR_NPOS!=temp_bgn  && VIZ_QSTR_NPOS==temp_end) {
            list.push_back(VizSubStr(*_str_ptr, temp_bgn, _str_ptr->size()-temp_bgn));
            temp_bgn = VizFindFirstNotOf(*_str_ptr, _space, temp_end);
        }
    }//while

    return list;
}

#endif //QT_CORE_LIB
