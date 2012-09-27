#include "findpunc.h"

void PuncFilter::setOutputFileName( QString fileName )
{
	outFileName = fileName;
}

void PuncFilter::parsePuncInputFile( QString fileName )
{
	file = new QFile(fileName);
	doc = new QTextDocument;
	if (file->open(QFile::Text|QFile::ReadOnly) == false)
		return;
	doc->setPlainText(file->readAll());
	file->close();

	QRegExp punc("^\\S+");
	QRegExp desc("\\w+");

	QList<lineCell*> data;

	for (int i = 0; i < doc->lineCount(); i++)
	{
		QString line = doc->findBlockByLineNumber(i).text();
		int pos1 = punc.indexIn(line, 0);
		lineCell* lc = new lineCell;
		lc->pattern = line.mid(pos1, punc.matchedLength());

		int pos2 = desc.indexIn(line, 0);
		lc->description = line.mid(pos2, desc.matchedLength());

		data.append(lc);
	}

	int maxLen = 0;
	foreach(lineCell* lc, data)
	{
		maxLen = lc->description.length() > maxLen ? lc	->description.length() : maxLen;
	}

	//generate punctuation codes
	
	foreach(lineCell* lc, data)
	{
		int spaceNum = maxLen - lc->description.length();
		QString space;
		for (int i = 0; i < spaceNum; i++)
			space.append(" ");
		codes << QString("addTokenType ( \"_%1\", %2\"%3\",\t\t\"_punctuation\" );\n").arg(lc->description).arg(space).arg(lc->pattern);
	}

	//generate letters and digits codes
	char delta = 'a' - 'A';
	for (char i = 'a'; i <= 'z'; ++i)
		codes<<QString("addTokenType ( \"_%1\", \"%2\", \"_letter\" );\n").arg(i).arg(i);

	for (char i = 'A'; i <= 'Z'; i++)
		codes<<QString("addTokenType ( \"_%1\", \"%2\", \"_letter\" );\n").arg(i).arg(i);

	codes<<QString("addTokenType ( \"_underline\", \"_\", \"_letter\" );\n");

	for (char i = '0'; i <= '9'; i++)
		codes<<QString("addTokenType ( \"_%1\", \"%2\", \"_digit\" );\n").arg(i).arg(i);
}

void PuncFilter::outPut( bool isVerbose /*= true*/ )
{
	QFile outputFile(outFileName);
	outputFile.open(QFile::Text | QFile::WriteOnly);
	foreach(QString s, codes)
	{
		if	(isVerbose)
			qDebug()<<s;
		outputFile.write(s.toStdString().c_str());
	}
	outputFile.close();
}

PuncFilter::PuncFilter()
{

}

PuncFilter::~PuncFilter()
{
	clearAll();
}

void PuncFilter::clearAll()
{
	codes.clear();
}
