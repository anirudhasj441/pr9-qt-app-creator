
#include "project_generator.h"
#include <QDebug>
#include <QTextStream>
#include <QCoreApplication>
#include <QTimer>
#include <QStringList>
#include <nlohmann/json.hpp>


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

    qDebug().noquote() << QString::fromStdString(this->mConfigJson.dump(4));
    this->close();
}

nlohmann::json ProjectGenerator::
getConfig() {
    nlohmann::json config = nlohmann::json::object( );

    /////////////////////// Project Name ///////////////////////////////////////
    QString projectName = this->getStdInput( "Project Name: ");

    ////////////////////// Project type ////////////////////////////////////////
    QMap<QString, ProjectType> choiceToProjectTypeMAp = {
        { "1", ProjectType::GUI },
        { "2", ProjectType::CLI }
    };

    QMap<ProjectType, QString> ProjectTypeToStringMap = {
        { ProjectType::GUI, "gui" },
        { ProjectType::CLI, "cli" }
    };

    QString projectTypeChoice = this->getStdInput( 
        "Select project type\n"
        "1. GUI\n"
        "2. CLI\n\n"
        "Enter your choice(1/2): [default: 1]", "1"
    );
    
    if( !choiceToProjectTypeMAp.contains( projectTypeChoice )) {
        qDebug() << "!Invalid choice";
        return config;
    }

    ProjectType projectType = choiceToProjectTypeMAp[ projectTypeChoice ];

    //////////////////////// additional libraries //////////////////////////////

    QStringList additionalLibs = QStringList({
        "cds", "jsoncons", "qt-qwt"
    });

    nlohmann::json additionalLibsObj = nlohmann::json::object();
    for( const QString& library: additionalLibs ) {
        if( ProjectType::CLI == projectType && "qt-qwt" == library ) {
            additionalLibsObj[ library.toStdString()] = false ;
            continue;
        }

        QString libCofirmation = this->getStdInput( 
                QString( "Would you like to include %1 (Y/N): [default: N]" ).
                arg( library ),
                "N"
        );

        additionalLibsObj[ library.toStdString()] = 
                libCofirmation.toLower() == "y";
    }
    
    config[ "project_name" ] = projectName.toStdString();
    config[ "project_type" ] = ProjectTypeToStringMap[projectType].
            toStdString();
    config[ "additional_libs" ] = additionalLibsObj;

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


QString ProjectGenerator::
getStdInput( QString aPrompt, QString aDefault ) {
    QString value = this->getStdInput( aPrompt );

    value = value.isEmpty() ? aDefault : value;

    return value;
}

void ProjectGenerator::
close() {
    qDebug() << "Closing Applicattion...";

    QTimer::singleShot( 0, this, &QCoreApplication::quit );
}