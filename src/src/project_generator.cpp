
#include "project_generator.h"
#include <QDebug>
#include <QTextStream>
#include <QCoreApplication>
#include <QTimer>
#include <QStringList>
#include <jsoncons/json.hpp>


ProjectGenerator::
ProjectGenerator( QObject* aParent ): QObject(aParent) {
    /// Nothing here yet


}

ProjectGenerator::
~ProjectGenerator() {
    /// Nothing here yet

}

void ProjectGenerator::
start() {
    
    this->mConfigJson = this->getConfig();

    std::cout << jsoncons::pretty_print( this->mConfigJson );
    this->close();
}

jsoncons::json ProjectGenerator::
getConfig() {
    jsoncons::json config = jsoncons::json::object( );

    QString projectName = this->getStdInput( "Project Name: ");

    QString projectTypeChoice = this->getStdInput( 
        "Select project type\n"
        "1. GUI\n"
        "2. CLI\n\n"
        "Enter your choice(1/2): [default: 1]"
    );

    projectTypeChoice = projectTypeChoice.isEmpty() ? "1" : projectTypeChoice;
    
    if( !QStringList({ "1", "2" }).contains( projectTypeChoice )) {
        qDebug() << "!Invalid choice";
        return config;
    }


    ProjectType projectType = projectTypeChoice == "1" ? 
            ProjectType::GUI : ProjectType::CLI;

    QString projectTypeStr;

    switch (projectType){
        case ProjectType::GUI:
            /* code */
            projectTypeStr = "gui";
            break;
        case ProjectType::CLI:
            projectTypeStr = "cli";
            break;
        default:
            break;
    }


   config["project_name"] = projectName.toStdString();
   config["project_type"] = projectTypeStr.toStdString();


   return config;
}

QString ProjectGenerator::
getStdInput( QString aPrompt ) {
    /// defingin Text Streams for prompts
    QTextStream qOutput( stdout );
    QTextStream qInput( stdin );
    
    qOutput << aPrompt;
    qOutput.flush();
    
    QString value = qInput.readLine();

    return value.trimmed();
}

void ProjectGenerator::
close() {
    qDebug() << "Closing Applicattion...";

    QTimer::singleShot( 0, this, &QCoreApplication::quit );
}