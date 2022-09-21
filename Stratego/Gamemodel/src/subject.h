#ifndef SUBJECT_H
#define SUBJECT_H
#include <string>
/**
 * @brief The Subject class
 */
class Observer;
class Subject
{
  public:
    /**
    * @brief addObserver adds an observer to the observers vector
    * @param o observer to add
    */
    virtual void addObserver(Observer * o) = 0;
    /**
     * @brief removeObserver removes an observer from the observers list
     * @param o observer to remove
     */
    virtual void removeObserver(Observer * o) = 0;
    /**
     * @brief notify notify that a change has happened in the model, and that the view must be updated
     */
    virtual void notify(const std::string & propertyName) = 0;

};

#endif // SUBJECT_H
