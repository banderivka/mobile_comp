#ifndef QUESTIONCLASS_H
#define QUESTIONCLASS_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <QString>

class Question
{

    struct answer
    {
        std::string text;
        bool checked;
        int rate;
    };

private:
    std::string _question;
    std::map< int, answer > _answers;

    int _answered; // -1 if unchecked

public:
    Question(std::string);
    Question(std::string question, std::vector< std::pair< int, std::string> >);

    void addAnswer(std::pair < int, std::string > &);
    void setAnswered(int);
    void clearAnswered();

    int getAnswered();
    std::string getQuestion();
    std::vector< std::string > getAnwsers(int);
    int getRate();

    std::string getQuestionResult();

};

#endif // QUESTIONCLASS_H
