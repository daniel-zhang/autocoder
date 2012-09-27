#pragma  once

#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextDocument>
#include <QTextBlock>
#include <QRegExp>
#include <QDebug>
#include <QList>

class PuncFilter
{
public:
	PuncFilter();
	~PuncFilter();
	void setOutputFileName(QString fileName);
	void parsePuncInputFile( QString fileName );
	void outPut( bool isVerbose = true);

private:
	void clearAll();
	QString outFileName;
	QFile* file;
	QTextDocument *doc;
	QStringList codes;
	
	class lineCell
	{
	public:
		QString pattern;
		QString description;
	};
};