/// @file: project_generator.h
///
/// @author Anirudha Jadhav(Devil) <anirudhasj441@gmail.com>

#include <QObject>
#include <jsoncons/json.hpp>

class QString;

enum class ProjectType {
    GUI,
    CLI
} typedef ProjectType;

class ProjectGenerator: public QObject {
    Q_OBJECT

public:
    /// constructor 
    ProjectGenerator( QObject* aParent = nullptr );
    
    /// destructor
    virtual ~ProjectGenerator();

public:
    /// entry function
    void start();

    /// closes the application
    void close();

private:
    jsoncons::json mConfigJson;

private:
    /// getting inputs from user by cli
    ///
    ///
    jsoncons::json getConfig();

    QString getStdInput( QString aPrompt );


};


