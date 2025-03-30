
#include "project_generator.h"
#include "exceptions/empty_input_exception.h"
#include <QDebug>
#include <QTextStream>
#include <QCoreApplication>
#include <QTimer>
#include <QStringList>
#include <QTemporaryDir>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <nlohmann/json.hpp>
#include <inja/inja.hpp>

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

    this->createProjectStructure();
    this->close();
}

nlohmann::json ProjectGenerator::
getConfig() {
    nlohmann::json config = nlohmann::json::object( );

    /////////////////////// Project Name ///////////////////////////////////////
    QString projectName = this->getStdInput( "Project Name: ");

    //////////////////////////// App Name //////////////////////////////////////
    QString appName = this->getStdInput( "App Name: ");

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
        "Enter your choice(1/2): [default: 1]", QString("1")
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
    config[ "app_name" ] = appName.toStdString();
    config[ "project_type" ] = ProjectTypeToStringMap[projectType].
            toStdString();
    config[ "additional_libs" ] = additionalLibsObj;

    return config;
}

bool ProjectGenerator::
createProjectStructure() {
    QTemporaryDir tempDir;

    if( !tempDir.isValid()) { return false; }

    QDir projectDir( tempDir.filePath( QString::fromStdString( 
            this->mConfigJson[ "project_name" ])));
    
    QDir targetDir( "./" );

    qDebug() << projectDir.absoluteFilePath( "src" );
    
    projectDir.mkdir( projectDir.absoluteFilePath( "src" ));

    QStringList templateList = QStringList({
        "CMakeLists.txt.template",
        "src/CMakeLists.txt.template"
    });

    for( const QString& templateName: templateList ) {
        QString templateFilePath = QString( ":/templates/templates/%1").
                arg( templateName );
        QString targetFilePath = projectDir.absoluteFilePath( 
                templateName.split( ".template").first()); 
        qDebug() << "targetFilePath: " << targetFilePath;
        if( !this->renderTemplate( templateFilePath, targetFilePath )) {
            qDebug() << "failed to render template:" << templateFilePath;
            continue;
        }

    }

    this->copyDirectoryRecursively( projectDir, targetDir );
    
    return true;
}

bool ProjectGenerator::
renderTemplate( const QString& aTemplate, const QString& aTarget ) {
    QFile templateFile( aTemplate );
    QFile targetFile( aTarget );

    if( !templateFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "failed to open file!!!";
        return false;
    }

    if( !targetFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "failed to open file: " << QFileInfo( targetFile ).baseName();
        return false;
    }

    QString fileContent = templateFile.readAll();

    std::string renderString = inja::render( 
        fileContent.toStdString(), 
        this->mConfigJson 
    );

    QTextStream targetFileStream( &targetFile );

    targetFileStream << QString::fromStdString( renderString );

    templateFile.close();
    targetFile.close();
    return true;
}

bool ProjectGenerator::
copyDirectoryRecursively(const QDir &sourceDir, const QDir &targetDir) {
    if (!sourceDir.exists()) {
        qWarning() << "Source directory does not exist:" << sourceDir.absolutePath();
        return false;
    }

    if (!targetDir.exists() && !targetDir.mkpath(".")) {
        qWarning() << "Failed to create target directory:" << targetDir.absolutePath();
        return false;
    }

    // Iterate over all entries (files and directories) in the source directory
    for (const QFileInfo &entry : sourceDir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot)) {
        QDir targetSubDir(targetDir.filePath(entry.fileName()));

        if (entry.isDir()) {
            // Recursively copy subdirectories
            if (!copyDirectoryRecursively(QDir(entry.filePath()), targetSubDir)) {
                return false;
            }
        } else {
            // Copy files
            if (!QFile::copy(entry.filePath(), targetSubDir.absolutePath())) {
                qWarning() << "Failed to copy file:" << entry.filePath() << "to" << targetSubDir.absolutePath();
                return false;
            }
        }
    }

    return true;
}

QString ProjectGenerator::
getStdInput( const QString& aPrompt, const bool& aAllowEmpty ) {
    /// defining Text Streams for prompts
    QTextStream qOutput( stdout );
    QTextStream qInput( stdin );
    
    qOutput << aPrompt;
    qOutput.flush();
    
    QString value = qInput.readLine();

    if( aAllowEmpty ) {
        return value.trimmed();
    }

    if( value.trimmed().isEmpty() ) {
        throw EmptyInputException();
    }

    return value.trimmed();
}


QString ProjectGenerator::
getStdInput( const QString& aPrompt, const QString& aDefault ) {
    QString value = this->getStdInput( aPrompt, true );

    value = value.isEmpty() ? aDefault : value;

    return value;
}

void ProjectGenerator::
close() {
    qDebug() << "Closing Applicattion...";

    QTimer::singleShot( 0, this, &QCoreApplication::quit );
}