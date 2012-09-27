#pragma  once

#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextDocument>
#include <QTextBlock>
#include <QRegExp>
#include <QDebug>

class SpecifierFilter
{
public:
	SpecifierFilter();
	~SpecifierFilter();
	
	void setOutputFileName(QString fileName);
	void parseInputFile( QString fileName );
	QStringList outPut( bool isVerbose = true);

private:
	void clearAll();
	QString outputFileName;
	QFile* file;
	QTextDocument *doc;
	QStringList specifiers;
};