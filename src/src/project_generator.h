/// @file: project_generator.h
///
/// @author Anirudha Jadhav(Devil) <anirudhasj441@gmail.com>

#ifndef PROJECT_GENERATOR_H
#define PROJECT_GENERATOR_H

#include <QObject>
#include <nlohmann/json.hpp>

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
    nlohmann::json mConfigJson;

private:
    /// getting inputs from user by cli
    ///
    ///
    nlohmann::json getConfig();

    /// get input from cli
    ///
    /// @param[ in ] aPrompt 
    ///     prompt message
    /// 
    /// @return 
    ///     trimmed QString inputed by user.
    QString getStdInput( QString aPrompt, bool aAllowEmpty = false );


    /// get input from cli with default value if user not specified any.
    /// 
    /// @param[ in ] aPrompt 
    ///     prompt message
    /// @param[ in ] aDefault 
    ///     default value if user not provide any.
    /// 
    /// @return 
    ///     trimmed QString inputed by user.
    QString getStdInput( QString aPrompt, QString aDefault );

    

    bool renderTemplate( QString aTemplate, QString aTarget );

};

#endif //PROJECT_GENERATOR_H
