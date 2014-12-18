#include "testClass.h"

void Test::loadQuestionsFromXml( const QDomNode& node )
{
    QDomNode domNode = node.firstChild();
    while(!domNode.isNull())
    {
        if(domNode.isElement())
        {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull())
            {
                if(domElement.tagName() == "name")
                {
                    std::string question = domElement.text().toLocal8Bit().constData();

                    Question qc(question);
                    _queVector.push_back(qc);

                }
                else if (domElement.tagName() == "answer")
                {
                    std::pair< int, std::string > answer(domElement.attribute("rate").toInt(), domElement.text().toLocal8Bit().constData());
                    _queVector.back().addAnswer(answer);
                }
            }
        }

        loadQuestionsFromXml(domNode);
        domNode = domNode.nextSibling();
    }

}

int Test::getNumberOfQuestions()
{
    return _queVector.size();
}

std::string Test::printTestResults()
{
    std::ostringstream os;
    std::string result;

    if (_queVector.size() == 0)
    {
        os << "Empty test!";
        return os.str();
    }
    else
        for (std::vector< Question >::iterator it = _queVector.begin(); it != _queVector.end(); ++it)
            result += it->getQuestionResult();
    os << "Number of answered questions:\t" << getNumberOfAnsweredQuestions() << std::endl << "Test rate:\t" << getTestRate() << std::endl;
    result += os.str();
    return result;
}

void Test::setActiveQuestion(int n)
{
    _numberOfActiveQuestion = n;
}

Question Test::getActiveQuestion()
{
    Question qc = _queVector.at(_numberOfActiveQuestion);
    return qc;
}

void Test::setAnswerOfActiveQuestion(int n)
{
    _queVector.at(_numberOfActiveQuestion).setAnswered(n);
}

int Test::getNumberOfActiveQuestion()
{
    return _numberOfActiveQuestion;
}

int Test::getNumberOfAnsweredQuestions()
{
    int k = 0;
    for (auto it : _queVector)
        if (it.getAnswered() > -1)
            k++;
    return k;
}

int Test::getTestRate()
{
    int k = 0;
    for (auto it : _queVector)
        k += it.getRate();
    return k;
}


Test::Test():
    _numberOfActiveQuestion(-1)
{
}
