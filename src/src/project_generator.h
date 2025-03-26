/// @file: project_gennerator.h
///
/// @author Anirudha jadhav <anirudhasj441@gmail.com>

#include <QObject>

class ProjectGenerator: public QObject {
    Q_OBJECT

public:
    /// construtor 
    ProjectGenerator();
    
    virtual ~ProjectGenerator();

    void start();

};


