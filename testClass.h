#ifndef QUESTIONGROUPBOX_H
#define QUESTIONGROUPBOX_H

#include <vector>
#include <questionClass.h>
#include <QtXml>
#include <QDebug>
#include <iostream>
#include <string>
#include <sstream>

class Test
{

public:
    Test();
    ~Test();

public:

    void setActiveQuestion(int);
    void setAnswerOfActiveQuestion(int);

    Question getActiveQuestion();
    int getNumberOfQuestions();
    int getNumberOfActiveQuestion();
    int getNumberOfAnsweredQuestions();
    int getTestRate();

    void loadQuestionsFromXml(const QDomNode&);
    std::string printTestResults();


private:
    std::vector< Question > _queVector;

    int _numberOfActiveQuestion;
};

#endif // QUESTIONGROUPBOX_H
