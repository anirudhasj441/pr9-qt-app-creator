/// @file: project_generator.h
///
/// Declaration of ProjectGenerator class
/// 
/// @author: Anirudha Jadhav(Devil) <anirudhasj441@gmail.com>
///
/// @version: 1.0
/// 
/// (C)2025 Coding Devil.
/// https://www.codingdevil.com/

#ifndef PROJECT_GENERATOR_H
#define PROJECT_GENERATOR_H

#include <QObject>
#include <nlohmann/json.hpp>

class QString;
class QDir;

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
    nlohmann::json mConfigJson; // configuration json object

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
    QString getStdInput( const QString& aPrompt, const bool& aAllowEmpty = false );


    /// get input from cli with default value if user not specified any.
    /// 
    /// @param[ in ] aPrompt 
    ///     prompt message
    /// @param[ in ] aDefault 
    ///     default value if user not provide any.
    /// 
    /// @return 
    ///     trimmed QString inputed by user.
    QString getStdInput( const QString& aPrompt, const QString& aDefault );

    /// create project structure
    ///
    /// @return
    ///     true if project structure created successfully.
    bool createProjectStructure();

    /// render template using inja template engine
    ///
    /// @param[ in ] aTemplate 
    ///     template file name
    /// @param[ in ] aTarget 
    ///     target file name
    ///
    /// @return 
    ///     true if template rendered successfully.
    bool renderTemplate( const QString& aTemplate, const QString& aTarget );

    /// copy directory recursively
    ///
    /// @param[ in ] sourceDir
    ///     source directory
    /// @param[ in ] targetDir
    ///     target directory
    ///
    /// @return
    ///     true if directory copied successfully.
    bool copyDirectoryRecursively(const QDir &sourceDir, const QDir &targetDir);

};

#endif //PROJECT_GENERATOR_H
