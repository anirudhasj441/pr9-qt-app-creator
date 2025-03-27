/// @file: project_generator.h
///
/// @author Anirudha Jadhav(Devil) <anirudhasj441@gmail.com>

#include <QObject>

class ProjectGenerator: public QObject {
    Q_OBJECT

public:
    /// constructor 
    ProjectGenerator();
    
    virtual ~ProjectGenerator();

    void start();

};


