/************************************************************************
Auto coder
************************************************************************/
#include <QCoreApplication>
#include <QString>
#include <QStringList>
#include <QList>
#include <QFile>
#include <QTextDocument>
#include <QTextBlock>
#include <QRegExp>
#include <QDebug>
#include <iostream>

#include "findpunc.h"
#include "findspecifier.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QString punctuationRaw = "C:\\WorkBase\\QtSandbox\\QtSandbox\\autocoder\\punctuation.txt";
	QString puncOutput = "C:\\WorkBase\\QtSandbox\\QtSandbox\\autocoder\\puncOutput.txt";

	QString specifierRaw = "C:\\WorkBase\\QtSandbox\\QtSandbox\\autocoder\\specifier.txt";
	QString speciOutput = "C:\\WorkBase\\QtSandbox\\QtSandbox\\autocoder\\speciOutput.txt";

	PuncFilter punc;
	punc.setOutputFileName(puncOutput);
	punc.parsePuncInputFile(punctuationRaw);
	punc.outPut();

	SpecifierFilter speci;
	speci.setOutputFileName(speciOutput);
	speci.parseInputFile(specifierRaw);
	speci.outPut();

	return a.exec();
	char s;
	std::cin>>s;
}
