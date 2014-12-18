#include "questionClass.h"

Question::Question(std::string question):
     _question(question), _answered(-1)
{
}

Question::Question(std::string question, std::vector< std::pair< int, std::string> > answers):
    _question(question), _answered(-1)
{
    int i;
    std::vector< std::pair <int, std::string> >::iterator it;

    for (i = 0, it = answers.begin(); it != answers.end(); ++it, ++i)
    {
        answer a;
        a.rate = it->first;
        a.text = it->second;
        a.checked = false;

        _answers[i] = a;
    }
}

void Question::addAnswer(std::pair < int, std::string > &pair)
{
    answer a;
    a.rate = pair.first;
    a.text = pair.second;
    a.checked = false;

    int size = _answers.size();
    _answers[size] = a;
}

void Question::setAnswered( int numberOfQuestion )
{
    if (_answered > -1)
        _answers.at(_answered).checked = false;

    _answered = numberOfQuestion;
    if (numberOfQuestion > -1)
        _answers.at(numberOfQuestion).checked = true;
}

void Question::clearAnswered()
{
    if (_answered)
         _answers.at(_answered).checked = false;

    _answered = 0;
}

int Question::getAnswered()
{
    return _answered;
}

std::string Question::getQuestion()
{
    return _question;
}

std::vector< std::string > Question::getAnwsers(int n)
{
    std::vector< std::string > vector;
    for (std::map< int, answer >::iterator it = _answers.begin(); it != _answers.end(); ++it)
    {
        vector.push_back(it->second.text);
    }
    return vector;
}

int Question::getRate()
{
    for (auto it :_answers)
        if (it.second.checked)
            return it.second.rate;
    return 0;
}

std::string Question::getQuestionResult()
{
    std::ostringstream os;

    os << "Question:\t" << _question << std::endl;
    if (_answered > -1)
        os << "Answer:\t" << _answers.at(_answered).text << "(" << _answers.at(_answered).rate << ")" << std::endl << std::endl;
    else
        os << "Not answered yet!!!" << std::endl << std::endl;
    return os.str();
    //for (std::map< int, answer >::iterator it = _answers.begin(); it != _answers.end(); ++it)
    //    std::cout << "Answer " << it->first << ": " << it->second.text << "(" << it->second.rate << ")" << std::endl;
}
