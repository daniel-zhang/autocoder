#include "findspecifier.h"



void SpecifierFilter::parseInputFile( QString fileName )
{
	file = new QFile(fileName);
	doc = new QTextDocument;
	if (file->open(QFile::Text|QFile::ReadOnly) == false)
		return;
	doc->setPlainText(file->readAll());
	file->close();

	QString line;
	QString specifier;
	QRegExp speci_regexp("^\\b\\w+\\b");

	for (int i = 0; i < doc->lineCount(); i++)
	{
		line = doc->findBlockByLineNumber(i).text();
		int pos = speci_regexp.indexIn(line, 0);
		if (pos != -1)
		{
			specifier = line.mid(pos, speci_regexp.matchedLength());
			bool flag = true;
			foreach(QString s, specifiers)
				if (s == specifier)
					flag = false;
			if (flag)
				specifiers<<specifier.toLower();
		}
	}
	//3 function calling specifiers that start with a upper-case letter:
	specifiers<<QString("Global");
	specifiers<<QString("Super");
	specifiers.sort();
}

QStringList SpecifierFilter::outPut( bool isVerbose )
{
	QFile file(outputFileName);
	if ( file.open(QFile::Text | QFile::WriteOnly) == false ) return specifiers;

	if	(isVerbose) qDebug("Total specifiers: %d", specifiers.count());
	
	int maxLen = 0;
	foreach(QString s, specifiers)
		maxLen = maxLen>s.length() ? maxLen : s.length();

	int itemsCount = 0;
	int itemsPerLine = 6;
	foreach(QString s, specifiers)
	{
		if (isVerbose) qDebug()<<s;
		itemsCount++;
		if (itemsCount % itemsPerLine == 0)
		{
			file.write( (s+"\n").toStdString().c_str() );
		}
		else
		{
			QString spacer = " ";
			for(int i = 0 ; i < maxLen - s.length(); i++)
				spacer.append(" ");

			file.write( (s+spacer).toStdString().c_str() );
		}
		
	}
	file.close();
	return specifiers;
}

SpecifierFilter::SpecifierFilter(){}

SpecifierFilter::~SpecifierFilter()
{
	clearAll();
}

void SpecifierFilter::clearAll()
{
	specifiers.clear();
}

void SpecifierFilter::setOutputFileName( QString fileName )
{
	outputFileName = fileName;
}
